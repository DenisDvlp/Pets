import 'dart:math' as math;
import 'dart:ui';

enum TowerKind { dart, rapid, bomb, frost, sniper, farm }

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
  double damageAt(int level) => damage * [1, 1.5, 2.25, 3.5, 5][level - 1];
  double intervalAt(int level) => interval * [1, .9, .8, .7, .6][level - 1];
  double rangeAt(int level) => range + (level - 1) * .25;
  int upgradeCost(int level) => (cost * [.75, 1.1, 1.6, 2.3][level - 1]).ceil();
  int incomeAt(int level) => [20, 35, 55, 80, 120][level - 1];
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
    8,
    0,
    Color(0xFF94BA46),
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
  EnemySpec('Blue Swift', 3, 1.5, 8, 2, Color(0xFF399EEB)),
  EnemySpec('Green Regenerator', 8, 1.2, 14, 3, Color(0xFF55BD78)),
  EnemySpec('Yellow Plated', 18, 1, 24, 5, Color(0xFFF7CC48)),
  EnemySpec('Violet Guardian', 40, .85, 45, 10, Color(0xFFB574DB), shield: 10),
];

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
        columns > 30 ||
        rows <= 0 ||
        rows > 20 ||
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
    'A winding trail through open grassland',
    24,
    16,
    15,
    [
      (column: 0, row: 3),
      (column: 7, row: 3),
      (column: 7, row: 10),
      (column: 17, row: 10),
      (column: 17, row: 5),
      (column: 23, row: 5),
    ],
  ),
  LevelDefinition(
    'River Switchback',
    'A longer route divided by a blue river',
    30,
    20,
    20,
    [
      (column: 0, row: 4),
      (column: 10, row: 4),
      (column: 10, row: 14),
      (column: 22, row: 14),
      (column: 22, row: 7),
      (column: 29, row: 7),
    ],
    river: true,
  ),
];

class Monkey {
  Monkey(this.id, this.spec, this.cell) : spent = spec.cost;
  final int id;
  final TowerSpec spec;
  final Cell cell;
  int level = 1;
  int spent;
  double angle = 0;
  double cooldown = 0;
  double farmTime = 0;
  TargetMode targetMode = TargetMode.first;
  int? targetId;
  Offset get position => Offset(cell.column + .5, cell.row + .5);
  double get range => spec.rangeAt(level);
  int get refund => (spent * .7).floor();
}

class Balloon {
  Balloon(this.id, this.tier)
    : health = enemySpecs[tier].health,
      shield = enemySpecs[tier].shield;
  final int id;
  final int tier;
  double health;
  double shield;
  double distance = 0;
  double sinceDamage = 0;
  double slow = 0;
  double slowTime = 0;
  bool resolved = false;
  EnemySpec get spec => enemySpecs[tier];
}

class Shot {
  Shot(this.position, this.velocity, this.damage, this.kind, this.level);
  Offset position;
  final Offset velocity;
  final double damage;
  final TowerKind kind;
  final int level;
  double life = 4;
}

class GameEffect {
  GameEffect(
    this.position,
    this.color, {
    this.radius = .35,
    this.lineEnd,
    this.label,
    this.life = .35,
  }) : duration = life;
  final Offset position;
  final Color color;
  final double radius;
  final Offset? lineEnd;
  final String? label;
  double life;
  final double duration;
}

class GameSession {
  GameSession(this.level);
  final LevelDefinition level;
  final List<Monkey> towers = [];
  final List<Balloon> enemies = [];
  final List<Shot> shots = [];
  final List<GameEffect> effects = [];
  SessionPhase phase = SessionPhase.ready;
  SessionPhase _beforePause = SessionPhase.ready;
  int money = 650;
  int lives = 100;
  int wave = 0;
  int popped = 0;
  int revision = 0;
  int speed = 1;
  int _nextId = 1;
  int _spawned = 0;
  List<int> _schedule = [];
  double _spawnTime = 0;
  double _autoTime = 3;
  bool autoStart = false;
  Monkey? selected;
  TowerSpec? buying;
  String message = '';
  void Function(String sound)? onSound;
  bool get editable =>
      phase == SessionPhase.ready || phase == SessionPhase.running;
  int get remaining => enemies.length + _schedule.length - _spawned;
  bool canPlace(Cell cell) =>
      level.contains(cell) &&
      level.terrain(cell) == Terrain.grass &&
      !towers.any((tower) => tower.cell == cell);
  void choose(TowerSpec spec) {
    buying = spec;
    selected = null;
    message = '';
    revision++;
  }

  void cancel() {
    buying = null;
    selected = null;
    message = '';
    revision++;
  }

  bool place(Cell cell) {
    if (!editable) return false;
    final existing = towers.where((tower) => tower.cell == cell).firstOrNull;
    if (existing != null && buying == null) {
      selected = existing;
      revision++;
      return true;
    }
    final spec = buying;
    if (spec == null) {
      cancel();
      return false;
    }
    if (!canPlace(cell) || money < spec.cost) {
      message = money < spec.cost
          ? 'Not enough cash'
          : 'Choose an empty grass tile';
      revision++;
      return false;
    }
    money -= spec.cost;
    final monkey = Monkey(_nextId++, spec, cell);
    towers.add(monkey);
    buying = null;
    selected = monkey;
    message = '';
    revision++;
    onSound?.call('buy');
    return true;
  }

  bool upgrade() {
    final monkey = selected;
    if (!editable ||
        monkey == null ||
        !towers.contains(monkey) ||
        monkey.level >= 5) {
      return false;
    }
    final cost = monkey.spec.upgradeCost(monkey.level);
    if (money < cost) return false;
    money -= cost;
    monkey.spent += cost;
    monkey.level++;
    revision++;
    onSound?.call('buy');
    return true;
  }

  bool sell() {
    final monkey = selected;
    if (!editable || monkey == null || !towers.remove(monkey)) return false;
    money += monkey.refund;
    selected = null;
    revision++;
    return true;
  }

  void pause() {
    if (!editable) return;
    _beforePause = phase;
    phase = SessionPhase.paused;
    revision++;
  }

  void resume() {
    if (phase != SessionPhase.paused) return;
    phase = _beforePause;
    revision++;
  }

  void startWave() {
    if (phase != SessionPhase.ready || wave >= level.waves) return;
    wave++;
    final maxTier = wave >= 14
        ? 4
        : wave >= 10
        ? 3
        : wave >= 6
        ? 2
        : wave >= 3
        ? 1
        : 0;
    final count = 8 + wave * 2 + (level.river ? 4 : 0);
    _schedule = List.generate(
      count,
      (index) => index % 3 == 0 ? maxTier : (index + wave) % (maxTier + 1),
    );
    _spawned = 0;
    _spawnTime = 0;
    for (final monkey in towers) {
      monkey.farmTime = 0;
    }
    phase = SessionPhase.running;
    revision++;
  }

  void hit(Balloon enemy, double damage, {bool pierceArmor = false}) {
    if (enemy.resolved || !enemies.contains(enemy)) return;
    enemy.sinceDamage = 0;
    var applied = enemy.tier == 3 && !pierceArmor
        ? math.max(.5, damage - 1)
        : damage;
    final shieldDamage = math.min(enemy.shield, applied);
    enemy.shield -= shieldDamage;
    applied -= shieldDamage;
    enemy.health -= applied;
    if (enemy.health <= 0) {
      enemy.resolved = true;
      money += enemy.spec.reward;
      popped++;
      effects.add(
        GameEffect(level.positionAt(enemy.distance), enemy.spec.color),
      );
      revision++;
      onSound?.call('pop');
    }
  }

  void update(double dt) {
    if (phase == SessionPhase.paused ||
        phase == SessionPhase.won ||
        phase == SessionPhase.lost) {
      return;
    }
    for (final effect in effects) {
      effect.life -= dt;
    }
    effects.removeWhere((effect) => effect.life <= 0);
    if (phase == SessionPhase.ready) {
      if (autoStart && wave > 0) {
        _autoTime -= dt;
        if (_autoTime <= 0) startWave();
      }
      return;
    }
    _spawnTime -= dt;
    while (_spawnTime <= 0 && _spawned < _schedule.length) {
      enemies.add(Balloon(_nextId++, _schedule[_spawned++]));
      _spawnTime += math.max(.35, .9 - wave * .025);
      revision++;
    }
    for (final enemy in enemies) {
      if (enemy.resolved) continue;
      enemy.sinceDamage += dt;
      if (enemy.tier == 2 && enemy.sinceDamage > 2) {
        enemy.health = math.min(enemy.spec.health, enemy.health + dt);
      }
      if (enemy.slowTime > 0) {
        enemy.slowTime -= dt;
      }
      if (enemy.slowTime <= 0) enemy.slow = 0;
      enemy.distance += enemy.spec.speed * (1 - enemy.slow) * dt;
      if (enemy.distance >= level.road.length - 1) {
        enemy.resolved = true;
        lives = math.max(0, lives - enemy.spec.leak);
        revision++;
      }
    }
    if (lives <= 0) {
      phase = SessionPhase.lost;
      buying = null;
      revision++;
      onSound?.call('lose');
      return;
    }
    for (final monkey in towers) {
      _updateTower(monkey, dt);
    }
    for (final shot in shots) {
      final previous = shot.position;
      shot.position += shot.velocity * dt;
      shot.life -= dt;
      for (final enemy in enemies) {
        if (enemy.resolved) continue;
        final position = level.positionAt(enemy.distance);
        if (_segmentDistance(position, previous, shot.position) > .25) continue;
        if (shot.kind == TowerKind.bomb) {
          final radius = [.9, 1, 1.1, 1.25, 1.5][shot.level - 1].toDouble();
          effects.add(
            GameEffect(position, const Color(0xFFFFA94A), radius: radius),
          );
          for (final nearby in enemies) {
            if ((level.positionAt(nearby.distance) - position).distance <=
                radius) {
              hit(nearby, shot.damage, pierceArmor: true);
            }
          }
        } else {
          hit(enemy, shot.damage);
        }
        shot.life = 0;
        break;
      }
    }
    shots.removeWhere((shot) => shot.life <= 0);
    enemies.removeWhere((enemy) => enemy.resolved);
    if (_spawned == _schedule.length && enemies.isEmpty) {
      shots.clear();
      phase = wave == level.waves ? SessionPhase.won : SessionPhase.ready;
      _autoTime = 3;
      revision++;
      if (phase == SessionPhase.won) onSound?.call('win');
    }
  }

  void _updateTower(Monkey monkey, double dt) {
    if (monkey.spec.kind == TowerKind.farm) {
      monkey.farmTime += dt;
      while (monkey.farmTime >= 8) {
        monkey.farmTime -= 8;
        final income = monkey.spec.incomeAt(monkey.level);
        money += income;
        effects.add(
          GameEffect(
            monkey.position,
            const Color(0xFFFADB65),
            label: '+\$$income',
            life: 1,
          ),
        );
        revision++;
      }
      return;
    }
    monkey.cooldown = math.max(0, monkey.cooldown - dt);
    final candidates = enemies
        .where(
          (enemy) =>
              !enemy.resolved &&
              (level.positionAt(enemy.distance) - monkey.position).distance <=
                  monkey.range,
        )
        .toList();
    if (candidates.isEmpty) {
      monkey.targetId = null;
      return;
    }
    candidates.sort((first, second) {
      final comparison = switch (monkey.targetMode) {
        TargetMode.first => second.distance.compareTo(first.distance),
        TargetMode.strongest => (second.health + second.shield).compareTo(
          first.health + first.shield,
        ),
        TargetMode.nearest =>
          (level.positionAt(first.distance) - monkey.position).distance
              .compareTo(
                (level.positionAt(second.distance) - monkey.position).distance,
              ),
      };
      return comparison == 0 ? first.id.compareTo(second.id) : comparison;
    });
    final target =
        candidates.where((enemy) => enemy.id == monkey.targetId).firstOrNull ??
        candidates.first;
    monkey.targetId = target.id;
    final targetPosition = level.positionAt(target.distance);
    final delta = targetPosition - monkey.position;
    final desired = math.atan2(delta.dy, delta.dx);
    final difference = math.atan2(
      math.sin(desired - monkey.angle),
      math.cos(desired - monkey.angle),
    );
    monkey.angle += difference.clamp(-7 * dt, 7 * dt);
    if (difference.abs() > .15 || monkey.cooldown > 0) return;
    monkey.cooldown = monkey.spec.intervalAt(monkey.level);
    final damage = monkey.spec.damageAt(monkey.level);
    if (monkey.spec.kind == TowerKind.sniper) {
      hit(target, damage, pierceArmor: true);
      effects.add(
        GameEffect(
          monkey.position,
          const Color(0xFFFFED9E),
          lineEnd: targetPosition,
          life: .15,
        ),
      );
    } else if (monkey.spec.kind == TowerKind.frost) {
      effects.add(
        GameEffect(
          monkey.position,
          const Color(0xFF8EE5F5),
          radius: monkey.range,
        ),
      );
      for (final enemy in candidates) {
        hit(enemy, damage);
        final slow =
            (.3 + (monkey.level - 1) * .05) * (enemy.tier == 4 ? .5 : 1);
        if (slow >= enemy.slow) {
          enemy.slow = slow;
          enemy.slowTime = 2 + (monkey.level - 1) * .25;
        }
      }
    } else {
      final direction = Offset(math.cos(monkey.angle), math.sin(monkey.angle));
      shots.add(
        Shot(
          monkey.position + direction * .35,
          direction * 6,
          damage,
          monkey.spec.kind,
          monkey.level,
        ),
      );
    }
  }

  static double _segmentDistance(Offset point, Offset start, Offset end) {
    final delta = end - start;
    final lengthSquared = delta.dx * delta.dx + delta.dy * delta.dy;
    if (lengthSquared == 0) return (point - start).distance;
    final relative = point - start;
    final fraction =
        ((relative.dx * delta.dx + relative.dy * delta.dy) / lengthSquared)
            .clamp(0.0, 1.0);
    return (point - (start + delta * fraction)).distance;
  }
}
