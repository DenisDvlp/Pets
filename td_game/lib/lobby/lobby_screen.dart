import 'dart:async';

import 'package:flutter/material.dart';

import '../game/model.dart';
import '../network/lan_session.dart';

class LobbyScreen extends StatefulWidget {
  const LobbyScreen({
    super.key,
    required this.onBack,
    required this.onStart,
    this.session,
  });

  final VoidCallback onBack;
  final ValueChanged<LanSession> onStart;
  final LanSession? session;

  @override
  State<LobbyScreen> createState() => _LobbyScreenState();
}

class _LobbyScreenState extends State<LobbyScreen> {
  static const _green = Color(0xFF187E69);
  final _name = TextEditingController(text: 'Monkey Defense');
  final _address = TextEditingController();
  final _port = TextEditingController();
  final _hostForm = GlobalKey<FormState>();
  final _joinForm = GlobalKey<FormState>();
  late LanDiscovery _discovery;
  LanSession? _session;
  int _levelIndex = 0;
  int _operation = 0;
  bool _busy = false;
  bool _discovering = true;
  bool _exiting = false;
  bool _startScheduled = false;
  bool _handedOff = false;
  String? _error;

  @override
  void initState() {
    super.initState();
    _discovery = LanDiscovery()..addListener(_discoveryChanged);
    unawaited(_startDiscovery(_discovery));
    _session = widget.session;
    _session?.addListener(_sessionChanged);
    _checkSession();
  }

  void _discoveryChanged() {
    if (mounted && !_exiting) setState(() {});
  }

  Future<void> _startDiscovery(LanDiscovery discovery) async {
    try {
      await discovery.start();
    } on Object catch (error) {
      if (mounted && identical(discovery, _discovery) && !_exiting) {
        setState(() => _error = 'Discovery failed: $error');
      }
    } finally {
      if (mounted && identical(discovery, _discovery) && !_exiting) {
        setState(() => _discovering = false);
      }
    }
  }

  void _retryDiscovery() {
    _discovery.removeListener(_discoveryChanged);
    _discovery.dispose();
    setState(() {
      _error = null;
      _discovering = true;
      _discovery = LanDiscovery()..addListener(_discoveryChanged);
    });
    unawaited(_startDiscovery(_discovery));
  }

  void _sessionChanged() {
    if (!mounted || _exiting || _handedOff) return;
    _checkSession();
    setState(() {});
  }

  void _checkSession() {
    final session = _session;
    if (session == null || _exiting || _handedOff) return;
    if (!session.connected) {
      session.removeListener(_sessionChanged);
      _session = null;
      _startScheduled = false;
      _error = session.error ?? 'Session disconnected.';
      unawaited(_closeSession(session));
      return;
    }
    if (!session.started || session.game == null || _startScheduled) return;
    _startScheduled = true;
    WidgetsBinding.instance.addPostFrameCallback((_) {
      if (!mounted || _exiting || _handedOff || !identical(session, _session)) {
        return;
      }
      _startScheduled = false;
      if (!session.connected || !session.started || session.game == null) {
        _sessionChanged();
        return;
      }
      _handedOff = true;
      session.removeListener(_sessionChanged);
      widget.onStart(session);
    });
  }

  Future<void> _closeSession(LanSession session) async {
    try {
      await session.close();
    } on Object catch (error) {
      if (mounted && !_exiting && !_handedOff) {
        setState(() => _error = 'Could not close session: $error');
      }
    }
  }

  Future<void> _connect(Future<LanSession> Function() connect) async {
    if (_busy || _exiting || _handedOff || _session != null) return;
    final operation = ++_operation;
    setState(() {
      _busy = true;
      _error = null;
    });
    try {
      final session = await connect();
      if (!mounted || _exiting || operation != _operation) {
        await _closeSession(session);
        return;
      }
      setState(() {
        _session = session;
        session.addListener(_sessionChanged);
        _checkSession();
      });
    } on Object catch (error) {
      if (mounted && !_exiting && operation == _operation) {
        setState(() => _error = 'Connection failed: $error');
      }
    } finally {
      if (mounted && !_exiting && operation == _operation) {
        setState(() => _busy = false);
      }
    }
  }

  void _host() {
    if (!_hostForm.currentState!.validate()) return;
    final name = _name.text.trim();
    final levelIndex = _levelIndex;
    unawaited(
      _connect(() => LanSession.host(name: name, levelIndex: levelIndex)),
    );
  }

  void _joinDirect() {
    if (!_joinForm.currentState!.validate()) return;
    final address = _address.text.trim();
    final port = int.parse(_port.text.trim());
    unawaited(_connect(() => LanSession.join(address, port)));
  }

  Future<void> _leave() async {
    if (_busy || _exiting || _handedOff) return;
    final session = _session;
    session?.removeListener(_sessionChanged);
    setState(() {
      _session = null;
      _startScheduled = false;
      _busy = true;
      _error = null;
    });
    if (session != null) await _closeSession(session);
    if (mounted && !_exiting) {
      setState(() => _busy = false);
      _discovery.refresh();
    }
  }

  Future<void> _back() async {
    if (_exiting || _handedOff) return;
    ++_operation;
    final session = _session;
    session?.removeListener(_sessionChanged);
    setState(() {
      _exiting = true;
      _session = null;
    });
    _discovery.removeListener(_discoveryChanged);
    await _discovery.close();
    if (session != null) await _closeSession(session);
    if (mounted) widget.onBack();
  }

  @override
  void dispose() {
    ++_operation;
    _discovery.removeListener(_discoveryChanged);
    _discovery.dispose();
    final session = _session;
    session?.removeListener(_sessionChanged);
    if (session != null && !_handedOff) unawaited(_closeSession(session));
    _name.dispose();
    _address.dispose();
    _port.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final session = _session;
    return PopScope(
      canPop: false,
      onPopInvokedWithResult: (didPop, result) {
        if (!didPop) unawaited(_back());
      },
      child: Scaffold(
        backgroundColor: const Color(0xFFF4F6F4),
        appBar: AppBar(
          backgroundColor: Colors.white,
          leading: IconButton(
            tooltip: 'Back',
            onPressed: _exiting || _handedOff ? null : () => unawaited(_back()),
            icon: const Icon(Icons.arrow_back),
          ),
          title: const Text('LAN Lobby'),
        ),
        body: SafeArea(
          child: SingleChildScrollView(
            padding: const EdgeInsets.all(16),
            child: Center(
              child: ConstrainedBox(
                constraints: const BoxConstraints(maxWidth: 1000),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.stretch,
                  children: [
                    if (_busy || _exiting) ...[
                      const LinearProgressIndicator(color: _green),
                      const SizedBox(height: 16),
                    ],
                    if (_error != null) _failure(_error!),
                    if (session == null) _browser() else _waitingRoom(session),
                  ],
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }

  Widget _failure(String message, {VoidCallback? retry}) => Padding(
    padding: const EdgeInsets.only(bottom: 16),
    child: Row(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        const Padding(
          padding: EdgeInsets.only(top: 3),
          child: Icon(Icons.warning_amber, color: Color(0xFFAE542C)),
        ),
        const SizedBox(width: 8),
        Expanded(child: SelectableText(message)),
        if (retry != null)
          IconButton(
            tooltip: 'Retry discovery',
            onPressed: retry,
            icon: const Icon(Icons.refresh),
          ),
      ],
    ),
  );

  Widget _heading(String title) => Padding(
    padding: const EdgeInsets.only(bottom: 12),
    child: Text(title, style: Theme.of(context).textTheme.titleLarge),
  );

  Widget _browser() => Column(
    crossAxisAlignment: CrossAxisAlignment.stretch,
    children: [
      Row(
        children: [
          Expanded(child: _heading('Nearby games')),
          IconButton(
            tooltip: 'Refresh games',
            onPressed: _busy || _exiting ? null : _retryDiscovery,
            icon: const Icon(Icons.refresh),
          ),
        ],
      ),
      if (_discovery.error != null)
        _failure(
          _discovery.error!,
          retry: _busy || _exiting ? null : _retryDiscovery,
        ),
      if (_discovering)
        const Padding(
          padding: EdgeInsets.symmetric(vertical: 20),
          child: Row(
            children: [
              SizedBox(
                width: 20,
                height: 20,
                child: CircularProgressIndicator(strokeWidth: 2),
              ),
              SizedBox(width: 12),
              Expanded(child: Text('Searching for games...')),
            ],
          ),
        )
      else if (_discovery.games.isEmpty)
        const Padding(
          padding: EdgeInsets.symmetric(vertical: 20),
          child: Text('No nearby games found.'),
        ),
      for (final listing in _discovery.games) ...[
        Row(
          children: [
            const Icon(Icons.sports_esports, color: _green),
            const SizedBox(width: 12),
            Expanded(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    listing.name,
                    style: Theme.of(context).textTheme.titleMedium,
                  ),
                  Text(
                    '${levels[listing.levelIndex].name} | '
                    '${listing.players}/${listing.capacity} players',
                  ),
                ],
              ),
            ),
            IconButton(
              tooltip: listing.players >= listing.capacity
                  ? 'Lobby full'
                  : 'Join game',
              onPressed:
                  _busy || _exiting || listing.players >= listing.capacity
                  ? null
                  : () => unawaited(
                      _connect(
                        () => LanSession.join(listing.address, listing.port),
                      ),
                    ),
              icon: const Icon(Icons.login, color: _green),
            ),
          ],
        ),
        const Divider(),
      ],
      const SizedBox(height: 24),
      LayoutBuilder(
        builder: (context, constraints) {
          final host = _createForm();
          final join = _directForm();
          if (constraints.maxWidth < 680) {
            return Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [host, const SizedBox(height: 28), join],
            );
          }
          return Row(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Expanded(child: host),
              const SizedBox(width: 32),
              Expanded(child: join),
            ],
          );
        },
      ),
    ],
  );

  Widget _createForm() => Form(
    key: _hostForm,
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        _heading('Create game'),
        TextFormField(
          controller: _name,
          enabled: !_busy && !_exiting,
          maxLength: NetworkConfig.maxNameLength,
          decoration: const InputDecoration(labelText: 'Lobby name'),
          validator: (value) => value == null || value.trim().isEmpty
              ? 'Enter a lobby name.'
              : null,
        ),
        const SizedBox(height: 12),
        DropdownButtonFormField<int>(
          initialValue: _levelIndex,
          isExpanded: true,
          decoration: const InputDecoration(labelText: 'Map'),
          items: [
            for (var index = 0; index < levels.length; index++)
              DropdownMenuItem(
                value: index,
                child: Text(
                  levels[index].name,
                  overflow: TextOverflow.ellipsis,
                ),
              ),
          ],
          onChanged: _busy || _exiting
              ? null
              : (value) {
                  if (value != null) setState(() => _levelIndex = value);
                },
        ),
        const SizedBox(height: 16),
        _preview(levels[_levelIndex]),
        const SizedBox(height: 16),
        FilledButton.icon(
          onPressed: _busy || _exiting ? null : _host,
          icon: const Icon(Icons.add),
          label: const Text('Create game'),
        ),
      ],
    ),
  );

  Widget _directForm() => Form(
    key: _joinForm,
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        _heading('Direct join'),
        TextFormField(
          controller: _address,
          enabled: !_busy && !_exiting,
          autocorrect: false,
          keyboardType: TextInputType.url,
          maxLength: NetworkConfig.maxAddressLength,
          decoration: const InputDecoration(labelText: 'Host address'),
          validator: (value) => value == null || value.trim().isEmpty
              ? 'Enter a host address.'
              : null,
        ),
        const SizedBox(height: 12),
        TextFormField(
          controller: _port,
          enabled: !_busy && !_exiting,
          keyboardType: TextInputType.number,
          decoration: const InputDecoration(labelText: 'Port'),
          validator: (value) {
            final port = int.tryParse(value?.trim() ?? '');
            return port == null || port < 1 || port > NetworkConfig.maxPort
                ? 'Enter a port from 1 to ${NetworkConfig.maxPort}.'
                : null;
          },
          onFieldSubmitted: (_) {
            if (!_busy && !_exiting) _joinDirect();
          },
        ),
        const SizedBox(height: 16),
        FilledButton.icon(
          onPressed: _busy || _exiting ? null : _joinDirect,
          icon: const Icon(Icons.login),
          label: const Text('Join game'),
        ),
      ],
    ),
  );

  Widget _waitingRoom(LanSession session) {
    final level = levels[session.levelIndex];
    return Column(
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        _heading(session.name),
        if (session.error != null) _failure(session.error!),
        Text(level.name, style: Theme.of(context).textTheme.titleMedium),
        Text(level.subtitle),
        const SizedBox(height: 16),
        _preview(level),
        const SizedBox(height: 20),
        if (session.isHost) ...[
          Text(
            'Host addresses',
            style: Theme.of(context).textTheme.titleMedium,
          ),
          if (session.addresses.isEmpty)
            const Text('No LAN addresses available.'),
          for (final address in session.addresses)
            SelectableText('$address:${session.port}'),
        ],
        SelectableText('Port: ${session.port}'),
        const SizedBox(height: 20),
        _heading(
          'Players (${session.players.length}/${NetworkConfig.maxPlayers})',
        ),
        for (final player in session.players) ...[
          Row(
            children: [
              Icon(
                player == 'Host' ? Icons.star_outline : Icons.person_outline,
                color: _green,
              ),
              const SizedBox(width: 12),
              Expanded(child: Text(player)),
            ],
          ),
          const Divider(),
        ],
        const SizedBox(height: 12),
        Text(
          session.isHost
              ? (session.players.length < NetworkConfig.minPlayers
                    ? 'Waiting for another player...'
                    : 'Ready to start.')
              : 'Waiting for the host to start...',
        ),
        const SizedBox(height: 16),
        Wrap(
          spacing: 12,
          runSpacing: 12,
          children: [
            if (session.isHost)
              FilledButton.icon(
                onPressed:
                    !_busy &&
                        !_exiting &&
                        !_handedOff &&
                        session.connected &&
                        !session.started &&
                        session.players.length >= NetworkConfig.minPlayers
                    ? session.start
                    : null,
                icon: const Icon(Icons.play_arrow),
                label: const Text('Start match'),
              ),
            OutlinedButton.icon(
              onPressed: _busy || _exiting || _handedOff
                  ? null
                  : () => unawaited(_leave()),
              icon: const Icon(Icons.logout),
              label: const Text('Leave lobby'),
            ),
          ],
        ),
      ],
    );
  }

  Widget _preview(LevelDefinition level) => Semantics(
    label: '${level.name} map preview',
    image: true,
    child: Center(
      child: ConstrainedBox(
        constraints: BoxConstraints(
          maxWidth: 280 * level.columns / level.rows,
          maxHeight: 280,
        ),
        child: AspectRatio(
          aspectRatio: level.columns / level.rows,
          child: CustomPaint(painter: _MapPreviewPainter(level)),
        ),
      ),
    ),
  );
}

class _MapPreviewPainter extends CustomPainter {
  const _MapPreviewPainter(this.level);
  final LevelDefinition level;

  @override
  void paint(Canvas canvas, Size size) {
    final cellWidth = size.width / level.columns;
    final cellHeight = size.height / level.rows;
    final paint = Paint();
    for (var row = 0; row < level.rows; row++) {
      for (var column = 0; column < level.columns; column++) {
        paint.color = switch (level.terrain((column: column, row: row))) {
          Terrain.grass =>
            (column + row).isEven
                ? const Color(0xFFA4D58D)
                : const Color(0xFF9BCD83),
          Terrain.road => const Color(0xFFE4C48A),
          Terrain.water => const Color(0xFF68BDD3),
          Terrain.rock => const Color(0xFF8A9690),
        };
        canvas.drawRect(
          Rect.fromLTWH(
            column * cellWidth,
            row * cellHeight,
            cellWidth + .2,
            cellHeight + .2,
          ),
          paint,
        );
      }
    }
    final route = Path();
    for (var index = 0; index < level.road.length; index++) {
      final cell = level.road[index];
      final horizontal = (cell.column + .5) * cellWidth;
      final vertical = (cell.row + .5) * cellHeight;
      if (index == 0) {
        route.moveTo(horizontal, vertical);
      } else {
        route.lineTo(horizontal, vertical);
      }
    }
    canvas.drawPath(
      route,
      Paint()
        ..color = const Color(0xFFBC945B)
        ..style = PaintingStyle.stroke
        ..strokeWidth = 2,
    );
    for (final cell in [level.road.first, level.road.last]) {
      canvas.drawCircle(
        Offset((cell.column + .5) * cellWidth, (cell.row + .5) * cellHeight),
        cellWidth * .3,
        Paint()
          ..color = cell == level.road.first
              ? const Color(0xFF187E69)
              : const Color(0xFFCF574F),
      );
    }
  }

  @override
  bool shouldRepaint(covariant _MapPreviewPainter oldDelegate) =>
      oldDelegate.level != level;
}
