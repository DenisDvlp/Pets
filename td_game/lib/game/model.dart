import 'dart:math' as math;
import 'dart:ui';

import 'game_config.dart';
export 'game_config.dart';

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
  int get refund => (spent * EconomyConfig.refundRate).floor();
}

class Balloon {
  Balloon(this.id, this.tier, {int wave = 1})
    : maxHealth =
          enemySpecs[tier].health *
          (1 + tierWaveRates[tier] * (math.max(1, wave) - 1)),
      maxShield =
          enemySpecs[tier].shield *
          (1 + tierWaveRates[tier] * (math.max(1, wave) - 1)) {
    health = maxHealth;
    shield = maxShield;
  }
  final int id;
  final int tier;
  final double maxHealth;
  final double maxShield;
  late double health;
  late double shield;
  double distance = 0;
  double sinceDamage = 0;
  double slow = 0;
  double slowTime = 0;
  double poison = 0;
  double poisonTime = 0;
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
  double life = TowerConfig.projectileLifetime;
}

class GameEffect {
  GameEffect(
    this.position,
    this.color, {
    this.radius = .35,
    this.lineEnd,
    this.label,
    this.life = .35,
    double? duration,
  }) : duration = duration ?? life;
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
  int money = EconomyConfig.initialMoney;
  int lives = EconomyConfig.initialLives;
  int wave = 0;
  int popped = 0;
  int revision = 0;
  int _speed = SimulationConfig.supportedSpeeds.first;
  int get speed => _speed;
  set speed(int value) => setSpeed(value);
  int _nextId = 1;
  int _spawned = 0;
  List<int> _schedule = [];
  double _spawnTime = 0;
  double _autoTime = WaveConfig.autoStartDelay;
  bool autoStart = false;
  bool replica = false;
  void Function(Map<String, dynamic>)? sendCommand;
  bool _applyingCommand = false;
  int? _replicaRemaining;
  Monkey? selected;
  TowerSpec? buying;
  String message = '';
  void Function(String sound)? onSound;
  bool get editable =>
      phase == SessionPhase.ready || phase == SessionPhase.running;
  int get remaining => replica && _replicaRemaining != null
      ? _replicaRemaining!
      : enemies.length + _schedule.length - _spawned;

  bool _send(Map<String, dynamic> command) {
    if (!replica || _applyingCommand) {
      return false;
    }
    sendCommand?.call(command);
    return true;
  }

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
    if (_send({
      'action': 'place',
      'kind': spec.kind.index,
      'column': cell.column,
      'row': cell.row,
    })) {
      return true;
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
        monkey.level >= TowerConfig.maxLevel) {
      return false;
    }
    final cost = monkey.spec.upgradeCost(monkey.level);
    if (money < cost) return false;
    if (_send({'action': 'upgrade', 'id': monkey.id})) return true;
    money -= cost;
    monkey.spent += cost;
    monkey.level++;
    revision++;
    onSound?.call('buy');
    return true;
  }

  bool sell() {
    final monkey = selected;
    if (!editable || monkey == null || !towers.contains(monkey)) return false;
    if (_send({'action': 'sell', 'id': monkey.id})) return true;
    towers.remove(monkey);
    money += monkey.refund;
    selected = null;
    revision++;
    return true;
  }

  void pause() {
    if (!editable) return;
    if (_send({'action': 'pause'})) return;
    _beforePause = phase;
    phase = SessionPhase.paused;
    revision++;
  }

  void resume() {
    if (phase != SessionPhase.paused) return;
    if (_send({'action': 'resume'})) return;
    phase = _beforePause;
    revision++;
  }

  void startWave() {
    if (phase != SessionPhase.ready || wave >= level.waves) return;
    if (_send({'action': 'wave'})) return;
    wave++;
    final maxTier = wave >= WaveConfig.tierThresholds[3]
        ? 4
        : wave >= WaveConfig.tierThresholds[2]
        ? 3
        : wave >= WaveConfig.tierThresholds[1]
        ? 2
        : wave >= WaveConfig.tierThresholds[0]
        ? 1
        : 0;
    final count =
        WaveConfig.baseEnemyCount +
        wave * WaveConfig.enemiesPerWave +
        (level.river ? WaveConfig.riverEnemyBonus : 0);
    _schedule = List.generate(
      count,
      (index) => index % WaveConfig.strongestTierFrequency == 0
          ? maxTier
          : (index + wave) % (maxTier + 1),
    );
    _spawned = 0;
    _spawnTime = 0;
    for (final monkey in towers) {
      monkey.farmTime = 0;
    }
    phase = SessionPhase.running;
    revision++;
  }

  void setSpeed(int value) {
    if (!SimulationConfig.supportsSpeed(value) ||
        phase == SessionPhase.won ||
        phase == SessionPhase.lost) {
      return;
    }
    if (_send({'action': 'speed', 'value': value})) return;
    if (speed == value) return;
    _speed = value;
    revision++;
  }

  void setTargetMode(TargetMode value) {
    final monkey = selected;
    if (!editable || monkey == null || !towers.contains(monkey)) return;
    if (_send({'action': 'target', 'id': monkey.id, 'value': value.index})) {
      return;
    }
    if (monkey.targetMode == value) return;
    monkey.targetMode = value;
    monkey.targetId = null;
    revision++;
  }

  static bool _integer(dynamic value, int minimum, int maximum) =>
      value is int && value >= minimum && value <= maximum;

  bool applyCommand(Map<String, dynamic> command) {
    if (replica || _applyingCommand) return false;
    final localSelected = selected;
    final localBuying = buying;
    final localMessage = message;
    _applyingCommand = true;
    try {
      final action = command['action'];
      if (action == 'place') {
        if (!_integer(command['kind'], 0, TowerKind.values.length - 1) ||
            !_integer(command['column'], 0, level.columns - 1) ||
            !_integer(command['row'], 0, level.rows - 1)) {
          return false;
        }
        final spec = towerSpecs[command['kind'] as int];
        final cell = (
          column: command['column'] as int,
          row: command['row'] as int,
        );
        if (!editable || !canPlace(cell) || money < spec.cost) return false;
        buying = spec;
        return place(cell);
      }
      if (action == 'upgrade' || action == 'sell' || action == 'target') {
        if (!_integer(command['id'], 1, SnapshotConfig.maxInteger)) {
          return false;
        }
        selected = towers
            .where((tower) => tower.id == command['id'])
            .firstOrNull;
        if (selected == null) return false;
        if (action == 'upgrade') return upgrade();
        if (action == 'sell') return sell();
        if (!editable ||
            !_integer(command['value'], 0, TargetMode.values.length - 1)) {
          return false;
        }
        setTargetMode(TargetMode.values[command['value'] as int]);
        return true;
      }
      switch (action) {
        case 'wave':
          if (phase != SessionPhase.ready || wave >= level.waves) return false;
          startWave();
          return true;
        case 'pause':
          if (!editable) return false;
          pause();
          return true;
        case 'resume':
          if (phase != SessionPhase.paused) return false;
          resume();
          return true;
        case 'speed':
          if (!SimulationConfig.supportsSpeed(command['value']) ||
              phase == SessionPhase.won ||
              phase == SessionPhase.lost) {
            return false;
          }
          setSpeed(command['value'] as int);
          return true;
        default:
          return false;
      }
    } finally {
      selected = localSelected != null && towers.contains(localSelected)
          ? localSelected
          : null;
      buying = localBuying;
      message = localMessage;
      _applyingCommand = false;
    }
  }

  Map<String, dynamic> toSnapshot({bool includePresentation = true}) => {
    'mapId': level.id,
    'money': money,
    'lives': lives,
    'wave': wave,
    'popped': popped,
    'phase': phase.index,
    'speed': speed,
    'autoStart': autoStart,
    'remaining': remaining,
    'revision': revision,
    'towers': towers
        .map(
          (tower) => {
            'id': tower.id,
            'kind': tower.spec.kind.index,
            'column': tower.cell.column,
            'row': tower.cell.row,
            'level': tower.level,
            'spent': tower.spent,
            'angle': tower.angle,
            'targetMode': tower.targetMode.index,
            'targetId': tower.targetId,
          },
        )
        .toList(),
    'enemies': enemies
        .map(
          (enemy) => {
            'id': enemy.id,
            'tier': enemy.tier,
            'health': enemy.health,
            'maxHealth': enemy.maxHealth,
            'shield': enemy.shield,
            'maxShield': enemy.maxShield,
            'distance': enemy.distance,
            'sinceDamage': enemy.sinceDamage,
            'slow': enemy.slow,
            'slowTime': enemy.slowTime,
            'poison': enemy.poison,
            'poisonTime': enemy.poisonTime,
            'resolved': enemy.resolved,
          },
        )
        .toList(),
    'shots': shots
        .take(includePresentation ? SnapshotConfig.maxShots : 0)
        .map(
          (shot) => {
            'position': [shot.position.dx, shot.position.dy],
            'velocity': [shot.velocity.dx, shot.velocity.dy],
            'damage': shot.damage,
            'kind': shot.kind.index,
            'level': shot.level,
            'life': shot.life,
          },
        )
        .toList(),
    'effects': effects
        .skip(
          includePresentation
              ? math.max(0, effects.length - SnapshotConfig.maxEffects)
              : effects.length,
        )
        .map(
          (effect) => {
            'position': [effect.position.dx, effect.position.dy],
            'color': effect.color.toARGB32(),
            'radius': effect.radius,
            'lineEnd': effect.lineEnd == null
                ? null
                : [effect.lineEnd!.dx, effect.lineEnd!.dy],
            'label': effect.label,
            'life': effect.life,
            'duration': effect.duration,
          },
        )
        .toList(),
  };

  void applySnapshot(
    Map<String, dynamic> snapshot, {
    bool preservePresentation = false,
    bool refreshEnemies = true,
  }) {
    if (!replica || snapshot['mapId'] != level.id) return;
    try {
      int integer(Map data, String key, int minimum, int maximum) {
        final value = data[key];
        if (!_integer(value, minimum, maximum)) throw const FormatException();
        return value as int;
      }

      double number(
        Map data,
        String key, {
        double minimum = 0,
        double maximum = SnapshotConfig.maxNumber,
      }) {
        final value = data[key];
        if (value is! num ||
            !value.isFinite ||
            value < minimum ||
            value > maximum) {
          throw const FormatException();
        }
        return value.toDouble();
      }

      bool boolean(Map data, String key) {
        final value = data[key];
        if (value is! bool) throw const FormatException();
        return value;
      }

      List<Map> records(String key) {
        final value = snapshot[key];
        if (value is! List ||
            value.length > SnapshotConfig.maxEntities ||
            value.any((item) => item is! Map)) {
          throw const FormatException();
        }
        return value.cast<Map>();
      }

      Offset point(dynamic value) {
        if (value is! List || value.length != 2) throw const FormatException();
        return Offset(
          number(
            {'x': value[0]},
            'x',
            minimum: -SnapshotConfig.maxCoordinate,
            maximum: SnapshotConfig.maxCoordinate,
          ),
          number(
            {'y': value[1]},
            'y',
            minimum: -SnapshotConfig.maxCoordinate,
            maximum: SnapshotConfig.maxCoordinate,
          ),
        );
      }

      final newMoney = integer(snapshot, 'money', 0, SnapshotConfig.maxInteger);
      final newLives = integer(
        snapshot,
        'lives',
        0,
        EconomyConfig.initialLives,
      );
      final newWave = integer(snapshot, 'wave', 0, level.waves);
      final newPopped = integer(
        snapshot,
        'popped',
        0,
        SnapshotConfig.maxInteger,
      );
      final newPhase =
          SessionPhase.values[integer(
            snapshot,
            'phase',
            0,
            SessionPhase.values.length - 1,
          )];
      if (!SimulationConfig.supportsSpeed(snapshot['speed'])) {
        throw const FormatException();
      }
      final newSpeed = snapshot['speed'] as int;
      final newAutoStart = boolean(snapshot, 'autoStart');
      final newRemaining = integer(
        snapshot,
        'remaining',
        0,
        SnapshotConfig.maxEntities,
      );
      final newRevision = integer(
        snapshot,
        'revision',
        0,
        SnapshotConfig.maxInteger,
      );
      final ids = <int>{};
      final cells = <Cell>{};
      int entityId(Map data) {
        final value = integer(data, 'id', 1, SnapshotConfig.maxInteger);
        if (!ids.add(value)) throw const FormatException();
        return value;
      }

      final newTowers = records('towers').map((data) {
        final cell = (
          column: integer(data, 'column', 0, level.columns - 1),
          row: integer(data, 'row', 0, level.rows - 1),
        );
        if (level.terrain(cell) != Terrain.grass || !cells.add(cell)) {
          throw const FormatException();
        }
        final tower =
            Monkey(
                entityId(data),
                towerSpecs[integer(data, 'kind', 0, towerSpecs.length - 1)],
                cell,
              )
              ..level = integer(data, 'level', 1, TowerConfig.maxLevel)
              ..spent = integer(data, 'spent', 0, SnapshotConfig.maxInteger)
              ..angle = number(
                data,
                'angle',
                minimum: -SnapshotConfig.maxNumber,
              )
              ..targetMode =
                  TargetMode.values[integer(
                    data,
                    'targetMode',
                    0,
                    TargetMode.values.length - 1,
                  )];
        if (data['targetId'] != null) {
          tower.targetId = integer(
            data,
            'targetId',
            1,
            SnapshotConfig.maxInteger,
          );
        }
        return tower;
      }).toList();
      final newEnemies = records('enemies').map((data) {
        final enemy = Balloon(
          entityId(data),
          integer(data, 'tier', 0, enemySpecs.length - 1),
          wave: newWave,
        );
        if ((number(data, 'maxHealth') - enemy.maxHealth).abs() >
                SnapshotConfig.healthTolerance ||
            (number(data, 'maxShield') - enemy.maxShield).abs() >
                SnapshotConfig.healthTolerance) {
          throw const FormatException();
        }
        enemy
          ..health = number(
            data,
            'health',
            minimum: -SnapshotConfig.maxNumber,
            maximum: enemy.maxHealth,
          )
          ..shield = number(data, 'shield', maximum: enemy.maxShield)
          ..distance = number(
            data,
            'distance',
            maximum: level.road.length.toDouble(),
          )
          ..sinceDamage = number(data, 'sinceDamage')
          ..slow = number(data, 'slow', maximum: BalloonConfig.maximumSlow)
          ..slowTime = number(
            data,
            'slowTime',
            minimum: -SnapshotConfig.maxNumber,
          )
          ..poison = number(data, 'poison')
          ..poisonTime = number(
            data,
            'poisonTime',
            minimum: -SnapshotConfig.maxNumber,
          )
          ..resolved = boolean(data, 'resolved');
        return enemy;
      }).toList();
      final newShots = records('shots')
          .map(
            (data) => Shot(
              point(data['position']),
              point(data['velocity']),
              number(data, 'damage'),
              TowerKind.values[integer(
                data,
                'kind',
                0,
                TowerKind.values.length - 1,
              )],
              integer(data, 'level', 1, TowerConfig.maxLevel),
            )..life = number(data, 'life', minimum: -SnapshotConfig.maxNumber),
          )
          .toList();
      final newEffects = records('effects').map((data) {
        final label = data['label'];
        if (label != null &&
            (label is! String ||
                label.length > SnapshotConfig.maxLabelLength)) {
          throw const FormatException();
        }
        return GameEffect(
          point(data['position']),
          Color(integer(data, 'color', 0, SnapshotConfig.maxColor)),
          radius: number(data, 'radius'),
          lineEnd: data['lineEnd'] == null ? null : point(data['lineEnd']),
          label: label as String?,
          life: number(data, 'life', minimum: -SnapshotConfig.maxNumber),
          duration: number(data, 'duration'),
        );
      }).toList();
      final selectedId = selected?.id;
      if (preservePresentation) {
        final existingEnemies = {for (final enemy in enemies) enemy.id: enemy};
        final existingTowers = {for (final tower in towers) tower.id: tower};
        final activeEnemyIds = newEnemies
            .where((enemy) => !enemy.resolved)
            .map((enemy) => enemy.id)
            .toSet();
        final incomingEnemyIds = newEnemies.map((enemy) => enemy.id).toSet();
        for (final enemy in enemies) {
          if (!incomingEnemyIds.contains(enemy.id) && !enemy.resolved) {
            effects.add(
              GameEffect(level.positionAt(enemy.distance), enemy.spec.color),
            );
          }
        }
        for (var index = 0; index < newEnemies.length; index++) {
          final incoming = newEnemies[index];
          final existing = existingEnemies[incoming.id];
          if (existing == null ||
              existing.tier != incoming.tier ||
              existing.maxHealth != incoming.maxHealth ||
              existing.maxShield != incoming.maxShield) {
            continue;
          }
          if (newPhase != SessionPhase.running) {
            existing.distance = incoming.distance;
          }
          if (refreshEnemies) {
            existing
              ..health = incoming.health
              ..shield = incoming.shield
              ..sinceDamage = incoming.sinceDamage
              ..slow = incoming.slow
              ..slowTime = incoming.slowTime
              ..poison = incoming.poison
              ..poisonTime = incoming.poisonTime
              ..resolved = incoming.resolved;
          }
          newEnemies[index] = existing;
        }
        for (var index = 0; index < newTowers.length; index++) {
          final incoming = newTowers[index];
          final existing = existingTowers[incoming.id];
          if (existing == null ||
              existing.spec.kind != incoming.spec.kind ||
              existing.cell != incoming.cell) {
            if (!activeEnemyIds.contains(incoming.targetId)) {
              incoming.targetId = null;
            }
            continue;
          }
          existing
            ..level = incoming.level
            ..spent = incoming.spent
            ..targetMode = incoming.targetMode;
          if (!activeEnemyIds.contains(existing.targetId)) {
            existing.targetId = null;
          }
          newTowers[index] = existing;
        }
      }
      towers
        ..clear()
        ..addAll(newTowers);
      enemies
        ..clear()
        ..addAll(newEnemies);
      if (!preservePresentation) {
        shots
          ..clear()
          ..addAll(newShots);
        effects
          ..clear()
          ..addAll(newEffects);
      } else if (newPhase == SessionPhase.ready ||
          newPhase == SessionPhase.won ||
          newPhase == SessionPhase.lost) {
        shots.clear();
      }
      money = newMoney;
      lives = newLives;
      wave = newWave;
      popped = newPopped;
      phase = newPhase;
      _speed = newSpeed;
      autoStart = newAutoStart;
      _replicaRemaining = newRemaining;
      revision = newRevision;
      selected = towers.where((tower) => tower.id == selectedId).firstOrNull;
    } on FormatException {
      return;
    }
  }

  void hit(Balloon enemy, double damage, {bool pierceArmor = false}) {
    if (enemy.resolved || !enemies.contains(enemy)) return;
    enemy.sinceDamage = 0;
    var applied = enemy.tier == BalloonConfig.armoredTier && !pierceArmor
        ? math.max(
            BalloonConfig.minimumArmoredDamage,
            damage - BalloonConfig.armorDamageReduction,
          )
        : damage;
    final shieldDamage = math.min(enemy.shield, applied);
    enemy.shield -= shieldDamage;
    applied -= shieldDamage;
    enemy.health -= applied;
    if (replica) {
      enemy.health = math.max(
        SnapshotConfig.minimumPredictedHealth,
        enemy.health,
      );
      return;
    }
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

  void predict(double dt) {
    if (replica) update(dt);
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
      if (!replica && autoStart && wave > 0) {
        _autoTime -= dt;
        if (_autoTime <= 0) startWave();
      }
      return;
    }
    if (!replica) {
      _spawnTime -= dt;
      while (_spawnTime <= 0 && _spawned < _schedule.length) {
        enemies.add(Balloon(_nextId++, _schedule[_spawned++], wave: wave));
        _spawnTime += math.max(
          WaveConfig.minimumSpawnInterval,
          WaveConfig.initialSpawnInterval -
              wave * WaveConfig.spawnIntervalReduction,
        );
        revision++;
      }
    }
    for (final enemy in enemies) {
      if (enemy.resolved) continue;
      enemy.sinceDamage += dt;
      if (enemy.tier == BalloonConfig.regeneratingTier &&
          enemy.sinceDamage > BalloonConfig.regenerationDelay) {
        enemy.health = math.min(
          enemy.maxHealth,
          enemy.health + dt * BalloonConfig.regenerationRate,
        );
      }
      if (enemy.slowTime > 0) {
        enemy.slowTime -= dt;
      }
      if (enemy.slowTime <= 0) enemy.slow = 0;
      enemy.distance += enemy.spec.speed * (1 - enemy.slow) * dt;
      if (enemy.distance >= level.road.length - 1) {
        if (replica) {
          enemy.distance = (level.road.length - 1).toDouble();
        } else {
          enemy.resolved = true;
          lives = math.max(0, lives - enemy.spec.leak);
          revision++;
        }
      }
    }
    if (!replica && lives <= 0) {
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
        if (_segmentDistance(position, previous, shot.position) >
            TowerConfig.projectileHitRadius) {
          continue;
        }
        if (shot.kind == TowerKind.bomb) {
          final radius = TowerConfig.splashRadii[shot.level - 1];
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
    if (replica) return;
    enemies.removeWhere((enemy) => enemy.resolved);
    if (_spawned == _schedule.length && enemies.isEmpty) {
      shots.clear();
      phase = wave == level.waves ? SessionPhase.won : SessionPhase.ready;
      _autoTime = WaveConfig.autoStartDelay;
      revision++;
      if (phase == SessionPhase.won) onSound?.call('win');
    }
  }

  void _updateTower(Monkey monkey, double dt) {
    if (monkey.spec.kind == TowerKind.support) {
      effects.add(
        GameEffect(
          monkey.position,
          const Color(0xFFFFB36B),
          radius: monkey.range,
          life: .12,
        ),
      );
      return;
    }
    if (monkey.spec.kind == TowerKind.farm) {
      if (replica) return;
      monkey.farmTime += dt;
      while (monkey.farmTime >= TowerConfig.farmInterval) {
        monkey.farmTime -= TowerConfig.farmInterval;
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
    var attackSpeed = TowerConfig.baseAttackSpeed;
    for (final support in towers) {
      if (support.spec.kind == TowerKind.support &&
          (support.position - monkey.position).distance <= support.range) {
        attackSpeed +=
            TowerConfig.supportAttackSpeedBonus +
            (support.level - 1) * TowerConfig.supportAttackSpeedPerLevel;
      }
    }
    monkey.cooldown = math.max(0, monkey.cooldown - dt * attackSpeed);
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
    monkey.angle += difference.clamp(
      -TowerConfig.rotationSpeed * dt,
      TowerConfig.rotationSpeed * dt,
    );
    if (difference.abs() > TowerConfig.aimingTolerance || monkey.cooldown > 0) {
      return;
    }
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
    } else if (monkey.spec.kind == TowerKind.laser) {
      hit(target, damage, pierceArmor: true);
      effects.add(
        GameEffect(
          monkey.position,
          const Color(0xFFB996FF),
          lineEnd: targetPosition,
          life: .18,
        ),
      );
    } else if (monkey.spec.kind == TowerKind.poison) {
      target.poison = damage * TowerConfig.poisonDamageMultiplier;
      target.poisonTime =
          TowerConfig.poisonDuration +
          monkey.level * TowerConfig.poisonDurationPerLevel;
      hit(
        target,
        damage * TowerConfig.poisonInitialDamageMultiplier,
        pierceArmor: true,
      );
      effects.add(
        GameEffect(
          targetPosition,
          const Color(0xFF79C95C),
          radius: .2,
          life: .2,
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
            (TowerConfig.slowFraction +
                (monkey.level - 1) * TowerConfig.slowFractionPerLevel) *
            (enemy.tier == BalloonConfig.guardianTier
                ? BalloonConfig.guardianSlowMultiplier
                : 1);
        if (slow >= enemy.slow) {
          enemy.slow = slow;
          enemy.slowTime = math.max(
            enemy.slowTime,
            TowerConfig.slowDuration +
                (monkey.level - 1) * TowerConfig.slowDurationPerLevel,
          );
        }
      }
    } else {
      final direction = Offset(math.cos(monkey.angle), math.sin(monkey.angle));
      shots.add(
        Shot(
          monkey.position + direction * TowerConfig.projectileOffset,
          direction * TowerConfig.projectileSpeed,
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
