import 'package:flutter_test/flutter_test.dart';
import 'package:td_game/main.dart';
import 'package:td_game/services/settings_store.dart';

void main() {
  testWidgets('Main menu and injected exit work without plugins', (
    tester,
  ) async {
    var exited = false;
    await tester.pumpWidget(
      MonkeyDefenseApp(
        settingsStore: MemorySettingsStore(),
        exitAction: () async {
          exited = true;
        },
      ),
    );
    await tester.pumpAndSettle();
    expect(find.text('Monkey Balloon Defense'), findsOneWidget);
    expect(find.text('Play'), findsOneWidget);
    expect(find.text('Settings'), findsOneWidget);
    await tester.tap(find.text('Exit'));
    await tester.pumpAndSettle();
    expect(exited, isTrue);
  });
}
