import 'dart:ui';

import 'package:flame/components.dart';
import 'package:flame/events.dart';
import 'package:flame/flame.dart';
import 'package:flutter/foundation.dart';
import 'int_size.dart';

class TileSet {
  final String _imagePath;
  final IntSize tileSize;
  final IntSize _mapSizeInTiles;
  late final List<Sprite> sprites;

  TileSet({
    required String imagePath,
    required this.tileSize,
    required IntSize mapSizeInTiles,
  }) : _imagePath = imagePath,
       _mapSizeInTiles = mapSizeInTiles;

  Future<void> load() async {
    final image = await Flame.images.load(_imagePath);
    sprites = List<Sprite>.generate(_mapSizeInTiles.y * _mapSizeInTiles.x, (
      index,
    ) {
      final x = (index % _mapSizeInTiles.x) * tileSize.x;
      final y = (index ~/ _mapSizeInTiles.x) * tileSize.y;
      return Sprite(
        image,
        srcPosition: Vector2(x.toDouble(), y.toDouble()),
        srcSize: tileSize.toVector2(),
      );
    });
  }
}

typedef TileCellOnTapCallback = void Function(TileCell cell);

class TileCell extends SpriteComponent with TapCallbacks {
  final int tileValue;
  final IntSize tilePosition;
  final TileCellOnTapCallback onTapDownCallback;
  final TileCellOnTapCallback onTapUpCallback;

  TileCell({
    super.position,
    super.size,
    super.sprite,
    required this.tileValue,
    required this.tilePosition,
    required this.onTapUpCallback,
    required this.onTapDownCallback,
  });

  @override
  void onTapDown(TapDownEvent event) {
    onTapDownCallback(this);
  }

  @override
  void onTapUp(TapUpEvent event) {
    onTapUpCallback(this);
  }
}

class TileMap extends PositionComponent {
  final TileSet tileSet;
  final IntSize mapSize;
  List<List<int>> mapValues = [];
  List<SpriteComponent> cells = [];
  PositionComponent _map = PositionComponent();
  late final TileCellOnTapCallback? onTileTapCallback;

  TileMap({
    required this.tileSet,
    required this.mapValues,
    super.position,
    double scale = 0.0,
    double perspective = 0.0,
    this.onTileTapCallback,
  }) : _map = PositionComponent(
         size:
             (IntSize(mapValues[0].length, mapValues.length) * tileSet.tileSize)
                 .toVector2(),
         anchor: Anchor.center,
       ),
       mapSize = IntSize(mapValues[0].length, mapValues.length),
       super(scale: Vector2.all(scale)) {
    onTileTapCallback ??= (TileCell tileCell) {
      debugPrint('Tile tapped: ${tileCell.tileValue} at position ${tileCell.tilePosition}');
    };
  }

  @override
  Future<void> onLoad() async {
    await tileSet.load();
    final tileSize = tileSet.tileSize;
    cells = List<SpriteComponent>.generate((mapSize.x * mapSize.y).toInt(), (
      index,
    ) {
      var position = Vector2(
        (index % mapSize.x) * tileSize.x.toDouble(),
        (index ~/ mapSize.x) * tileSize.y.toDouble(),
      );
      final x = index ~/ mapSize.x;
      final y = index % mapSize.x;
      final spriteValue = mapValues[x][y];
      return TileCell(
        position: position,
        size: Vector2(tileSize.x.toDouble(), tileSize.y.toDouble()),
        sprite: tileSet.sprites[spriteValue],
        tileValue: spriteValue,
        tilePosition: IntSize(y, x),
        onTapDownCallback: onTileTapCallback!,
        onTapUpCallback: onTileTapCallback!,
      );
    });
    _map.addAll(cells);
    add(_map);
  }
}
