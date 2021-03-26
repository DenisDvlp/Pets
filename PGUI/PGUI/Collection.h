#pragma once
#include <string>
#include <vector>
#include "Macros.h"

class CPoint
{
  int m_x = 0;
  int m_y = 0;

public:

  CPoint();
  CPoint(int x, int y);

  void set(int x, int y);
  void shift(int dx, int dy);
  int x();
  void x(int x);
  int y();
  void y(int y);

  double distance(CPoint point);

  bool operator==(CPoint point);
  bool operator!=(CPoint point);
  bool operator>(CPoint point);
  bool operator<(CPoint point);
  bool operator>=(CPoint point);
  bool operator<=(CPoint point);
  CPoint operator+(CPoint point);
  CPoint operator-(CPoint point);
};

class CRect;

class CSize
{
  int m_width = 0;
  int m_height = 0;

public:

  CSize();
  CSize(int width, int height);

  void set(int width, int height);
  void shift(int dwidth, int dheight);
  int width();
  void width(int width);
  int height();
  void height(int height);

  int square();
  CRect rect();
  bool isEmpty();

  bool operator==(CSize size);
  bool operator!=(CSize size);
};

class CRect
{
  CPoint m_position;
  CSize m_size;

public:

  CRect();
  CRect(CPoint position, CSize size);
  CRect(CPoint position, int width, int height);
  CRect(int x, int y, CSize size);
  CRect(int x, int y, int width, int height);

  void set(CPoint position, CSize size);
  void set(CPoint position, int width, int height);
  void set(int x, int y, CSize size);
  void set(int x, int y, int width, int height);

  int  x();
  void x(int x);
  int  y();
  void y(int y);
  int  width();
  void width(int width);
  int  height();
  void height(int height);

  int  left();
  void left(int left);
  int  top();
  void top(int top);
  int  right();
  void right(int right);
  int  bottom();
  void bottom(int bottom);

  CPoint leftTop();
  void   leftTop(CPoint point);
  CPoint rightTop();
  void   rightTop(CPoint point);
  CPoint leftBottom();
  void   leftBottom(CPoint point);
  CPoint rightBottom();
  void   rightBottom(CPoint point);
  CPoint center();
  void   center(CPoint center);

  int    square();
  CPoint position();
  CSize  size();
  void   expand(int left, int top, int right, int bottom);
  CPoint localPoint(CPoint absolutePoint);
  CPoint localPoint(CPoint absolutePoint, CRect relativeRect);
  CPoint absolutePoint(CPoint localPoint);
  CPoint absolutePoint(CPoint localPoint, CRect relativeRect);
  CRect  unionRect(CRect rect);
  CRect  intersectRect(CRect rect);

  bool isIntersectWith(CRect rect);
  bool hasRect(CRect rect);
  bool hasPoint(CPoint point);
  bool isEmpty();

  bool operator==(CRect rect);
  bool operator!=(CRect rect);
};

typedef std::string CString;

class CStrings
{
  typedef std::vector<std::string> ArrayOfStrings;

  ArrayOfStrings m_strings;

  static void splitHelper(ArrayOfStrings &stringsDest, CString &string, char delimiter);
  static void insertPureHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings);
  static void insertHelper(ArrayOfStrings &stringsDest, int index, CString &string);
  static void insertHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings);

public:
  static CStrings split(CString string, char delimiter);

  CStrings();
  CStrings(CString string);
  CStrings(ArrayOfStrings strings);

  int size();
  CString text();
  CString delimitedText(CString delimiter);
  void text(CString string);

  void add(CString string);
  void add(CStrings strings);
  void add(ArrayOfStrings strings);
  void insert(int index, CString text);
  void insert(int index, CStrings strings);
  void insert(int index, ArrayOfStrings strings);
  void remove(int index);
  void remove(CString string);
  void remove(int from, int count);
  void clear();
  int find(CString string);
  CSize drawingSize();

  CString& operator[](int index);
};