import 'package:flame/game.dart';
import 'package:flutter/material.dart';
import 'game.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();

  final MaterialApp app = MaterialApp(
    title: 'Flame Game',
    home: Scaffold(
      body: GameWidget(game: WildHomeGame()),
    ),
  );
  runApp(app);
}
