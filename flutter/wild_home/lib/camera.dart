import 'package:flame/camera.dart';
import 'common/constants.dart';
class MainCamera extends CameraComponent {
  MainCamera() : super.withFixedResolution(width: screenWidth, height: screenHeight);
}
