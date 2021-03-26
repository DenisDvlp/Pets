#pragma once

#define repeat(var, times) for(int var = 0; i < times; i++)
#define print(text) std::cout<<text<<std::endl;

#define me (*this)
#define classname

#define thename(name) m_##name
#define createprop(type, name) type thename(name) = type();
#define propsetter(type, name, set) classname& name(type value) { thename(name) = set; return me; }
#define propgetter(type, name, get) type name() { type value = thename(name); return get; }
#define setter(type, name, set) classname& name(type value) { set; return me; }
#define getter(type, name, get) type name() { return get; }

//property with protected variable
#define property(type, name, set, get) \
  protected: createprop(type, name) \
  public: propsetter(type, name, set) \
  public: propgetter(type, name, get) private:
#define propertyreadonly(type, name, set, get) \
  protected: createprop(type, name) \
  protected: propsetter(type, name, set) \
  public: propgetter(type, name, get) private:

//property without protected variable
#define setget(type, name, set, get) \
  setter(type, name, set) \
  getter(type, name, get)

// SETTER & GETTER
// directives above makes easier to create properties
// EXAMPLE:
/*
#define classname A
struct A
{
property(int, x, value, value);
property(int, y, (value < 0 ? 0 : value), value);
property(int, z, setZ(value), getZ(value));
propertyreadonly(int, X, x(value).x(), x());

int setZ(int value)
{
X(20);
return value;
}
int getZ(int value)
{
return value;
}
};

A a;
a.x(10);
cout << a.x();
a.y(-12);
cout << a.y();
a.X(20); //error: setter is protected member
cout << a.X();
*/

typedef int ALIGN;
#define  ALIGN_TEXT_LEFT    0  //00000
#define  ALIGN_TEXT_TOP     0  //00000
#define  ALIGN_TEXT_RIGHT   1  //00001
#define  ALIGN_TEXT_BOTTOM  2  //00010
#define  ALIGN_TEXT_VCENTER 4  //00100
#define  ALIGN_TEXT_HCENTER 8  //01000

#define  ALIGN_NONE         0  //00000
#define  ALIGN_LEFT         1  //00001
#define  ALIGN_RIGHT        2  //00010
#define  ALIGN_TOP          4  //00100
#define  ALIGN_BOTTOM       8  //01000
#define  ALIGN_CENTER       16 //10000

#define  ALIGN_HORIZONTAL     (ALIGN_LEFT | ALIGN_RIGHT)          //00011
#define  ALIGN_VERTICAL       (ALIGN_TOP | ALIGN_BOTTOM)          //01100

#define  ALIGN_TOP_LEFT       (ALIGN_LEFT | ALIGN_TOP)            //00101
#define  ALIGN_TOP_RIGHT      (ALIGN_RIGHT | ALIGN_TOP)           //00110
#define  ALIGN_BOTTOM_LEFT    (ALIGN_LEFT | ALIGN_BOTTOM)         //01001
#define  ALIGN_BOTTOM_RIGHT   (ALIGN_RIGHT | ALIGN_BOTTOM)        //01010

#define  ALIGN_CONTENT        (ALIGN_HORIZONTAL | ALIGN_VERTICAL) //01111

#define  ALIGN_CONTENT_LEFT   (ALIGN_LEFT | ALIGN_VERTICAL)       //01101
#define  ALIGN_CONTENT_RIGHT  (ALIGN_RIGHT | ALIGN_VERTICAL)      //01110
#define  ALIGN_CONTENT_TOP    (ALIGN_TOP | ALIGN_HORIZONTAL)      //00111
#define  ALIGN_CONTENT_BOTTOM (ALIGN_BOTTOM | ALIGN_HORIZONTAL)   //01011

#define HASFLAG(flags, flag) ((flags & flag) == flag)

typedef int COLOR;
#define COLOR_TRANSPARENT -1
#define COLOR_BLACK        0
#define COLOR_DARKBLUE     1
#define COLOR_DARKGREEN    2
#define COLOR_DARKCYAN     3
#define COLOR_DARKRED      4
#define COLOR_DARKPURPLE   5
#define COLOR_DARKYELLOW   6
#define COLOR_GRAY         7
#define COLOR_DARKGRAY     8
#define COLOR_BLUE         9
#define COLOR_GREEN        10
#define COLOR_CYAN         11
#define COLOR_RED          12
#define COLOR_PURPLE       13
#define COLOR_YELLOW       14
#define COLOR_WHITE        15


#define FONT_SIZE_MIN      5
#define FONT_SIZE_MAX      40
#define CONSOLE_WIDTH_MIN  14
#define CONSOLE_WIDTH_MAX  500
#define CONSOLE_HEIGHT_MIN 1
#define CONSOLE_HEIGHT_MAX 200