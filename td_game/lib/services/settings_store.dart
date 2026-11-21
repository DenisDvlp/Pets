import 'package:shared_preferences/shared_preferences.dart';

class DefenseSettings {
  const DefenseSettings({
    this.volume = .6,
    this.grid = false,
    this.autoStart = false,
    this.completed = const {},
  });
  final double volume;
  final bool grid;
  final bool autoStart;
  final Set<int> completed;
  DefenseSettings copyWith({
    double? volume,
    bool? grid,
    bool? autoStart,
    Set<int>? completed,
  }) => DefenseSettings(
    volume: volume ?? this.volume,
    grid: grid ?? this.grid,
    autoStart: autoStart ?? this.autoStart,
    completed: completed ?? this.completed,
  );
}

abstract interface class SettingsStore {
  Future<DefenseSettings> load();
  Future<void> save(DefenseSettings settings);
}

class MemorySettingsStore implements SettingsStore {
  MemorySettingsStore([this.value = const DefenseSettings()]);
  DefenseSettings value;
  @override
  Future<DefenseSettings> load() async => value;
  @override
  Future<void> save(DefenseSettings settings) async {
    value = settings;
  }
}

class PreferencesSettingsStore implements SettingsStore {
  final SharedPreferencesAsync _preferences = SharedPreferencesAsync();
  @override
  Future<DefenseSettings> load() async {
    try {
      final volume = await _preferences.getDouble('volume') ?? .6;
      final completed = await _preferences.getStringList('completed') ?? [];
      return DefenseSettings(
        volume: volume.isFinite ? volume.clamp(0, 1) : .6,
        grid: await _preferences.getBool('grid') ?? false,
        autoStart: await _preferences.getBool('autoStart') ?? false,
        completed: completed.map(int.tryParse).whereType<int>().toSet(),
      );
    } catch (_) {
      return const DefenseSettings();
    }
  }

  @override
  Future<void> save(DefenseSettings settings) async {
    try {
      await _preferences.setDouble('volume', settings.volume);
      await _preferences.setBool('grid', settings.grid);
      await _preferences.setBool('autoStart', settings.autoStart);
      await _preferences.setStringList(
        'completed',
        settings.completed.map((index) => '$index').toList(),
      );
    } catch (_) {}
  }
}
