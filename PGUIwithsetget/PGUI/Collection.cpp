#include "Collection.h"

//CPoint

CPoint::CPoint() {}
CPoint::CPoint(int x, int y)
{
	set(x, y);
}
CPoint& CPoint::set(int x, int y)
{
	return me.x(x).y(y);
}
double CPoint::distance(CPoint & point)
{
	return sqrt(x() * point.x() + y() * point.y());
}
bool CPoint::operator==(CPoint &point)
{
	return x() == point.x() && y() == point.y();
}
bool CPoint::operator!=(CPoint &point)
{
	return !(me == point);
}
CPoint CPoint::operator+(CPoint &point)
{
	return CPoint(x() + point.x(), y() + point.y());
}
CPoint CPoint::operator-(CPoint &point)
{
	return CPoint(x() - point.x(), y() - point.y());
}

//CSize

CSize::CSize(){}
CSize::CSize(int width, int height)
{
	set(width, height);
}
CSize& CSize::set(int width, int height)
{
	return me.width(width).height(height);
}
bool CSize::operator==(CSize &size)
{
	return width() == size.width() && height() == size.height();
}
bool CSize::operator!=(CSize &size)
{
	return !(me == size);
}

//CRect

CRect::CRect(){}
CRect::CRect(CPoint &position, CSize &size)
{
	set(position, size);
}
CRect::CRect(CPoint &position, int width, int height)
{
	set(position, width, height);
}
CRect::CRect(int x, int y, CSize &size)
{
	set(x, y, size);
}
CRect::CRect(int x, int y, int width, int height)
{
	set(x, y, width, height);
}
CRect& CRect::set(CPoint &position, CSize &size)
{
	return me.position(position).size(size);
}
CRect& CRect::set(CPoint &position, int width, int height)
{
	return me.position(position).width(width).height(height);
}
CRect& CRect::set(int x, int y, CSize &size)
{
	return me.x(x).y(y).size(size);
}
CRect& CRect::set(int x, int y, int width, int height)
{
	return me.x(x).y(y).width(width).height(height);
}
CPoint CRect::localPoint(CPoint &point)
{
	return localPoint(point, CRect());
}
CPoint CRect::localPoint(CPoint &point, CRect &rect)
{
	return CPoint( rect.x() - x() + point.x(), rect.y() - y() + point.y());
}
CPoint CRect::absolutePoint(CPoint &point)
{
	return absolutePoint(point, CRect());
}
CPoint CRect::absolutePoint(CPoint &point, CRect &rect)
{
	return CPoint(x() - rect.x() + point.x(), y() - rect.y() + point.y());
}
CRect CRect::unionRect(CRect &rect)
{
	CRect r;
	r.x(Min(x(), rect.x()));
	r.y(Min(y(), rect.y()));
	r.width(Max(right(), rect.right()) - r.x());
	r.height(Max(bottom(), rect.bottom()) - r.y());
	return r;
}
CRect CRect::intersectRect(CRect &rect)
{
	CRect r;
	r.x(Max(x(), rect.x()));
	r.y(Max(y(), rect.y()));
	r.width(Min(right(), rect.right()) - r.x());
	r.height(Min(bottom(), rect.bottom()) - r.y());
	return r;
}
bool CRect::isIntersectWith(CRect &rect)
{
	return !intersectRect(rect).isEmpty();
}
bool CRect::hasRect(CRect &rect)
{
	return
		rect.x() >= x() && rect.right() <= right() &&
		rect.y() >= y() && rect.bottom() <= bottom();
}
bool CRect::hasPoint(CPoint &point)
{
	return
		point.x() >= x() && point.x() < right() &&
		point.y() >= y() && point.y() < bottom();
}
bool CRect::isEmpty()
{
	return !width() || !height();
}
bool CRect::operator==(CRect &rect)
{
	return position() == rect.position() && size() == rect.size();
}
bool CRect::operator!=(CRect &rect)
{
	return !(me == rect);
}

//CStrings

CStrings CStrings::split(string text, char c)
{
	CStrings ss;
	int prev = 0;
	int pos = text.find(c, 0);
	while (pos >= 0) {
		ss.strings.push_back(text.substr(prev, pos++ - prev));
		prev = pos;
		pos = text.find(c, pos);
	}
	pos = text.size();
	if(prev <= text.size())
		ss.strings.push_back(text.substr(prev));
	return ss;
}

CStrings::CStrings(){}
CStrings::CStrings(string text)
{
	me.text(text);
}
CStrings::CStrings(vector<string> &strings)
{
	add(strings);
}
string CStrings::getText()
{
	string text;
	for_each(strings.begin(), strings.end(), [&text](string str){
		text.append(str).append("\n");
	});
	return text.substr(0, text.size() - 1);
}
CStrings& CStrings::add(string text)
{
	CStrings ss;
	if (text.find('\n', 0) >= 0) {
		ss.text(text);
		add(ss);
	}
	else
		strings.push_back(text);
	return me;
}
CStrings& CStrings::add(CStrings &strings)
{
	return add(strings.strings);
}
CStrings& CStrings::add(vector<string> &strs)
{
	for_each(strs.begin(), strs.end(), [this](string str){
		strings.push_back(str);
	});
	return me;
}
CStrings& CStrings::insert(int index, string text)
{
	strings.insert(strings.begin() + index, text);
	return me;
}
CStrings& CStrings::insert(int index, CStrings &strings)
{
	return insert(index, strings.strings);
}
CStrings& CStrings::insert(int index, vector<string>& strings)
{
	strings.insert(strings.begin() + index, strings.begin(), strings.end());
	return me;
}
CStrings& CStrings::remove(int index)
{
	strings.erase(strings.begin() + index);
	return me;
}
CStrings& CStrings::remove(int from, int count)
{
	strings.erase(strings.begin() + from, strings.begin() + from + count);
	return me;
}
CStrings& CStrings::clear()
{
	strings.clear();
	return me;
}
CSize CStrings::drawingSize()
{
	int height = strings.size();
	int width = 0;
	for_each(strings.begin(), strings.end(), [&width](string str){
		if (width < str.size()) width = str.size();
	});
	return CSize(width, height);
}
string& CStrings::operator[](int index)
{
	if (index < 0 || index >= strings.size())
		throw -1;
	return strings[index];
}

//Utils

int Max(int a, int b) {
	return a > b ? a : b;
}
int Min(int a, int b) {
	return a < b ? a : b;
}
int Max(int a, int b, int c) {
	int x = Max(a, b);
	return x > c ? x : c;
}
int Min(int a, int b, int c) {
	int x = Min(a, b);
	return x < c ? x : c;
}
int Max(int a, int b, int c, int d) {
	int x = Max(a, b, c);
	return x > d ? x : d;
}
int Min(int a, int b, int c, int d) {
	int x = Max(a, b, c);
	return x < d ? x : d;
}