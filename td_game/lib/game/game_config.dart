import 'dart:ui';

abstract final class EconomyConfig {
  static const initialMoney = 650;
  static const initialLives = 100;
  static const refundRate = .7;
}

abstract final class TowerConfig {
  static const maxLevel = 5;
  static const damageMultipliers = <double>[1, 1.5, 2.25, 3.5, 5];
  static const intervalMultipliers = <double>[1, .9, .8, .7, .6];
  static const rangePerLevel = .25;
  static const upgradeCostMultipliers = <double>[.75, 1.1, 1.6, 2.3];
  static const farmIncome = <int>[20, 35, 55, 80, 120];
  static const farmInterval = 8.0;
  static const rotationSpeed = 7.0;
  static const aimingTolerance = .15;
  static const baseAttackSpeed = 1.0;
  static const supportAttackSpeedBonus = .1;
  static const supportAttackSpeedPerLevel = .05;
  static const poisonDamageMultiplier = 1.5;
  static const poisonInitialDamageMultiplier = .5;
  static const poisonDuration = 3.0;
  static const poisonDurationPerLevel = .25;
  static const slowFraction = .3;
  static const slowFractionPerLevel = .05;
  static const slowDuration = 2.0;
  static const slowDurationPerLevel = .25;
  static const projectileSpeed = 6.0;
  static const projectileOffset = .35;
  static const projectileLifetime = 4.0;
  static const projectileHitRadius = .25;
  static const splashRadii = <double>[.9, 1, 1.1, 1.25, 1.5];
}

abstract final class BalloonConfig {
  static const regeneratingTier = 2;
  static const armoredTier = 3;
  static const guardianTier = 4;
  static const minimumArmoredDamage = .5;
  static const armorDamageReduction = 1.0;
  static const regenerationDelay = 2.0;
  static const regenerationRate = 1.0;
  static const guardianSlowMultiplier = .5;
  static const maximumSlow = 1.0;
}

abstract final class WaveConfig {
  static const baseEnemyCount = 8;
  static const enemiesPerWave = 2;
  static const riverEnemyBonus = 4;
  static const tierThresholds = <int>[3, 6, 10, 14];
  static const strongestTierFrequency = 3;
  static const minimumSpawnInterval = .35;
  static const initialSpawnInterval = .9;
  static const spawnIntervalReduction = .025;
  static const autoStartDelay = 3.0;
}

abstract final class SimulationConfig {
  static const supportedSpeeds = <int>[1, 5];
  static bool supportsSpeed(Object? value) =>
      value is int && value > 0 && supportedSpeeds.contains(value);

  static const tickSeconds = 1 / 120;
  static const maxFrameSeconds = .1;
}

abstract final class MapConfig {
  static const maxColumns = 30;
  static const maxRows = 20;
}

abstract final class SnapshotConfig {
  static const snapshotInterval = Duration(milliseconds: 100);
  static const correctionInterval = Duration(seconds: 2);
  static const minimumPredictedHealth = .01;
  static const maxEntities = 4096;
  static const maxShots = 256;
  static const maxEffects = 128;
  static const maxLabelLength = 128;
  static const maxInteger = 0x7fffffff;
  static const maxColor = 0xffffffff;
  static const maxNumber = 1e9;
  static const maxCoordinate = 1000.0;
  static const healthTolerance = .000001;
}

enum TowerKind {
  dart,
  rapid,
  bomb,
  frost,
  sniper,
  farm,
  laser,
  support,
  poison,
}

enum TargetMode { first, strongest, nearest }

enum SessionPhase { ready, running, paused, won, lost }

enum Terrain { grass, road, water, rock }

typedef Cell = ({int column, int row});

class TowerSpec {
  const TowerSpec(
    this.kind,
    this.name,
    this.role,
    this.cost,
    this.damage,
    this.interval,
    this.range,
    this.color,
  );
  final TowerKind kind;
  final String name;
  final String role;
  final int cost;
  final double damage;
  final double interval;
  final double range;
  final Color color;
  double damageAt(int level) =>
      damage * TowerConfig.damageMultipliers[level - 1];
  double intervalAt(int level) =>
      interval * TowerConfig.intervalMultipliers[level - 1];
  double rangeAt(int level) => range + (level - 1) * TowerConfig.rangePerLevel;
  int upgradeCost(int level) =>
      (cost * TowerConfig.upgradeCostMultipliers[level - 1]).ceil();
  int incomeAt(int level) => TowerConfig.farmIncome[level - 1];
}

const towerSpecs = <TowerSpec>[
  TowerSpec(
    TowerKind.dart,
    'Dart Scout',
    'Balanced dart attacks',
    100,
    1,
    .65,
    3,
    Color(0xFF187E69),
  ),
  TowerSpec(
    TowerKind.rapid,
    'Rapid Gunner',
    'Fast single-target fire',
    220,
    1,
    .22,
    2.75,
    Color(0xFFE8AB33),
  ),
  TowerSpec(
    TowerKind.bomb,
    'Bomb Lobber',
    'Splash damage • armor piercing',
    280,
    3,
    1.3,
    3.5,
    Color(0xFFE96750),
  ),
  TowerSpec(
    TowerKind.frost,
    'Frost Monkey',
    'Area pulse • slows balloons',
    180,
    1,
    1.4,
    2.5,
    Color(0xFF58C5DC),
  ),
  TowerSpec(
    TowerKind.sniper,
    'Longshot',
    'Long range • armor piercing',
    350,
    8,
    1.8,
    7,
    Color(0xFF57668C),
  ),
  TowerSpec(
    TowerKind.farm,
    'Banana Farmer',
    'Cash every 8 active-wave seconds',
    250,
    0,
    TowerConfig.farmInterval,
    0,
    Color(0xFF94BA46),
  ),
  TowerSpec(
    TowerKind.laser,
    'Laser Monk',
    'Continuous piercing beam',
    320,
    2.5,
    .9,
    4,
    Color(0xFF9A67E8),
  ),
  TowerSpec(
    TowerKind.support,
    'Drum Captain',
    'Nearby monkeys attack faster',
    300,
    0,
    8,
    3.5,
    Color(0xFFCF7F3C),
  ),
  TowerSpec(
    TowerKind.poison,
    'Toxin Slinger',
    'Damage over time • strong against armor',
    240,
    1.5,
    1.1,
    3,
    Color(0xFF6DBB5A),
  ),
];

class EnemySpec {
  const EnemySpec(
    this.name,
    this.health,
    this.speed,
    this.reward,
    this.leak,
    this.color, {
    this.shield = 0,
  });
  final String name;
  final double health;
  final double speed;
  final int reward;
  final int leak;
  final Color color;
  final double shield;
}

const enemySpecs = <EnemySpec>[
  EnemySpec('Red Basic', 1, 1, 5, 1, Color(0xFFEF5966)),
  EnemySpec('Blue Swift', 4, 1.5, 8, 2, Color(0xFF399EEB)),
  EnemySpec('Green Regenerator', 12, 1.2, 14, 3, Color(0xFF55BD78)),
  EnemySpec('Yellow Plated', 30, 1, 24, 5, Color(0xFFF7CC48)),
  EnemySpec('Violet Guardian', 75, .85, 45, 10, Color(0xFFB574DB), shield: 15),
];

const tierWaveRates = <double>[0, .015, .03, .045, .06];

class LevelDefinition {
  LevelDefinition(
    this.name,
    this.subtitle,
    this.columns,
    this.rows,
    this.waves,
    List<Cell> corners, {
    this.river = false,
  }) {
    if (columns <= 0 ||
        columns > MapConfig.maxColumns ||
        rows <= 0 ||
        rows > MapConfig.maxRows ||
        waves <= 0 ||
        corners.length < 2 ||
        corners.any((cell) => !contains(cell))) {
      throw ArgumentError('Invalid map dimensions or route');
    }
    for (var index = 0; index < corners.length - 1; index++) {
      final start = corners[index];
      final end = corners[index + 1];
      if (start.column != end.column && start.row != end.row) {
        throw ArgumentError('Road segments must be orthogonal');
      }
      final steps =
          (end.column - start.column).abs() + (end.row - start.row).abs();
      for (var step = 0; step < steps; step++) {
        road.add((
          column: start.column + (end.column - start.column).sign * step,
          row: start.row + (end.row - start.row).sign * step,
        ));
      }
    }
    road.add(corners.last);
    if (road.length < 2 || road.toSet().length != road.length) {
      throw ArgumentError('Invalid map dimensions or route');
    }
    roadSet = road.toSet();
  }
  final String name;
  final String subtitle;
  String get id => name.toLowerCase().replaceAll(' ', '-');
  final int columns;
  final int rows;
  final int waves;
  final bool river;
  final List<Cell> road = [];
  late final Set<Cell> roadSet;
  bool contains(Cell cell) =>
      cell.column >= 0 &&
      cell.row >= 0 &&
      cell.column < columns &&
      cell.row < rows;
  Terrain terrain(Cell cell) {
    if (roadSet.contains(cell)) return Terrain.road;
    if (river && cell.column >= 14 && cell.column <= 16) return Terrain.water;
    if ((cell.column * 13 + cell.row * 7) % 71 == 0 && cell.row > 0) {
      return Terrain.rock;
    }
    return Terrain.grass;
  }

  Offset positionAt(double distance) {
    final clamped = distance.clamp(0.0, road.length - 1.0);
    final index = clamped.floor();
    final start = road[index];
    if (index == road.length - 1) {
      return Offset(start.column + .5, start.row + .5);
    }
    final end = road[index + 1];
    final fraction = clamped - index;
    return Offset(
      start.column + .5 + (end.column - start.column) * fraction,
      start.row + .5 + (end.row - start.row) * fraction,
    );
  }
}

final levels = <LevelDefinition>[
  LevelDefinition(
    'Meadow Bend',
    'Open grassland along a gentle multi-S trail',
    24,
    16,
    23,
    [
      (column: 0, row: 3),
      (column: 7, row: 3),
      (column: 7, row: 10),
      (column: 11, row: 10),
      (column: 11, row: 5),
      (column: 15, row: 5),
      (column: 15, row: 12),
      (column: 19, row: 12),
      (column: 19, row: 7),
      (column: 23, row: 7),
    ],
  ),
  LevelDefinition(
    'River Switchback',
    'Bank hairpins linked by separate river crossings',
    30,
    20,
    30,
    [
      (column: 0, row: 4),
      (column: 10, row: 4),
      (column: 10, row: 9),
      (column: 5, row: 9),
      (column: 5, row: 15),
      (column: 23, row: 15),
      (column: 23, row: 10),
      (column: 19, row: 10),
      (column: 19, row: 6),
      (column: 12, row: 6),
      (column: 12, row: 2),
      (column: 26, row: 2),
      (column: 26, row: 7),
      (column: 29, row: 7),
    ],
    river: true,
  ),
  LevelDefinition(
    'Mountain Pass',
    'Stepped ridges and deep mountain switchbacks',
    30,
    20,
    38,
    [
      (column: 0, row: 10),
      (column: 5, row: 10),
      (column: 5, row: 2),
      (column: 10, row: 2),
      (column: 10, row: 6),
      (column: 15, row: 6),
      (column: 15, row: 16),
      (column: 20, row: 16),
      (column: 20, row: 3),
      (column: 25, row: 3),
      (column: 25, row: 10),
      (column: 29, row: 10),
    ],
  ),
  LevelDefinition(
    'Desert Oasis',
    'Nested open detours around an oasis clearing',
    28,
    18,
    27,
    [
      (column: 0, row: 9),
      (column: 3, row: 9),
      (column: 3, row: 2),
      (column: 23, row: 2),
      (column: 23, row: 6),
      (column: 7, row: 6),
      (column: 7, row: 14),
      (column: 18, row: 14),
      (column: 18, row: 10),
      (column: 26, row: 10),
      (column: 26, row: 16),
      (column: 27, row: 16),
    ],
  ),
  LevelDefinition(
    'Crystal Crossroads',
    'Angular hooks through four crystal quadrants',
    25,
    17,
    30,
    [
      (column: 0, row: 8),
      (column: 6, row: 8),
      (column: 6, row: 3),
      (column: 14, row: 3),
      (column: 14, row: 7),
      (column: 10, row: 7),
      (column: 10, row: 13),
      (column: 18, row: 13),
      (column: 18, row: 3),
      (column: 22, row: 3),
      (column: 22, row: 13),
      (column: 24, row: 13),
    ],
  ),
  LevelDefinition(
    'Volcano Loop',
    'Two open curls around an untouched volcanic core',
    22,
    18,
    33,
    [
      (column: 0, row: 9),
      (column: 3, row: 9),
      (column: 3, row: 3),
      (column: 9, row: 3),
      (column: 9, row: 13),
      (column: 5, row: 13),
      (column: 5, row: 16),
      (column: 17, row: 16),
      (column: 17, row: 5),
      (column: 13, row: 5),
      (column: 13, row: 2),
      (column: 20, row: 2),
      (column: 20, row: 14),
      (column: 21, row: 14),
    ],
  ),
  LevelDefinition(
    'Twin Rivers',
    'Unequal bank loops along a broad river slalom',
    28,
    20,
    36,
    [
      (column: 0, row: 5),
      (column: 8, row: 5),
      (column: 8, row: 2),
      (column: 22, row: 2),
      (column: 22, row: 8),
      (column: 5, row: 8),
      (column: 5, row: 16),
      (column: 11, row: 16),
      (column: 11, row: 12),
      (column: 25, row: 12),
      (column: 25, row: 17),
      (column: 27, row: 17),
    ],
    river: true,
  ),
];
