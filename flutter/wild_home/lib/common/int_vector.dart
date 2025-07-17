import 'package:flame/components.dart';

class IntVector2 {
  int x = 0;
  int y = 0;

  IntVector2(this.x, this.y);

  IntVector2.zero();

  IntVector2.all(int x): this(x, x);

  IntVector2.fromVector2(Vector2 v): this(v.x.toInt(), v.y.toInt());
  Vector2 toVector2() => Vector2(x.toDouble(), y.toDouble());

  void inflate(int dx, int dy) {
    x += dx;
    y += dy;
  }

  void inflateAll(int d) {
    inflate(d, d);
  }

  void set(int x, int y) {
    this.x = x;
    this.y = y;
  }

  void swap() {
    final temp = x;
    x = y;
    y = temp;
  }

  void scale(double factor) {
    x = (x * factor).toInt();
    y = (y * factor).toInt();
  }

  IntVector2 copy() {
    return IntVector2(x, y);
  }

  IntVector2 operator -() => IntVector2(-x, -y);

  IntVector2 operator -(IntVector2 other) => IntVector2(
    x - other.x,
    y - other.y,
  );

  IntVector2 operator +(IntVector2 other) => IntVector2(
    x + other.x,
    y + other.y,
  );

  IntVector2 operator *(IntVector2 other) => IntVector2(
    x * other.x,
    y * other.y,
  );

  IntVector2 operator /(IntVector2 other) => IntVector2(
    x ~/ other.x,
    y ~/ other.y,
  );

  @override
  String toString(){
    return 'IntVector2{x: $x, y: $y}';
  }
}
