#define me (*this)
#define classname
#define createprop(type, name) private: type _##name = static_cast<type>(0);
#define getter(type, name, get) public: type name() { type value = _##name; return get; }
#define setter(type, name, set) public: classname& name(type value) { _##name = set; return me; } private:
#define property(type, name, set, get) \
	createprop(type, name) \
	getter(type, name, get) \
	setter(type, name, value)
#define propertyreadonly(type, name, get) \
	createprop(type, name) \
	getter(type, name, get)

#define classname A
class A {
	property(int, x, setx(value), getx(value));
	propertyreadonly(float, y, value);
	property(char*, c, setc(value), value);

	int getx(int value);
	float gety(float value);
	char* setc(char* value);

};