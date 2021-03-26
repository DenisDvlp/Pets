#include "Collection.h"
#include "Utils.h"
#include <algorithm>
#include <cmath>

//CPoint

CPoint::CPoint() {}

CPoint::CPoint(int x, int y) :
  m_x(x),
  m_y(y)
{}

inline void CPoint::set(int x, int y)
{
  m_x = x;
  m_y = y;
}

void CPoint::shift(int x, int y)
{
  m_x += x;
  m_y += y;
}

inline int CPoint::x()
{
  return m_x;
}

inline void CPoint::x(int x)
{
  m_x = x;
}

inline int CPoint::y()
{
  return m_y;
}

inline void CPoint::y(int y)
{
  m_y = y;
}

inline double CPoint::distance(CPoint point)
{
  return sqrt(m_x * point.m_x + m_y * point.m_y);
}

inline bool CPoint::operator==(CPoint point)
{
  return m_x == point.m_x && m_y == point.m_y;
}

inline bool CPoint::operator!=(CPoint point)
{
  return !(*this == point);
}

inline bool CPoint::operator>(CPoint point)
{
  return
    m_x >= point.m_x && m_y >  point.m_y ||
    m_x >  point.m_x && m_y >= point.m_y;
}

inline bool CPoint::operator<(CPoint point)
{
  return
    m_x <= point.m_x && m_y <  point.m_y ||
    m_x <  point.m_x && m_y <= point.m_y;
}

inline bool CPoint::operator>=(CPoint point)
{
  return *this > point || *this == point;
}

inline bool CPoint::operator<=(CPoint point)
{
  return *this < point || *this == point;
}

inline CPoint CPoint::operator+(CPoint point)
{
  return CPoint(m_x + point.m_x, m_y + point.m_y);
}

inline CPoint CPoint::operator-(CPoint point)
{
  return CPoint(m_x - point.m_x, m_y - point.m_y);
}

//CSize

CSize::CSize(){}

CSize::CSize(int width, int height) :
  m_width(width),
  m_height(height)
{}

inline void CSize::set(int width, int height)
{
  m_width  = width;
  m_height = height;
}

void CSize::shift(int dwidth, int dheight)
{
  m_width  += dwidth;
  m_height += dheight;
}

inline int CSize::width()
{
  return m_width;
}

inline void CSize::width(int width)
{
  m_width = width;
}

inline int CSize::height()
{
  return m_height;
}

inline void CSize::height(int height)
{
  m_height = height;
}

inline int CSize::square()
{
  return m_width * m_height;
}

inline CRect CSize::rect()
{
  return CRect(0, 0, m_width, m_height);
}

bool CSize::isEmpty()
{
  return m_width | m_height;
}

inline bool CSize::operator==(CSize size)
{
  return m_width == size.m_width && m_height == size.m_height;
}

inline bool CSize::operator!=(CSize size)
{
  return !(*this == size);
}

//CRect

CRect::CRect(){}

CRect::CRect(CPoint position, CSize size) :
  m_position(position),
  m_size(size)
{}

CRect::CRect(CPoint position, int width, int height) :
  m_position(position),
  m_size(width, height)
{}

CRect::CRect(int x, int y, CSize size) :
  m_position(x, y),
  m_size(size)
{}

CRect::CRect(int x, int y, int width, int height) :
  m_position(x, y),
  m_size(width, height)
{}

inline void CRect::set(CPoint position, CSize size)
{
  m_position = position;
  m_size = size;
}

inline void CRect::set(CPoint position, int width, int height)
{
  m_position = position;
  m_size.set(width, height);
}

inline void CRect::set(int x, int y, CSize size)
{
  m_position.set(x, y);
  m_size = size;
}

inline void CRect::set(int x, int y, int width, int height)
{
  m_position.set(x, y);
  m_size.set(width, height);
}

inline int CRect::x()
{
  return m_position.x();
}

inline void CRect::x(int x)
{
  m_position.x(x);
}

inline int CRect::y()
{
  return m_position.y();
}

inline void CRect::y(int y)
{
  m_position.y(y);
}

inline int CRect::width()
{
  return m_size.width();
}

inline void CRect::width(int width)
{
  m_size.width(width);
}

inline int CRect::height()
{
  return m_size.height();
}

inline void CRect::height(int height)
{
  m_size.height(height);
}

inline int CRect::left()
{
  return m_position.x();
}

inline void CRect::left(int left)
{
  m_size.width(right() - left);
  m_position.x(left);
}

inline int CRect::top()
{
  return m_position.y();
}

inline void CRect::top(int top)
{
  m_size.height(bottom() - top);
  m_position.y(top);
}

inline int CRect::right()
{
  return m_position.x() + m_size.width();
}

inline void CRect::right(int right)
{
  m_size.width(right - m_position.x());
}

inline int CRect::bottom()
{
  return m_position.y() + m_size.height();
}

inline void CRect::bottom(int bottom)
{
  m_size.height(bottom - m_position.y());
}

inline CPoint CRect::leftTop()
{
  return m_position;
}

inline void CRect::leftTop(CPoint point)
{
  left(point.x());
  top( point.y());
}

inline CPoint CRect::rightTop()
{
  return CPoint(right(), m_position.y());
}

inline void CRect::rightTop(CPoint point)
{
  right(point.x());
  top(  point.y());
}

inline CPoint CRect::leftBottom()
{
  return CPoint(m_position.x(), bottom());
}

inline void CRect::leftBottom(CPoint point)
{
  left(  point.x());
  bottom(point.y());
}

inline CPoint CRect::rightBottom()
{
  return CPoint(right(), bottom());
}

inline void CRect::rightBottom(CPoint point)
{
  right( point.x());
  bottom(point.y());
}

inline CPoint CRect::center()
{
  return CPoint(m_position.x() + m_size.width() / 2, m_position.x() + m_size.height() / 2);
}

inline void CRect::center(CPoint point)
{
  m_position.set(point.x() - m_size.width() / 2, point.y() - m_size.width() / 2);
}

inline int CRect::square()
{
  return m_size.square();
}

inline CPoint CRect::position()
{
  return m_position;
}

inline CSize CRect::size()
{
  return m_size;
}

void CRect::expand(int left, int top, int right, int bottom)
{
  m_position.shift(left, top);
  m_size.shift(right + left, top + bottom);
}

CPoint CRect::localPoint(CPoint absolutePoint)
{
  return absolutePoint - m_position;
}

CPoint CRect::localPoint(CPoint absolutePoint, CRect relativeRect)
{
  return absolutePoint - m_position + relativeRect.m_position;
}

CPoint CRect::absolutePoint(CPoint localPoint)
{
  return localPoint + m_position;
}

CPoint CRect::absolutePoint(CPoint localPoint, CRect relativeRect)
{
  return localPoint + m_position - relativeRect.m_position;
}

CRect CRect::unionRect(CRect rect)
{
  CRect r(min(m_position, rect.m_position), 0, 0);
  r.rightBottom(max(rightBottom(), rect.rightBottom()));
  return r;
}

CRect CRect::intersectRect(CRect rect)
{
  CRect r(max(m_position, rect.m_position), 0, 0);
  r.rightBottom(min(rightBottom(), rect.rightBottom()));
  return r;
}
bool CRect::isIntersectWith(CRect rect)
{
  return rightBottom() > rect.m_position &&
    rect.rightBottom() >      m_position;
}
bool CRect::hasRect(CRect rect)
{
  return rect.m_position >= m_position && rect.rightBottom() <= rightBottom();
}
bool CRect::hasPoint(CPoint point)
{
  return point >= m_position && point < rightBottom();
}
bool CRect::isEmpty()
{
  return m_size.isEmpty();
}
bool CRect::operator==(CRect rect)
{
  return m_position == rect.m_position && m_size == rect.m_size;
}
bool CRect::operator!=(CRect rect)
{
  return !(*this == rect);
}

//CStrings

CStrings CStrings::split(CString string, char delimiter)
{
  CStrings strings;
  splitHelper(strings.m_strings, string, delimiter);
  return strings;
}

CStrings::CStrings()
{}

CStrings::CStrings(CString string)
{
  splitHelper(m_strings, string, '\n');
}

CStrings::CStrings(ArrayOfStrings strings)
{
  addHelper(m_strings, strings);
}

void CStrings::splitHelper(ArrayOfStrings &stringsDest, CString &string, char delimiter)
{
  int prev = 0;
  int pos = string.find(delimiter, 0);
  while (pos >= 0)
  {
    stringsDest.push_back(string.substr(prev, pos++ - prev));
    prev = pos;
    pos = string.find(delimiter, pos);
  }
  pos = string.size();
  if (prev <= string.size())
  {
    stringsDest.push_back(string.substr(prev));
  }
}

void CStrings::insertPureHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings)
{
  stringsDest.insert(stringsDest.begin() + index, strings.begin(), strings.end());
}

void CStrings::insertHelper(ArrayOfStrings &stringsDest, int index, CString &string)
{
  ArrayOfStrings stringsSrc;
  splitHelper(stringsSrc, string, '\n');
  insertPureHelper(stringsDest, index, stringsSrc);
}

void CStrings::insertHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings)
{
  ArrayOfStrings stringsSrc;
  for (ArrayOfStrings::iterator it = strings.begin(); it != strings.end(); it++)
  {
    insertHelper(stringsSrc, stringsSrc.size() - 1, *it);
  }
  insertPureHelper(stringsDest, index, stringsSrc);
}

int CStrings::size()
{
  m_strings.size();
}

CString CStrings::text()
{
  return delimitedText("\n");
}

void CStrings::text(CString string)
{
  splitHelper(m_strings, string, '\n');
}

CString CStrings::delimitedText(CString delimiter)
{
  CString string;
  for (ArrayOfStrings::iterator it = m_strings.begin(); it != m_strings.end(); it++)
  {
    string.append(*it).append(delimiter);
  }
  return string.substr(0, string.size() - 1);
}

void CStrings::add(CString string)
{
  insertHelper(m_strings, m_strings.size() - 1, string);
}

void CStrings::add(CStrings strings)
{
  insertPureHelper(m_strings, m_strings.size() - 1, strings.m_strings);
}

void CStrings::add(ArrayOfStrings strings)
{
  insertHelper(m_strings, m_strings.size() - 1, strings);
}

void CStrings::insert(int index, CString string)
{
  insertHelper(m_strings, index, string);
}

void CStrings::insert(int index, CStrings strings)
{
  insertPureHelper(m_strings, index, strings.m_strings);
}

void CStrings::insert(int index, ArrayOfStrings strings)
{
  insertHelper(m_strings, index, strings);
}

void CStrings::remove(int index)
{
  m_strings.erase(m_strings.begin() + index);
}

void CStrings::remove(CString string)
{
  int index = find(string);
  remove(index);
}

void CStrings::remove(int from, int count)
{
  m_strings.erase(m_strings.begin() + from, m_strings.begin() + from + count);
}

void CStrings::clear()
{
  m_strings.clear();
}

int CStrings::find(CString string)
{
  int i = 0;
  for (ArrayOfStrings::iterator it = m_strings.begin(); it != m_strings.end(); it++)
  {
    if (*it == string)
    {
      return i;
    }
    i++;
  }
  return -1;
}

CSize CStrings::drawingSize()
{
  int height = m_strings.size();
  int width = 0;
  for (ArrayOfStrings::iterator it = m_strings.begin(); it != m_strings.end(); it++)
  {
    if (width < it->size())
    {
      width = it->size();
    }
  }
  return CSize(width, height);
}
CString& CStrings::operator[](int index)
{
  if (index < 0 || index >= m_strings.size())
  {
    throw -1;
  }
  return m_strings[index];
}
