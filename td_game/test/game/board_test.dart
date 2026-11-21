import 'dart:io';
import 'dart:ui' as ui;

import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/game/defense_game.dart';
import 'package:td_game/game/model.dart';
import 'package:td_game/services/settings_store.dart';

void main() {
  test('replica frames simulate motion while preserving shared stats', () {
    final host = GameSession(levels.first)
      ..phase = SessionPhase.running
      ..wave = 1
      ..speed = SimulationConfig.supportedSpeeds.last
      ..autoStart = true;
    final enemy = Balloon(1, 2)
      ..distance = 2
      ..health = 4;
    final monkey = Monkey(2, towerSpecs.first, (column: 1, row: 2))..angle = 3;
    host.enemies.add(enemy);
    host.towers.add(monkey);
    final replica = GameSession(levels.first)..replica = true;
    final game = DefenseGame(
      session: replica,
      settings: const DefenseSettings(autoStart: false),
      onChanged: () {},
      audioEnabled: false,
    );
    addTearDown(game.dispose);

    replica.applySnapshot(host.toSnapshot());
    final stats = (
      replica.money,
      replica.lives,
      replica.wave,
      replica.popped,
      replica.remaining,
      replica.phase,
    );
    game.update(.1);
    expect(
      game.renderDistance(replica.enemies.single),
      closeTo(2 + enemy.spec.speed * .1 * replica.speed, .02),
    );
    expect((
      replica.money,
      replica.lives,
      replica.wave,
      replica.popped,
      replica.remaining,
      replica.phase,
    ), stats);
    expect(replica.autoStart, isTrue);

    for (final phase in [
      SessionPhase.paused,
      SessionPhase.won,
      SessionPhase.lost,
    ]) {
      host.phase = phase;
      enemy.distance += 1;
      monkey.angle += .1;
      replica.applySnapshot(host.toSnapshot());
      final stopped = replica.toSnapshot();
      expect(game.renderDistance(replica.enemies.first), enemy.distance);
      expect(game.renderAngle(replica.towers.single), monkey.angle);
      game.update(.025);
      expect(replica.toSnapshot(), equals(stopped));
    }
  });

  testWidgets(
    'downloaded tiles load and board clicks remain aligned after resize',
    (tester) async {
      tester.view.physicalSize = const Size(960, 640);
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final session = GameSession(levels.first);
      final game = DefenseGame(
        session: session,
        settings: const DefenseSettings(grid: true),
        onChanged: () {},
        audioEnabled: false,
      );
      final boundary = GlobalKey();
      await tester.runAsync(() async {
        await tester.pumpWidget(
          MaterialApp(
            home: RepaintBoundary(
              key: boundary,
              child: GameWidget(game: game),
            ),
          ),
        );
        final state = tester.state<GameWidgetState<DefenseGame>>(
          find.byType(GameWidget<DefenseGame>),
        );
        await state.loaderFuture.timeout(const Duration(seconds: 15));
      });
      await tester.pump();
      expect(game.terrainSprites.length, 4);
      expect(
        game.terrainSprites[Terrain.grass]!.srcSize.x,
        game.terrainSprites[Terrain.grass]!.srcSize.y,
      );
      session.choose(towerSpecs.first);
      await tester.tapAt(const Offset(60, 100));
      await tester.pump();
      expect(session.towers.single.cell, (column: 1, row: 2));
      expect(session.money, 550);
      tester.view.physicalSize = const Size(1280, 720);
      await tester.pump();
      session.choose(towerSpecs[1]);
      await tester.tapAt(const Offset(167.5, 112.5));
      await tester.pump();
      expect(session.towers.last.cell, (column: 1, row: 2));
      expect(session.towers.length, 1);
      session.cancel();
      session.choose(towerSpecs[1]);
      await tester.tapAt(const Offset(212.5, 112.5));
      await tester.pump();
      expect(session.towers.last.cell, (column: 2, row: 2));
      expect(session.money, 330);
      session.startWave();
      for (var index = 0; index < 180; index++) {
        game.update(1 / 60);
      }
      await tester.pump();
      expect(session.enemies.length + session.popped, greaterThan(0));
      expect(tester.takeException(), isNull);
      if (Platform.environment['SAVE_SCREENSHOTS'] == 'true') {
        await tester.runAsync(() async {
          final render =
              boundary.currentContext!.findRenderObject()!
                  as RenderRepaintBoundary;
          final image = await render.toImage();
          final bytes = await image.toByteData(format: ui.ImageByteFormat.png);
          final directory = Directory('build/test_snapshots')
            ..createSync(recursive: true);
          File(
            '${directory.path}/board.png',
          ).writeAsBytesSync(bytes!.buffer.asUint8List());
          image.dispose();
        });
      }
      await tester.pumpWidget(const SizedBox.shrink());
      await tester.pump(const Duration(milliseconds: 100));
      game.dispose();
    },
  );
}
