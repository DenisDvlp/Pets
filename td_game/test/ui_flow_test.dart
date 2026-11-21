import 'dart:io';
import 'dart:ui' as ui;

import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/app.dart';
import 'package:td_game/game/defense_game.dart';
import 'package:td_game/game/model.dart';
import 'package:td_game/services/settings_store.dart';

void main() {
  testWidgets('defeat retry and victory next level create fresh games', (
    tester,
  ) async {
    final store = MemorySettingsStore();
    await tester.pumpWidget(
      MonkeyDefenseApp(settingsStore: store, audioEnabled: false),
    );
    await tester.pumpAndSettle();
    await tester.tap(find.text('Play'));
    await tester.pumpAndSettle();

    Future<DefenseGame> loadGame() async {
      late DefenseGame game;
      await tester.runAsync(() async {
        await tester.pump();
        final state = tester.state<GameWidgetState<DefenseGame>>(
          find.byType(GameWidget<DefenseGame>),
        );
        await state.loaderFuture.timeout(const Duration(seconds: 15));
        game = tester
            .widget<GameWidget<DefenseGame>>(
              find.byType(GameWidget<DefenseGame>),
            )
            .game!;
      });
      await tester.pump();
      return game;
    }

    await tester.tap(find.text('Play').first);
    final lostGame = await loadGame();
    lostGame.session.phase = SessionPhase.lost;
    lostGame.session.lives = 0;
    lostGame.notify();
    await tester.pump();
    await tester.pump(const Duration(milliseconds: 300));
    expect(find.text('Defense defeated'), findsOneWidget);
    expect(find.text('Retry'), findsOneWidget);
    expect(find.text('Level Select'), findsOneWidget);
    expect(find.text('Next Level'), findsNothing);
    await tester.tap(find.text('Retry'));
    final retried = await loadGame();
    expect(retried, isNot(same(lostGame)));
    expect(retried.session.level, levels.first);
    expect(retried.session.lives, EconomyConfig.initialLives);

    retried.session.phase = SessionPhase.won;
    retried.notify();
    await tester.pump();
    await tester.pump(const Duration(milliseconds: 300));
    expect(find.text('Campaign secured!'), findsOneWidget);
    await tester.tap(find.text('Next Level'));
    final next = await loadGame();
    expect(next.session.level, levels[1]);
    expect(next.session.phase, SessionPhase.ready);
    expect(next.session.wave, 0);
    expect(store.value.completed, contains(0));
    expect(find.byType(Dialog), findsNothing);
    await tester.pumpWidget(const SizedBox.shrink());
    await tester.pump(const Duration(milliseconds: 100));
  });

  for (final size in [const Size(960, 640), const Size(1920, 1080)]) {
    testWidgets('complete menu and gameplay flow at ${size.width}', (
      tester,
    ) async {
      tester.view.physicalSize = size;
      tester.view.devicePixelRatio = 1;
      addTearDown(tester.view.resetPhysicalSize);
      addTearDown(tester.view.resetDevicePixelRatio);
      final store = MemorySettingsStore();
      final boundary = GlobalKey();
      await tester.pumpWidget(
        RepaintBoundary(
          key: boundary,
          child: MonkeyDefenseApp(settingsStore: store, audioEnabled: false),
        ),
      );
      await tester.pumpAndSettle();
      await tester.tap(find.text('Settings'));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Show grid'));
      await tester.pumpAndSettle();
      expect(store.value.grid, isTrue);
      await tester.tap(find.text('Done'));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Play'));
      await tester.pumpAndSettle();
      expect(find.text('Meadow Bend'), findsOneWidget);
      expect(find.text('River Switchback'), findsOneWidget);
      await tester.runAsync(() async {
        await tester.tap(find.text('Play').first);
        await tester.pump();
        final state = tester.state<GameWidgetState<DefenseGame>>(
          find.byType(GameWidget<DefenseGame>),
        );
        await state.loaderFuture.timeout(const Duration(seconds: 15));
      });
      await tester.pump();
      final game = tester
          .widget<GameWidget<DefenseGame>>(find.byType(GameWidget<DefenseGame>))
          .game!;
      expect(game.terrainSprites, isNotEmpty);
      expect(tester.takeException(), isNull);
      await tester.tap(find.text('Dart Scout'));
      await tester.pump();
      final rect = tester.getRect(find.byType(GameWidget<DefenseGame>));
      final scale = (rect.width / (24 * 32)).clamp(0, rect.height / (16 * 32));
      final origin =
          rect.center - Offset(24 * 32 * scale / 2, 16 * 32 * scale / 2);
      await tester.tapAt(origin + Offset(1.5 * 32 * scale, 2.5 * 32 * scale));
      await tester.pump(const Duration(milliseconds: 100));
      expect(game.session.towers.length, 1);
      expect(game.session.money, 550);
      expect(find.text('L1'), findsOneWidget);
      if (Platform.environment['SAVE_SCREENSHOTS'] == 'true') {
        await tester.runAsync(() async {
          final render =
              boundary.currentContext!.findRenderObject()!
                  as RenderRepaintBoundary;
          final image = await render.toImage();
          final bytes = await image.toByteData(format: ui.ImageByteFormat.png);
          Directory('build/test_snapshots').createSync(recursive: true);
          File(
            'build/test_snapshots/game_${size.width.toInt()}.png',
          ).writeAsBytesSync(bytes!.buffer.asUint8List());
          image.dispose();
        });
      }
      await tester.tap(find.byTooltip('Pause'));
      await tester.pump();
      await tester.pump(const Duration(milliseconds: 300));
      expect(game.session.phase, SessionPhase.paused);
      expect(
        find.descendant(of: find.byType(Dialog), matching: find.text('Paused')),
        findsOneWidget,
      );
      await tester.tap(find.text('Resume'));
      await tester.pump(const Duration(milliseconds: 300));
      expect(game.session.phase, SessionPhase.ready);
      await tester.tap(find.text('Start Wave'));
      await tester.pump(const Duration(milliseconds: 100));
      expect(game.session.phase, SessionPhase.running);
      await tester.tap(find.byTooltip('Pause'));
      await tester.pump();
      await tester.pump(const Duration(milliseconds: 300));
      await tester.tap(find.text('Main Menu'));
      await tester.pumpAndSettle();
      expect(find.text('Monkey Balloon Defense'), findsOneWidget);
      expect(tester.takeException(), isNull);
      await tester.pumpWidget(const SizedBox.shrink());
      await tester.pump(const Duration(milliseconds: 100));
    });
  }
}
