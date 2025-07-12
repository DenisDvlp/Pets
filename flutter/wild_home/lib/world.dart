import 'package:flame/camera.dart';
import 'package:flame/components.dart';
import 'tile_map.dart';
import 'int_size.dart';

class MyWorld extends World {

  final tileSet = TileSet(
    tileSize: IntSize(256, 256),
    mapSizeInTiles: IntSize(4, 4),
    imagePath: 'tiles.png'
  );

  void onTileTapCallback(TileCell tileCell) {
    print('[my] Tile tapped: ${tileCell.tileValue} at position ${tileCell.tilePosition}');
  }

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
      scale: 0.2,
      onTileTapCallback: onTileTapCallback,
    );
    add(tileMap);

  }
}
