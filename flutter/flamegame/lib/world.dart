import 'package:flame/camera.dart';
import 'package:flame/components.dart';
import 'package:flamegame/tile_map.dart';

class MyWorld extends World {

  TileMap tileMap = TileMap(
    tileSize: Vector2(256.0, 256.0),
    mapSizeInTiles: Vector2(4.0, 4.0),
    imagePath: 'tiles.png', // imagePath
    rotate:Vector3(-0.16, 0.0, -0.125),
    perspective: 0.000,
    position: Vector2(100, 0),
    scale: 0.5,
  );
  MyWorld() : super();

  @override
  Future<void> onLoad() async {
    add(tileMap);
  }
}
