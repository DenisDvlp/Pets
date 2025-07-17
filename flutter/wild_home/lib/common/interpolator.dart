import 'dart:math';

enum Interpolation {
  linear,
  quad,
  cubic,
  outLinear,
  outQuad,
  outCubic,
  sin,
  cos,
}

class Interpolator {
  final Interpolation _interpolation;
  double _start = 0;
  late final double _duration;
  bool loop;
  void Function(double value)? onUpdate;
  void Function()? onEnd;

  Interpolator(double duration, Interpolation interpolation, this.loop)
    : _duration = duration,
      _interpolation = interpolation;

  void fromStart(){
    _start = 0;
  }

  void update(double dt) {
    if(!loop && (_start ~/ _duration) > 0 ) {
      return;
    }

    double fraction = (_start.remainder(_duration) + dt) / _duration;
    _start += dt;

    if(fraction >= 1) {
      fraction = 1;
    }


    double value = 0;
    switch (_interpolation) {
      case Interpolation.linear:
        value = _linear(fraction);
      case Interpolation.quad:
        value = _quad(fraction);
      case Interpolation.cubic:
        value = _cubic(fraction);
      case Interpolation.outLinear:
        value = _outLinear(fraction);
      case Interpolation.outQuad:
        value = _outQuad(fraction);
      case Interpolation.outCubic:
        value = _outCubic(fraction);
      case Interpolation.sin:
        value = _sin(fraction);
      case Interpolation.cos:
        value = _cos(fraction);
    }
    onUpdate?.call(value);
    if(fraction >= 1) {
      onEnd?.call();
    }
  }

  double _linear(double t) => t;
  double _quad(double t) => t * t;
  double _cubic(double t) => t * t * t * t;
  double _sin(double t) => sin(t * pi);
  double _outLinear(double t) => 1 - _linear(t);
  double _outQuad(double t) => 1 - _quad(t);
  double _outCubic(double t) => 1 - _cubic(t);
  double _cos(double t) => 1 - _sin(t);
}
