import 'package:flame/camera.dart';
import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'camera.dart';
import 'world.dart';

class WildHomeGame extends FlameGame with SingleGameInstance {
  WildHomeGame() : super( world: MainWorld()) {
    camera = MainCamera();
  }

  @override
  Color backgroundColor() {
    // ignore: deprecated_member_use
    return Colors.red;
  }

  @override
  Future<void> onGameResize(Vector2 size) async {
    super.onGameResize(size);
    //camera.viewport = FixedResolutionViewport(resolution: size);
    print('Game resized to: $size');
  }

  @override
  Future<void> onLoad() async {}
}
