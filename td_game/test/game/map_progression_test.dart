import 'dart:convert';
import 'dart:ui';

import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/game/model.dart';

void main() {
  test('replica prediction preserves authority until reconciled snapshots', () {
    final host = GameSession(levels.first);
    host.towers.addAll([
      Monkey(100, towerSpecs.first, (column: 1, row: 2))
        ..angle = const Offset(0, 1).direction,
      Monkey(101, towerSpecs[TowerKind.farm.index], (column: 2, row: 2)),
    ]);
    host.startWave();
    host.update(0);
    host.enemies.first.distance = 1;
    host.enemies.add(
      Balloon(102, 0, wave: host.wave)
        ..distance = host.level.road.length - 1.01,
    );
    final hostBefore = host.toSnapshot();
    host.predict(1);
    expect(host.toSnapshot(), hostBefore);

    final replica = GameSession(levels.first)..replica = true;
    replica.applySnapshot(host.toSnapshot(includePresentation: false));
    final tower = replica.towers.first;
    final enemy = replica.enemies.first;
    replica.selected = tower;
    final sounds = <String>[];
    replica.onSound = sounds.add;
    final authority = (
      replica.money,
      replica.lives,
      replica.wave,
      replica.popped,
      replica.phase,
      replica.remaining,
      replica.revision,
    );
    final ids = replica.enemies.map((enemy) => enemy.id).toList();
    replica.predict(.01);
    expect(enemy.distance, greaterThan(1));
    expect(replica.shots, isNotEmpty);
    replica.hit(enemy, enemy.maxHealth + enemy.maxShield + 100);
    expect(enemy.health, .01);
    for (var tick = 0; tick < 1200; tick++) {
      replica.predict(1 / 120);
    }
    expect(replica.enemies.map((enemy) => enemy.id), ids);
    expect(replica.enemies.every((enemy) => !enemy.resolved), true);
    expect(replica.enemies.last.distance, host.level.road.length - 1);
    expect((
      replica.money,
      replica.lives,
      replica.wave,
      replica.popped,
      replica.phase,
      replica.remaining,
      replica.revision,
    ), authority);
    expect(sounds, isEmpty);

    tower
      ..angle = .7
      ..cooldown = .4
      ..farmTime = .8
      ..targetId = enemy.id;
    final predictedDistance = enemy.distance;
    final localShot = Shot(tower.position, Offset.zero, 1, TowerKind.dart, 1);
    final localEffect = GameEffect(tower.position, const Color(0xFF123456));
    replica.shots.add(localShot);
    replica.effects.add(localEffect);
    host.towers.first
      ..level = 2
      ..spent = 500
      ..targetMode = TargetMode.strongest;
    final lean = host.toSnapshot(includePresentation: false);
    expect(lean['shots'], isEmpty);
    expect(lean['effects'], isEmpty);
    replica.applySnapshot(lean, preservePresentation: true);
    expect(replica.selected, same(tower));
    expect(replica.enemies.first, same(enemy));
    expect(enemy.distance, predictedDistance);
    expect(enemy.health, host.enemies.first.health);
    expect(tower.angle, .7);
    expect(tower.cooldown, .4);
    expect(tower.farmTime, .8);
    expect(tower.targetId, enemy.id);
    expect(tower.level, 2);
    expect(tower.spent, 500);
    expect(tower.targetMode, TargetMode.strongest);
    expect(replica.shots, contains(same(localShot)));
    expect(replica.effects, contains(same(localEffect)));

    host.pause();
    replica.applySnapshot(host.toSnapshot(), preservePresentation: true);
    expect(enemy.distance, host.enemies.first.distance);
    host.enemies.clear();
    replica.applySnapshot(host.toSnapshot(), preservePresentation: true);
    expect(replica.enemies, isEmpty);
    expect(tower.targetId, isNull);
    expect(replica.effects.length, greaterThan(1));
    expect(sounds, isEmpty);
    host.phase = SessionPhase.ready;
    host.autoStart = true;
    replica.applySnapshot(host.toSnapshot(), preservePresentation: true);
    replica.predict(WaveConfig.autoStartDelay + 1);
    expect(replica.phase, SessionPhase.ready);
    expect(replica.wave, host.wave);
  });

  test('configured speeds govern assignments, commands and snapshots', () {
    expect(SimulationConfig.supportedSpeeds, isNotEmpty);
    expect(
      SimulationConfig.supportedSpeeds.toSet().length,
      SimulationConfig.supportedSpeeds.length,
    );
    final host = GameSession(levels.first);
    final replica = GameSession(levels.first)..replica = true;
    expect(host.speed, SimulationConfig.supportedSpeeds.first);
    for (final speed in SimulationConfig.supportedSpeeds) {
      expect(speed, greaterThan(0));
      host.speed = speed;
      expect(host.speed, speed);
      expect(host.applyCommand({'action': 'speed', 'value': speed}), true);
      replica.applySnapshot(host.toSnapshot());
      expect(replica.speed, speed);
    }
    final before = host.speed;
    host.speed = 999;
    expect(host.speed, before);
    expect(host.applyCommand({'action': 'speed', 'value': 999}), false);
    replica.applySnapshot({...host.toSnapshot(), 'speed': 999});
    expect(replica.speed, before);
  });

  test(
    'seven distinct routes preserve dimensions, spacing and grass pockets',
    () {
      expect(levels.map((level) => level.waves), [23, 30, 38, 27, 30, 33, 36]);
      expect(levels.map((level) => (level.columns, level.rows)), [
        (24, 16),
        (30, 20),
        (30, 20),
        (28, 18),
        (25, 17),
        (22, 18),
        (28, 20),
      ]);
      expect(levels.map((level) => level.id).toSet().length, 7);
      expect(levels.map((level) => level.road.toString()).toSet().length, 7);
      for (final level in levels) {
        expect(level.road.first.column, 0);
        expect(level.road.last.column, level.columns - 1);
        expect(level.road.toSet().length, level.road.length);
        var turns = 0;
        Cell? previousDirection;
        for (var index = 1; index < level.road.length; index++) {
          final start = level.road[index - 1];
          final end = level.road[index];
          expect(level.contains(end), true);
          expect(level.terrain(end), Terrain.road);
          final direction = (
            column: end.column - start.column,
            row: end.row - start.row,
          );
          expect(direction.column.abs() + direction.row.abs(), 1);
          if (previousDirection != null && previousDirection != direction) {
            turns++;
          }
          previousDirection = direction;
          for (var other = 0; other < index - 1; other++) {
            final cell = level.road[other];
            expect(
              (cell.column - end.column).abs() + (cell.row - end.row).abs(),
              greaterThan(1),
              reason: '${level.id}: neighboring unjoined road stretches',
            );
          }
        }
        expect(turns, greaterThanOrEqualTo(8), reason: level.id);
        final reserved = <Cell>{};
        var pockets = 0;
        for (var row = 0; row < level.rows - 1; row++) {
          for (var column = 0; column < level.columns - 1; column++) {
            final pocket = <Cell>[
              (column: column, row: row),
              (column: column + 1, row: row),
              (column: column, row: row + 1),
              (column: column + 1, row: row + 1),
            ];
            if (pocket.every(
              (cell) =>
                  level.terrain(cell) == Terrain.grass &&
                  !reserved.contains(cell),
            )) {
              reserved.addAll(pocket);
              pockets++;
            }
          }
        }
        expect(pockets, greaterThanOrEqualTo(4), reason: level.id);
      }
      for (var column = 0; column <= 6; column++) {
        expect(levels.first.road[column], (column: column, row: 3));
      }
      expect(levels.first.terrain((column: 1, row: 2)), Terrain.grass);
      expect(levels.first.terrain((column: 2, row: 2)), Terrain.grass);
      for (final level in levels.where((level) => level.river)) {
        final crossings = level.road
            .where((cell) => cell.column == 15)
            .map((cell) => cell.row)
            .toSet();
        expect(crossings.length, greaterThanOrEqualTo(3));
      }
    },
  );

  test('tier durability scales by wave and spawning uses current wave', () {
    expect(enemySpecs.map((spec) => spec.health), [1, 4, 12, 30, 75]);
    expect(enemySpecs.last.shield, 15);
    for (var tier = 0; tier < 5; tier++) {
      final base = Balloon(1, tier);
      final late = Balloon(1, tier, wave: 38);
      expect(
        late.maxHealth,
        closeTo(base.maxHealth * (1 + tierWaveRates[tier] * 37), .000001),
      );
      expect(late.maxHealth, greaterThanOrEqualTo(base.maxHealth));
      expect(late.maxShield, greaterThanOrEqualTo(base.maxShield));
      expect(Balloon(1, tier, wave: 0).maxHealth, base.maxHealth);
    }
    final introduction = Balloon(1, 4, wave: 14);
    expect(
      introduction.maxHealth + introduction.maxShield,
      closeTo(160.2, .000001),
    );
    expect(
      ((introduction.maxHealth + introduction.maxShield) /
              towerSpecs[TowerKind.sniper.index].damageAt(5))
          .ceil(),
      5,
    );
    final late = Balloon(1, 4, wave: 38);
    expect(late.maxHealth + late.maxShield, closeTo(289.8, .000001));
    final session = GameSession(levels[2])..wave = 37;
    session.startWave();
    session.update(0);
    expect(session.enemies.first.maxHealth, late.maxHealth);
    expect(session.enemies.first.maxShield, late.maxShield);
  });

  test('wave-scaled regeneration caps at instance maximum', () {
    final session = GameSession(levels[2])
      ..phase = SessionPhase.running
      ..wave = 38;
    final enemy = Balloon(100, 2, wave: 38)
      ..health = 15
      ..sinceDamage = 3;
    session.enemies.add(enemy);
    for (var tick = 0; tick < 40 * 120; tick++) {
      session.update(1 / 120);
    }
    expect(enemy.health, enemy.maxHealth);
    expect(enemy.health, greaterThan(enemy.spec.health));
  });

  test('one lone level-five sniper cannot clear a mixed late wave', () {
    final session = GameSession(levels[2])..wave = 37;
    final sniper = Monkey(10000, towerSpecs[TowerKind.sniper.index], (
      column: 18,
      row: 10,
    ))..level = 5;
    session.towers.add(sniper);
    session.startWave();
    final seenTiers = <int>{};
    for (
      var tick = 0;
      tick < 360 * 120 && session.phase == SessionPhase.running;
      tick++
    ) {
      session.update(1 / 120);
      seenTiers.addAll(session.enemies.map((enemy) => enemy.tier));
    }
    expect(seenTiers.length, greaterThan(1));
    expect(seenTiers, contains(4));
    expect(session.phase, SessionPhase.lost);
    expect(session.popped, greaterThan(0));
  });

  test(
    'host commands preserve local UI and reject malformed or forbidden actions',
    () {
      final session = GameSession(levels.first)..money = 10000;
      session.choose(towerSpecs.first);
      session.place((column: 1, row: 2));
      final local = session.selected!;
      session.buying = towerSpecs[1];
      session.message = 'Local message';
      final remotePlace = <String, dynamic>{
        'action': 'place',
        'kind': 4,
        'column': 2,
        'row': 2,
      };
      expect(session.applyCommand(remotePlace), true);
      final remote = session.towers.last;
      expect(
        session.applyCommand({'action': 'upgrade', 'id': remote.id}),
        true,
      );
      expect(
        session.applyCommand({'action': 'target', 'id': remote.id, 'value': 1}),
        true,
      );
      expect(remote.targetMode, TargetMode.strongest);
      expect(session.selected, same(local));
      expect(session.buying, towerSpecs[1]);
      expect(session.message, 'Local message');
      final before = session.toSnapshot();
      for (final command in <Map<String, dynamic>>[
        {},
        {'action': 'unknown'},
        {'action': 'place', 'kind': -1, 'column': 3, 'row': 2},
        {'action': 'place', 'kind': 99, 'column': 3, 'row': 2},
        {'action': 'place', 'kind': 1, 'column': 1.0, 'row': 2},
        {'action': 'place', 'kind': 1, 'column': -1, 'row': 2},
        {'action': 'place', 'kind': 1, 'column': 999999999, 'row': 2},
        {'action': 'place', 'kind': 1, 'column': 1, 'row': 3},
        remotePlace,
        {'action': 'upgrade', 'id': 0},
        {'action': 'sell', 'id': 999},
        {'action': 'target', 'id': remote.id, 'value': 99},
        {'action': 'speed', 'value': double.nan},
        {'action': 'speed', 'value': 999},
        {'action': 'resume'},
      ]) {
        expect(session.applyCommand(command), false, reason: '$command');
        expect(session.toSnapshot(), before);
      }
      expect(
        session.applyCommand({
          'action': 'speed',
          'value': SimulationConfig.supportedSpeeds.last,
        }),
        true,
      );
      expect(session.speed, SimulationConfig.supportedSpeeds.last);
      expect(session.applyCommand({'action': 'wave'}), true);
      expect(session.applyCommand({'action': 'wave'}), false);
      expect(session.applyCommand({'action': 'pause'}), true);
      expect(
        session.applyCommand({'action': 'upgrade', 'id': remote.id}),
        false,
      );
      expect(session.applyCommand({'action': 'resume'}), true);
      expect(session.applyCommand({'action': 'sell', 'id': remote.id}), true);
      expect(session.selected, same(local));
      expect(session.applyCommand({'action': 'sell', 'id': local.id}), true);
      expect(session.selected, isNull);
      session.phase = SessionPhase.won;
      expect(session.applyCommand({'action': 'speed', 'value': 1}), false);
      expect(session.applyCommand(remotePlace), false);
    },
  );

  test(
    'replica actions send numeric commands without shared-state mutations',
    () {
      final host = GameSession(levels.first);
      host.choose(towerSpecs.first);
      host.place((column: 1, row: 2));
      final replica = GameSession(levels.first)..replica = true;
      replica.applySnapshot(host.toSnapshot());
      final commands = <Map<String, dynamic>>[];
      replica.sendCommand = commands.add;
      replica.place((column: 1, row: 2));
      final before = replica.toSnapshot();
      expect(replica.upgrade(), true);
      expect(replica.sell(), true);
      replica.setTargetMode(TargetMode.nearest);
      replica.setSpeed(SimulationConfig.supportedSpeeds.last);
      replica.startWave();
      replica.pause();
      replica.choose(towerSpecs[1]);
      expect(replica.place((column: 2, row: 2)), true);
      expect(replica.toSnapshot(), {
        ...before,
        'revision': (before['revision'] as int) + 1,
      });
      expect(commands, [
        {'action': 'upgrade', 'id': 1},
        {'action': 'sell', 'id': 1},
        {'action': 'target', 'id': 1, 'value': 2},
        {'action': 'speed', 'value': SimulationConfig.supportedSpeeds.last},
        {'action': 'wave'},
        {'action': 'pause'},
        {'action': 'place', 'kind': 1, 'column': 2, 'row': 2},
      ]);
      replica.cancel();
      expect(replica.buying, isNull);
      expect(commands.length, 7);
      expect(replica.applyCommand({'action': 'wave'}), false);
      host.pause();
      replica.applySnapshot(host.toSnapshot());
      replica.resume();
      expect(commands.last, {'action': 'resume'});
      expect(replica.phase, SessionPhase.paused);
    },
  );

  test(
    'snapshots round trip rendered fields, retain local intent and apply atomically',
    () {
      final host = GameSession(levels.first)..wave = 13;
      host.choose(towerSpecs[4]);
      host.place((column: 1, row: 2));
      host.startWave();
      host.update(.1);
      host.enemies.first
        ..slow = .25
        ..slowTime = 3
        ..poison = 2
        ..poisonTime = 4;
      host.shots.add(
        Shot(const Offset(2, 2), const Offset(3, 0), 5, TowerKind.bomb, 3)
          ..life = 2,
      );
      host.effects.add(
        GameEffect(
          const Offset(1, 2),
          const Color(0xFF123456),
          lineEnd: const Offset(3, 4),
          label: '+20',
          life: .8,
        )..life = .4,
      );
      host.speed = SimulationConfig.supportedSpeeds.last;
      host.autoStart = true;
      host.pause();
      final replica = GameSession(levels.first)..replica = true;
      Map<String, dynamic> wire(Map<String, dynamic> value) =>
          jsonDecode(jsonEncode(value)) as Map<String, dynamic>;
      replica.applySnapshot(wire(host.toSnapshot()));
      expect(replica.toSnapshot(), host.toSnapshot());
      replica.selected = replica.towers.first;
      replica.buying = towerSpecs[1];
      replica.message = 'Local';
      host.towers.first.angle = 1.2;
      host.enemies.first.distance += .2;
      replica.applySnapshot(wire(host.toSnapshot()));
      expect(replica.selected, same(replica.towers.first));
      expect(replica.buying, towerSpecs[1]);
      expect(replica.message, 'Local');
      expect(replica.enemies.first.maxHealth, host.enemies.first.maxHealth);
      expect(replica.toSnapshot(), host.toSnapshot());
      final before = replica.toSnapshot();
      for (final bad in <Map<String, dynamic>>[
        {...wire(before), 'money': -1},
        {...wire(before), 'mapId': 'unknown'},
        {...wire(before), 'speed': 999},
        {
          ...wire(before),
          'towers': [null],
        },
        {
          ...wire(before),
          'enemies': [
            {...(wire(before)['enemies'] as List).first as Map, 'maxHealth': 1},
          ],
        },
        {
          ...wire(before),
          'shots': [
            {
              ...(wire(before)['shots'] as List).first as Map,
              'damage': double.infinity,
            },
          ],
        },
      ]) {
        replica.applySnapshot(bad);
        expect(replica.toSnapshot(), before);
      }
      host.phase = SessionPhase.ready;
      host.selected = host.towers.first;
      host.sell();
      replica.applySnapshot(wire(host.toSnapshot()));
      expect(replica.selected, isNull);
      expect(replica.buying, towerSpecs[1]);
    },
  );
}
