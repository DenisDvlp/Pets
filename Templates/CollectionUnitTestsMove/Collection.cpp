#include "Collection.h"
#include "Utils.h"
#include <cmath>
#include <algorithm>

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

bool CPoint::isZero()
{
  return !(m_x | m_y);
}

double CPoint::distance(CPoint point)
{
  return sqrt(pow(m_x - point.m_x, 2) + pow(m_y - point.m_y, 2));
}

bool CPoint::operator==(CPoint point)
{
  return m_x == point.m_x && m_y == point.m_y;
}

bool CPoint::operator!=(CPoint point)
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

CPoint & CPoint::operator+=(CPoint point)
{
  m_x += point.m_x;
  m_y += point.m_y;
  return *this;
}

CPoint & CPoint::operator-=(CPoint point)
{
  m_x -= point.m_x;
  m_y -= point.m_y;
  return *this;
}

//CSize

CSize::CSize(){}

CSize::CSize(int width, int height)
{
  this->width(width);
  this->height(height);
}

void CSize::set(int width, int height)
{
  this->width(width);
  this->height(height);
}

inline int CSize::width()
{
  return m_width;
}

inline void CSize::width(int width)
{
  m_width = width < 0 ? 0 : width;
}

inline int CSize::height()
{
  return m_height;
}

inline void CSize::height(int height)
{
  m_height = height < 0 ? 0 : height;
}

inline CRect CSize::rect()
{
  return CRect(0, 0, m_width, m_height);
}

bool CSize::isZero()
{
  return !(m_width | m_height);
}

bool CSize::isEmpty()
{
  return !m_width || !m_height;
}

inline int CSize::square()
{
  return m_width * m_height;
}

void CSize::augment(int dwidth, int dheight)
{
  width(m_width + dwidth);
  height(m_height + dheight);
}

bool CSize::operator==(CSize &size)
{
  return m_width == size.m_width && m_height == size.m_height;
}

bool CSize::operator!=(CSize &size)
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

void CRect::set(CPoint position, CSize size)
{
  m_position = position;
  m_size = size;
}

void CRect::set(CPoint position, int width, int height)
{
  m_position = position;
  m_size.set(width, height);
}

void CRect::set(int x, int y, CSize size)
{
  m_position.set(x, y);
  m_size = size;
}

void CRect::set(int x, int y, int width, int height)
{
  m_position.set(x, y);
  m_size.set(width, height);
}

int CRect::x()
{
  return m_position.x();
}

void CRect::x(int x)
{
  m_position.x(x);
}

int CRect::y()
{
  return m_position.y();
}

void CRect::y(int y)
{
  m_position.y(y);
}

int CRect::width()
{
  return m_size.width();
}

void CRect::width(int width)
{
  m_size.width(width);
}

int CRect::height()
{
  return m_size.height();
}

void CRect::height(int height)
{
  m_size.height(height);
}

int CRect::left()
{
  return m_position.x();
}

inline void CRect::left(int left)
{
  int right = this->right();
  left = min(right, left);
  m_size.width(right - left);
  m_position.x(left);
}

int CRect::top()
{
  return m_position.y();
}

inline void CRect::top(int top)
{
  int bottom = this->bottom();
  top = min(bottom, top);
  m_size.height(bottom - top);
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
  top(point.y());
}

void CRect::leftTop(int left, int top)
{
  this->left(left);
  this->top(top);
}
 
inline CPoint CRect::rightTop()
{
  return CPoint(right(), m_position.y());
}

inline void CRect::rightTop(CPoint point)
{
  right(point.x());
  top(point.y());
}

void CRect::rightTop(int right, int top)
{
  this->right(right);
  this->top(top);
}

inline CPoint CRect::leftBottom()
{
  return CPoint(m_position.x(), bottom());
}

inline void CRect::leftBottom(CPoint point)
{
  left(point.x());
  bottom(point.y());
}

void CRect::leftBottom(int left, int bottom)
{
  this->left(left);
  this->bottom(bottom);
}

inline CPoint CRect::rightBottom()
{
  return CPoint(right(), bottom());
}

inline void CRect::rightBottom(CPoint point)
{
  right(point.x());
  bottom(point.y());
}

void CRect::rightBottom(int right, int bottom)
{
  this->right(right);
  this->bottom(bottom);
}

inline CPoint CRect::center()
{
  return CPoint(m_position.x() + m_size.width() / 2, m_position.y() + m_size.height() / 2);
}

inline void CRect::center(CPoint point)
{
  m_position += point - center();
}

void CRect::center(int x, int y)
{
  center(CPoint(x, y));
}

CPoint CRect::position()
{
  return m_position;
}

void CRect::position(CPoint position)
{
  m_position = position;
}

void CRect::position(int x, int y)
{
  m_position.set(x, y);
}

CSize CRect::size()
{
  return m_size;
}

void CRect::size(CSize size)
{
  m_size = size;
}

void CRect::size(int width, int height)
{
  m_size.set(width, height);
}

int CRect::square()
{
  return m_size.square();
}

void CRect::expand(int left, int top, int right, int bottom)
{
  m_position.shift(-left, -top);
  m_size.augment(right + left, top + bottom);
}

CPoint CRect::localPoint(CPoint absolutePoint)
{
  return absolutePoint - m_position;
}

CPoint CRect::localPoint(int x, int y)
{
  return CPoint(x, y) - m_position;
}

CPoint CRect::absolutePoint(CPoint localPoint)
{
  return localPoint + m_position;
}

CPoint CRect::absolutePoint(int x, int y)
{
  return CPoint(x, y) + m_position;
}

bool CRect::isIntersectWith(CRect rect)
{
  return 
    rightBottom() > rect.m_position &&
    rect.rightBottom() > m_position;
}

bool CRect::hasRect(CRect rect)
{
  return rect.m_position >= m_position && rect.rightBottom() <= rightBottom();
}

bool CRect::hasPoint(CPoint point)
{
  return point >= m_position && point < rightBottom();
}

bool CRect::isZero()
{
  return m_size.isZero() && m_position.isZero();
}

bool CRect::isEmpty()
{
  return m_size.isEmpty();
}

CRect CRect::operator+(CRect rect)
{
  CRect r(min(m_position, rect.m_position), 0, 0);
  r.rightBottom(max(rightBottom(), rect.rightBottom()));
  return r;
}

CRect CRect::operator*(CRect rect)
{
  CRect r(max(m_position, rect.m_position), 0, 0);
  r.rightBottom(min(rightBottom(), rect.rightBottom()));
  return r;
}

CRect & CRect::operator+=(CRect rect)
{
  m_position = min(m_position, rect.m_position);
  rightBottom(max(rightBottom(), rect.rightBottom()));
  return *this;
}

CRect & CRect::operator*=(CRect rect)
{
  m_position = max(m_position, rect.m_position);
  rightBottom(min(rightBottom(), rect.rightBottom()));
  return *this;
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

const CString CStrings::delimiter = "\n";

CStrings CStrings::split(CString string, CString delimiter)
{
  CStrings strings;
  splitHelper(strings.m_strings, string, delimiter);
  return strings;
}

CStrings::CStrings()
{}

CStrings::CStrings(CString string)
{
  splitHelper(m_strings, string, delimiter);
}

CStrings::CStrings(ArrayOfStrings strings)
{
  insertHelper(m_strings, m_strings.size() - 1, strings);
}

void CStrings::splitHelper(ArrayOfStrings &stringsDest, CString &string, CString delimiter)
{
  int prev = 0;
  int delSize = delimiter.size();
  int strSize = string.size();
  int pos = string.find(delimiter, 0);
  if (delSize)
  {
    while (pos >= 0)
    {
      int sz = pos - prev;
      stringsDest.push_back(std::move(string.substr(prev, sz)));
      prev = pos + delSize;
      pos = string.find(delimiter, prev);
    }
  }
  if (prev <= strSize)
  {
    stringsDest.push_back(std::move(string.substr(prev, strSize - prev)));
  }
}

void CStrings::insertPureHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings)
{
  if (isInRange(0, index, int(stringsDest.size())))
  {
    stringsDest.insert(stringsDest.begin() + index, strings.begin(), strings.end());
  }
}

void CStrings::insertHelper(ArrayOfStrings &stringsDest, int index, CString &string)
{
  ArrayOfStrings stringsSrc;
  splitHelper(stringsSrc, string, delimiter);
  insertPureHelper(stringsDest, index, stringsSrc);
}

void CStrings::insertHelper(ArrayOfStrings &stringsDest, int index, ArrayOfStrings &strings)
{
  ArrayOfStrings stringsSrc;
  for (ArrayOfStrings::iterator it = strings.begin(); it != strings.end(); it++)
  {
    insertHelper(stringsSrc, stringsSrc.size(), *it);
  }
  insertPureHelper(stringsDest, index, stringsSrc);
}

int CStrings::size()
{
  return m_strings.size();
}

CString CStrings::text()
{
  return delimitedText(CString() + delimiter);
}

void CStrings::text(CString string)
{
  splitHelper(m_strings, string, delimiter);
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
  insertHelper(m_strings, m_strings.size(), string);
}

void CStrings::add(CStrings strings)
{
  insertPureHelper(m_strings, m_strings.size(), strings.m_strings);
}

void CStrings::add(ArrayOfStrings strings)
{
  insertHelper(m_strings, m_strings.size(), strings);
}

void CStrings::insert(CString string, int index)
{
  insertHelper(m_strings, index, string);
}

void CStrings::insert(CStrings strings, int index)
{
  insertPureHelper(m_strings, index, strings.m_strings);
}

void CStrings::insert(ArrayOfStrings strings, int index)
{
  insertHelper(m_strings, index, strings);
}

void CStrings::remove(int index)
{
  if (isInRange(0, index, int(m_strings.size()) - 1))
  {
    m_strings.erase(m_strings.begin() + index);
  }
}

void CStrings::remove(CString string)
{
  remove(find(string));
}

void CStrings::removeAll(CString string)
{
  m_strings.erase(std::remove(m_strings.begin(), m_strings.end(), string), m_strings.end());
}

void CStrings::remove(int from, int count)
{
  if (isInRange(0, from, int(m_strings.size()) - 1))
  {
    m_strings.erase(m_strings.begin() + from, m_strings.begin() + from + count);
  }
}

void CStrings::clear()
{
  m_strings.clear();
}

int CStrings::find(CString string)
{
  ArrayOfStrings::iterator it = std::find(m_strings.begin(), m_strings.end(), string);
  int i = -1;
  if (it != m_strings.end())
  {
    i = std::distance(m_strings.begin(), it);
  }
  return i;
}

CSize CStrings::drawingSize()
{
  int width = 0;
  for (ArrayOfStrings::iterator it = m_strings.begin(); it != m_strings.end(); it++)
  {
    if (width < int(it->size()))
    {
      width = it->size();
    }
  }
  return CSize(width, m_strings.size());
}

CString& CStrings::operator[](int index)
{
  if(isInRange(0, index, int(m_strings.size()) - 1))
  {
    return m_strings[index];
  }
  throw - 1;
}
