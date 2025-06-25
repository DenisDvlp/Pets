import 'package:flame/game.dart';
import 'camera.dart';
import 'world.dart';

class MyGame extends FlameGame with SingleGameInstance {
  MyGame() : super(camera: MyCamera(), world: MyWorld());

  @override
  Future<void> onLoad() async {}
}
