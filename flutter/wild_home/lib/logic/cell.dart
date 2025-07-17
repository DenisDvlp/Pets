import 'package:wild_home/common/int_vector.dart';

enum Material {
  none,

  // Natural materials
  grass,
  dirt,
  sand,
  gravel,
  stone,
  cobblestone,
  clay,
  snow,
  ice,
  water,
  lava,
  wood,
  leaves,
  moss,
  mud,
  coal_ore,
  iron_ore,
  copper_ore,
  gold_ore,
  obsidian,

  // Artificial materials
  brick,
  glass,
  concrete,
  planks,
  torch,
  ladder,
  furnace,
  crafting_table,
  door,
  chest,
  wool,
  fence,
}

class Cell {
  static final int maxLayers = 64;

  final IntVector2 position;
  Material material = Material.none;
  int topValue = -1;
  int layer = -1;
  bool isDiggable = false;
  bool isBusy = false;

  Cell(this.position);
}
