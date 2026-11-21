# Monkey Balloon Defense

A Windows-first, offline Flutter/Flame tower defense with original monkey and
balloon visuals. The board is strictly orthographic: square tiles viewed from
directly above, without isometric projection or overlapping terrain.

## Run

Requires a Flutter SDK compatible with the Dart constraint in pubspec.yaml and
Visual Studio with Desktop development with C++. The downloaded Kenney terrain
is already in assets/PNG/Default size/.

```powershell
flutter pub get
flutter run -d windows
```

Build with `flutter build windows`. Distribute the entire
build/windows/x64/runner/Release directory, not only the executable. All assets
are bundled locally; no runtime downloads are required.

## Play

- Play opens Meadow Bend (24x16, 15 waves) and River Switchback (30x20,
	20 waves). Both maps are available immediately.
- Buy a monkey, then click an empty grass tile. Roads, water, rocks and occupied
	cells cannot accept purchases. Hover previews placement and attack range.
- Right-click or Escape cancels a selection. Escape without a selection pauses.
- Click a deployed monkey to inspect, upgrade, sell, or choose First,
	Strongest or Nearest targeting.
- Start Wave begins the next wave. Pause freezes combat and income. 1x/2x
	changes all simulation timing together. Clearing the last wave wins;
	losing all lives ends the defense.
- Settings control sound volume, grid visibility and automatic next waves.
	Settings and completed levels persist locally. In-progress games are not saved.
	Switching away from the Windows app pauses gameplay.

Each campaign starts with $650 and 100 lives. Kills pay once; escapes cost lives
and pay nothing. Farmers earn only during active waves, never while paused or
waiting between waves. Selling refunds 70% of all money spent, rounded down.

## Monkeys

Every monkey has five total levels: purchased at L1, upgraded four times to L5.
The inspector displays current/next stats and upgrade prices. Attacking heads
rotate toward valid targets along the shortest angular direction.

| Monkey | Base Price | Role |
| --- | ---: | --- |
| Dart Scout | 100 | Balanced single-target darts |
| Rapid Gunner | 220 | Rapid single-target fire |
| Bomb Lobber | 280 | Splash damage that bypasses armor |
| Frost Monkey | 180 | Area damage and slowing; strongest slow wins |
| Longshot | 350 | Long-range armor-piercing hitscan shots |
| Banana Farmer | 250 | Pays 20/35/55/80/120 every 8 active-wave seconds |

## Balloons

Five independent types, without downgrading or splitting:

| Type | Health | Speed (tiles/sec) | Reward | Escaped Lives | Ability |
| --- | ---: | ---: | ---: | ---: | --- |
| Red Basic | 1 | 1 | 5 | 1 | Basic balloon |
| Blue Swift | 3 | 1.5 | 8 | 2 | Faster movement |
| Green Regenerator | 8 | 1.2 | 14 | 3 | Heals after 2 seconds without damage |
| Yellow Plated | 18 | 1 | 24 | 5 | Reduces ordinary hits by 1, minimum 0.5 |
| Violet Guardian | 40 + 10 shield | 0.85 | 45 | 10 | Shield and half-strength slowing |

Movement is continuous through road-cell centers and turns. Fixed 120 Hz
simulation steps and swept projectile segments avoid fast-dart tunneling.
Longshot damage is hitscan; its visible trace is cosmetic. Exceptional frame
stalls cap catch-up rather than advancing through a long invisible interval.

## Assets and Code

- Terrain comes from [Kenney Tower Defense (Top-Down)](https://kenney.nl/assets/tower-defense-top-down),
	CC0. The original license remains in assets/License.txt.
- Terrain mappings are in lib/game/defense_game.dart. Grass uses tile024,
	road tile050, water tile074 with a blue overlay, and rocks are drawn on grass.
	Replace these mappings with new square textures without changing game rules.
- Monkey/balloon/equipment/effect artwork is original Canvas rendering in
	defense_game.dart; shop portraits are in app.dart. These simple placeholders
	can later be replaced with SpriteComponents.
- Original synthesized WAV effects are in assets/audio/. Reproduce them with
	tools/generate_audio.ps1. An unavailable audio device does not block gameplay.
- Definitions, paths, combat, waves and economy: lib/game/model.dart.
- Flame rendering/input: lib/game/defense_game.dart.
- Flutter menus, HUD, shop and dialogs: lib/app.dart.
- Injectable settings storage: lib/services/settings_store.dart.

Uses the [official Flame documentation](https://docs.flame-engine.org/latest/)
for the game loop, camera/world, input and asset loading. No proprietary Bloons
artwork, branding, maps or code is included. This version has finite campaigns,
linear upgrades, no multiplayer and no map editor. Balance is a playable starting
point; River's farm economy is forgiving.

## Verify

```powershell
flutter analyze
flutter test
```

Tests cover maps, continuous movement, economy, L5 bounds, all enemy abilities,
farming, pause, once-only rewards, aiming, swept hits, victory/defeat and no-cheat
winning strategies for both levels. Widget tests load the real terrain and
exercise resized placement and menu/game flows at compact and desktop sizes.

```powershell
$env:SAVE_SCREENSHOTS = 'true'
flutter test test/game/board_test.dart test/ui_flow_test.dart
```

Screenshots go to build/test_snapshots/. Widget tests substitute a test font;
evaluate final typography and audio in the native Windows application. UI flows
are checked at 960x640 and 1920x1080, placement also at 1280x720.
