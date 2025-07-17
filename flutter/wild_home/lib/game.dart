import 'package:flame/camera.dart';
import 'package:flame/game.dart';
import 'camera.dart';
import 'world.dart';

class MyGame extends FlameGame with SingleGameInstance {
  MyGame() : super(camera: MyCamera(), world: MyWorld());

  @override
  Future<void> onGameResize(Vector2 size) async {
    super.onGameResize(size);
    camera.viewport = FixedResolutionViewport(resolution: size);
    print('Game resized to: $size');
  }

  @override
  Future<void> onLoad() async {}
}
