#include "BasicTypes.h"
#include <iostream>
#include <memory>

using namespace std;

void check(const bool isCorrect) {
  if (isCorrect)
    cout << "OK\n";
  else
    cout << "FAIL\n";
}

void testPoint()
{
  CPoint p1(3, 4);
  CPoint p2(0, 0);
  CPoint p3(2, -6);
  CPoint p4(3, 4);
  CPoint p5(-2, 0);

  check(p1 > p2);
  check(p1 > p5);
  check(p5 < p2);
  check(p5 > p2);
  check(p5 >= p2);
  check(p5 <= p2);
  check(p1.distance(p2 + p4));

  check(p1 > p2);
  check(p1.distance(p2) == 5);
  check(p2.distance(p1) == 5);
  check(p1 + p2 == p1);
  check(p2 != p3);
  check(p1 >= p4);
  check(p1 <= p4);
  check(p1 == p4);

  p1.shift(-3, -4);
  check(p1 > p2);
  check(p1 < p2);
  check(p1 >= p2);
  check(p1 <= p2);
  check(p1 == p2);
  check(p1 != p2);


  p2 = p4 + p3;
  p2 = p2 - p4;
  check(p3 == p2);

  p2.set(p3.x(), p3.y());
  check(p3 == p2);

  p1.x(-10);
  check(p1.x() == -10);
  p1.y(-11);
  check(p1.y() == -11);

  p1.set(1, 1);
  p2.set(2, 2);
  p2 += p1;
  check(p2 == CPoint(3,3));

}

CSize getSize()
{
  return CSize();
}

void testSize()
{
  CSize s1(3, 4);
  CSize s2(0, 0);
  CSize s3(-3, -4);

  check("\nCSize\n");
  check(s1 == s2);
  check(s1 != s2);
  check(s1 == s3);
  check(s1 != s3);
  check(!s1.isEmpty());
  check(s2.isEmpty());
  check(s3.isEmpty());
  check(s1.square() == 12);
  check(s2.square() == 0);
  check(s3.square() == 0);
  s3.inc(s1.width(), s1.height());
  check(s3 == s1);
  s2.set(-3, -4);
  s2.width(-3);
  s2.height(-4);
  check(CSize(-3, -4) == s2);
  check(s2 == getSize());
  check(!s2.width());
  check(!s2.height());
  check(s2 == CSize(-3, -4));

  s3 = CSize(4, 4);
  s3.inc(-5, 3);
  check(s3 == CSize(-1, 7));
}

void testRect()
{
  CRect r1(0, 0, 0, 0);
  CRect r2(0, 0, 1, 0);
  CRect r3(0, 0, 0, 1);
  CRect r4(0, 0, 7, 3);
  CRect r5(0, 1, 0, 0);
  CRect r6(1, 0, -3, -7);
  CRect r7(1, 1, 0, 0);

  check(r1.isEmpty());
  check(r2.isEmpty());
  check(r3.isEmpty());
  check(!r4.isEmpty());
  check(r5.isEmpty());
  check(r6.isEmpty());
  check(r7.isEmpty());

  check(r1.isZero());
  check(!r2.isZero());
  check(!r3.isZero());
  check(!r4.isZero());
  check(!r5.isZero());
  check(!r6.isZero());
  check(!r7.isZero());

  r1.set(1, 1, 0, 0);
  check(r1 == r7);
  r1.set(r2.position(), r2.size());
  check(r1 == r2);
  r1.set(r3.x(), r3.y(), r3.size());
  check(r1 == r3);
  r1.set(r6.x(), r6.y(), r6.width(), r6.height());
  check(r1 == r6);
  r1.set(r4.position(), r4.width(), r4.height());
  check(r1 == r4);

  check(r4.square() == 21);
  check(r6.square() == 0);
  check(r5.square() == 0);
  r5.x(-10);
  check(r5.x() == -10);
  r5.y(-11);
  check(r5.y() == -11);
  r5.width(-12);
  check(r5.width() == 0);
  r5.height(-13);
  check(r5.height() == 0);
  r5.width(12);
  check(r5.width() == 12);
  r5.height(13);
  check(r5.height() == 13);

  r5 = CRect(1,1,4,4);
  r5.expand(1, 1, 2, 2);
  check(r5 == CRect(0, 0, 7, 7));

  check(r5.position().isZero());
  check(r5.size() == CSize(7, 7));
  check(r5.square() == 49);

  r5.x(2);
  r5.y(4);
  CPoint p = r5.localPoint(CPoint(2, 4));
  check(p == CPoint(0, 0));

  p = r5.absolutePoint(CPoint(2, 4));
  check(p == CPoint(4, 8));

  r1.set(1, 2, 3, 4);
  check(r1.left() == 1);
  check(r1.right() == 4);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 3);

  r1.left(-2);
  check(r1.left() == -2);
  check(r1.right() == 4);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 6);

  r1.left(7);
  check(r1.left() == 4);
  check(r1.right() == 4);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 0);

  r1.left(7);
  check(r1.left() == 4);
  check(r1.right() == 4);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 0);

  r1.left(1);
  check(r1.left() == 1);
  check(r1.right() == 4);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 3);

  r1.right(-2);
  check(r1.left() == 1);
  check(r1.right() == 1);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 0);

  r1.right(6);
  check(r1.left() == 1);
  check(r1.right() == 6);
  check(r1.top() == 2);
  check(r1.bottom() == 6);
  check(r1.width() == 5);

  r1.top(8);
  check(r1.left() == 1);
  check(r1.right() == 6);
  check(r1.top() == 6);
  check(r1.bottom() == 6);
  check(r1.height() == 0);

  r1.top(-8);
  check(r1.left() == 1);
  check(r1.right() == 6);
  check(r1.top() == -8);
  check(r1.bottom() == 6);
  check(r1.height() == 14);

  r1.bottom(-10);
  check(r1.left() == 1);
  check(r1.right() == 6);
  check(r1.top() == -8);
  check(r1.bottom() == -8);
  check(r1.height() == 0);
  check(r1.square() == 0);

  r1.bottom(8);
  check(r1.left() == 1);
  check(r1.right() == 6);
  check(r1.top() == -8);
  check(r1.bottom() == 8);
  check(r1.height() == 16);
  check(r1.square() == 80);

  r1.left(0);
  r1.right(0);
  r1.top(0);
  r1.bottom(0);

  check(r1.left() == 0);
  check(r1.right() == 0);
  check(r1.top() == 0);
  check(r1.bottom() == 0);
  check(r1.square() == 0);
  check(r1.isZero());
  check(r1.isEmpty());

  r1.position(2, 3);
  check(r1.localPoint(0, 0) == CPoint(-2, -3));
  check(r1.absolutePoint(0, 0) == CPoint(2, 3));
  check(r1.localPoint(2, 3) == CPoint(0, 0));
  check(r1.absolutePoint(2, 3) == CPoint(4, 6));

  r1.set(2, 3, 4, 5);
  r2.set(0, 0, 4, 5);

  r3 = r1 + r2;
  check(r3 == CRect(0, 0, 6, 8));
  check(r3.hasRect(r1));
  check(!r1.hasRect(r2));
  check(r1.isIntersectWith(r2));
  r3 = r1 * r2;
  check(r3 == CRect(2, 3, 2, 2));
  check(r1.hasRect(r3));
  r3 += r1;
  check(r3 == r1);
  r1 *= r2;
  check(r1 == CRect(2, 3, 2, 2));

  r1.set(2, 3, 4, 5);
  r2.set(-10, 0, 2, 2);
  check(!r1.isIntersectWith(r2));
  check(!r1.hasRect(r2));
  r2.set(10, 0, 2, 2);
  check(!r1.isIntersectWith(r2));
  check(!r1.hasRect(r2));
  r2.set(0, 10, 2, 2);
  check(!r1.isIntersectWith(r2));
  check(!r1.hasRect(r2));
  r2.set(0, -10, 2, 2);
  check(!r1.isIntersectWith(r2));
  check(!r1.hasRect(r2));
  r2.set(3, 3, 2, 2);
  check(r1.isIntersectWith(r2));
  check(r1.hasRect(r2));

  p = r1.center();
  check(p == CPoint(4, 5));
  r1.center(0, 0);
  check(r1.position() == CPoint(-2, -2));
  check(r1.size() == CSize(4, 5));
}

void testStrings()
{
  /*StringList s1 = "1\n22\n333";
  check(s1.size() == 3);
  check(s1[0] == "1");
  check(s1[1] == "22");
  check(s1[2] == "333");
  check(s1.text() == "1\n22\n333");
  s1.insert("!", 0);
  check(s1[0] == "!");
  check(s1[1] == "1");
  s1.insert(s1, 5);
  print(s1);
  CStrings s2 = CStrings::split("----223332222444422", "22");
  s2.add("zzz");
  print(s2);
  s2.removeByValue("zzz");
  s2.removeByValueAll("");
  s2.clear();
  print(s2);
  s2.add("!");
  s2.add(s1);
  print(s2);
  int index = s2.find("qawe");
  check(index == -1);
  index = s2.find("!");
  check(index == 0);
  s2.text("123v345v367v3", "v3");
  check(s2.text() == "123\n45\n67\n");*/
}

template<typename T>
void print(T &list) {
  cout << "-----" << endl;
  for (int i = 0; i < list.size(); i++) {
    cout << list[i] << endl;
  }
}
template<typename T>
void print(std::vector<T> &list) {
  cout << "-----" << endl;
  for (auto &it : list) {
    cout << it << endl;
  }
}
template<typename T>
void print(std::list<T> &list) {
  cout << "-----" << endl;
  for(auto &it : list){
    cout << it << endl;
  }
}
void print(int arr[], int size) {
  cout << "-----" << endl;
  for (int i = 0; i < size; i++) {
    cout << arr[i] << endl;
  }
}


void testList()
{
  vector<STDString> v = {
    "v1",
    "v2",
    "v3",
    "v4",
  };
  list<STDString> l = {
    "l1",
    "l2",
    "l3",
    "l4",
  };
  STDString s1 = "s1";
  STDString s2 = "s2";
  Vector<STDString> l1 = {
    "1",
    "2",
    "3",
    "4",
    "4",
    "4",
  };
  Vector<STDString> l2;
  check(l1.size() == 6);
  check(l2.size() == 0);
  l2 = l1;
  check(l2.size() == 6);
  l1.clear();
  check(l1.size() == 0);
  check(l2[0] == "1");
  check(l2[1] == "2");
  check(l2[2] == "3");
  check(l2[3] == "4");
  check(l2 == l2);
  check(l1 != l2);
  l2.sort();
  l2.reverse(2, 3);
  l1.add({ "a","b" });
  check(l1[0] == "a");
  check(l1[1] == "b");
  l2.removeByValueAll("4", 3, 10);
  check(l2.find("4") == 2);
  l2.removeByValue("4", 2, 10);
  check(l2.find("4") == -1);
  l2.replace("2", "1");
  l2.replace("1", "2");
  //l2.replace("2", { "x", "y" });
  print(v);
  print(l);
  print(l2);
}

void test()
{
  //testPoint();
  //testSize();
  //testRect();
  //testStrings();
  testList();
}

int main() {
  //test();
  return 0;
}

