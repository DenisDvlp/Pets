import 'dart:ui';
import 'dart:math' as math;
import 'package:flutter/foundation.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/game/model.dart';

const step = 1 / 120;

final combatLevel = LevelDefinition('Combat fixture', '', 24, 16, 23, [
  (column: 0, row: 3),
  (column: 7, row: 3),
  (column: 7, row: 10),
  (column: 17, row: 10),
  (column: 17, row: 5),
  (column: 23, row: 5),
]);

const buildCells = <String, List<Cell>>{
  'meadow-bend': [
    (column: 6, row: 4),
    (column: 8, row: 9),
    (column: 10, row: 6),
    (column: 10, row: 9),
    (column: 14, row: 9),
  ],
  'river-switchback': [
    (column: 9, row: 5),
    (column: 6, row: 10),
    (column: 9, row: 8),
    (column: 6, row: 14),
    (column: 20, row: 11),
  ],
  'mountain-pass': [
    (column: 6, row: 9),
    (column: 9, row: 5),
    (column: 11, row: 5),
    (column: 14, row: 7),
    (column: 18, row: 10),
  ],
  'desert-oasis': [
    (column: 4, row: 8),
    (column: 8, row: 7),
    (column: 8, row: 13),
    (column: 17, row: 13),
    (column: 19, row: 9),
  ],
  'crystal-crossroads': [
    (column: 5, row: 7),
    (column: 11, row: 6),
    (column: 11, row: 12),
    (column: 13, row: 8),
    (column: 17, row: 8),
  ],
  'volcano-loop': [
    (column: 4, row: 8),
    (column: 8, row: 7),
    (column: 8, row: 12),
    (column: 10, row: 12),
    (column: 14, row: 10),
  ],
  'twin-rivers': [
    (column: 7, row: 4),
    (column: 9, row: 7),
    (column: 10, row: 9),
    (column: 10, row: 13),
    (column: 20, row: 9),
  ],
};

GameSession combatSession() => GameSession(combatLevel)
  ..phase = SessionPhase.running
  ..wave = 1;

Balloon addEnemy(GameSession session, int tier, {double distance = 5}) {
  final enemy = Balloon(1000 + session.enemies.length, tier)
    ..distance = distance;
  session.enemies.add(enemy);
  return enemy;
}

Monkey addTower(
  GameSession session,
  TowerKind kind, {
  Cell cell = (column: 5, row: 2),
  int level = 1,
}) {
  final tower = Monkey(
    session.towers.length + 1,
    towerSpecs.firstWhere((spec) => spec.kind == kind),
    cell,
  )..level = level;
  session.towers.add(tower);
  return tower;
}

void advance(GameSession session, double seconds) {
  final ticks = (seconds / step).round();
  for (var tick = 0; tick < ticks; tick++) {
    session.update(step);
  }
}

void aimAt(GameSession session, Monkey tower, Balloon enemy) {
  final delta = session.level.positionAt(enemy.distance) - tower.position;
  tower.angle = math.atan2(delta.dy, delta.dx);
}

void main() {
  test('maps are bounded and paths move continuously through corners', () {
    for (final level in levels) {
      expect(level.columns, lessThanOrEqualTo(30));
      expect(level.rows, lessThanOrEqualTo(20));
      expect(level.road.toSet().length, level.road.length);
      for (var index = 1; index < level.road.length; index++) {
        expect(
          (level.positionAt(index.toDouble()) - level.positionAt(index - 1.0))
              .distance,
          1,
        );
        expect(
          (level.positionAt(index - .001) - level.positionAt(index + .001))
              .distance,
          lessThan(.003),
        );
      }
    }
    expect(levels.first.positionAt(.5), const Offset(1, 3.5));
  });
  test('placement and upgrading never double spend or exceed five levels', () {
    final session = GameSession(levels.first);
    session.choose(towerSpecs.first);
    expect(session.place((column: 1, row: 3)), false);
    expect(session.money, 650);
    expect(session.place((column: 1, row: 2)), true);
    expect(session.money, 550);
    session.money = 10000;
    for (var index = 0; index < 4; index++) {
      expect(session.upgrade(), true);
    }
    expect(session.selected!.level, 5);
    final money = session.money;
    expect(session.upgrade(), false);
    expect(session.money, money);
    expect(session.sell(), true);
    expect(session.sell(), false);
  });

  test('invalid levels reject dimensions, wave counts, and routes', () {
    for (final dimensions in [
      (0, 4),
      (-1, 4),
      (4, 0),
      (4, -1),
      (31, 4),
      (4, 21),
    ]) {
      expect(
        () => LevelDefinition('Invalid', '', dimensions.$1, dimensions.$2, 1, [
          (column: 0, row: 0),
        ]),
        throwsArgumentError,
      );
    }
    for (final waves in [0, -1]) {
      expect(
        () => LevelDefinition('Invalid', '', 4, 4, waves, [
          (column: 0, row: 0),
          (column: 3, row: 0),
        ]),
        throwsArgumentError,
      );
    }
    for (final corners in <List<Cell>>[
      [],
      [(column: 0, row: 0)],
      [(column: 0, row: 0), (column: 1, row: 1)],
      [(column: -1, row: 0), (column: 3, row: 0)],
      [(column: 0, row: 0), (column: 4, row: 0)],
      [(column: 0, row: 0), (column: 1000000000, row: 0)],
      [(column: 0, row: 0), (column: 0, row: 0)],
      [(column: 0, row: 0), (column: 3, row: 0), (column: 0, row: 0)],
    ]) {
      expect(
        () => LevelDefinition('Invalid', '', 4, 4, 1, corners),
        throwsArgumentError,
      );
    }
  });

  test(
    'armor subtracts one with a half damage floor; piercing bypasses it',
    () {
      final session = combatSession();
      final plated = addEnemy(session, 3);
      session.hit(plated, 1);
      expect(plated.health, 29.5);
      session.hit(plated, 3);
      expect(plated.health, 27.5);
      session.hit(plated, 3, pierceArmor: true);
      expect(plated.health, 24.5);
      expect(session.money, 650);
    },
  );

  test('each enemy moves at its catalog speed on fixed simulation steps', () {
    for (var tier = 0; tier < enemySpecs.length; tier++) {
      final session = combatSession();
      final enemy = addEnemy(session, tier);
      advance(session, 1);
      expect(enemy.distance, closeTo(5 + enemy.spec.speed, .0001));
    }
  });

  test('shield absorbs damage before health and never regenerates', () {
    final session = combatSession();
    final guardian = addEnemy(session, 4);
    session.hit(guardian, 6);
    expect(guardian.shield, 9);
    expect(guardian.health, 75);
    session.hit(guardian, 12, pierceArmor: true);
    expect(guardian.shield, 0);
    expect(guardian.health, 72);
    advance(session, 3);
    expect(guardian.shield, 0);
    expect(guardian.health, 72);
  });

  test('regeneration waits two seconds, resets on damage, and caps at max', () {
    final session = combatSession();
    final regenerator = addEnemy(session, 2);
    session.hit(regenerator, 3);
    advance(session, 1.9);
    expect(regenerator.health, 9);
    advance(session, .3);
    expect(regenerator.health, closeTo(9.2, .02));
    session.hit(regenerator, 1);
    final health = regenerator.health;
    advance(session, 1.9);
    expect(regenerator.health, health);
    advance(session, 6);
    expect(regenerator.health, regenerator.spec.health);
  });

  for (final tier in [3, 4]) {
    test('frost slows tier $tier without stacking and expires', () {
      final session = combatSession();
      final enemy = addEnemy(session, tier);
      final frost = addTower(session, TowerKind.frost, level: 5);
      aimAt(session, frost, enemy);
      session.update(0);
      expect(enemy.slow, tier == 4 ? .25 : .5);
      expect(enemy.slowTime, 3);
      frost.cooldown = 0;
      session.update(0);
      expect(enemy.slow, tier == 4 ? .25 : .5);
      session.towers.clear();
      final distance = enemy.distance;
      advance(session, 1);
      expect(
        enemy.distance - distance,
        closeTo(enemy.spec.speed * (tier == 4 ? .75 : .5), .001),
      );
      advance(session, 2.1);
      expect(enemy.slow, 0);
    });
  }

  test('weaker frost cannot shorten the strongest slow duration', () {
    final session = combatSession();
    final enemy = addEnemy(session, 4);
    final strong = addTower(session, TowerKind.frost, level: 5);
    aimAt(session, strong, enemy);
    session.update(0);
    session.towers.clear();
    final weak = addTower(session, TowerKind.frost);
    aimAt(session, weak, enemy);
    session.update(0);
    expect(enemy.slow, .25);
    expect(enemy.slowTime, 3);
    enemy.slowTime = 1;
    weak.cooldown = 0;
    session.update(0);
    expect(enemy.slow, .25);
    expect(enemy.slowTime, 1);
    enemy.slow = 0;
    enemy.slowTime = 0;
    weak.cooldown = 0;
    session.update(0);
    expect(enemy.slow, .15);
    expect(enemy.slowTime, 2);
    weak.level = 5;
    weak.cooldown = 0;
    session.update(0);
    expect(enemy.slow, .25);
    expect(enemy.slowTime, 3);
    enemy.slowTime = 1;
    weak.cooldown = 0;
    session.update(0);
    expect(enemy.slow, .25);
    expect(enemy.slowTime, 3);
  });

  test(
    'farms pay only in active waves, preserve fractions, reset next wave',
    () {
      final session = combatSession();
      addEnemy(session, 4, distance: 0);
      final farm = addTower(session, TowerKind.farm);
      advance(session, 7);
      expect(session.money, 650);
      session.pause();
      advance(session, 16);
      expect(farm.farmTime, closeTo(7, .0001));
      expect(session.money, 650);
      session.resume();
      session.selected = farm;
      expect(session.upgrade(), true);
      final afterUpgrade = session.money;
      advance(session, 1.01);
      expect(session.money, afterUpgrade + 35);
      session.phase = SessionPhase.ready;
      advance(session, 24);
      expect(session.money, afterUpgrade + 35);
      session.startWave();
      expect(farm.farmTime, 0);
      for (final phase in [SessionPhase.won, SessionPhase.lost]) {
        session.phase = phase;
        final elapsed = farm.farmTime;
        advance(session, 24);
        expect(farm.farmTime, elapsed);
        expect(session.money, afterUpgrade + 35);
      }
    },
  );

  test('kills and leaks resolve once with mutually exclusive rewards', () {
    final session = combatSession();
    final killed = addEnemy(session, 1);
    final leaked = addEnemy(
      session,
      4,
      distance: session.level.road.length - 1.001,
    );
    session.hit(killed, 100);
    session.hit(killed, 100);
    expect(session.money, 658);
    expect(session.popped, 1);
    session.update(step);
    expect(session.lives, 90);
    expect(session.enemies, isEmpty);
    session.hit(leaked, 100);
    session.hit(killed, 100);
    session.update(step);
    expect(session.money, 658);
    expect(session.popped, 1);
    expect(session.lives, 90);
  });

  test('all six towers have five levels and exact costs and refunds', () {
    for (final spec in towerSpecs) {
      final session = GameSession(levels.first)..money = 10000;
      session.choose(spec);
      expect(session.place((column: 1, row: 2)), true);
      var spent = spec.cost;
      for (var level = 1; level <= 5; level++) {
        expect(session.selected!.level, level);
        expect(
          spec.damageAt(level),
          spec.damage * [1, 1.5, 2.25, 3.5, 5][level - 1],
        );
        expect(
          spec.intervalAt(level),
          spec.interval * [1, .9, .8, .7, .6][level - 1],
        );
        expect(spec.rangeAt(level), spec.range + (level - 1) * .25);
        expect(spec.incomeAt(level), [20, 35, 55, 80, 120][level - 1]);
        if (level < 5) {
          final cost = (spec.cost * [.75, 1.1, 1.6, 2.3][level - 1]).ceil();
          expect(spec.upgradeCost(level), cost);
          expect(session.upgrade(), true);
          spent += cost;
        }
      }
      expect(session.selected!.spent, spent);
      expect(session.money, 10000 - spent);
      expect(session.upgrade(), false);
      expect(session.sell(), true);
      expect(session.money, 10000 - spent + (spent * .7).floor());
      expect(session.sell(), false);
    }
  });

  test(
    'economy commands reject unaffordable, paused, and terminal changes',
    () {
      final session = GameSession(levels.first);
      session.choose(towerSpecs.first);
      expect(session.place((column: 1, row: 2)), true);
      final tower = session.selected!;
      session.money = 0;
      expect(session.upgrade(), false);
      expect(tower.level, 1);
      expect(tower.spent, 100);
      session.choose(towerSpecs.first);
      expect(session.place((column: 2, row: 2)), false);
      expect(session.towers.length, 1);
      session.selected = tower;
      session.pause();
      session.money = 1000;
      expect(session.upgrade(), false);
      expect(session.sell(), false);
      expect(session.place((column: 2, row: 2)), false);
      session.resume();
      expect(session.phase, SessionPhase.ready);
      for (final phase in [SessionPhase.won, SessionPhase.lost]) {
        session.phase = phase;
        expect(session.upgrade(), false);
        expect(session.sell(), false);
        expect(session.place((column: 2, row: 2)), false);
      }
      expect(session.money, 1000);
      expect(tower.level, 1);
      expect(session.towers, [tower]);
    },
  );

  test(
    'target modes acquire by progress, shield-inclusive strength, proximity',
    () {
      for (final mode in TargetMode.values) {
        final session = combatSession();
        final tower = addTower(session, TowerKind.dart)..targetMode = mode;
        final first = addEnemy(session, 0, distance: 6);
        final strong = addEnemy(session, 4, distance: 4)..health = 1;
        final near = addEnemy(session, 2, distance: 5);
        session.update(0);
        expect(tower.targetId, switch (mode) {
          TargetMode.first => first.id,
          TargetMode.strongest => strong.id,
          TargetMode.nearest => near.id,
        });
        final retained = tower.targetId;
        first.distance = 7;
        session.update(0);
        expect(tower.targetId, retained);
        session.enemies.firstWhere((enemy) => enemy.id == retained).resolved =
            true;
        session.update(0);
        expect(tower.targetId, isNot(retained));
      }
    },
  );

  test('target ties use entity ID and out-of-range targets are released', () {
    final session = combatSession();
    final tower = addTower(session, TowerKind.dart);
    final first = addEnemy(session, 4);
    final second = addEnemy(session, 4);
    session.enemies
      ..clear()
      ..addAll([second, first]);
    session.update(0);
    expect(tower.targetId, first.id);
    first.distance = 20;
    session.update(0);
    expect(tower.targetId, second.id);
    second.distance = 20;
    session.update(0);
    expect(tower.targetId, isNull);
    expect(session.shots, isEmpty);
  });

  test('rotation crosses both pi boundaries by the bounded shortest arc', () {
    for (final direction in [-1, 1]) {
      final session = combatSession();
      addEnemy(session, 4, distance: 0);
      final tower = addTower(session, TowerKind.dart, cell: (column: 2, row: 3))
        ..angle = direction * (math.pi - .01);
      final before = tower.angle;
      session.update(step);
      expect((tower.angle - before).abs(), lessThanOrEqualTo(7 * step));
      expect((tower.angle - before) * direction, greaterThan(0));
      expect(session.shots.length, 1);
    }
  });

  test(
    'projectile segment detects a crossed center and bomb splashes once',
    () {
      for (final kind in [TowerKind.dart, TowerKind.bomb]) {
        final session = combatSession();
        final enemy = addEnemy(session, 3);
        final nearby = addEnemy(session, 3, distance: 5.5);
        final distant = addEnemy(session, 3, distance: 7);
        session.shots.add(
          Shot(const Offset(4.5, 3.5), const Offset(6, 0), 3, kind, 1),
        );
        session.update(.3);
        expect(enemy.health, kind == TowerKind.bomb ? 27 : 28);
        expect(nearby.health, kind == TowerKind.bomb ? 27 : 30);
        expect(distant.health, 30);
        expect(session.shots, isEmpty);
        session.update(step);
        expect(enemy.health, kind == TowerKind.bomb ? 27 : 28);
      }
    },
  );

  test('sniper hits instantly through armor without creating a projectile', () {
    final session = combatSession();
    final enemy = addEnemy(session, 3);
    final sniper = addTower(session, TowerKind.sniper);
    aimAt(session, sniper, enemy);
    session.update(0);
    expect(enemy.health, 22);
    expect(session.shots, isEmpty);
  });

  test('pause freezes movement, statuses, shots, cooldowns, and effects', () {
    final session = combatSession();
    final enemy = addEnemy(session, 2)
      ..slow = .3
      ..slowTime = 2;
    final tower = addTower(session, TowerKind.dart)..cooldown = 1;
    final shot = Shot(Offset.zero, const Offset(6, 0), 1, TowerKind.dart, 1);
    final effect = GameEffect(Offset.zero, const Color(0xFFFFFFFF));
    session.shots.add(shot);
    session.effects.add(effect);
    session.pause();
    advance(session, 10);
    expect(enemy.distance, 5);
    expect(enemy.sinceDamage, 0);
    expect(enemy.slowTime, 2);
    expect(tower.cooldown, 1);
    expect(shot.position, Offset.zero);
    expect(shot.life, 4);
    expect(effect.life, effect.duration);
    session.resume();
    expect(session.phase, SessionPhase.running);
  });

  test('wave waits for all spawns and resolves victory exactly once', () {
    final level = LevelDefinition('Short', '', 4, 4, 2, [
      (column: 0, row: 0),
      (column: 3, row: 0),
    ]);
    final session = GameSession(level);
    final sounds = <String>[];
    session.onSound = sounds.add;
    for (var wave = 1; wave <= 2; wave++) {
      session.startWave();
      session.startWave();
      expect(session.wave, wave);
      session.update(step);
      session.hit(session.enemies.single, 100);
      session.update(step);
      expect(session.enemies, isEmpty);
      expect(session.remaining, greaterThan(0));
      expect(session.phase, SessionPhase.running);
      for (
        var tick = 0;
        tick < 2400 && session.phase == SessionPhase.running;
        tick++
      ) {
        for (final enemy in session.enemies) {
          session.hit(enemy, 100);
        }
        session.update(step);
      }
      expect(session.phase, wave == 2 ? SessionPhase.won : SessionPhase.ready);
      expect(session.shots, isEmpty);
    }
    expect(session.lives, 100);
    expect(session.popped, 22);
    expect(sounds.where((sound) => sound == 'win').length, 1);
    session.update(100);
    session.startWave();
    expect(session.wave, 2);
    expect(sounds.where((sound) => sound == 'win').length, 1);
  });

  test('final wave fatal leak defeats before victory or tower attacks', () {
    final session = combatSession()
      ..wave = levels.first.waves
      ..lives = 10;
    final enemy = addEnemy(
      session,
      4,
      distance: session.level.road.length - 1.001,
    );
    final sniper = addTower(
      session,
      TowerKind.sniper,
      cell: (column: 23, row: 4),
      level: 5,
    );
    aimAt(session, sniper, enemy);
    final sounds = <String>[];
    session.onSound = sounds.add;
    session.update(step);
    expect(session.phase, SessionPhase.lost);
    expect(session.lives, 0);
    expect(session.money, 650);
    expect(session.popped, 0);
    session.update(10);
    session.hit(enemy, 100);
    expect(sounds, ['lose']);
    expect(session.lives, 0);
    expect(session.money, 650);
  });

  test(
    'a completed final wave can win with nonfatal leaks and no kill income',
    () {
      final level = LevelDefinition('Short', '', 4, 4, 1, [
        (column: 0, row: 0),
        (column: 3, row: 0),
      ]);
      final session = GameSession(level)..autoStart = true;
      session.startWave();
      advance(session, 15);
      expect(session.phase, SessionPhase.won);
      expect(session.lives, 90);
      expect(session.money, 650);
      expect(session.popped, 0);
      expect(session.remaining, 0);
      advance(session, 15);
      expect(session.wave, 1);
      expect(session.lives, 90);
    },
  );

  for (final level in levels) {
    test('${level.name} is winnable with budgeted mixed towers and upgrades', () {
      final session = GameSession(level);
      final cells = buildCells[level.id]!;
      for (final cell in cells) {
        expect(session.canPlace(cell), true, reason: '${level.id}: $cell');
      }
      final rapid = cells[0];
      final dart = cells[1];
      const farm = (column: 1, row: 1);
      final bomb = cells[2];
      final frost = cells[3];
      final sniper = cells[4];
      final plan = <({TowerKind kind, Cell cell, int targetLevel})>[
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 1),
        (kind: TowerKind.farm, cell: farm, targetLevel: 1),
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 2),
        (kind: TowerKind.dart, cell: dart, targetLevel: 2),
        (kind: TowerKind.farm, cell: farm, targetLevel: 2),
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 2),
        (kind: TowerKind.farm, cell: farm, targetLevel: 3),
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 3),
        (kind: TowerKind.bomb, cell: bomb, targetLevel: 1),
        (kind: TowerKind.frost, cell: frost, targetLevel: 1),
        (kind: TowerKind.farm, cell: farm, targetLevel: 4),
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 4),
        (kind: TowerKind.farm, cell: farm, targetLevel: 5),
        (kind: TowerKind.sniper, cell: sniper, targetLevel: 1),
        (kind: TowerKind.bomb, cell: bomb, targetLevel: 2),
        (kind: TowerKind.frost, cell: frost, targetLevel: 2),
        (kind: TowerKind.rapid, cell: rapid, targetLevel: 5),
        (kind: TowerKind.bomb, cell: bomb, targetLevel: 5),
        (kind: TowerKind.sniper, cell: sniper, targetLevel: 5),
        (kind: TowerKind.frost, cell: frost, targetLevel: 5),
        (kind: TowerKind.dart, cell: dart, targetLevel: 5),
      ];
      var purchase = 0;
      var ticks = 0;
      while (session.phase == SessionPhase.ready) {
        while (purchase < plan.length) {
          final action = plan[purchase];
          final existing = session.towers
              .where((tower) => tower.cell == action.cell)
              .firstOrNull;
          final spec = towerSpecs.firstWhere(
            (spec) => spec.kind == action.kind,
          );
          if (existing == null) {
            if (session.money < spec.cost) break;
            session.choose(spec);
            expect(session.place(action.cell), true);
          } else {
            session.selected = existing;
          }
          final tower = session.selected!;
          while (tower.level < action.targetLevel &&
              session.money >= spec.upgradeCost(tower.level)) {
            expect(session.upgrade(), true);
          }
          if (tower.level < action.targetLevel) break;
          purchase++;
        }
        session.startWave();
        var waveTicks = 0;
        while (session.phase == SessionPhase.running && waveTicks < 120 * 360) {
          session.update(step);
          expect(session.money, greaterThanOrEqualTo(0));
          waveTicks++;
        }
        ticks += waveTicks;
        expect(
          waveTicks,
          lessThan(120 * 360),
          reason: 'Wave ${session.wave} stalled',
        );
        expect(
          session.phase,
          isNot(SessionPhase.lost),
          reason:
              'Lost wave ${session.wave}, cash ${session.money}, '
              'pops ${session.popped}, purchases $purchase',
        );
      }
      expect(session.phase, SessionPhase.won);
      expect(session.wave, level.waves);
      expect(session.lives, greaterThan(0));
      expect(session.towers.map((tower) => tower.spec.kind).toSet().length, 6);
      expect(session.towers.any((tower) => tower.level == 5), true);
      debugPrint(
        '${level.name}: won ${session.wave} waves, '
        '${session.lives} lives, ${session.popped} pops, '
        '\$${session.money} remaining, ${(ticks * step).toStringAsFixed(1)}s; '
        'tower levels ${session.towers.map((tower) => '${tower.spec.kind.name}:${tower.level}').join(', ')}',
      );
    });
  }

  test('catalog provides nine towers and five generated maps', () {
    expect(towerSpecs.length, 9);
    expect(levels.length, greaterThanOrEqualTo(5));
    for (final spec in towerSpecs) {
      expect(spec.upgradeCost(1), greaterThan(spec.cost ~/ 2));
      expect(spec.damageAt(5), greaterThanOrEqualTo(spec.damageAt(1)));
      expect(spec.rangeAt(5), greaterThanOrEqualTo(spec.rangeAt(1)));
    }
  });

  test('every catalog level has a valid bounded route', () {
    for (final level in levels) {
      expect(level.columns, lessThanOrEqualTo(30), reason: level.name);
      expect(level.rows, lessThanOrEqualTo(20), reason: level.name);
      expect(level.road.length, greaterThan(1), reason: level.name);
      expect(level.road.toSet().length, level.road.length, reason: level.name);
    }
  });
}
