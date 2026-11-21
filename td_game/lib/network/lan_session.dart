import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math';

import 'package:flutter/foundation.dart';

import '../game/model.dart';
import 'network_config.dart';
export 'network_config.dart';

const _magic = NetworkConfig.magic;
const _protocol = NetworkConfig.protocolVersion;
const _balance = NetworkConfig.balanceVersion;
const _discoveryPort = NetworkConfig.discoveryPort;
const _maxFrame = NetworkConfig.maxFrameBytes;
const _maxQueue = NetworkConfig.maxQueueBytes;
const _timeout = NetworkConfig.timeout;

Map<String, dynamic> _envelope(String type) => {
  'magic': _magic,
  'protocol': _protocol,
  'balance': _balance,
  'speeds': SimulationConfig.supportedSpeeds,
  'type': type,
};

bool _compatible(Map<String, dynamic> message) =>
    message['magic'] == _magic &&
    message['protocol'] == _protocol &&
    message['balance'] == _balance &&
    message['speeds'] is List &&
    listEquals(message['speeds'] as List, SimulationConfig.supportedSpeeds);

bool _validLevel(Object? value) =>
    value is int && value >= 0 && value < levels.length;

bool _text(Object? value, {int max = NetworkConfig.maxNameLength}) =>
    value is String && value.trim().isNotEmpty && value.length <= max;

bool _boundedJson(Object? value, [int depth = 0]) {
  if (depth > NetworkConfig.maxJsonDepth) return false;
  if (value == null || value is bool) return true;
  if (value is num) {
    return value.isFinite && value.abs() <= NetworkConfig.maxJsonNumber;
  }
  if (value is String) return value.length <= NetworkConfig.maxJsonStringLength;
  if (value is List) {
    return value.length <= NetworkConfig.maxJsonListLength &&
        value.every((entry) => _boundedJson(entry, depth + 1));
  }
  if (value is Map<String, dynamic>) {
    return value.length <= NetworkConfig.maxJsonFields &&
        value.entries.every(
          (entry) =>
              entry.key.length <= NetworkConfig.maxJsonKeyLength &&
              _boundedJson(entry.value, depth + 1),
        );
  }
  return false;
}

const _stateFields = [
  'mapId',
  'money',
  'lives',
  'wave',
  'popped',
  'phase',
  'speed',
  'autoStart',
  'remaining',
  'revision',
];
const _towerFields = [
  'id',
  'kind',
  'column',
  'row',
  'level',
  'spent',
  'targetMode',
];

Object? _copyJson(Object? value, [int depth = 0]) {
  if (depth > NetworkConfig.maxJsonDepth) {
    throw const FormatException('Snapshot nesting limit exceeded');
  }
  if (value is Map<String, dynamic>) {
    if (value.length > NetworkConfig.maxJsonFields ||
        value.keys.any((key) => key.length > NetworkConfig.maxJsonKeyLength)) {
      throw const FormatException('Snapshot field limit exceeded');
    }
    return value.map(
      (key, entry) => MapEntry(key, _copyJson(entry, depth + 1)),
    );
  }
  if (value is List) {
    if (value.length > SnapshotConfig.maxEntities) {
      throw const FormatException('Snapshot record limit exceeded');
    }
    return value.map((entry) => _copyJson(entry, depth + 1)).toList();
  }
  if (value is String && value.length > NetworkConfig.maxJsonStringLength ||
      value is num && !value.isFinite) {
    throw const FormatException('Invalid snapshot value');
  }
  return value;
}

bool _sameJson(Object? first, Object? second) {
  if (first is Map && second is Map) {
    return first.length == second.length &&
        first.keys.every(
          (key) =>
              second.containsKey(key) && _sameJson(first[key], second[key]),
        );
  }
  if (first is List && second is List) {
    return first.length == second.length &&
        List.generate(
          first.length,
          (index) => _sameJson(first[index], second[index]),
        ).every((equal) => equal);
  }
  return first == second;
}

class _Peer {
  _Peer(this.socket, this.onMessage, this.onLost) {
    socket.setOption(SocketOption.tcpNoDelay, true);
    subscription = socket.listen(
      _read,
      onError: (Object error) => stop('Socket error: $error'),
      onDone: () => stop('Connection closed'),
      cancelOnError: true,
    );
  }

  final Socket socket;
  final void Function(_Peer, Map<String, dynamic>) onMessage;
  final void Function(_Peer, String) onLost;
  late final StreamSubscription<List<int>> subscription;
  final List<int> _frame = [];
  final List<List<int>> _outgoing = [];
  int _queuedBytes = 0;
  bool _writing = false;
  Future<void>? _draining;
  bool _rejecting = false;
  bool closed = false;
  String? label;
  int commandId = 0;
  int commandCount = 0;
  DateTime commandWindow = DateTime.now();
  DateTime lastSeen = DateTime.now();
  int _frameCount = 0;
  DateTime _frameWindow = DateTime.now();

  void _read(List<int> bytes) {
    try {
      for (final byte in bytes) {
        if (closed || _rejecting) return;
        if (byte == 10) {
          final now = DateTime.now();
          if (now.difference(_frameWindow) >= NetworkConfig.rateWindow) {
            _frameWindow = now;
            _frameCount = 0;
          }
          if (++_frameCount > NetworkConfig.maxFramesPerWindow) {
            throw const FormatException('Message rate exceeded');
          }
          if (_frame.isEmpty) throw const FormatException('Empty frame');
          final decoded = jsonDecode(utf8.decode(_frame));
          _frame.clear();
          if (decoded is! Map<String, dynamic>) {
            throw const FormatException('Expected JSON object');
          }
          onMessage(this, decoded);
          lastSeen = DateTime.now();
        } else {
          if (_frame.length >= _maxFrame) {
            throw const FormatException('Frame exceeds configured limit');
          }
          _frame.add(byte);
        }
      }
    } on Object catch (error) {
      stop('Invalid network message: $error');
    }
  }

  bool send(Map<String, dynamic> message) {
    if (closed) return false;
    try {
      final bytes = utf8.encode('${jsonEncode(message)}\n');
      return sendEncoded(bytes);
    } on Object catch (error) {
      stop('Cannot encode network message: $error');
      return false;
    }
  }

  bool sendEncoded(List<int> bytes) {
    if (closed) return false;
    if (bytes.length - 1 > _maxFrame ||
        _queuedBytes + bytes.length > _maxQueue) {
      stop('Network write queue exceeded');
      return false;
    }
    _queuedBytes += bytes.length;
    _outgoing.add(bytes);
    if (!_writing) _draining = _drain();
    return true;
  }

  Future<void> _drain() async {
    _writing = true;
    try {
      while (!closed && _outgoing.isNotEmpty) {
        final bytes = _outgoing.removeAt(0);
        socket.add(bytes);
        await socket.flush().timeout(_timeout);
        _queuedBytes -= bytes.length;
      }
    } on Object catch (error) {
      stop('Network write failed: $error');
    } finally {
      _writing = false;
    }
  }

  Future<void> reject(String reason, {bool hostClosed = false}) async {
    if (closed || _rejecting) return;
    _rejecting = true;
    send({..._envelope(hostClosed ? 'closed' : 'rejected'), 'reason': reason});
    try {
      await _draining?.timeout(NetworkConfig.closeTimeout);
    } on Object catch (_) {}
    stop(reason);
  }

  void stop(String reason) {
    if (closed) return;
    closed = true;
    _outgoing.clear();
    _frame.clear();
    unawaited(subscription.cancel());
    socket.destroy();
    onLost(this, reason);
  }
}

class LanSession extends ChangeNotifier {
  LanSession._({required this.isHost, this.name = '', this.levelIndex = 0});

  final bool isHost;
  bool started = false;
  bool connected = false;
  String? error;
  GameSession? game;
  String name;
  int levelIndex;
  List<String> get players => List.unmodifiable(_players);
  int port = 0;
  List<String> addresses = [];
  final String _id =
      '${DateTime.now().microsecondsSinceEpoch}-${Random.secure().nextInt(1 << 32)}';
  final List<String> _players = [];
  final Set<_Peer> _peers = {};
  ServerSocket? _server;
  StreamSubscription<Socket>? _accept;
  _Peer? _host;
  _Advertiser? _advertiser;
  Timer? _heartbeat;
  Timer? _publisher;
  Completer<void>? _joined;
  Future<void>? _closing;
  bool _isClosing = false;
  bool _disposed = false;
  int _nextPlayer = 1;
  int _nextCommand = 0;
  final Map<int, Map<String, dynamic>> _pendingCommands = {};
  int get pendingCommands => _pendingCommands.length;
  int _snapshotSequence = 0;
  int _lastSnapshot = -1;
  String? _lastCriticalSignature;
  DateTime? _lastCorrectionAt;
  Map<String, dynamic>? _previousSnapshot;
  Map<String, dynamic>? _authoritativeSnapshot;
  DateTime _lastPing = DateTime.now();

  static Future<LanSession> host({
    required String name,
    required int levelIndex,
  }) async {
    if (!_text(name) || !_validLevel(levelIndex)) {
      throw ArgumentError('Invalid lobby name or map index');
    }
    final session = LanSession._(
      isHost: true,
      name: name.trim(),
      levelIndex: levelIndex,
    );
    try {
      session._server = await ServerSocket.bind(InternetAddress.anyIPv4, 0);
      session.port = session._server!.port;
      session.connected = true;
      session._players.add('Host');
      session._accept = session._server!.listen(
        session._acceptSocket,
        onError: (Object error) {
          session.error = 'Host listener failed: $error';
          unawaited(session.close());
        },
      );
      session._runTimers();
      try {
        final interfaces = await NetworkInterface.list(
          type: InternetAddressType.IPv4,
        );
        session.addresses = interfaces
            .expand((interface) => interface.addresses)
            .map((address) => address.address)
            .toSet()
            .toList();
      } on Object {
        session.addresses = [];
      }
      session._advertiser = _Advertiser(session);
      await session._advertiser!.start();
      return session;
    } on Object {
      await session.close();
      rethrow;
    }
  }

  static Future<LanSession> join(String address, int port) async {
    if (!_text(address, max: NetworkConfig.maxAddressLength) ||
        port <= 0 ||
        port > NetworkConfig.maxPort) {
      throw ArgumentError('Invalid host address or port');
    }
    final session = LanSession._(isHost: false);
    session.port = port;
    session._joined = Completer<void>();
    try {
      final socket = await Socket.connect(
        address.trim(),
        port,
        timeout: _timeout,
      );
      session._host = _Peer(socket, session._guestMessage, session._lost);
      session._runTimers();
      session._host!.send(_envelope('hello'));
      await session._joined!.future.timeout(_timeout);
      return session;
    } on Object {
      await session.close();
      rethrow;
    }
  }

  void _notify() {
    if (!_disposed) notifyListeners();
  }

  void _runTimers() {
    _heartbeat = Timer.periodic(NetworkConfig.heartbeatCheckInterval, (_) {
      final now = DateTime.now();
      final peers = isHost ? _peers.toList() : [?_host];
      for (final peer in peers) {
        if (now.difference(peer.lastSeen) >= _timeout) {
          peer.stop('Connection timed out');
        } else if (now.difference(_lastPing) >=
            NetworkConfig.heartbeatInterval) {
          peer.send(_envelope('ping'));
        }
      }
      if (now.difference(_lastPing) >= NetworkConfig.heartbeatInterval) {
        _lastPing = now;
      }
    });
    if (isHost) {
      _publisher = Timer.periodic(
        SnapshotConfig.snapshotInterval,
        (_) => publish(),
      );
    }
  }

  void _acceptSocket(Socket socket) {
    if (!connected || _peers.length >= NetworkConfig.maxPendingPeers) {
      socket.destroy();
      return;
    }
    _peers.add(_Peer(socket, _hostMessage, _lost));
  }

  void _hostMessage(_Peer peer, Map<String, dynamic> message) {
    if (!_compatible(message)) {
      unawaited(peer.reject('Incompatible protocol or balance version'));
      return;
    }
    final type = message['type'];
    if (peer.label == null) {
      if (type != 'hello') {
        unawaited(peer.reject('Handshake required'));
      } else if (started) {
        unawaited(peer.reject('Match already started'));
      } else if (_players.length >= NetworkConfig.maxPlayers) {
        unawaited(peer.reject('Lobby is full'));
      } else {
        peer.label = 'Player ${_nextPlayer++}';
        _players.add(peer.label!);
        peer.send({
          ..._envelope('welcome'),
          'name': name,
          'levelIndex': levelIndex,
          'players': _players,
        });
        _roster();
      }
      return;
    }
    switch (type) {
      case 'ping':
        peer.send(_envelope('pong'));
      case 'pong':
        break;
      case 'leave':
        peer.stop('Player left');
      case 'command':
        final id = message['id'];
        final command = message['command'];
        if (id is! int ||
            id <= 0 ||
            id > NetworkConfig.maxCommandId ||
            command is! Map<String, dynamic> ||
            !_boundedJson(command)) {
          peer.stop('Invalid command');
          return;
        }
        if (id <= peer.commandId) return;
        peer.commandId = id;
        final now = DateTime.now();
        if (now.difference(peer.commandWindow) >= NetworkConfig.rateWindow) {
          peer.commandWindow = now;
          peer.commandCount = 0;
        }
        if (++peer.commandCount > NetworkConfig.maxCommandsPerWindow) {
          peer.stop('Command rate exceeded');
          return;
        }
        final accepted = _applyCommand(command, guest: true);
        peer.send({
          ..._envelope('result'),
          'id': id,
          'accepted': accepted,
          'command': command,
          'reason': accepted ? '' : 'Action unavailable; shared state changed',
        });
      default:
        peer.stop('Unknown message type');
    }
  }

  List<String> _readRoster(Object? value) {
    if (value is! List ||
        value.isEmpty ||
        value.length > NetworkConfig.maxPlayers ||
        value.any((entry) => !_text(entry)) ||
        value.toSet().length != value.length) {
      throw const FormatException('Invalid roster');
    }
    return value.cast<String>();
  }

  void _guestMessage(_Peer peer, Map<String, dynamic> message) {
    if (!_compatible(message)) {
      peer.stop('Incompatible protocol or balance version');
      return;
    }
    switch (message['type']) {
      case 'rejected':
      case 'closed':
        final reason = message['reason'];
        peer.stop(
          _text(reason, max: NetworkConfig.maxReasonLength)
              ? reason as String
              : 'Host closed',
        );
      case 'welcome':
        if (connected ||
            !_text(message['name']) ||
            !_validLevel(message['levelIndex'])) {
          throw const FormatException('Invalid welcome or map index');
        }
        name = message['name'] as String;
        levelIndex = message['levelIndex'] as int;
        _players.addAll(_readRoster(message['players']));
        connected = true;
        _joined!.complete();
        _notify();
      case 'roster':
        if (!connected) throw const FormatException('Handshake required');
        final roster = _readRoster(message['players']);
        _players
          ..clear()
          ..addAll(roster);
        _notify();
      case 'reset':
        if (!connected || !_validLevel(message['levelIndex'])) {
          throw const FormatException('Invalid lobby reset or map index');
        }
        levelIndex = message['levelIndex'] as int;
        started = false;
        game = null;
        _pendingCommands.clear();
        _lastSnapshot = -1;
        _authoritativeSnapshot = null;
        _previousSnapshot = null;
        _lastCorrectionAt = null;
        _lastCriticalSignature = null;
        _snapshotSequence = 0;
        _notify();
      case 'start':
        if (!connected || started || message['levelIndex'] != levelIndex) {
          throw const FormatException('Invalid match start');
        }
        final replica = GameSession(levels[levelIndex]);
        replica.replica = true;
        replica.sendCommand = sendCommand;
        game = replica;
        _applySnapshot(message);
        started = true;
        _notify();
      case 'snapshot':
        if (!started) throw const FormatException('Match not started');
        _applySnapshot(message);
      case 'delta':
        if (!started) throw const FormatException('Match not started');
        _applyDelta(message);
      case 'result':
        _applyResult(message);
      case 'ping':
        peer.send(_envelope('pong'));
      case 'pong':
        break;
      default:
        peer.stop('Unknown message type');
    }
  }

  void _applySnapshot(Map<String, dynamic> message) {
    final sequence = message['sequence'];
    final snapshot = message['snapshot'];
    if (sequence is! int ||
        sequence != (_lastSnapshot == -1 ? 1 : _lastSnapshot + 1) ||
        sequence < 1 ||
        sequence > NetworkConfig.maxCommandId ||
        snapshot is! Map<String, dynamic>) {
      throw const FormatException('Invalid snapshot');
    }
    final candidate = _copyJson(snapshot) as Map<String, dynamic>;
    _validateSnapshot(candidate);
    _applyAuthoritative(message, candidate, refreshEnemies: true);
  }

  void _validateSnapshot(Map<String, dynamic> snapshot) {
    for (final key in ['towers', 'enemies', 'shots', 'effects']) {
      final records = snapshot[key];
      if (records is! List ||
          records.length > SnapshotConfig.maxEntities ||
          records.any((record) => record is! Map<String, dynamic>)) {
        throw const FormatException('Invalid snapshot records');
      }
    }
    final validator = GameSession(levels[levelIndex])..replica = true;
    validator.applySnapshot(snapshot);
    final validated = validator.toSnapshot(includePresentation: false);
    if (validated.entries.any(
      (entry) => !_sameJson(entry.value, snapshot[entry.key]),
    )) {
      throw const FormatException('Invalid authoritative snapshot');
    }
  }

  void _applyDelta(Map<String, dynamic> message) {
    final baseline = _authoritativeSnapshot;
    final sequence = message['sequence'];
    final state = message['state'];
    if (baseline == null ||
        message['baseSequence'] is! int ||
        message['baseSequence'] != _lastSnapshot ||
        sequence is! int ||
        sequence != _lastSnapshot + 1 ||
        sequence > NetworkConfig.maxCommandId ||
        state is! Map<String, dynamic> ||
        state.keys.any((key) => !_stateFields.contains(key))) {
      throw const FormatException('Invalid delta sequence or state');
    }
    final candidate = _copyJson(baseline) as Map<String, dynamic>;
    candidate.addAll(state);
    for (final key in ['towers', 'enemies']) {
      final additions = message[key];
      final removals =
          message[key == 'towers' ? 'removedTowerIds' : 'removedEnemyIds'];
      if (additions is! List ||
          removals is! List ||
          additions.length > SnapshotConfig.maxEntities ||
          removals.length > SnapshotConfig.maxEntities) {
        throw const FormatException('Invalid delta records');
      }
      final records = {
        for (final record in candidate[key] as List)
          record['id'] as int: record as Map<String, dynamic>,
      };
      final removedIds = <int>{};
      for (final id in removals) {
        if (id is! int || !removedIds.add(id) || !records.containsKey(id)) {
          throw const FormatException('Invalid delta removal');
        }
        records.remove(id);
      }
      final addedIds = <int>{};
      for (final record in additions) {
        if (record is! Map<String, dynamic>) {
          throw const FormatException('Invalid delta record');
        }
        final id = record['id'];
        if (id is! int ||
            id < 1 ||
            id > SnapshotConfig.maxInteger ||
            !addedIds.add(id) ||
            removedIds.contains(id)) {
          throw const FormatException('Invalid delta ID');
        }
        if (key == 'towers') {
          if (record.length != _towerFields.length ||
              !_towerFields.every(record.containsKey)) {
            throw const FormatException('Invalid tower delta');
          }
          records[id] = {
            ...?records[id],
            if (!records.containsKey(id)) 'angle': 0.0,
            if (!records.containsKey(id)) 'targetId': null,
            ...record,
          };
        } else {
          if (records.containsKey(id)) {
            throw const FormatException('Delta enemy already exists');
          }
          records[id] = _copyJson(record) as Map<String, dynamic>;
        }
      }
      candidate[key] = records.values.toList();
    }
    _validateSnapshot(candidate);
    _applyAuthoritative(message, candidate, refreshEnemies: false);
  }

  void _applyAuthoritative(
    Map<String, dynamic> message,
    Map<String, dynamic> snapshot, {
    required bool refreshEnemies,
  }) {
    final session = game!;
    final previousPopped = session.popped;
    final previousPhase = session.phase;
    final previousSpent = {
      for (final tower in session.towers) tower.id: tower.spent,
    };
    session.applySnapshot(
      snapshot,
      preservePresentation: true,
      refreshEnemies: refreshEnemies,
    );
    _authoritativeSnapshot = snapshot;
    _lastSnapshot = message['sequence'] as int;
    if (started) {
      if (session.popped > previousPopped) session.onSound?.call('pop');
      if (session.towers.any(
        (tower) => tower.spent > (previousSpent[tower.id] ?? 0),
      )) {
        session.onSound?.call('buy');
      }
      if (session.phase != previousPhase) {
        if (session.phase == SessionPhase.won) session.onSound?.call('win');
        if (session.phase == SessionPhase.lost) session.onSound?.call('lose');
      }
    }
    _notify();
  }

  void _applyResult(Map<String, dynamic> message) {
    final id = message['id'];
    final accepted = message['accepted'];
    final command = message['command'];
    final reason = message['reason'];
    if (id is! int ||
        id <= 0 ||
        id > NetworkConfig.maxCommandId ||
        accepted is! bool ||
        command is! Map<String, dynamic> ||
        !_boundedJson(command) ||
        reason is! String ||
        reason.length > NetworkConfig.maxJsonStringLength) {
      throw const FormatException('Invalid command result');
    }
    final pending = _pendingCommands.remove(id);
    final session = game;
    if (pending == null || session == null || !started) return;
    if (!accepted) {
      session.message =
          'Action rejected: ${reason.trim().isEmpty ? 'Action unavailable; shared state changed' : reason}';
      session.revision++;
    } else if (pending['action'] == 'place' &&
        session.buying?.kind.index == pending['kind']) {
      final tower = session.towers
          .where(
            (tower) =>
                tower.cell.column == pending['column'] &&
                tower.cell.row == pending['row'] &&
                tower.spec.kind.index == pending['kind'],
          )
          .firstOrNull;
      if (tower != null) {
        session.buying = null;
        session.selected = tower;
        session.message = '';
        session.revision++;
      }
    }
    _notify();
  }

  void _lost(_Peer peer, String reason) {
    if (isHost) {
      _peers.remove(peer);
      if (peer.label != null) {
        _players.remove(peer.label);
        if (connected) _roster();
      }
    } else {
      connected = false;
      _pendingCommands.clear();
      if (!_isClosing) error = 'Host connection lost: $reason';
      _heartbeat?.cancel();
      if (_joined != null && !_joined!.isCompleted) {
        _joined!.completeError(StateError(reason));
      }
      _notify();
    }
  }

  void _broadcast(Map<String, dynamic> message) {
    final bytes = utf8.encode('${jsonEncode(message)}\n');
    for (final peer in _peers.toList()) {
      if (peer.label != null) peer.sendEncoded(bytes);
    }
  }

  void _roster() {
    _broadcast({
      ..._envelope('roster'),
      'players': _players,
      'started': started,
    });
    _advertiser?.announce();
    _notify();
  }

  void start() {
    if (!isHost ||
        !connected ||
        started ||
        _players.length < NetworkConfig.minPlayers) {
      return;
    }
    game = GameSession(levels[levelIndex]);
    started = true;
    _advertiser?.close();
    _snapshotSequence = 0;
    _lastSnapshot = -1;
    _authoritativeSnapshot = null;
    _lastCriticalSignature = _criticalSignature(game!);
    _lastCorrectionAt = DateTime.now();
    _previousSnapshot = game!.toSnapshot(includePresentation: false);
    _broadcast({
      ..._envelope('start'),
      'levelIndex': levelIndex,
      'sequence': ++_snapshotSequence,
      'snapshot': _previousSnapshot,
    });
    _roster();
  }

  void returnToLobby({int? levelIndex}) {
    if (!isHost || !connected || !started) return;
    if (levelIndex != null && !_validLevel(levelIndex)) {
      throw ArgumentError('Invalid map index');
    }
    this.levelIndex = levelIndex ?? this.levelIndex;
    started = false;
    game = null;
    _lastCriticalSignature = null;
    _lastCorrectionAt = null;
    _previousSnapshot = null;
    _authoritativeSnapshot = null;
    _snapshotSequence = 0;
    _lastSnapshot = -1;
    _broadcast({..._envelope('reset'), 'levelIndex': this.levelIndex});
    _advertiser?.close();
    _advertiser = _Advertiser(this);
    unawaited(_advertiser!.start());
    _roster();
  }

  void sendCommand(Map<String, dynamic> command) {
    if (!connected || !started || !_boundedJson(command)) return;
    if (isHost) {
      _applyCommand(command, guest: false);
    } else {
      final id = ++_nextCommand;
      _pendingCommands[id] = Map<String, dynamic>.from(command);
      final sent = _host?.send({
        ..._envelope('command'),
        'id': id,
        'command': command,
      });
      if (sent != true) _pendingCommands.remove(id);
      _notify();
    }
  }

  bool _applyCommand(Map<String, dynamic> command, {required bool guest}) {
    if (!started || game == null) return false;
    if (guest && command['action'] == 'autoStart') return false;
    try {
      final accepted = game!.applyCommand(command);
      publish();
      _notify();
      return accepted;
    } on Object catch (_) {
      return false;
    }
  }

  String _criticalSignature(GameSession session) => jsonEncode({
    'mapId': session.level.id,
    'phase': session.phase.index,
    'speed': session.speed,
    'autoStart': session.autoStart,
    'money': session.money,
    'lives': session.lives,
    'wave': session.wave,
    'popped': session.popped,
    'remaining': session.remaining,
    'towers': [
      for (final tower in session.towers)
        [
          tower.id,
          tower.spec.kind.index,
          tower.cell.column,
          tower.cell.row,
          tower.level,
          tower.spent,
          tower.targetMode.index,
        ],
    ],
    'enemies': [
      for (final enemy in session.enemies) [enemy.id, enemy.tier],
    ],
  });

  void publish({bool force = false}) {
    if (!isHost || !connected || !started || game == null) return;
    final session = game!;
    final signature = _criticalSignature(session);
    final now = DateTime.now();
    final correction =
        force ||
        _previousSnapshot == null ||
        _lastCorrectionAt == null ||
        now.difference(_lastCorrectionAt!) >= SnapshotConfig.correctionInterval;
    if (!correction && signature == _lastCriticalSignature) {
      return;
    }
    final snapshot = session.toSnapshot(includePresentation: false);
    final baseSequence = _snapshotSequence;
    if (correction) {
      _broadcast({
        ..._envelope('snapshot'),
        'sequence': ++_snapshotSequence,
        'snapshot': snapshot,
      });
      _lastCorrectionAt = now;
    } else {
      final previous = _previousSnapshot!;
      final oldTowers = {
        for (final tower in previous['towers'] as List) tower['id']: tower,
      };
      final oldEnemies = {
        for (final enemy in previous['enemies'] as List) enemy['id']: enemy,
      };
      final towers = snapshot['towers'] as List;
      final enemies = snapshot['enemies'] as List;
      final towerIds = towers.map((tower) => tower['id']).toSet();
      final enemyIds = enemies.map((enemy) => enemy['id']).toSet();
      _broadcast({
        ..._envelope('delta'),
        'sequence': ++_snapshotSequence,
        'baseSequence': baseSequence,
        'state': {
          for (final key in _stateFields)
            if (snapshot[key] != previous[key]) key: snapshot[key],
        },
        'towers': [
          for (final tower in towers)
            if (oldTowers[tower['id']] == null ||
                _towerFields.any(
                  (key) => tower[key] != oldTowers[tower['id']][key],
                ))
              {for (final key in _towerFields) key: tower[key]},
        ],
        'removedTowerIds': oldTowers.keys
            .where((id) => !towerIds.contains(id))
            .toList(),
        'enemies': [
          for (final enemy in enemies)
            if (!oldEnemies.containsKey(enemy['id'])) enemy,
        ],
        'removedEnemyIds': oldEnemies.keys
            .where((id) => !enemyIds.contains(id))
            .toList(),
      });
    }
    _previousSnapshot = snapshot;
    _lastCriticalSignature = signature;
  }

  Future<void> close() => _closing ??= _close();

  Future<void> _close() async {
    _isClosing = true;
    connected = false;
    _pendingCommands.clear();
    _lastCriticalSignature = null;
    _lastCorrectionAt = null;
    _previousSnapshot = null;
    _authoritativeSnapshot = null;
    _snapshotSequence = 0;
    _lastSnapshot = -1;
    _heartbeat?.cancel();
    _publisher?.cancel();
    _advertiser?.close();
    final disconnects = _peers
        .toList()
        .map((peer) => peer.reject('Host closed the session', hostClosed: true))
        .toList();
    _host?.stop('Player left');
    await _accept?.cancel();
    await _server?.close();
    await Future.wait(disconnects);
    _notify();
  }

  @override
  void dispose() {
    _disposed = true;
    unawaited(close());
    super.dispose();
  }
}

class LanListing {
  const LanListing({
    required this.id,
    required this.name,
    required this.levelIndex,
    required this.players,
    required this.capacity,
    required this.address,
    required this.port,
  });

  final String id;
  final String name;
  final int levelIndex;
  final int players;
  final int capacity;
  final String address;
  final int port;
}

Future<RawDatagramSocket> _bindUdp(int port) async {
  try {
    return await RawDatagramSocket.bind(
      InternetAddress.anyIPv4,
      port,
      reuseAddress: true,
      reusePort: !Platform.isWindows,
    );
  } on SocketException {
    return RawDatagramSocket.bind(
      InternetAddress.anyIPv4,
      port,
      reuseAddress: true,
      reusePort: false,
    );
  }
}

Map<String, dynamic>? _datagram(Datagram datagram) {
  if (datagram.data.length > NetworkConfig.maxDatagramBytes) return null;
  try {
    final value = jsonDecode(utf8.decode(datagram.data));
    return value is Map<String, dynamic> && _compatible(value) ? value : null;
  } on Object {
    return null;
  }
}

class _Advertiser {
  _Advertiser(this.session);

  final LanSession session;
  RawDatagramSocket? _socket;
  StreamSubscription<RawSocketEvent>? _subscription;
  Timer? _timer;
  final List<RawDatagramSocket> _interfaces = [];

  Future<void> start() async {
    try {
      _socket = await _bindUdp(_discoveryPort);
      if (!session.connected || session.started) {
        close();
        return;
      }
      _socket!.broadcastEnabled = true;
      _subscription = _socket!.listen((event) {
        if (event != RawSocketEvent.read) return;
        Datagram? datagram;
        while ((datagram = _socket?.receive()) != null) {
          final query = _datagram(datagram!);
          if (query?['type'] == 'query') {
            announce(datagram.address, datagram.port);
          }
        }
      }, onError: (Object error) => _fail(error));
      for (final address in session.addresses) {
        try {
          final socket = await RawDatagramSocket.bind(address, 0);
          if (!session.connected || session.started) {
            socket.close();
            close();
            return;
          }
          socket.broadcastEnabled = true;
          _interfaces.add(socket);
        } on Object catch (_) {}
      }
      _timer = Timer.periodic(
        NetworkConfig.discoveryInterval,
        (_) => announce(),
      );
      announce();
    } on Object catch (error) {
      _fail(error);
    }
  }

  void _fail(Object error) {
    session.error = 'LAN discovery unavailable; direct IP still works: $error';
    close();
    session._notify();
  }

  void announce([InternetAddress? address, int port = _discoveryPort]) {
    if (_socket == null || !session.connected || session.started) return;
    try {
      final data = utf8.encode(
        jsonEncode({
          ..._envelope('listing'),
          'id': session._id,
          'name': session.name,
          'levelIndex': session.levelIndex,
          'players': session.players.length,
          'capacity': NetworkConfig.maxPlayers,
          'port': session.port,
        }),
      );
      _socket!.send(
        data,
        address ?? InternetAddress(NetworkConfig.broadcastAddress),
        port,
      );
      if (address == null) {
        for (final socket in _interfaces) {
          try {
            socket.send(
              data,
              InternetAddress(NetworkConfig.broadcastAddress),
              port,
            );
          } on Object catch (_) {}
        }
      }
    } on Object catch (error) {
      _fail(error);
    }
  }

  void close() {
    _timer?.cancel();
    unawaited(_subscription?.cancel());
    _socket?.close();
    _socket = null;
    for (final socket in _interfaces) {
      socket.close();
    }
    _interfaces.clear();
  }
}

class LanDiscovery extends ChangeNotifier {
  LanDiscovery({
    DateTime Function()? clock,
    List<InternetAddress>? destinations,
  }) : _clock = clock ?? DateTime.now,
       _useInterfaces = destinations == null,
       _destinations =
           destinations ??
           [
             InternetAddress(NetworkConfig.broadcastAddress),
             InternetAddress.loopbackIPv4,
           ];

  final DateTime Function() _clock;
  final bool _useInterfaces;
  final List<InternetAddress> _destinations;
  final Map<String, LanListing> _games = {};
  final Map<String, DateTime> _seen = {};
  List<LanListing> get games => List.unmodifiable(_games.values);
  String? error;
  RawDatagramSocket? _socket;
  StreamSubscription<RawSocketEvent>? _subscription;
  Timer? _timer;
  Future<void>? _starting;
  bool _closed = false;
  bool _disposed = false;
  final List<RawDatagramSocket> _interfaces = [];
  final List<StreamSubscription<RawSocketEvent>> _interfaceSubscriptions = [];

  Future<void> start() {
    if (_closed) return Future.error(StateError('Discovery is closed'));
    return _starting ??= _start();
  }

  Future<void> _start() async {
    try {
      _socket = await _bindUdp(0);
      if (_closed) {
        _socket!.close();
        _socket = null;
        return;
      }
      _socket!.broadcastEnabled = true;
      _subscription = _listen(_socket!);
      if (_useInterfaces) {
        try {
          final interfaces = await NetworkInterface.list(
            type: InternetAddressType.IPv4,
          );
          for (final address in interfaces.expand((entry) => entry.addresses)) {
            try {
              final socket = await RawDatagramSocket.bind(address, 0);
              if (_closed) {
                socket.close();
                return;
              }
              socket.broadcastEnabled = true;
              _interfaces.add(socket);
              _interfaceSubscriptions.add(_listen(socket));
            } on Object catch (_) {}
          }
        } on Object catch (_) {}
      }
      _timer = Timer.periodic(
        NetworkConfig.discoveryInterval,
        (_) => refresh(),
      );
      refresh();
    } on Object catch (failure) {
      error = 'LAN discovery unavailable: $failure';
      _notify();
    }
  }

  StreamSubscription<RawSocketEvent> _listen(RawDatagramSocket socket) =>
      socket.listen(
        (event) {
          if (event != RawSocketEvent.read || _closed) return;
          Datagram? datagram;
          while ((datagram = socket.receive()) != null) {
            final message = _datagram(datagram!);
            if (message != null) _listing(message, datagram.address.address);
          }
        },
        onError: (Object failure) {
          error = 'LAN discovery unavailable: $failure';
          _notify();
        },
      );

  void _listing(Map<String, dynamic> message, String address) {
    final id = message['id'];
    final name = message['name'];
    final level = message['levelIndex'];
    final players = message['players'];
    final port = message['port'];
    if (message['type'] != 'listing' ||
        !_text(id, max: NetworkConfig.maxIdentifierLength) ||
        !_text(name) ||
        !_validLevel(level) ||
        players is! int ||
        players < 1 ||
        players > NetworkConfig.maxPlayers ||
        message['capacity'] != NetworkConfig.maxPlayers ||
        port is! int ||
        port < 1 ||
        port > NetworkConfig.maxPort) {
      return;
    }
    if (_games.length >= NetworkConfig.maxListings && !_games.containsKey(id)) {
      return;
    }
    _games[id as String] = LanListing(
      id: id,
      name: name as String,
      levelIndex: level as int,
      players: players,
      capacity: NetworkConfig.maxPlayers,
      address: address,
      port: port,
    );
    _seen[id] = _clock();
    _notify();
  }

  void refresh() {
    if (_closed) return;
    final now = _clock();
    final stale = _seen.keys
        .where(
          (id) => now.difference(_seen[id]!) >= NetworkConfig.listingLifetime,
        )
        .toList();
    for (final id in stale) {
      _seen.remove(id);
      _games.remove(id);
    }
    if (stale.isNotEmpty) _notify();
    if (_socket == null) return;
    final query = utf8.encode(jsonEncode(_envelope('query')));
    for (final socket in [_socket!, ..._interfaces]) {
      for (final address in _destinations) {
        try {
          socket.send(query, address, _discoveryPort);
        } on Object catch (failure) {
          error = 'LAN discovery unavailable: $failure';
          _notify();
        }
      }
    }
  }

  void _notify() {
    if (!_disposed && !_closed) notifyListeners();
  }

  Future<void> close() async {
    _closed = true;
    _timer?.cancel();
    _socket?.close();
    _socket = null;
    await _subscription?.cancel();
    for (final socket in _interfaces) {
      socket.close();
    }
    await Future.wait(_interfaceSubscriptions.map((entry) => entry.cancel()));
    _interfaces.clear();
    _interfaceSubscriptions.clear();
    _games.clear();
    _seen.clear();
  }

  @override
  void dispose() {
    _disposed = true;
    unawaited(close());
    super.dispose();
  }
}
