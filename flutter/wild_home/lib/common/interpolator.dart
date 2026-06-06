import 'dart:math';

class Interpolator {
  double _start = 0;
  late final double _duration;
  int _inOutFactor;
  int _coefficient;
  bool _loop;
  void Function(double value)? onUpdate;
  void Function()? onEnd;

  Interpolator(
    double duration, {
    int inOutFactor = 1,
    bool loop = false,
    bool reverse = false,
  }) : _duration = duration,
       _inOutFactor = inOutFactor,
       _loop = loop,
       _coefficient = reverse ? 2 : 1;

  void fromStart() {
    _start = 0;
  }

  void update(double dt) {
    if (!_loop && (_start >= _duration)) {
      return;
    }

    double fraction = (_start.remainder(_duration) + dt) / _duration;
    _start += dt;

    if (fraction >= 1) {
      fraction = _loop ? fraction.remainder(1) : 1;
    }

    final double value = (fraction < 0.5)
        ? _function(_coefficient * fraction)
        : 1 - _function(1 - _coefficient * fraction);

    onUpdate?.call(value);
    if (fraction >= 1) {
      onEnd?.call();
    }
  }

  double _function(double x) =>
      pow(2, _inOutFactor - 1) * pow(x, _inOutFactor).toDouble();
}
