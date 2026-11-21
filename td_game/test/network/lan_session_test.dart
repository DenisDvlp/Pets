import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:ui';

import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/game/model.dart';
import 'package:td_game/network/lan_session.dart';

Future<void> until(bool Function() condition, [LanSession? session]) async {
  final deadline = DateTime.now().add(const Duration(seconds: 4));
  while (!condition()) {
    if (DateTime.now().isAfter(deadline)) {
      fail('Condition timed out: ${session?.error}');
    }
    await Future<void>.delayed(const Duration(milliseconds: 10));
  }
}

Map<String, dynamic> frame(String type) => {
  'magic': NetworkConfig.magic,
  'protocol': NetworkConfig.protocolVersion,
  'balance': NetworkConfig.balanceVersion,
  'speeds': SimulationConfig.supportedSpeeds,
  'type': type,
};

void main() {
  final sessions = <LanSession>[];

  Future<LanSession> host() async {
    final session = await LanSession.host(name: 'Loopback', levelIndex: 0);
    sessions.add(session);
    return session;
  }

  Future<LanSession> join(LanSession host) async {
    final guest = await LanSession.join('127.0.0.1', host.port);
    sessions.add(guest);
    return guest;
  }

  tearDown(() async {
    for (final session in sessions.reversed) {
      await session.close();
      session.dispose();
    }
    sessions.clear();
  });

  test('validates direct addresses and map index before binding', () async {
    await expectLater(
      LanSession.host(name: 'Bad', levelIndex: -1),
      throwsArgumentError,
    );
    await expectLater(LanSession.join('', 1), throwsArgumentError);
    await expectLater(LanSession.join('127.0.0.1', 65536), throwsArgumentError);
  });

  test('rejects an invalid welcome map and closes failed joins', () async {
    final server = await ServerSocket.bind(InternetAddress.loopbackIPv4, 0);
    final sockets = <Socket>[];
    final listener = server.listen((socket) {
      sockets.add(socket);
      socket.listen((_) {
        socket.add(
          utf8.encode(
            '${jsonEncode({
              ...frame('welcome'),
              'name': 'Invalid map',
              'levelIndex': levels.length,
              'players': ['Host', 'Player 1'],
            })}\n',
          ),
        );
      });
    });
    addTearDown(() async {
      for (final socket in sockets) {
        socket.destroy();
      }
      await listener.cancel();
      await server.close();
    });
    await expectLater(
      LanSession.join('127.0.0.1', server.port),
      throwsA(isA<StateError>()),
    );
  });

  test(
    'closed sessions release TCP binding and allow replacement guests',
    () async {
      final owner = await host();
      final guest = await join(owner);
      await guest.close();
      await until(() => owner.players.length == 1, owner);
      final replacement = await join(owner);
      expect(replacement.players.length, 2);
      final port = owner.port;
      await owner.close();
      await owner.close();
      await until(() => !replacement.connected, replacement);
      final rebound = await ServerSocket.bind(InternetAddress.anyIPv4, port);
      await rebound.close();
    },
  );

  test(
    'four-player roster, host-only start, full and late rejection',
    () async {
      final owner = await host();
      owner.start();
      expect(owner.started, isFalse);
      final first = await join(owner);
      final second = await join(owner);
      final third = await join(owner);
      await until(() => first.players.length == 4, first);
      expect(first.players, owner.players);
      expect(second.players, owner.players);
      expect(third.players, owner.players);
      first.start();
      expect(first.started, isFalse);
      await expectLater(
        LanSession.join('127.0.0.1', owner.port),
        throwsA(isA<StateError>()),
      );
      owner.start();
      await until(() => third.started, third);
      expect(first.game!.replica, isTrue);
      expect(owner.game!.replica, isFalse);
      expect(first.game!.toSnapshot(), owner.game!.toSnapshot());
      await third.close();
      await until(() => owner.players.length == 3, owner);
      expect(owner.started, isTrue);
      await expectLater(
        LanSession.join('127.0.0.1', owner.port),
        throwsA(isA<StateError>()),
      );
    },
  );

  test('next map immediately starts a fresh match on host and guest', () async {
    final owner = await host();
    final guest = await join(owner);
    owner.start();
    await until(() => guest.started, guest);
    final previous = guest.game;
    owner.game!.phase = SessionPhase.won;
    owner.publish();
    await until(() => guest.game!.phase == SessionPhase.won, guest);
    owner.returnToLobby(levelIndex: 1);
    owner.start();
    await until(() => guest.started && guest.levelIndex == 1, guest);
    expect(guest.game, isNot(same(previous)));
    expect(guest.game!.level, levels[1]);
    expect(guest.game!.phase, SessionPhase.ready);
    expect(guest.game!.wave, 0);
    expect(guest.game!.toSnapshot(), owner.game!.toSnapshot());
  });

  test('co-op shares every configured speed in both directions', () async {
    final owner = await host();
    final guest = await join(owner);
    owner.start();
    await until(() => guest.started, guest);
    for (final speed in SimulationConfig.supportedSpeeds) {
      owner.game!.setSpeed(speed);
      owner.publish();
      await until(() => guest.game!.speed == speed, guest);
    }
    for (final speed in SimulationConfig.supportedSpeeds.reversed) {
      guest.game!.setSpeed(speed);
      await until(
        () => owner.game!.speed == speed && guest.pendingCommands == 0,
        guest,
      );
      expect(guest.game!.speed, owner.game!.speed);
    }
  });

  test('host returns guests to the lobby and starts a fresh match', () async {
    final owner = await host();
    final guest = await join(owner);
    owner.start();
    await until(() => guest.started, guest);
    guest.game!.startWave();
    await until(() => guest.game!.wave == 1, guest);
    guest.returnToLobby(levelIndex: 1);
    expect(guest.started, isTrue);
    expect(owner.started, isTrue);

    var notifiedReset = false;
    guest.addListener(() {
      if (!guest.started && guest.game == null) notifiedReset = true;
    });
    owner.returnToLobby(levelIndex: 1);
    expect(owner.started, isFalse);
    expect(owner.game, isNull);
    await until(() => notifiedReset, guest);
    expect(guest.connected, isTrue);
    expect(guest.levelIndex, 1);
    expect(guest.players, owner.players);

    final discovery = LanDiscovery(
      destinations: [InternetAddress.loopbackIPv4],
    );
    addTearDown(discovery.dispose);
    await discovery.start();
    await until(() => discovery.games.any((entry) => entry.port == owner.port));
    expect(discovery.games.single.levelIndex, 1);
    final newcomer = await join(owner);
    owner.start();
    await until(() => guest.started && newcomer.started, guest);
    expect(guest.game!.toSnapshot(), owner.game!.toSnapshot());
    expect(guest.game!.wave, 0);
    guest.game!.startWave();
    await until(() => guest.game!.wave == 1, guest);
  });

  test(
    'guest commands and timer snapshots work independently of revision',
    () async {
      final owner = await host();
      final guest = await join(owner);
      owner.start();
      await until(() => guest.started, guest);
      guest.sendCommand({'action': 'wave'});
      await until(() => owner.game!.wave == 1, owner);
      await until(() => guest.game!.wave == 1, guest);
      guest.sendCommand({'action': 'pause'});
      await until(() => guest.game!.phase == SessionPhase.paused, guest);
      final revision = owner.game!.revision;
      owner.game!.money += 7;
      await until(() => guest.game!.money == owner.game!.money, guest);
      expect(owner.game!.revision, revision);
      final snapshot = guest.game!.toSnapshot();
      guest.game!.update(1);
      expect(guest.game!.toSnapshot(), snapshot);
      await owner.close();
      await until(() => !guest.connected, guest);
      expect(guest.error, contains('Host'));
    },
  );

  test(
    'concurrent placements report results and forward snapshot audio',
    () async {
      final owner = await host();
      final first = await join(owner);
      final second = await join(owner);
      final sounds = <LanSession, List<String>>{first: [], second: []};
      for (final guest in sounds.keys) {
        guest.addListener(() {
          guest.game?.onSound = sounds[guest]!.add;
        });
      }
      owner.start();
      await until(() => first.started && second.started);
      expect(sounds.values.every((events) => events.isEmpty), isTrue);
      final cell = [
        for (var row = 0; row < owner.game!.level.rows; row++)
          for (var column = 0; column < owner.game!.level.columns; column++)
            (column: column, row: row),
      ].firstWhere(owner.game!.canPlace);
      final spec = towerSpecs.first;
      for (final guest in sounds.keys) {
        guest.game!.choose(spec);
        expect(guest.game!.place(cell), isTrue);
        expect(guest.pendingCommands, 1);
      }
      await until(
        () => first.pendingCommands == 0 && second.pendingCommands == 0,
      );
      expect(owner.game!.towers, hasLength(1));
      expect(owner.game!.money, 650 - spec.cost);
      final winner = first.game!.buying == null ? first : second;
      final loser = winner == first ? second : first;
      expect(winner.game!.selected?.cell, cell);
      expect(winner.game!.selected, same(winner.game!.towers.single));
      expect(loser.game!.buying, spec);
      expect(loser.game!.selected, isNull);
      expect(loser.game!.message, startsWith('Action rejected: '));
      expect(loser.game!.message, contains('shared state changed'));
      expect(first.connected && second.connected, isTrue);
      expect(first.error, isNull);
      expect(second.error, isNull);
      for (final events in sounds.values) {
        expect(events, ['buy']);
      }

      owner.game!.popped += 3;
      owner.game!.towers.single.spent++;
      owner.game!.phase = SessionPhase.won;
      owner.publish();
      await until(() => sounds.values.every((events) => events.length == 4));
      for (final events in sounds.values) {
        expect(events, ['buy', 'pop', 'buy', 'win']);
      }
      final notifications = Completer<void>();
      winner.addListener(() {
        if (!notifications.isCompleted) notifications.complete();
      });
      owner.publish(force: true);
      await notifications.future.timeout(const Duration(seconds: 4));
      expect(sounds.values.every((events) => events.length == 4), isTrue);
      owner.returnToLobby();
      await until(() => !first.started && !second.started);
      expect(first.pendingCommands, 0);
      expect(second.pendingCommands, 0);
    },
  );

  test(
    'sparse deltas publish critical changes and timed corrections',
    () async {
      final owner = await host();
      final guest = await join(owner);
      final socket = await Socket.connect('127.0.0.1', owner.port);
      addTearDown(socket.destroy);
      final messages = <Map<String, dynamic>>[];
      final subscription = socket
          .cast<List<int>>()
          .transform(utf8.decoder)
          .transform(const LineSplitter())
          .listen((line) {
            messages.add(jsonDecode(line) as Map<String, dynamic>);
          });
      addTearDown(subscription.cancel);
      socket.add(utf8.encode('${jsonEncode(frame('hello'))}\n'));
      await socket.flush();
      await until(
        () => messages.any((message) => message['type'] == 'welcome'),
      );
      owner.start();
      await until(
        () =>
            guest.started &&
            messages.any((message) => message['type'] == 'start'),
      );
      final initial = messages.singleWhere(
        (message) => message['type'] == 'start',
      );
      expect(initial['snapshot']['shots'], isEmpty);
      expect(initial['snapshot']['effects'], isEmpty);
      final enemy = Balloon(100, 1);
      owner.game!.enemies.add(enemy);
      owner.game!.shots.add(
        Shot(Offset.zero, const Offset(1, 0), 1, towerSpecs.first.kind, 1),
      );
      owner.game!.effects.add(GameEffect(Offset.zero, const Color(0xFFFFFFFF)));
      owner.publish();
      await until(
        () =>
            guest.game!.enemies.length == 1 &&
            messages.any((message) => message['type'] == 'delta'),
      );
      final delta = messages.lastWhere((message) => message['type'] == 'delta');
      expect(delta.containsKey('snapshot'), isFalse);
      expect(delta.containsKey('shots'), isFalse);
      expect(delta.containsKey('effects'), isFalse);
      expect(delta['enemies'], hasLength(1));
      expect(delta['towers'], isEmpty);
      expect(delta['baseSequence'], initial['sequence']);
      expect(delta['sequence'], (initial['sequence'] as int) + 1);
      var notifications = 0;
      guest.addListener(() => notifications++);
      final packets = messages
          .where((message) => message['type'] == 'snapshot')
          .length;
      enemy.distance = 1;
      enemy.health -= .5;
      enemy.slowTime = 1;
      owner.game!.revision++;
      for (var poll = 0; poll < 5; poll++) {
        owner.publish();
      }
      await Future<void>.delayed(const Duration(milliseconds: 250));
      expect(notifications, 0);
      expect(
        messages.where((message) => message['type'] == 'snapshot'),
        hasLength(packets),
      );
      expect(guest.game!.enemies.single.distance, 0);
      final changes = Timer.periodic(const Duration(milliseconds: 100), (_) {
        owner.game!.money++;
        owner.publish();
      });
      try {
        await until(() => guest.game!.enemies.single.distance == 1, guest);
      } finally {
        changes.cancel();
      }
      expect(guest.game!.enemies.single.health, enemy.health);
      await until(
        () => messages.any((message) => message['type'] == 'snapshot'),
      );
      final correction = messages.lastWhere(
        (message) => message['type'] == 'snapshot',
      );
      expect(correction['snapshot']['shots'], isEmpty);
      expect(correction['snapshot']['effects'], isEmpty);
      owner.game!.money++;
      owner.publish();
      await until(
        () =>
            guest.game!.money == owner.game!.money &&
            messages.any(
              (message) =>
                  message['type'] == 'delta' &&
                  message['state']['money'] == owner.game!.money,
            ),
        guest,
      );
      final stats = messages.lastWhere((message) => message['type'] == 'delta');
      expect(stats['enemies'], isEmpty);
      expect(stats['towers'], isEmpty);
      owner.game!.enemies
        ..clear()
        ..add(Balloon(101, 2));
      owner.publish();
      await until(
        () =>
            guest.game!.enemies.single.id == 101 &&
            messages.any(
              (message) =>
                  message['type'] == 'delta' &&
                  (message['removedEnemyIds'] as List).contains(100),
            ),
        guest,
      );
      expect(guest.game!.enemies.single.tier, 2);
      final replacement = messages.lastWhere(
        (message) => message['type'] == 'delta',
      );
      expect(replacement['removedEnemyIds'], [100]);
      expect(replacement['enemies'], hasLength(1));
      expect(owner.players, hasLength(3));
      expect(guest.players, owner.players);
    },
  );

  test('tower delta preserves predicted enemy health and status', () async {
    final owner = await host();
    final guest = await join(owner);
    owner.start();
    await until(() => guest.started, guest);
    owner.game!.startWave();
    owner.game!.enemies.add(Balloon(100, 2));
    owner.publish();
    await until(() => guest.game!.enemies.length == 1, guest);
    final predicted = guest.game!.enemies.single;
    predicted
      ..distance = 1
      ..health -= .5
      ..sinceDamage = .7
      ..slow = .5
      ..slowTime = 1
      ..poison = .2
      ..poisonTime = 2;
    final health = predicted.health;
    final cell = [
      for (var row = 0; row < owner.game!.level.rows; row++)
        for (var column = 0; column < owner.game!.level.columns; column++)
          (column: column, row: row),
    ].firstWhere(owner.game!.canPlace);
    owner.game!.choose(towerSpecs.first);
    owner.game!.place(cell);
    owner.publish();
    await until(() => guest.game!.towers.length == 1, guest);
    expect(guest.game!.money, owner.game!.money);
    expect(guest.game!.enemies.single, same(predicted));
    expect(predicted.distance, 1);
    expect(predicted.health, health);
    expect(predicted.sinceDamage, .7);
    expect(predicted.slow, .5);
    expect(predicted.slowTime, 1);
    expect(predicted.poison, .2);
    expect(predicted.poisonTime, 2);
  });

  test(
    'split and coalesced frames, duplicate command IDs, bad versions',
    () async {
      final owner = await host();
      final socket = await Socket.connect('127.0.0.1', owner.port);
      addTearDown(socket.destroy);
      final messages = <Map<String, dynamic>>[];
      final subscription = socket
          .cast<List<int>>()
          .transform(utf8.decoder)
          .transform(const LineSplitter())
          .listen((line) {
            messages.add(jsonDecode(line) as Map<String, dynamic>);
          });
      addTearDown(subscription.cancel);
      final hello = utf8.encode('${jsonEncode(frame('hello'))}\n');
      socket.add(hello.sublist(0, 5));
      await socket.flush();
      socket.add(hello.sublist(5));
      await socket.flush();
      await until(
        () => messages.any((message) => message['type'] == 'welcome'),
      );
      owner.start();
      final command = {
        ...frame('command'),
        'id': 1,
        'command': {'action': 'wave'},
      };
      socket.add(
        utf8.encode('${jsonEncode(command)}\n${jsonEncode(command)}\n'),
      );
      await socket.flush();
      await until(() => owner.game!.wave == 1, owner);
      expect(owner.players.length, 2);
      socket.add(
        utf8.encode('${jsonEncode({...frame('ping'), 'protocol': 99})}\n'),
      );
      await socket.flush();
      await until(() => owner.players.length == 1, owner);
    },
  );

  test('oversized and malformed frames do not harm the host', () async {
    final owner = await host();
    final guest = await join(owner);
    for (final payload in ['not json\n', '${'x' * (256 * 1024 + 1)}\n']) {
      final socket = await Socket.connect('127.0.0.1', owner.port);
      final done = Completer<void>();
      socket.listen(
        (_) {},
        onError: (Object _) {
          if (!done.isCompleted) done.complete();
        },
        onDone: () {
          if (!done.isCompleted) done.complete();
        },
      );
      socket.add(utf8.encode(payload));
      await done.future.timeout(const Duration(seconds: 4));
      socket.destroy();
    }
    expect(owner.connected, isTrue);
    expect(guest.connected, isTrue);
    expect(owner.players.length, 2);
  });

  test('malformed commands disconnect only their sender', () async {
    final owner = await host();
    final guest = await join(owner);
    final socket = await Socket.connect('127.0.0.1', owner.port);
    addTearDown(socket.destroy);
    final subscription = socket.listen((_) {});
    addTearDown(subscription.cancel);
    socket.add(utf8.encode('${jsonEncode(frame('hello'))}\n'));
    await socket.flush();
    await until(() => owner.players.length == 3, owner);
    socket.add(
      utf8.encode(
        '${jsonEncode({
          ...frame('command'),
          'id': -1,
          'command': {'action': 'wave'},
        })}\n',
      ),
    );
    await socket.flush();
    await until(() => owner.players.length == 2, owner);
    expect(guest.connected, isTrue);
    expect(owner.connected, isTrue);
  });

  test(
    'discovery is independent, deduplicates and expires stopped hosts',
    () async {
      final owner = await host();
      final now = DateTime.now();
      final discovery = LanDiscovery(
        clock: () => now,
        destinations: [InternetAddress.loopbackIPv4],
      );
      addTearDown(discovery.dispose);
      await discovery.start();
      await until(() => discovery.games.isNotEmpty);
      expect(discovery.games.single.port, owner.port);
      expect(discovery.games.single.address, '127.0.0.1');
      discovery.refresh();
      expect(discovery.games.length, 1);
      await discovery.close();
      final replacement = LanDiscovery(
        destinations: [InternetAddress.loopbackIPv4],
      );
      addTearDown(replacement.dispose);
      await replacement.start();
      await until(() => replacement.games.length == 1);
      await join(owner);
      owner.start();
      await until(() => replacement.games.isEmpty);
    },
  );
}
