import 'dart:io';
import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'game/defense_game.dart';
import 'game/model.dart';
import 'lobby/lobby_screen.dart';
import 'network/lan_session.dart';
import 'services/settings_store.dart';

class MonkeyDefenseApp extends StatefulWidget {
  const MonkeyDefenseApp({
    super.key,
    this.settingsStore,
    this.exitAction,
    this.audioEnabled = true,
  });
  final SettingsStore? settingsStore;
  final Future<void> Function()? exitAction;
  final bool audioEnabled;
  @override
  State<MonkeyDefenseApp> createState() => _MonkeyDefenseAppState();
}

class _MonkeyDefenseAppState extends State<MonkeyDefenseApp> {
  late final SettingsStore store =
      widget.settingsStore ?? PreferencesSettingsStore();
  DefenseSettings settings = const DefenseSettings();
  int page = 0;
  int levelIndex = 0;
  int runId = 0;
  LanSession? lan;
  bool edited = false;
  bool exiting = false;
  Future<void> pendingSave = Future<void>.value();
  @override
  void initState() {
    super.initState();
    _load();
  }

  Future<void> _load() async {
    try {
      final loaded = await store.load();
      if (mounted && !edited) setState(() => settings = loaded);
    } catch (_) {}
  }

  Future<void> _save(DefenseSettings value) {
    edited = true;
    setState(() => settings = value);
    pendingSave = pendingSave
        .catchError((Object _) {})
        .then((_) => store.save(value));
    return pendingSave;
  }

  void _play(int index) => setState(() {
    levelIndex = index;
    runId++;
    page = 2;
  });

  void _lanChanged() {
    final connection = lan;
    if (!mounted || connection == null) return;
    if (!connection.connected || !connection.started) {
      setState(() => page = 3);
    }
  }

  void _startCoop(LanSession connection) {
    lan?.removeListener(_lanChanged);
    lan = connection;
    connection.addListener(_lanChanged);
    connection.game!.autoStart = connection.isHost
        ? settings.autoStart
        : connection.game!.autoStart;
    setState(() {
      levelIndex = connection.levelIndex;
      runId++;
      page = 2;
    });
  }

  void _leaveCoop({bool menu = false}) {
    final connection = lan;
    connection?.removeListener(_lanChanged);
    lan = null;
    connection?.close();
    setState(() => page = menu ? 0 : 3);
  }

  void _restartCoop({int? next}) {
    lan?.returnToLobby(levelIndex: next);
    if (next != null) lan?.start();
  }

  @override
  void dispose() {
    lan?.removeListener(_lanChanged);
    lan?.close();
    super.dispose();
  }

  Future<void> _exit() async {
    if (exiting) return;
    setState(() => exiting = true);
    try {
      await pendingSave.catchError((Object _) {});
      await store.save(settings);
      await lan?.close();
      if (widget.exitAction != null) {
        await widget.exitAction!();
      } else {
        exit(0);
      }
    } finally {
      if (mounted) setState(() => exiting = false);
    }
  }

  @override
  Widget build(BuildContext context) => MaterialApp(
    debugShowCheckedModeBanner: false,
    title: 'Monkey Balloon Defense',
    theme: ThemeData(
      useMaterial3: true,
      fontFamily: 'Segoe UI',
      scaffoldBackgroundColor: _paper,
      colorScheme: ColorScheme.fromSeed(
        seedColor: _green,
        primary: _green,
        surface: Colors.white,
        onSurface: _ink,
      ),
      cardTheme: const CardThemeData(
        elevation: 0,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.all(Radius.circular(8)),
        ),
      ),
      dialogTheme: const DialogThemeData(
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.all(Radius.circular(8)),
        ),
      ),
      dividerTheme: const DividerThemeData(color: Color(0xFFDDE4DF)),
      filledButtonTheme: FilledButtonThemeData(
        style: FilledButton.styleFrom(
          padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 14),
          shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(6)),
        ),
      ),
    ),
    home: Builder(
      builder: (context) {
        if (page == 0) {
          return _MainMenu(
            onPlay: () => setState(() => page = 1),
            onCoop: () => setState(() => page = 3),
            onSettings: () => _showSettings(context, settings, _save),
            onExit: exiting ? null : _exit,
          );
        }
        if (page == 1) {
          return _LevelSelect(
            settings: settings,
            onPlay: _play,
            onBack: () => setState(() => page = 0),
          );
        }
        if (page == 3) {
          return LobbyScreen(
            session: lan,
            onBack: () => _leaveCoop(menu: true),
            onStart: _startCoop,
          );
        }
        return _GameScreen(
          key: ValueKey(runId),
          audioEnabled: widget.audioEnabled,
          levelIndex: levelIndex,
          settings: settings,
          connection: lan,
          onSettings: _save,
          onComplete: () => _save(
            settings.copyWith(completed: {...settings.completed, levelIndex}),
          ),
          onRestart: lan != null
              ? () => _restartCoop()
              : () => _play(levelIndex),
          onNext: levelIndex + 1 < levels.length && (lan?.isHost ?? true)
              ? () => lan != null
                    ? _restartCoop(next: levelIndex + 1)
                    : _play(levelIndex + 1)
              : null,
          onMenu: () =>
              lan != null ? _leaveCoop(menu: true) : setState(() => page = 0),
          onLevels: () => lan != null ? _leaveCoop() : setState(() => page = 1),
        );
      },
    ),
  );
}

const _ink = Color(0xFF253631);
const _green = Color(0xFF187E69);
const _paper = Color(0xFFF4F6F4);

class _MainMenu extends StatelessWidget {
  const _MainMenu({
    required this.onPlay,
    required this.onCoop,
    required this.onSettings,
    this.onExit,
  });
  final VoidCallback onPlay;
  final VoidCallback onCoop;
  final VoidCallback onSettings;
  final VoidCallback? onExit;
  @override
  Widget build(BuildContext context) => Scaffold(
    body: Stack(
      children: [
        Positioned.fill(child: CustomPaint(painter: _MapPainter(levels.first))),
        Positioned.fill(
          child: ColoredBox(color: Colors.white.withValues(alpha: .88)),
        ),
        Center(
          child: SingleChildScrollView(
            padding: const EdgeInsets.all(28),
            child: ConstrainedBox(
              constraints: const BoxConstraints(maxWidth: 430),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const _Portrait(kind: TowerKind.dart, size: 92),
                  const SizedBox(height: 22),
                  const Text(
                    'Monkey Balloon Defense',
                    textAlign: TextAlign.center,
                    style: TextStyle(
                      fontSize: 38,
                      height: 1.12,
                      fontWeight: FontWeight.w800,
                    ),
                  ),
                  const SizedBox(height: 32),
                  SizedBox(
                    width: 240,
                    child: FilledButton.icon(
                      onPressed: onPlay,
                      icon: const Icon(Icons.play_arrow_rounded),
                      label: const Text('Play'),
                    ),
                  ),
                  const SizedBox(height: 10),
                  SizedBox(
                    width: 240,
                    child: OutlinedButton.icon(
                      onPressed: onCoop,
                      icon: const Icon(Icons.groups_outlined),
                      label: const Text('Co-op Lobby'),
                    ),
                  ),
                  const SizedBox(height: 10),
                  SizedBox(
                    width: 240,
                    child: OutlinedButton.icon(
                      onPressed: onSettings,
                      icon: const Icon(Icons.tune),
                      label: const Text('Settings'),
                    ),
                  ),
                  const SizedBox(height: 6),
                  TextButton.icon(
                    onPressed: onExit,
                    icon: const Icon(Icons.exit_to_app),
                    label: const Text('Exit'),
                  ),
                ],
              ),
            ),
          ),
        ),
      ],
    ),
  );
}

class _LevelSelect extends StatelessWidget {
  const _LevelSelect({
    required this.settings,
    required this.onBack,
    required this.onPlay,
  });
  final DefenseSettings settings;
  final VoidCallback onBack;
  final ValueChanged<int> onPlay;
  @override
  Widget build(BuildContext context) => Scaffold(
    appBar: AppBar(
      leading: IconButton(
        onPressed: onBack,
        tooltip: 'Main menu',
        icon: const Icon(Icons.arrow_back),
      ),
      title: const Text('Choose a level'),
    ),
    body: LayoutBuilder(
      builder: (context, constraints) => SingleChildScrollView(
        padding: const EdgeInsets.all(24),
        child: Center(
          child: ConstrainedBox(
            constraints: const BoxConstraints(maxWidth: 1000),
            child: Wrap(
              spacing: 20,
              runSpacing: 20,
              children: [
                for (var index = 0; index < levels.length; index++)
                  SizedBox(
                    width: constraints.maxWidth < 700
                        ? (constraints.maxWidth - 48).clamp(0, 480).toDouble()
                        : ((constraints.maxWidth - 68) / 2)
                              .clamp(0, 480)
                              .toDouble(),
                    child: Card(
                      clipBehavior: Clip.antiAlias,
                      margin: EdgeInsets.zero,
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          AspectRatio(
                            aspectRatio: 1.8,
                            child: CustomPaint(
                              painter: _MapPainter(levels[index]),
                            ),
                          ),
                          Padding(
                            padding: const EdgeInsets.all(18),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                Row(
                                  children: [
                                    Expanded(
                                      child: Text(
                                        levels[index].name,
                                        style: const TextStyle(
                                          fontSize: 22,
                                          fontWeight: FontWeight.w700,
                                        ),
                                      ),
                                    ),
                                    if (settings.completed.contains(index))
                                      const Tooltip(
                                        message: 'Completed',
                                        child: Icon(
                                          Icons.verified,
                                          color: _green,
                                        ),
                                      ),
                                  ],
                                ),
                                const SizedBox(height: 8),
                                Text(levels[index].subtitle),
                                const SizedBox(height: 12),
                                Text(
                                  '${levels[index].waves} waves  /  ${levels[index].columns} x ${levels[index].rows}',
                                  style: const TextStyle(
                                    color: Color(0xFF66756D),
                                  ),
                                ),
                                const SizedBox(height: 18),
                                FilledButton.icon(
                                  onPressed: () => onPlay(index),
                                  icon: const Icon(Icons.play_arrow),
                                  label: const Text('Play'),
                                ),
                              ],
                            ),
                          ),
                        ],
                      ),
                    ),
                  ),
              ],
            ),
          ),
        ),
      ),
    ),
  );
}

Future<void> _showSettings(
  BuildContext context,
  DefenseSettings settings,
  Future<void> Function(DefenseSettings) onChanged,
) => showDialog<void>(
  context: context,
  builder: (context) =>
      _SettingsDialog(settings: settings, onChanged: onChanged),
);

class _SettingsDialog extends StatefulWidget {
  const _SettingsDialog({required this.settings, required this.onChanged});

  final DefenseSettings settings;
  final Future<void> Function(DefenseSettings) onChanged;

  @override
  State<_SettingsDialog> createState() => _SettingsDialogState();
}

class _SettingsDialogState extends State<_SettingsDialog> {
  late DefenseSettings value = widget.settings;
  Future<void> pending = Future<void>.value();
  bool saving = false;
  String? error;

  void _change(DefenseSettings settings) {
    setState(() {
      value = settings;
      error = null;
    });
    pending = widget.onChanged(value).catchError((Object _) {
      if (mounted) setState(() => error = 'Settings could not be saved.');
    });
  }

  Future<void> _done() async {
    setState(() => saving = true);
    await pending;
    if (mounted) Navigator.pop(context);
  }

  @override
  Widget build(BuildContext context) {
    return Dialog(
      child: ConstrainedBox(
        constraints: const BoxConstraints(maxWidth: 420),
        child: SingleChildScrollView(
          padding: const EdgeInsets.all(24),
          child: Column(
            mainAxisSize: MainAxisSize.min,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              const Text(
                'Settings',
                style: TextStyle(fontSize: 24, fontWeight: FontWeight.w700),
              ),
              const SizedBox(height: 24),
              Row(
                children: [
                  const Icon(Icons.volume_up_outlined),
                  const SizedBox(width: 12),
                  const Expanded(child: Text('Sound effects')),
                  Text('${(value.volume * 100).round()}%'),
                ],
              ),
              Slider(
                value: value.volume.clamp(0, 1),
                divisions: 20,
                label: '${(value.volume * 100).round()}%',
                onChanged: saving
                    ? null
                    : (volume) => _change(value.copyWith(volume: volume)),
              ),
              SwitchListTile.adaptive(
                contentPadding: EdgeInsets.zero,
                title: const Text('Show grid'),
                secondary: const Icon(Icons.grid_4x4),
                value: value.grid,
                onChanged: saving
                    ? null
                    : (grid) => _change(value.copyWith(grid: grid)),
              ),
              SwitchListTile.adaptive(
                contentPadding: EdgeInsets.zero,
                title: const Text('Auto-start waves'),
                secondary: const Icon(Icons.skip_next_outlined),
                value: value.autoStart,
                onChanged: saving
                    ? null
                    : (auto) => _change(value.copyWith(autoStart: auto)),
              ),
              if (error != null)
                Text(
                  error!,
                  style: TextStyle(color: Theme.of(context).colorScheme.error),
                ),
              const SizedBox(height: 20),
              Align(
                alignment: Alignment.centerRight,
                child: FilledButton(
                  onPressed: saving ? null : _done,
                  child: Text(saving ? 'Saving...' : 'Done'),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

enum _GameAction { resume, settings, restart, menu, levels, next }

class _GameScreen extends StatefulWidget {
  const _GameScreen({
    super.key,
    required this.audioEnabled,
    required this.levelIndex,
    required this.settings,
    required this.onSettings,
    required this.onComplete,
    required this.onRestart,
    required this.onMenu,
    required this.onLevels,
    this.onNext,
    this.connection,
  });
  final int levelIndex;
  final bool audioEnabled;
  final DefenseSettings settings;
  final Future<void> Function(DefenseSettings) onSettings;
  final Future<void> Function() onComplete;
  final VoidCallback onRestart;
  final VoidCallback onMenu;
  final VoidCallback onLevels;
  final VoidCallback? onNext;
  final LanSession? connection;
  @override
  State<_GameScreen> createState() => _GameScreenState();
}

class _GameScreenState extends State<_GameScreen> with WidgetsBindingObserver {
  late final GameSession session;
  late final DefenseGame game;
  bool dialogOpen = false;
  bool resultShown = false;
  bool sessionEnded = false;
  @override
  void initState() {
    super.initState();
    session =
        widget.connection?.game ??
        (GameSession(levels[widget.levelIndex])
          ..autoStart = widget.settings.autoStart);
    game = DefenseGame(
      audioEnabled: widget.audioEnabled,
      session: session,
      settings: widget.settings,
      onChanged: _changed,
    )..sharedSession = widget.connection != null;
    widget.connection?.addListener(_networkChanged);
    WidgetsBinding.instance.addObserver(this);
  }

  @override
  void didUpdateWidget(covariant _GameScreen oldWidget) {
    super.didUpdateWidget(oldWidget);
    game.settings = widget.settings;
    if (widget.connection == null || widget.connection!.isHost) {
      session.autoStart = widget.settings.autoStart;
    }
  }

  @override
  void dispose() {
    WidgetsBinding.instance.removeObserver(this);
    widget.connection?.removeListener(_networkChanged);
    game.dispose();
    super.dispose();
  }

  @override
  void didChangeAppLifecycleState(AppLifecycleState state) {
    if (state == AppLifecycleState.inactive ||
        state == AppLifecycleState.paused ||
        state == AppLifecycleState.hidden) {
      if (session.editable && (widget.connection?.isHost ?? true)) _pause();
    }
  }

  void _command(VoidCallback command) {
    command();
    widget.connection?.publish();
    game.notify();
  }

  void _networkChanged() {
    if (!mounted) return;
    if (!widget.connection!.connected || !widget.connection!.started) {
      sessionEnded = true;
      if (dialogOpen) Navigator.of(context).pop();
      return;
    }
    _changed();
  }

  void _changed() {
    if (!mounted) return;
    setState(() {});
    if (!resultShown &&
        !dialogOpen &&
        (session.phase == SessionPhase.won ||
            session.phase == SessionPhase.lost)) {
      resultShown = true;
      dialogOpen = true;
      WidgetsBinding.instance.addPostFrameCallback((_) {
        if (mounted) _result();
      });
    }
  }

  void _pause() {
    if (dialogOpen || !session.editable) return;
    if (widget.connection != null) {
      _command(session.pause);
      return;
    }
    dialogOpen = true;
    _command(session.pause);
    WidgetsBinding.instance.addPostFrameCallback((_) {
      if (mounted) _pauseDialog();
    });
  }

  Future<void> _coopSettings() async {
    if (dialogOpen) return;
    dialogOpen = true;
    await _showSettings(context, widget.settings, widget.onSettings);
    if (mounted) {
      dialogOpen = false;
      _changed();
    }
  }

  Future<void> _pauseDialog() async {
    final action = await showDialog<_GameAction>(
      context: context,
      barrierDismissible: false,
      builder: (context) => _ActionDialog(
        title: 'Paused',
        subtitle: session.level.name,
        actions: const [
          (_GameAction.resume, Icons.play_arrow, 'Resume'),
          (_GameAction.settings, Icons.tune, 'Settings'),
          (_GameAction.restart, Icons.refresh, 'Restart'),
          (_GameAction.menu, Icons.home_outlined, 'Main Menu'),
        ],
      ),
    );
    if (!mounted) return;
    if (action == _GameAction.settings) {
      await _showSettings(context, widget.settings, widget.onSettings);
      if (mounted) await _pauseDialog();
      return;
    }
    dialogOpen = false;
    if (action == null || action == _GameAction.resume) {
      _command(session.resume);
    } else {
      _navigate(action);
    }
  }

  Future<void> _result() async {
    final won = session.phase == SessionPhase.won;
    final coop = widget.connection != null;
    final host = widget.connection?.isHost ?? true;
    if (won) {
      try {
        await widget.onComplete();
      } catch (_) {}
    }
    if (!mounted ||
        sessionEnded ||
        (coop &&
            (!widget.connection!.connected || !widget.connection!.started))) {
      return;
    }
    final action = await showDialog<_GameAction>(
      context: context,
      barrierDismissible: false,
      builder: (context) => _ActionDialog(
        title: won ? 'Campaign secured!' : 'Defense defeated',
        subtitle:
            '${session.level.name}\nWave ${session.wave} / ${session.level.waves}  |  ${session.popped} popped  |  ${session.lives} lives',
        emblem: won ? Icons.emoji_events_outlined : Icons.heart_broken_outlined,
        actions: [
          if (won && widget.onNext != null)
            (_GameAction.next, Icons.arrow_forward, 'Next Level'),
          if (host)
            (
              _GameAction.restart,
              Icons.refresh,
              coop ? 'Retry with Team' : 'Retry',
            ),
          (
            _GameAction.levels,
            Icons.map_outlined,
            coop ? 'Leave to Lobby' : 'Level Select',
          ),
          (_GameAction.menu, Icons.home_outlined, 'Main Menu'),
        ],
      ),
    );
    if (!mounted) return;
    dialogOpen = false;
    if (sessionEnded ||
        (coop &&
            (!widget.connection!.connected || !widget.connection!.started))) {
      return;
    }
    _navigate(action ?? _GameAction.levels);
  }

  void _navigate(_GameAction action) {
    switch (action) {
      case _GameAction.restart:
        widget.onRestart();
      case _GameAction.menu:
        widget.onMenu();
      case _GameAction.levels:
        widget.onLevels();
      case _GameAction.next:
        widget.onNext?.call();
      case _GameAction.resume:
      case _GameAction.settings:
        break;
    }
  }

  @override
  Widget build(BuildContext context) => CallbackShortcuts(
    bindings: {
      const SingleActivator(LogicalKeyboardKey.escape): () {
        if (dialogOpen) return;
        if (session.buying != null || session.selected != null) {
          _command(session.cancel);
        } else {
          _pause();
        }
      },
    },
    child: Focus(
      autofocus: true,
      child: Scaffold(
        body: SafeArea(
          child: Column(
            children: [
              _hud(),
              Expanded(
                child: LayoutBuilder(
                  builder: (context, constraints) {
                    final board = ColoredBox(
                      color: const Color(0xFF286E51),
                      child: GameWidget<DefenseGame>(
                        game: game,
                        loadingBuilder: (context) => const Center(
                          child: CircularProgressIndicator(color: Colors.white),
                        ),
                        errorBuilder: (context, error) => Center(
                          child: Padding(
                            padding: const EdgeInsets.all(24),
                            child: Column(
                              mainAxisSize: MainAxisSize.min,
                              children: [
                                const Icon(
                                  Icons.error_outline,
                                  color: Colors.white,
                                  size: 36,
                                ),
                                const SizedBox(height: 12),
                                const Text(
                                  'Unable to load the battlefield.',
                                  style: TextStyle(color: Colors.white),
                                ),
                                const SizedBox(height: 16),
                                FilledButton.icon(
                                  onPressed: widget.onRestart,
                                  icon: const Icon(Icons.refresh),
                                  label: const Text('Retry'),
                                ),
                                TextButton(
                                  onPressed: widget.onMenu,
                                  child: const Text(
                                    'Main Menu',
                                    style: TextStyle(color: Colors.white),
                                  ),
                                ),
                              ],
                            ),
                          ),
                        ),
                      ),
                    );
                    if (constraints.maxWidth < 700) {
                      return Column(
                        children: [
                          Expanded(child: board),
                          SizedBox(height: 220, child: _shop()),
                        ],
                      );
                    }
                    return Row(
                      crossAxisAlignment: CrossAxisAlignment.stretch,
                      children: [
                        Expanded(child: board),
                        SizedBox(
                          width: constraints.maxWidth < 1100 ? 264 : 300,
                          child: _shop(),
                        ),
                      ],
                    );
                  },
                ),
              ),
              _status(),
            ],
          ),
        ),
      ),
    ),
  );

  Widget _hud() => Material(
    color: Colors.white,
    child: Padding(
      padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 8),
      child: Wrap(
        spacing: 16,
        runSpacing: 6,
        crossAxisAlignment: WrapCrossAlignment.center,
        children: [
          Text(
            session.level.name,
            style: const TextStyle(fontWeight: FontWeight.w700),
          ),
          if (widget.connection case final connection?)
            _Counter(
              icon: Icons.groups_outlined,
              text:
                  '${connection.players.length} / ${NetworkConfig.maxPlayers}',
              color: _green,
            ),
          _Counter(
            icon: Icons.payments_outlined,
            text: '\$${session.money}',
            color: _green,
          ),
          _Counter(
            icon: Icons.favorite,
            text: '${session.lives}',
            color: const Color(0xFFD65865),
          ),
          _Counter(
            icon: Icons.flag_outlined,
            text: '${session.wave} / ${session.level.waves}',
            color: _ink,
          ),
          _Counter(
            icon: Icons.air,
            text: '${session.remaining} left',
            color: _ink,
          ),
          FilledButton.icon(
            onPressed: session.phase == SessionPhase.ready
                ? () => _command(session.startWave)
                : null,
            style: FilledButton.styleFrom(
              padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 12),
            ),
            icon: const Icon(Icons.play_arrow, size: 20),
            label: Text(
              session.phase == SessionPhase.running
                  ? 'Wave active'
                  : 'Start Wave',
            ),
          ),
          Tooltip(
            message: 'Game speed',
            child: SizedBox(
              width: 96,
              child: DropdownButton<int>(
                value: session.speed,
                isExpanded: true,
                items: [
                  for (final speed in SimulationConfig.supportedSpeeds)
                    DropdownMenuItem(value: speed, child: Text('${speed}x')),
                ],
                onChanged: session.editable
                    ? (value) {
                        if (value != null) {
                          _command(() => session.setSpeed(value));
                        }
                      }
                    : null,
              ),
            ),
          ),
          IconButton(
            onPressed: session.editable ? _pause : null,
            tooltip: 'Pause',
            icon: const Icon(Icons.pause),
          ),
          if (widget.connection != null)
            IconButton(
              onPressed: _coopSettings,
              tooltip: 'Settings',
              icon: const Icon(Icons.tune),
            ),
          if (widget.connection != null)
            IconButton(
              onPressed: widget.onLevels,
              tooltip: 'Leave game',
              icon: const Icon(Icons.logout),
            ),
          if (widget.connection != null && session.phase == SessionPhase.paused)
            FilledButton.icon(
              onPressed: () => _command(session.resume),
              icon: const Icon(Icons.play_arrow),
              label: const Text('Resume'),
            ),
        ],
      ),
    ),
  );

  Widget _shop() => Material(
    color: Colors.white,
    child: SingleChildScrollView(
      padding: const EdgeInsets.all(14),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Row(
            children: [
              const Expanded(
                child: Text(
                  'Monkey squad',
                  style: TextStyle(fontSize: 18, fontWeight: FontWeight.w700),
                ),
              ),
              if (session.buying != null || session.selected != null)
                IconButton(
                  onPressed: () => _command(session.cancel),
                  tooltip: 'Clear selection',
                  icon: const Icon(Icons.close),
                  visualDensity: VisualDensity.compact,
                ),
            ],
          ),
          const SizedBox(height: 10),
          LayoutBuilder(
            builder: (context, constraints) => Wrap(
              spacing: 8,
              runSpacing: 8,
              children: [
                for (final spec in towerSpecs)
                  SizedBox(
                    width: (constraints.maxWidth - 8) / 2,
                    child: _ShopItem(
                      spec: spec,
                      selected: session.buying == spec,
                      enabled: session.editable && session.money >= spec.cost,
                      onTap: () => _command(() => session.choose(spec)),
                    ),
                  ),
              ],
            ),
          ),
          const SizedBox(height: 14),
          const Divider(),
          if (session.selected case final monkey?)
            _inspector(monkey)
          else if (session.buying case final spec?) ...[
            Text(
              spec.name,
              style: const TextStyle(fontSize: 18, fontWeight: FontWeight.w700),
            ),
            const SizedBox(height: 6),
            Text(spec.role),
            const SizedBox(height: 10),
            ..._statRows(spec, 1, null),
          ] else ...[
            const Text(
              'Squad overview',
              style: TextStyle(fontSize: 16, fontWeight: FontWeight.w700),
            ),
            const SizedBox(height: 8),
            Text('${session.towers.length} monkeys deployed'),
            Text('${session.popped} balloons popped'),
          ],
        ],
      ),
    ),
  );

  Widget _inspector(Monkey monkey) {
    final maxed = monkey.level >= TowerConfig.maxLevel;
    final cost = maxed ? 0 : monkey.spec.upgradeCost(monkey.level);
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Row(
          children: [
            Expanded(
              child: Text(
                monkey.spec.name,
                style: const TextStyle(
                  fontSize: 18,
                  fontWeight: FontWeight.w700,
                ),
              ),
            ),
            Text(
              'L${monkey.level}',
              style: const TextStyle(
                color: _green,
                fontWeight: FontWeight.w800,
              ),
            ),
          ],
        ),
        const SizedBox(height: 6),
        Text(monkey.spec.role),
        const SizedBox(height: 12),
        Row(
          children: [
            const Expanded(
              child: Text(
                'Stats',
                style: TextStyle(fontWeight: FontWeight.w600),
              ),
            ),
            Text(
              maxed
                  ? 'L${TowerConfig.maxLevel} / MAX'
                  : 'L${monkey.level}  >  L${monkey.level + 1}',
              style: const TextStyle(color: _green),
            ),
          ],
        ),
        const SizedBox(height: 8),
        ..._statRows(
          monkey.spec,
          monkey.level,
          maxed ? null : monkey.level + 1,
        ),
        if (monkey.spec.kind != TowerKind.farm) ...[
          const SizedBox(height: 12),
          DropdownButtonFormField<TargetMode>(
            key: ValueKey('${monkey.id}-${monkey.targetMode.name}'),
            initialValue: monkey.targetMode,
            isExpanded: true,
            decoration: const InputDecoration(
              labelText: 'Target mode',
              border: OutlineInputBorder(),
              isDense: true,
            ),
            items: [
              for (final mode in TargetMode.values)
                DropdownMenuItem(
                  value: mode,
                  child: Text(switch (mode) {
                    TargetMode.first => 'First',
                    TargetMode.strongest => 'Strongest',
                    TargetMode.nearest => 'Nearest',
                  }),
                ),
            ],
            onChanged: session.editable
                ? (mode) => _command(() {
                    if (mode != null) {
                      session.setTargetMode(mode);
                    }
                  })
                : null,
          ),
        ],
        const SizedBox(height: 14),
        SizedBox(
          width: double.infinity,
          child: FilledButton.icon(
            onPressed: !maxed && session.editable && session.money >= cost
                ? () => _command(() {
                    session.upgrade();
                  })
                : null,
            icon: Icon(maxed ? Icons.verified : Icons.upgrade),
            label: Text(maxed ? 'Max Level' : 'Upgrade  \$$cost'),
          ),
        ),
        const SizedBox(height: 8),
        SizedBox(
          width: double.infinity,
          child: OutlinedButton.icon(
            onPressed: session.editable
                ? () => _command(() {
                    session.sell();
                  })
                : null,
            icon: const Icon(Icons.sell_outlined),
            label: Text('Sell  \$${monkey.refund}'),
          ),
        ),
      ],
    );
  }

  List<Widget> _statRows(TowerSpec spec, int current, int? next) {
    final rows = <Widget>[];
    if (spec.kind == TowerKind.farm) {
      rows.add(
        _statRow(
          'Income / ${_number(TowerConfig.farmInterval)}s',
          '\$${spec.incomeAt(current)}',
          next == null ? null : '\$${spec.incomeAt(next)}',
        ),
      );
    } else {
      rows.add(
        _statRow(
          'Damage',
          _number(spec.damageAt(current)),
          next == null ? null : _number(spec.damageAt(next)),
        ),
      );
      rows.add(
        _statRow(
          'Interval',
          '${_number(spec.intervalAt(current))}s',
          next == null ? null : '${_number(spec.intervalAt(next))}s',
        ),
      );
      rows.add(
        _statRow(
          'Range',
          _number(spec.rangeAt(current)),
          next == null ? null : _number(spec.rangeAt(next)),
        ),
      );
      if (spec.kind == TowerKind.bomb) {
        rows.add(
          _statRow(
            'Splash radius',
            _number(TowerConfig.splashRadii[current - 1]),
            next == null ? null : _number(TowerConfig.splashRadii[next - 1]),
          ),
        );
      }
      if (spec.kind == TowerKind.frost) {
        rows.add(
          _statRow(
            'Slow',
            '${_number(100 * (TowerConfig.slowFraction + (current - 1) * TowerConfig.slowFractionPerLevel))}%',
            next == null
                ? null
                : '${_number(100 * (TowerConfig.slowFraction + (next - 1) * TowerConfig.slowFractionPerLevel))}%',
          ),
        );
        rows.add(
          _statRow(
            'Slow duration',
            '${_number(TowerConfig.slowDuration + (current - 1) * TowerConfig.slowDurationPerLevel)}s',
            next == null
                ? null
                : '${_number(TowerConfig.slowDuration + (next - 1) * TowerConfig.slowDurationPerLevel)}s',
          ),
        );
      }
      if (spec.kind == TowerKind.support) {
        rows.add(
          _statRow(
            'Aura radius',
            _number(spec.rangeAt(current)),
            next == null ? null : _number(spec.rangeAt(next)),
          ),
        );
        rows.add(
          _statRow(
            'Attack bonus',
            '${_number(100 * (TowerConfig.supportAttackSpeedBonus + (current - 1) * TowerConfig.supportAttackSpeedPerLevel))}%',
            next == null
                ? null
                : '${_number(100 * (TowerConfig.supportAttackSpeedBonus + (next - 1) * TowerConfig.supportAttackSpeedPerLevel))}%',
          ),
        );
      }
      if (spec.kind == TowerKind.laser) {
        rows.add(
          _statRow(
            'Piercing beam',
            _number(spec.damageAt(current)),
            next == null ? null : _number(spec.damageAt(next)),
          ),
        );
      }
      if (spec.kind == TowerKind.poison) {
        rows.add(
          _statRow(
            'Toxin burst',
            _number(
              spec.damageAt(current) *
                  TowerConfig.poisonInitialDamageMultiplier,
            ),
            next == null
                ? null
                : _number(
                    spec.damageAt(next) *
                        TowerConfig.poisonInitialDamageMultiplier,
                  ),
          ),
        );
        rows.add(
          _statRow(
            'Toxin duration',
            '${_number(TowerConfig.poisonDuration + current * TowerConfig.poisonDurationPerLevel)}s',
            next == null
                ? null
                : '${_number(TowerConfig.poisonDuration + next * TowerConfig.poisonDurationPerLevel)}s',
          ),
        );
      }
    }
    return rows;
  }

  Widget _statRow(String label, String current, String? next) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 3),
      child: Row(
        children: [
          Expanded(
            child: Text(
              label,
              style: const TextStyle(color: Color(0xFF66756D)),
            ),
          ),
          Text(current, style: const TextStyle(fontWeight: FontWeight.w600)),
          if (next != null) ...[
            const Padding(
              padding: EdgeInsets.symmetric(horizontal: 6),
              child: Icon(Icons.arrow_forward, size: 12),
            ),
            Text(
              next,
              style: const TextStyle(
                color: _green,
                fontWeight: FontWeight.w600,
              ),
            ),
          ],
        ],
      ),
    );
  }

  Widget _status() {
    final text = session.message.isNotEmpty
        ? session.message
        : session.buying != null
        ? '${session.buying!.name} selected'
        : session.phase == SessionPhase.ready
        ? 'Ready for wave ${session.wave + 1}'
        : session.phase == SessionPhase.running
        ? 'Defense in progress'
        : session.phase == SessionPhase.paused
        ? 'Paused'
        : 'Campaign complete';
    return ColoredBox(
      color: Colors.white,
      child: SizedBox(
        height: 32,
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 14),
          child: Row(
            children: [
              Expanded(
                child: Text(
                  text,
                  maxLines: 1,
                  overflow: TextOverflow.ellipsis,
                  style: TextStyle(
                    fontSize: 12,
                    color: session.message.isNotEmpty
                        ? const Color(0xFFB4423D)
                        : _ink,
                  ),
                ),
              ),
              if (widget.settings.autoStart)
                const Text(
                  'Auto-start ON',
                  style: TextStyle(fontSize: 12, color: _green),
                ),
            ],
          ),
        ),
      ),
    );
  }
}

String _number(num value) =>
    value.toStringAsFixed(2).replaceFirst(RegExp(r'\.?0+$'), '');

class _ActionDialog extends StatelessWidget {
  const _ActionDialog({
    required this.title,
    required this.subtitle,
    required this.actions,
    this.emblem,
  });
  final String title;
  final String subtitle;
  final IconData? emblem;
  final List<(_GameAction, IconData, String)> actions;
  @override
  Widget build(BuildContext context) {
    return PopScope(
      canPop: false,
      child: Dialog(
        child: ConstrainedBox(
          constraints: const BoxConstraints(maxWidth: 390),
          child: SingleChildScrollView(
            padding: const EdgeInsets.all(24),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                if (emblem != null)
                  Padding(
                    padding: const EdgeInsets.only(bottom: 14),
                    child: Icon(emblem, size: 48, color: _green),
                  ),
                Text(
                  title,
                  textAlign: TextAlign.center,
                  style: const TextStyle(
                    fontSize: 26,
                    fontWeight: FontWeight.w700,
                  ),
                ),
                const SizedBox(height: 10),
                Text(subtitle, textAlign: TextAlign.center),
                const SizedBox(height: 22),
                for (var index = 0; index < actions.length; index++)
                  Padding(
                    padding: const EdgeInsets.only(bottom: 8),
                    child: index == 0
                        ? FilledButton.icon(
                            onPressed: () =>
                                Navigator.pop(context, actions[index].$1),
                            icon: Icon(actions[index].$2),
                            label: Text(actions[index].$3),
                          )
                        : OutlinedButton.icon(
                            onPressed: () =>
                                Navigator.pop(context, actions[index].$1),
                            icon: Icon(actions[index].$2),
                            label: Text(actions[index].$3),
                          ),
                  ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class _Counter extends StatelessWidget {
  const _Counter({required this.icon, required this.text, required this.color});
  final IconData icon;
  final String text;
  final Color color;
  @override
  Widget build(BuildContext context) => Row(
    mainAxisSize: MainAxisSize.min,
    children: [
      Icon(icon, size: 18, color: color),
      const SizedBox(width: 5),
      Text(text, style: const TextStyle(fontWeight: FontWeight.w700)),
    ],
  );
}

class _ShopItem extends StatelessWidget {
  const _ShopItem({
    required this.spec,
    required this.selected,
    required this.enabled,
    required this.onTap,
  });
  final TowerSpec spec;
  final bool selected;
  final bool enabled;
  final VoidCallback onTap;
  @override
  Widget build(BuildContext context) => Tooltip(
    message: '${spec.name}: ${spec.role}',
    child: Semantics(
      button: true,
      selected: selected,
      enabled: enabled,
      child: Material(
        color: selected ? const Color(0xFFE3F2EC) : _paper,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(6),
          side: BorderSide(
            color: selected ? _green : const Color(0xFFE0E5E1),
            width: selected ? 2 : 1,
          ),
        ),
        clipBehavior: Clip.antiAlias,
        child: InkWell(
          onTap: enabled ? onTap : null,
          child: SizedBox(
            height: 112,
            child: Padding(
              padding: const EdgeInsets.all(8),
              child: Column(
                children: [
                  Opacity(
                    opacity: enabled ? 1 : .45,
                    child: _Portrait(kind: spec.kind, size: 42),
                  ),
                  const SizedBox(height: 5),
                  Text(
                    spec.name,
                    maxLines: 1,
                    overflow: TextOverflow.ellipsis,
                    style: const TextStyle(
                      fontSize: 12,
                      fontWeight: FontWeight.w600,
                    ),
                  ),
                  const SizedBox(height: 3),
                  Text(
                    '\$${spec.cost}',
                    style: TextStyle(
                      fontSize: 13,
                      fontWeight: FontWeight.w700,
                      color: enabled ? _green : const Color(0xFF89938E),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    ),
  );
}

class _Portrait extends StatelessWidget {
  const _Portrait({required this.kind, this.size = 48});
  final TowerKind kind;
  final double size;
  @override
  Widget build(BuildContext context) => SizedBox.square(
    dimension: size,
    child: Stack(
      children: [
        Positioned.fill(
          child: CustomPaint(
            painter: _MonkeyPainter(towerSpecs[kind.index].color),
          ),
        ),
        Positioned(
          right: 0,
          bottom: 0,
          child: DecoratedBox(
            decoration: BoxDecoration(
              color: towerSpecs[kind.index].color,
              shape: BoxShape.circle,
            ),
            child: Padding(
              padding: EdgeInsets.all(size * .05),
              child: Icon(
                switch (kind) {
                  TowerKind.dart => Icons.near_me,
                  TowerKind.rapid => Icons.bolt,
                  TowerKind.bomb => Icons.local_fire_department,
                  TowerKind.frost => Icons.ac_unit,
                  TowerKind.sniper => Icons.my_location,
                  TowerKind.farm => Icons.eco,
                  TowerKind.laser => Icons.wb_sunny_outlined,
                  TowerKind.support => Icons.sports,
                  TowerKind.poison => Icons.science_outlined,
                },
                color: Colors.white,
                size: size * .25,
              ),
            ),
          ),
        ),
      ],
    ),
  );
}

class _MonkeyPainter extends CustomPainter {
  const _MonkeyPainter(this.accent);
  final Color accent;
  @override
  void paint(Canvas canvas, Size size) {
    canvas.save();
    canvas.scale(size.width / 100, size.height / 100);
    final paint = Paint()..color = const Color(0xFF85624C);
    canvas.drawCircle(const Offset(18, 45), 15, paint);
    canvas.drawCircle(const Offset(82, 45), 15, paint);
    paint.color = const Color(0xFFE5C299);
    canvas.drawCircle(const Offset(18, 45), 9, paint);
    canvas.drawCircle(const Offset(82, 45), 9, paint);
    paint.color = const Color(0xFF85624C);
    canvas.drawOval(const Rect.fromLTWH(18, 12, 64, 77), paint);
    paint.color = const Color(0xFFE5C299);
    canvas.drawOval(const Rect.fromLTWH(26, 33, 48, 48), paint);
    paint.color = accent;
    canvas.drawRRect(
      RRect.fromRectAndRadius(
        const Rect.fromLTWH(20, 23, 60, 12),
        const Radius.circular(3),
      ),
      paint,
    );
    paint.color = _ink;
    canvas.drawCircle(const Offset(38, 49), 4, paint);
    canvas.drawCircle(const Offset(62, 49), 4, paint);
    canvas.drawOval(const Rect.fromLTWH(45, 60, 10, 6), paint);
    paint
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2.5;
    canvas.drawArc(const Rect.fromLTWH(37, 61, 26, 14), .2, 2.7, false, paint);
    canvas.restore();
  }

  @override
  bool shouldRepaint(covariant _MonkeyPainter oldDelegate) =>
      accent != oldDelegate.accent;
}

class _MapPainter extends CustomPainter {
  const _MapPainter(this.level);
  final LevelDefinition level;
  @override
  void paint(Canvas canvas, Size size) {
    final cellWidth = size.width / level.columns;
    final cellHeight = size.height / level.rows;
    final paint = Paint();
    for (var row = 0; row < level.rows; row++) {
      for (var column = 0; column < level.columns; column++) {
        paint.color = switch (level.terrain((column: column, row: row))) {
          Terrain.road => const Color(0xFFC5C7AD),
          Terrain.water => const Color(0xFF65B9D0),
          Terrain.rock => const Color(0xFF7C9180),
          Terrain.grass =>
            (column + row) % 2 == 0
                ? const Color(0xFF3B9673)
                : const Color(0xFF37916E),
        };
        canvas.drawRect(
          Rect.fromLTWH(
            column * cellWidth,
            row * cellHeight,
            cellWidth + .5,
            cellHeight + .5,
          ),
          paint,
        );
      }
    }
    for (final entry in [
      (level.road.first, const Color(0xFFF4C64D)),
      (level.road.last, const Color(0xFFE86766)),
    ]) {
      paint.color = entry.$2;
      canvas.drawCircle(
        Offset(
          (entry.$1.column + .5) * cellWidth,
          (entry.$1.row + .5) * cellHeight,
        ),
        cellWidth * .4,
        paint,
      );
    }
    for (final placement in [(4, 6, 0), (12, 8, 2), (20, 10, 3)]) {
      canvas.save();
      canvas.translate(placement.$1 * cellWidth, placement.$2 * cellHeight);
      _MonkeyPainter(
        towerSpecs[placement.$3].color,
      ).paint(canvas, Size(cellWidth * 1.7, cellHeight * 1.7));
      canvas.restore();
    }
    for (var index = 0; index < 5; index++) {
      final point = level.positionAt((index * 4 + 2).toDouble());
      paint.color = enemySpecs[index].color;
      canvas.drawOval(
        Rect.fromCenter(
          center: Offset(point.dx * cellWidth, point.dy * cellHeight),
          width: cellWidth * .65,
          height: cellHeight * .85,
        ),
        paint,
      );
    }
  }

  @override
  bool shouldRepaint(covariant _MapPainter oldDelegate) =>
      level != oldDelegate.level;
}
