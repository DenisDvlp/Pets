import 'package:wild_home/common/int_vector.dart';

import 'cell.dart';

class Map {
  List<List<Cell>> cells = [];

  void generate(int width, int height) {
    cells = List.generate(height, (y) {
      return List.generate(width, (x) {
        return Cell(IntVector2(x, y), );
      });
    });
  }

  int get width => cells.isEmpty ? cells[0].length : 0;
  int get height => cells.length;
}
