import 'package:flutter/material.dart';
import 'app.dart';

export 'app.dart' show MonkeyDefenseApp;

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(const MonkeyDefenseApp());
}
