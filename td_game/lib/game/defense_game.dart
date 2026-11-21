import 'dart:math' as math;

import 'package:flame/components.dart';
import 'package:flame/events.dart';
import 'package:flame/game.dart';
import 'package:flame_audio/flame_audio.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:flutter/painting.dart';
import 'package:flutter/widgets.dart' show KeyEventResult;

import '../services/settings_store.dart';
import 'model.dart';

class DefenseGame extends FlameGame with KeyboardEvents {
  DefenseGame({
    required this.session,
    required this.settings,
    required this.onChanged,
    this.audioEnabled = true,
  }) : super(
         camera: CameraComponent.withFixedResolution(
           width: session.level.columns * tileSize,
           height: session.level.rows * tileSize,
         ),
       );

  static const double tileSize = 32;
  final GameSession session;
  DefenseSettings settings;
  final VoidCallback onChanged;
  final bool audioEnabled;
  final Map<Terrain, Sprite> terrainSprites = {};
  final Map<String, AudioPool> _sounds = {};
  double _accumulator = 0;
  int _revision = -1;
  bool _disposed = false;

  @override
  Color backgroundColor() => const Color(0xFFDAE8DE);

  @override
  Future<void> onLoad() async {
    images.prefix = 'assets/PNG/Default size/';
    const tileIds = {
      Terrain.grass: '024',
      Terrain.road: '050',
      Terrain.water: '074',
      Terrain.rock: '024',
    };
    for (final entry in tileIds.entries) {
      terrainSprites[entry.key] = Sprite(
        await images.load('towerDefense_tile${entry.value}.png'),
      );
    }
    camera.viewfinder.position = Vector2(
      session.level.columns * tileSize / 2,
      session.level.rows * tileSize / 2,
    );
    world.add(_Board(this));
    if (audioEnabled) {
      for (final sound in ['buy', 'pop', 'win', 'lose']) {
        try {
          _sounds[sound] = await FlameAudio.createPool(
            '$sound.wav',
            minPlayers: 1,
            maxPlayers: sound == 'pop' ? 4 : 1,
          );
        } catch (error) {
          debugPrint('Sound unavailable: $sound ($error)');
        }
      }
      session.onSound = (sound) {
        if (settings.volume > 0 && !_disposed) {
          _sounds[sound]?.start(volume: settings.volume);
        }
      };
    }
  }

  void notify() {
    if (_disposed) return;
    _revision = session.revision;
    onChanged();
  }

  @override
  void update(double dt) {
    super.update(dt);
    session.autoStart = settings.autoStart;
    _accumulator += math.min(dt, .1) * session.speed;
    while (_accumulator >= 1 / 120) {
      session.update(1 / 120);
      _accumulator -= 1 / 120;
    }
    if (_revision != session.revision) notify();
  }

  @override
  KeyEventResult onKeyEvent(
    KeyEvent event,
    Set<LogicalKeyboardKey> keysPressed,
  ) {
    if (event is KeyDownEvent &&
        event.logicalKey == LogicalKeyboardKey.escape) {
      if (session.buying != null || session.selected != null) {
        session.cancel();
      } else {
        return KeyEventResult.ignored;
      }
      notify();
      return KeyEventResult.handled;
    }
    return KeyEventResult.ignored;
  }

  @override
  void dispose() {
    if (_disposed) return;
    _disposed = true;
    session.onSound = null;
    for (final sound in _sounds.values) {
      sound.dispose();
    }
    _sounds.clear();
    super.dispose();
  }
}

class _Board extends PositionComponent
    with TapCallbacks, SecondaryTapCallbacks, HoverCallbacks {
  _Board(this.game)
    : super(
        size: Vector2(
          game.session.level.columns * DefenseGame.tileSize,
          game.session.level.rows * DefenseGame.tileSize,
        ),
      );
  final DefenseGame game;
  Cell? hoverCell;
  static const tile = DefenseGame.tileSize;
  GameSession get session => game.session;
  Cell _cell(Vector2 point) =>
      (column: (point.x / tile).floor(), row: (point.y / tile).floor());

  @override
  void onTapUp(TapUpEvent event) {
    session.place(_cell(event.localPosition));
    game.notify();
  }

  @override
  void onSecondaryTapUp(SecondaryTapUpEvent event) {
    session.cancel();
    game.notify();
  }

  @override
  void onPointerMove(PointerMoveEvent event) {
    hoverCell = _cell(event.localPosition);
  }

  @override
  void onHoverExit() {
    hoverCell = null;
  }

  @override
  void render(Canvas canvas) {
    final level = session.level;
    for (var row = 0; row < level.rows; row++) {
      for (var column = 0; column < level.columns; column++) {
        final cell = (column: column, row: row);
        final terrain = level.terrain(cell);
        game.terrainSprites[terrain]?.render(
          canvas,
          position: Vector2(column * tile, row * tile),
          size: Vector2.all(tile),
        );
        if (terrain == Terrain.water) {
          canvas.drawRect(
            Rect.fromLTWH(column * tile, row * tile, tile, tile),
            Paint()..color = const Color(0xFF459FC4).withValues(alpha: .8),
          );
          canvas.drawLine(
            Offset(column * tile + 6, row * tile + 18),
            Offset(column * tile + 24, row * tile + 18),
            Paint()
              ..color = const Color(0xFF83D1E1)
              ..strokeWidth = 1.5,
          );
        }
        if (terrain == Terrain.rock) {
          final center = Offset((column + .5) * tile, (row + .5) * tile);
          canvas.drawOval(
            Rect.fromCenter(center: center, width: 23, height: 19),
            Paint()..color = const Color(0xFF7E9491),
          );
          canvas.drawOval(
            Rect.fromCenter(
              center: center.translate(-2, -3),
              width: 16,
              height: 10,
            ),
            Paint()..color = const Color(0xFFB0C1B7),
          );
        }
        if (game.settings.grid) {
          canvas.drawRect(
            Rect.fromLTWH(column * tile, row * tile, tile, tile),
            Paint()
              ..color = const Color(0x33213D32)
              ..style = PaintingStyle.stroke
              ..strokeWidth = .5,
          );
        }
      }
    }
    _marker(canvas, level.road.first, const Color(0xFF146C56), 'IN');
    _marker(canvas, level.road.last, const Color(0xFFD14945), 'OUT');
    final selected = session.selected;
    if (selected != null && selected.range > 0) {
      _range(canvas, selected.position, selected.range, selected.spec.color);
    }
    for (final monkey in session.towers) {
      drawMonkey(
        canvas,
        monkey.position * tile,
        tile,
        monkey.spec,
        monkey.angle,
        monkey.level,
        selected == monkey,
      );
    }
    for (final enemy in session.enemies) {
      if (!enemy.resolved) _balloon(canvas, enemy);
    }
    for (final shot in session.shots) {
      final center = shot.position * tile;
      final color = shot.kind == TowerKind.bomb
          ? const Color(0xFF323F40)
          : const Color(0xFFFFF1B8);
      canvas.drawCircle(
        center,
        shot.kind == TowerKind.bomb ? 3.5 : 1.8,
        Paint()..color = color,
      );
    }
    for (final effect in session.effects) {
      final progress = 1 - effect.life / effect.duration;
      final paint = Paint()
        ..color = effect.color.withValues(alpha: 1 - progress)
        ..style = PaintingStyle.stroke
        ..strokeWidth = 2;
      if (effect.lineEnd != null) {
        canvas.drawLine(effect.position * tile, effect.lineEnd! * tile, paint);
      } else if (effect.label != null) {
        _text(
          canvas,
          effect.label!,
          effect.position * tile - Offset(0, progress * 25),
          effect.color,
          12,
        );
      } else {
        canvas.drawCircle(
          effect.position * tile,
          effect.radius * tile * progress,
          paint,
        );
      }
    }
    final buying = session.buying;
    final cell = hoverCell;
    if (buying != null && cell != null && level.contains(cell)) {
      final valid = session.canPlace(cell) && session.money >= buying.cost;
      final center = Offset(cell.column + .5, cell.row + .5);
      final color = valid ? const Color(0xFFFAF9DE) : const Color(0xFFEF4F54);
      if (buying.range > 0) _range(canvas, center, buying.range, color);
      canvas.drawRect(
        Rect.fromLTWH(cell.column * tile, cell.row * tile, tile, tile),
        Paint()..color = color.withValues(alpha: .4),
      );
      drawMonkey(canvas, center * tile, tile, buying, 0, 1, false);
    }
  }

  void _range(Canvas canvas, Offset center, double radius, Color color) {
    canvas.drawCircle(
      center * tile,
      radius * tile,
      Paint()..color = color.withValues(alpha: .09),
    );
    canvas.drawCircle(
      center * tile,
      radius * tile,
      Paint()
        ..color = color.withValues(alpha: .65)
        ..style = PaintingStyle.stroke
        ..strokeWidth = 1,
    );
  }

  void _marker(Canvas canvas, Cell cell, Color color, String label) {
    final center = Offset((cell.column + .5) * tile, (cell.row + .5) * tile);
    canvas.drawCircle(center, 12, Paint()..color = color);
    _text(canvas, label, center, const Color(0xFFFFFFFF), 8);
  }

  void _balloon(Canvas canvas, Balloon enemy) {
    final center = session.level.positionAt(enemy.distance) * tile;
    canvas.drawOval(
      Rect.fromCenter(center: center.translate(1, 3), width: 15, height: 17),
      Paint()..color = const Color(0x33233F35),
    );
    canvas.drawOval(
      Rect.fromCenter(center: center, width: 14, height: 17),
      Paint()..color = enemy.spec.color,
    );
    canvas.drawOval(
      Rect.fromCenter(center: center.translate(-2, -4), width: 3, height: 5),
      Paint()..color = const Color(0x99FFFFFF),
    );
    final knot = Path()
      ..moveTo(center.dx, center.dy + 7)
      ..lineTo(center.dx - 2, center.dy + 11)
      ..lineTo(center.dx + 2, center.dy + 11)
      ..close();
    canvas.drawPath(knot, Paint()..color = enemy.spec.color);
    if (enemy.tier == 2) {
      _text(canvas, '+', center, const Color(0xFFFFFFFF), 12);
    }
    if (enemy.tier == 3) {
      canvas.drawOval(
        Rect.fromCenter(center: center, width: 10, height: 13),
        Paint()
          ..color = const Color(0xFF937735)
          ..style = PaintingStyle.stroke
          ..strokeWidth = 2,
      );
    }
    if (enemy.shield > 0) {
      canvas.drawCircle(
        center,
        11,
        Paint()
          ..color = const Color(0xCCDBA5FF)
          ..style = PaintingStyle.stroke
          ..strokeWidth = 1.5,
      );
    }
    if (enemy.slow > 0) {
      canvas.drawCircle(
        center,
        10,
        Paint()
          ..color = const Color(0xFF9DEAF9)
          ..style = PaintingStyle.stroke
          ..strokeWidth = 1,
      );
    }
    if (enemy.health < enemy.spec.health) {
      canvas.drawRect(
        Rect.fromLTWH(center.dx - 7, center.dy - 13, 14, 2),
        Paint()..color = const Color(0xFF293A34),
      );
      canvas.drawRect(
        Rect.fromLTWH(
          center.dx - 7,
          center.dy - 13,
          14 * (enemy.health / enemy.spec.health).clamp(0, 1),
          2,
        ),
        Paint()..color = const Color(0xFFC8F1B0),
      );
    }
  }
}

void drawMonkey(
  Canvas canvas,
  Offset center,
  double size,
  TowerSpec spec,
  double angle,
  int level,
  bool selected,
) {
  canvas.save();
  canvas.translate(center.dx, center.dy);
  canvas.scale(size / 32);
  canvas.drawCircle(
    Offset.zero,
    13.5,
    Paint()
      ..color = selected ? const Color(0xFFFFF3A3) : const Color(0xFF365E4D),
  );
  canvas.drawCircle(Offset.zero, 11.5, Paint()..color = spec.color);
  final tail = Path()
    ..moveTo(-5, 6)
    ..quadraticBezierTo(-12, 11, -10, 3);
  canvas.drawPath(
    tail,
    Paint()
      ..color = const Color(0xFF73513F)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 2.5,
  );
  canvas.save();
  canvas.rotate(angle);
  canvas.drawOval(
    const Rect.fromLTWH(-9, -8, 10, 16),
    Paint()..color = const Color(0xFF986345),
  );
  canvas.drawCircle(
    const Offset(0, -7),
    3.2,
    Paint()..color = const Color(0xFF986345),
  );
  canvas.drawCircle(
    const Offset(0, 7),
    3.2,
    Paint()..color = const Color(0xFF986345),
  );
  canvas.drawCircle(Offset.zero, 7, Paint()..color = const Color(0xFF986345));
  canvas.drawOval(
    const Rect.fromLTWH(-1, -5, 7, 10),
    Paint()..color = const Color(0xFFEFC797),
  );
  canvas.drawCircle(
    const Offset(3, -2.5),
    1,
    Paint()..color = const Color(0xFF28352F),
  );
  canvas.drawCircle(
    const Offset(3, 2.5),
    1,
    Paint()..color = const Color(0xFF28352F),
  );
  final equipment = Paint()..color = spec.color;
  if (spec.kind == TowerKind.farm) {
    final banana = Path()
      ..moveTo(5, -5)
      ..quadraticBezierTo(14, 0, 6, 5);
    canvas.drawPath(
      banana,
      Paint()
        ..color = const Color(0xFFFFDC53)
        ..style = PaintingStyle.stroke
        ..strokeWidth = 3,
    );
  } else {
    canvas.drawRRect(
      RRect.fromRectAndRadius(
        Rect.fromLTWH(5, -2, spec.kind == TowerKind.sniper ? 8 : 6, 4),
        const Radius.circular(1),
      ),
      equipment,
    );
    if (spec.kind == TowerKind.bomb) {
      canvas.drawCircle(
        const Offset(9, 0),
        3,
        Paint()..color = const Color(0xFF354644),
      );
    }
    if (spec.kind == TowerKind.frost) {
      canvas.drawCircle(
        const Offset(10, 0),
        2.5,
        Paint()..color = const Color(0xFFDAF9FF),
      );
    }
    if (spec.kind == TowerKind.laser) {
      canvas.drawCircle(
        const Offset(11, 0),
        2,
        Paint()..color = const Color(0xFFD9C2FF),
      );
    }
    if (spec.kind == TowerKind.support) {
      canvas.drawRRect(
        RRect.fromRectAndRadius(
          const Rect.fromLTWH(4, -5, 9, 10),
          const Radius.circular(2),
        ),
        Paint()..color = const Color(0xFFDCA06A),
      );
    }
    if (spec.kind == TowerKind.poison) {
      canvas.drawCircle(
        const Offset(10, 0),
        2.5,
        Paint()..color = const Color(0xFF86D76A),
      );
    }
  }
  canvas.restore();
  for (var index = 0; index < level; index++) {
    canvas.drawCircle(
      Offset((index - (level - 1) / 2) * 3, 11),
      1,
      Paint()..color = const Color(0xFFFFE496),
    );
  }
  canvas.restore();
}

void _text(
  Canvas canvas,
  String value,
  Offset center,
  Color color,
  double size,
) {
  final painter = TextPainter(
    text: TextSpan(
      text: value,
      style: TextStyle(
        color: color,
        fontSize: size,
        fontWeight: FontWeight.bold,
      ),
    ),
    textDirection: TextDirection.ltr,
  )..layout();
  painter.paint(canvas, center - Offset(painter.width / 2, painter.height / 2));
}
