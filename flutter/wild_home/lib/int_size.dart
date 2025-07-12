import 'package:flame/components.dart';

class IntSize {
  int x = 0;
  int y = 0;

  IntSize(this.x, this.y);

  IntSize.zero();

  IntSize.all(int x): this(x, x);

  IntSize.fromVector2(Vector2 v): this(v.x.toInt(), v.y.toInt());
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

  IntSize copy() {
    return IntSize(x, y);
  }

  IntSize operator -() => IntSize(-x, -y);

  IntSize operator -(IntSize other) => IntSize(
    x - other.x,
    y - other.y,
  );

  IntSize operator +(IntSize other) => IntSize(
    x + other.x,
    y + other.y,
  );

  IntSize operator *(IntSize other) => IntSize(
    x * other.x,
    y * other.y,
  );

  IntSize operator /(IntSize other) => IntSize(
    x ~/ other.x,
    y ~/ other.y,
  );

  String toString(){
    return 'IntSize{ x: $x, y: $y }';
  }
}