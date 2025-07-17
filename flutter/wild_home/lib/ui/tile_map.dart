import 'package:flame/components.dart';
import 'package:flame/events.dart';
import 'package:flame/flame.dart';
import 'package:flame/sprite.dart';
import 'package:flutter/foundation.dart';
import '../common/int_vector.dart';
import '../common/interpolator.dart';

class TileSet {
  final String _imagePath;
  final IntVector2 tileSize;
  final IntVector2 _mapSizeInTiles;
  late final List<Sprite> sprites;

  TileSet({
    required String imagePath,
    required this.tileSize,
    required IntVector2 mapSizeInTiles,
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

class TileCell extends SpriteComponent with TapCallbacks, HoverCallbacks {
  int _tileValue;
  final IntVector2 tilePosition;
  TileCellOnTapCallback onTapDownCallback;
  TileCellOnTapCallback onTapUpCallback;

  TileCell({
    super.position,
    super.size,
    super.sprite,
    super.bleed,
    required int tileValue,
    required this.tilePosition,
    required this.onTapUpCallback,
    required this.onTapDownCallback,
  }) : _tileValue = tileValue;

  set tileValue (int newValue) {
    _tileValue = newValue;
  }

  int get tileValue => _tileValue;

  @override
  void onLoad() {

  }
  @override
  void onTapDown(TapDownEvent event) {
    onTapDownCallback(this);
  }

  @override
  void onTapUp(TapUpEvent event) {
    onTapUpCallback(this);
  }

  @override
  void update(double dt) {

  }

  @override
  void onHoverEnter() {

  }

  @override
  void onHoverExit() {

  }
}

class TileMap extends PositionComponent with PointerMoveCallbacks  {
  final TileSet tileSet;
  final IntVector2 mapSize;
  List<List<int>> mapValues = [];
  List<TileCell> cells = [];
  final interpolator = Interpolator(2.0, Interpolation.cubic, false);

  TileMap({
    required this.tileSet,
    required this.mapValues,
    super.position,
    double scale = 0.0,
    double perspective = 0.0
  }) : mapSize = IntVector2(mapValues[0].length, mapValues.length),
       super(
         size:
             (IntVector2(mapValues[0].length, mapValues.length) * tileSet.tileSize)
                 .toVector2(),
         anchor: Anchor.center,
         scale: Vector2.all(scale),
       ) {
  }

  void update(double dt) {
    interpolator.update(dt);
  }

  void onTileTapDownCallback(TileCell tileCell) {
    if(tileCell.tileValue == 0){
      interpolator.onUpdate?.call(1.0);
      interpolator.onEnd?.call();
      interpolator.onUpdate = (double value){
        tileCell.width = 256 * value;
        tileCell.height = 256 * value;
      };
      interpolator.onEnd = (){
        tileCell.sprite = tileSet.sprites[0];
        tileCell.tileValue = 0;
      };
      interpolator.fromStart();
      tileCell.sprite = tileSet.sprites[11];
      tileCell.tileValue = 11;
    }
    debugPrint(
      'Tile tapped down: ${tileCell.tileValue} at position ${tileCell.tilePosition}',
    );
  }

  void onTileTapUpCallback(TileCell tileCell) {
    debugPrint(
      'Tile tapped up: ${tileCell.tileValue} at position ${tileCell.tilePosition}',
    );
  }

  @override
  void onLoad() async {
    await tileSet.load();

    final tileSize = tileSet.tileSize;
    cells = List<TileCell>.generate((mapSize.x * mapSize.y).toInt(), (
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
        bleed: 0.5,
        tileValue: spriteValue,
        tilePosition: IntVector2(y, x),
        onTapDownCallback: onTileTapDownCallback!,
        onTapUpCallback: onTileTapUpCallback!,
      );
    });
    addAll(cells);
  }

  @override
  void onPointerMove(PointerMoveEvent event) {
    final localPosition = event.localPosition;
    print('Pointer moved to: $localPosition');
    final tileSize = tileSet.tileSize.toVector2();
    final x = (localPosition.x / tileSize.x).floor();
    final y = (localPosition.y / tileSize.y).floor();

    if (x >= 0 && x < mapSize.x && y >= 0 && y < mapSize.y) {
      final index = y * mapSize.x + x;
      if (index < cells.length) {
        final cell = cells[index];
        debugPrint('Mouse over tile: ${cell.tileValue} at position ($x, $y)');
      }
    }
  }
}
