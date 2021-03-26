#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "Macros.h"
using std::for_each;
using std::string;
using std::vector;

#define classname CPoint
class CPoint
{
	property(int, x, value, value);
	property(int, y, value, value);

public:

	CPoint();
	CPoint(int x, int y);
	//set
	CPoint& set(int x, int y);
	//func
	double distance(CPoint &point);
	//operator
	bool operator==(CPoint &point);
	bool operator!=(CPoint &point);
	CPoint operator+(CPoint &point);
	CPoint operator-(CPoint &point);
};

#define classname CSize
class CSize
{
	property(int, width, (value < 0 ? 0 : value), value);
	property(int, height, (value < 0 ? 0 : value), value);

public:

	CSize();
	CSize(int width, int height);
	//set
	CSize& set(int width, int height);
	//get
	getter(int, square, width() * height());
	//operator
	bool operator==(CSize &size);
	bool operator!=(CSize &size);
};

#define classname CRect
class CRect
{
	propertyreadonly(CPoint, position, value, value);
	propertyreadonly(CSize, size, value, value);

	setget(int, x, _position.x(value), _position.x());
	setget(int, y, _position.y(value), _position.y());
	setget(int, width, _size.width(value), _size.width());
	setget(int, height, _size.height(value), _size.height());

public:

	//constructor
	CRect();
	CRect(CPoint &position, CSize &size);
	CRect(CPoint &position, int width, int height);
	CRect(int x, int y, CSize &size);
	CRect(int x, int y, int width, int height);
	//set
	CRect& set(CPoint &position, CSize &size);
	CRect& set(CPoint &position, int width, int height);
	CRect& set(int x, int y, CSize &size);
	CRect& set(int x, int y, int width, int height);
	//get
	getter(int, left, x());
	getter(int, top, y());
	getter(int, right, x() + width());
	getter(int, bottom, y() + height());
	getter(CPoint, center, CPoint(x() + width() / 2, y() + height() / 2));
	getter(int, square, _size.square());
	//func
	CPoint localPoint(CPoint &point);
	CPoint localPoint(CPoint &point, CRect &rect);
	CPoint absolutePoint(CPoint &point);
	CPoint absolutePoint(CPoint &point, CRect &rect);
	CRect unionRect(CRect &rect);
	CRect intersectRect(CRect &rect);
	//is
	bool isIntersectWith(CRect &rect);
	bool hasRect(CRect &rect);
	bool hasPoint(CPoint &point);
	bool isEmpty();
	//operator
	bool operator==(CRect &rect);
	bool operator!=(CRect &rect);
};

#define classname CStrings
class CStrings
{
	vector<string> strings;
	setget(string, text, me = split(value, '\n'), getText());
	string getText();

public:
	static CStrings split(string text, char c);

	getter(int, count, strings.size());

	CStrings();
	CStrings(string text);
	CStrings(vector<string> &strings);
	CStrings& add(string str);
	CStrings& add(CStrings &strings);
	CStrings& add(vector<string> &strings);
	CStrings& insert(int index, string text);
	CStrings& insert(int index, CStrings &strings);
	CStrings& insert(int index, vector<string> &strings);
	CStrings& remove(int index);
	CStrings& remove(int from, int count);
	CStrings& clear();
	CSize drawingSize();
	string& operator[](int index);
};

int Max(int a, int b);
int Max(int a, int b, int c);
int Max(int a, int b, int c, int d);
int Min(int a, int b);
int Min(int a, int b, int c);
int Min(int a, int b, int c, int d);