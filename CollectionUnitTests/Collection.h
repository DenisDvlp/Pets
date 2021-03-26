#pragma once
#include <string>
#include <vector>

class CPoint
{
  int m_x = 0;
  int m_y = 0;

public:

  CPoint();
  CPoint(int x, int y);

  void    set(int x, int y);
  void    shift(int dx, int dy);
          
  int     x();
  void    x(int x);
  int     y();
  void    y(int y);
          
  bool    isZero();
  double  distance(CPoint point);
          
  bool    operator==(CPoint point);
  bool    operator!=(CPoint point);
  bool    operator>(CPoint point);
  bool    operator<(CPoint point);
  bool    operator>=(CPoint point);
  bool    operator<=(CPoint point);
  CPoint  operator+(CPoint point);
  CPoint  operator-(CPoint point);
  CPoint& operator+=(CPoint point);
  CPoint& operator-=(CPoint point);
};

class CRect;

class CSize
{
  int m_width  = 0;
  int m_height = 0;

public:

  CSize();
  CSize(int width, int height);

  void  set(int width, int height);

  int   width();
  void  width(int width);
  int   height();
  void  height(int height);

  CRect rect();

  bool  isZero();
  bool  isEmpty();
  int   square();
  void  augment(int dwidth, int dheight);

  bool  operator==(CSize &size);
  bool  operator!=(CSize &size);
};

class CRect
{
  CPoint m_position;
  CSize  m_size;

public:

  CRect();
  CRect(CPoint position, CSize size);
  CRect(CPoint position, int width, int height);
  CRect(int x, int y, CSize size);
  CRect(int x, int y, int width, int height);

  void   set(CPoint position, CSize size);
  void   set(CPoint position, int width, int height);
  void   set(int x, int y, CSize size);
  void   set(int x, int y, int width, int height);

  int    x();
  void   x(int x);
  int    y();
  void   y(int y);
  int    width();
  void   width(int width);
  int    height();
  void   height(int height);

  int    left();
  void   left(int left);
  int    top();
  void   top(int top);
  int    right();
  void   right(int right);
  int    bottom();
  void   bottom(int bottom);

  CPoint leftTop();
  void   leftTop(CPoint point);
  void   leftTop(int left, int top);
  CPoint rightTop();
  void   rightTop(CPoint point);
  void   rightTop(int right, int top);
  CPoint leftBottom();
  void   leftBottom(CPoint point);
  void   leftBottom(int left, int bottom);
  CPoint rightBottom();
  void   rightBottom(CPoint point);
  void   rightBottom(int right, int bottom);

  CPoint center();
  void   center(CPoint center);
  void   center(int x, int y);
  CPoint position();
  void   position(CPoint position);
  void   position(int x, int y);
  CSize  size();
  void   size(CSize size);
  void   size(int width, int height);

  int    square();
  void   expand(int left, int top, int right, int bottom);
  CPoint localPoint(CPoint absolutePoint);
  CPoint localPoint(int x, int y);
  CPoint absolutePoint(CPoint localPoint);
  CPoint absolutePoint(int x, int y);

  bool   isIntersectWith(CRect rect);
  bool   hasRect(CRect rect);
  bool   hasPoint(CPoint point);
  bool   isZero();
  bool   isEmpty();

  CRect  operator+(CRect rect);
  CRect  operator*(CRect rect);
  CRect& operator+=(CRect rect);
  CRect& operator*=(CRect rect);
  bool   operator==(CRect rect);
  bool   operator!=(CRect rect);
};

typedef std::string CString;

class CStrings
{
  typedef std::vector<std::string> ArrayOfStrings;

  ArrayOfStrings m_strings;

  static void splitHelper(ArrayOfStrings &stringsDest, CString &string, CString delimiter);
  static void insertPureHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings);
  static void insertHelper(ArrayOfStrings &stringsDest, int index, CString &string);
  static void insertHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings);

public:
  static const CString delimiter;
  static CStrings split(CString string, CString delimiter);

  CStrings();
  CStrings(CString string);
  CStrings(ArrayOfStrings strings);

  int      size();
  CString  text();
  CString  delimitedText(CString delimiter);
  void     text(CString string);
           
  void     add(CString string);
  void     add(CStrings strings);
  void     add(ArrayOfStrings strings);
  void     insert(CString text, int index);
  void     insert(CStrings strings, int index);
  void     insert(ArrayOfStrings strings, int index);
  void     remove(int index);
  void     remove(CString string);
  void     removeAll(CString string);
  void     remove(int from, int count);
  void     clear();
  int      find(CString string);
  CSize    drawingSize();

  CString& operator[](int index);
};