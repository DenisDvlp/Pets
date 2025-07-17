import 'package:flame/camera.dart';
import 'package:flame/components.dart';
import 'ui/tile_map.dart';
import 'common/int_vector.dart';

class MyWorld extends World {

  final tileSet = TileSet(
    tileSize: IntVector2(256, 256),
    mapSizeInTiles: IntVector2(4, 4),
    imagePath: 'tiles.png'
  );

  @override
  Future<void> onLoad() async {
    final tileMap = TileMap(
      tileSet: tileSet,
      mapValues: [
        [0, 1, 2, 3],
        [0, 1, 2, 3],
        [4, 5, 8, 7],
        [4, 5, 6, 7],
        [8, 9, 10, 11],
        [12, 13, 14, 15],
      ],
      position: Vector2(0, 0),
      scale: 1.0
    );
    add(tileMap);

  }
}
