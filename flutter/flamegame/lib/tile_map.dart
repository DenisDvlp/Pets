import 'package:flame/components.dart';
import 'package:flame/game.dart';
import 'package:flame/rendering.dart';
import 'package:flame/geometry.dart';

class TileMap extends PositionComponent {
  final Vector2 tileSize;
  final Vector2 mapSizeInTiles;
  final String imagePath;
  late final Sprite tileMap;
  List<SpriteComponent> tiles = [];
  PositionComponent map = PositionComponent();

  TileMap({
    required this.tileSize,
    required this.mapSizeInTiles,
    required this.imagePath,
    Vector2? position,
    double scale = 0.0,
    Vector3? rotate,
    double perspective = 0.0,
  }) : map = PositionComponent(
         size: Vector2(
           (tileSize.x * mapSizeInTiles.x).toDouble(),
           (tileSize.y * mapSizeInTiles.y).toDouble(),
         ),
         anchor: Anchor.center
       ),
  super(
        scale: Vector2.all(scale),
        position: position,
       ) {
    rotate ??= Vector3.zero();
    map.decorator =
      Rotate3DDecorator(
        angleX: tau * rotate.x,
        angleY: tau * rotate.y,
        angleZ: tau * rotate.z,
        perspective: perspective,
      );
    map.decorator.addLast(Transform2DDecorator(map.transform));
  }

  @override
  Future<void> onLoad() async {
    tileMap = await Sprite.load(imagePath);
    for (int y = 0; y < mapSizeInTiles.y; y++) {
      for (int x = 0; x < mapSizeInTiles.x; x++) {
        tiles.add(
          SpriteComponent(
            position: Vector2(
              (x * tileSize.x).toDouble(),
              (y * tileSize.y).toDouble(),
            ),
            size: Vector2(tileSize.x.toDouble(), tileSize.y.toDouble()),
            sprite: Sprite(
              tileMap.image,
              srcPosition: Vector2(
                (x * tileSize.x).toDouble(),
                (y * tileSize.y).toDouble(),
              ),
              srcSize: Vector2(tileSize.x.toDouble(), tileSize.y.toDouble()),
            ),
          ),
        );
      }
    }
    add(map);
    map.addAll(tiles);
  }
}
