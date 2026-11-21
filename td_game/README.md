# Monkey Balloon Defense

A Windows-first Flutter/Flame tower defense with solo and LAN co-op, original monkey and
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

- Play opens level selection. All seven maps are available immediately, with
  distinct winding paths, hairpins, open curls and river crossings.
- Buy a monkey, then click an empty grass tile. Roads, water, rocks and occupied
	cells cannot accept purchases. Hover previews placement and attack range.
- Right-click or Escape cancels a selection. Escape without a selection pauses.
- Click a deployed monkey to inspect, upgrade, sell, or choose First,
	Strongest or Nearest targeting.
- Start Wave begins the next wave. Pause freezes combat and income. Game speed
	changes all simulation timing together. Clearing the last wave wins;
	losing all lives ends the defense.
- Settings control sound volume, grid visibility and automatic next waves.
	Settings and completed levels persist locally. In-progress games are not saved.
  Switching away pauses solo play; in co-op, only host inactivity pauses the team.

Each campaign starts with $650 and 100 lives. Kills pay once; escapes cost lives
and pay nothing. Farmers earn only during active waves, never while paused or
waiting between waves. Selling refunds 70% of all money spent, rounded down.

Core gameplay tuning is centralized in `lib/game/game_config.dart`: tower and
balloon catalogs, upgrade scaling, economy, waves, armor/regeneration/status
effects, projectile behavior, map limits, simulation timing and snapshot limits.
The model, inspector and Flame loop consume those same values. LAN ports,
player capacity, timeouts, discovery and message limits are centralized in
`lib/network/network_config.dart`. Map geometry is configured in `lib/game/game_config.dart`;
purely visual drawing dimensions and UI styling remain with their renderers.

Supported game-speed multipliers are configured in `lib/game/game_config.dart`
by `SimulationConfig.supportedSpeeds` (currently `[1, 5]`). Use a nonempty list of unique
positive integers; its first entry is the initial speed. The HUD, local actions,
network commands and snapshots all use this list. LAN peers must have identical
configured lists to connect. Changing the list requires rebuilding the game.

| Map | Waves | Route |
| --- | ---: | --- |
| Meadow Bend | 23 | Multi-S serpentine |
| River Switchback | 30 | Bank hairpins and repeated crossings |
| Mountain Pass | 38 | Stepped ridge switchbacks |
| Desert Oasis | 27 | Nested rectangular detours |
| Crystal Crossroads | 30 | Interlocking angular hooks |
| Volcano Loop | 33 | Connected curls around a central clearing |
| Twin Rivers | 36 | Unequal alternating-bank slalom |

## LAN Co-op

1. Connect Windows PCs to the same local network and open **Co-op Lobby**.
2. One player creates a game, choosing a name and map. Others select the
	waiting game and join. Up to four players can join, including the host.
3. Once at least two players are present, the host starts the match.

Cash, lives and towers are shared. Everyone may build, upgrade, sell, change
targeting, start waves, pause/resume and choose speed. The host decides combat
results and team statistics. Clients simulate balloon movement, aiming, bullets
and shooting effects locally without waiting for network frames. Predicted hits
never award cash, spend lives, remove balloons or decide victory/defeat.
Tower changes, balloon spawns/removals and team statistics use compact ordered
deltas; unchanged state produces no gameplay packets. Changes are checked every
100 ms, and commands publish promptly. Lean authoritative reports every two seconds
update health/status. Client positions are visual guesses: no drift calculations,
position reconciliation or lockstep synchronization runs during active play.
When play stops, the displayed scene may refresh from the host report.
Bullets and transient effects are
not transmitted. Visual hits may differ slightly from the host by design. Volume
and grid preferences stay local; the host's auto-start setting controls the team.
Connected players each record completed maps locally.

Only the host can retry or choose the next map from the result popup. Retry
returns the team to the waiting room; Next Level immediately starts the next map
for the connected team when enough players remain. Guests can leave without ending the others' match. Host
departure or connection loss ends the connection and returns guests to Lobby.
Mid-match joining, reconnection and host migration are not supported.

Allow the game through Windows Defender Firewall on **Private networks** when
prompted. Discovery uses UDP port **45873**; gameplay uses the TCP port shown
in the host's waiting room. No administrator commands or Bonjour installation
are required by the game. When discovery is unavailable, enter one of the host's
displayed IPv4 addresses and TCP port under direct join. Direct join still needs
firewall access to that port. Guest Wi-Fi/client isolation, VPN routing or separate
subnets may prevent connections. Both PCs must run the updated protocol version;
older snapshot-only builds cannot join. No internet service, authentication or encryption
is provided; use a trusted LAN.

For a local smoke test, launch the packaged executable twice from the Release
directory, create a game in one window and join `127.0.0.1` with its displayed
port in the other. Verify discovery separately on two physical PCs.

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
| Blue Swift | 4 | 1.5 | 8 | 2 | Faster movement |
| Green Regenerator | 12 | 1.2 | 14 | 3 | Heals after 2 seconds without damage |
| Yellow Plated | 30 | 1 | 24 | 5 | Reduces ordinary hits by 1, minimum 0.5 |
| Violet Guardian | 75 + 15 shield | 0.85 | 45 | 10 | Shield and half-strength slowing |

The table gives base durability. Health and shields are multiplied by
`1 + growth * (wave - 1)`, with per-wave growth of 0%, 1.5%, 3%, 4.5%, and 6%
by tier. Regeneration caps at the balloon's scaled maximum. A Guardian at its
wave-14 introduction has 160.2 combined health and shield, requiring at least
five unbuffed level-5 Longshot hits.

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
linear upgrades and LAN multiplayer, but no map editor. Balance is a playable
starting point; longer routes offer more farm income and firing opportunities.

## Verify

```powershell
flutter analyze
flutter test
```

Tests cover maps, continuous movement, economy, L5 bounds, all enemy abilities,
farming, pause, once-only rewards, aiming, swept hits, victory/defeat and no-cheat
winning strategies for all seven levels. Network checks cover host/client state,
shared spending, waiting-room restart and connection cleanup. Widget tests load the real terrain and
exercise resized placement and menu/game flows at compact and desktop sizes.

```powershell
$env:SAVE_SCREENSHOTS = 'true'
flutter test test/game/board_test.dart test/ui_flow_test.dart
```

Screenshots go to build/test_snapshots/. Widget tests substitute a test font;
evaluate final typography and audio in the native Windows application. UI flows
are checked at 960x640 and 1920x1080, placement also at 1280x720.
