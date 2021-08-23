#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <windows.h>
#include <ctime>

using namespace std;

struct Key
{
	time_t timePressed = 0;
	bool pressed = false;
	bool longpressed = false;
};

class Keyboard
{
	time_t states[256] = { 0 };
	vector<int> pressed;
	vector<int> unpressed;
	vector<int> longpressed;
	vector<int> autotyped;
	time_t millis = 0;
	time_t longpressInterval = 800;
	time_t typeInterval = 300;
	time_t doublepressInterval = 500;

	Keyboard() {}

public:

	enum {
		KEY_ESC = 27,
		KEY_ENTER = 13,
		KEY_SPACE = 32,
		KEY_PRE_ARROW = 224,
		KEY_PRE_NUMLOCK = 0,
		KEY_ARROW_LEFT = 37,
		KEY_ARROW_RIGHT = 39,
		KEY_ARROW_UP = 38,
		KEY_ARROW_DOWN = 40
	};

	static const char* toString(int m) {

		char *str = "";

		switch (m)
		{
		case KEY_ESC: str = "KEY_ESC"; break;
		case KEY_SPACE: str = "KEY_SPACE"; break;
		case KEY_ENTER: str = "KEY_ENTER"; break;
		case KEY_ARROW_LEFT: str = "KEY_LEFT"; break;
		case KEY_ARROW_RIGHT: str = "KEY_RIGHT"; break;
		case KEY_ARROW_UP: str = "KEY_UP"; break;
		case KEY_ARROW_DOWN: str = "KEY_DOWN"; break;
		case VK_LBUTTON: str = "VK_LBUTTON"; break;
		default: cout << m;
		}

		return str;
	}

	static Keyboard& instance() {
		static Keyboard inst;
		return inst;
	}

	bool changed() {

		time_t t = clock();

		autotyped.clear();
		longpressed.clear();
		pressed.clear();
		unpressed.clear();

		bool state = false;
		bool changed = false;

		for (int i = 1; i < 256; i++)
		{
			state = HIWORD(GetKeyState(i));
			if (state)
			{
				if (states[i] == 0)
				{
					pressed.push_back(i);
					changed = true;
				} 
				else if (t - states[i] >= longpressInterval)
				{
					longpressed.push_back(i);
					changed = true;
				}
				if (changed)
				{
					states[i] = t;
				}
			}
			else
			{
				if (states[i] > 0)
				{
					unpressed.push_back(i);
					changed = true;
				}
				if (changed)
				{
					states[i] = 0;
				}
			}
		}
		return changed;
	}

	vector<int> keysDown() {
		return pressed;
	}

	vector<int> keysUp() {
		return unpressed;
	}

	vector<int> keysLongDown() {
		return longpressed;
	}
};

class Application
{

	bool opened = true;
	vector<int> messages;
	int currentMessageIndex = 0;

	Application() {}

public:

	static Application& instance() {
		static Application inst;
		return inst;
	}

	int readMessage() {
		if (messages.size() == 0) return 0;
		if (currentMessageIndex == messages.size())
		{
			currentMessageIndex = 0;
			messages.clear();
			return 0;
		}
		return messages[currentMessageIndex++];
	}

	void sendMessage(int msg) {
		messages.push_back(msg);
	}

	void close() {
		opened = false;
	}

	void run() {
		while (opened) {
			readout();
			proccessing();
		}
	}

private:

	void readout() {
		if (Keyboard::instance().changed())
		{
			vector<int> keysDown = Keyboard::instance().keysDown();
			vector<int> keysUp = Keyboard::instance().keysUp();
			vector<int> keysLongDown = Keyboard::instance().keysLongDown();
			for (auto key : keysDown)
			{
				sendMessage(key);
			}
			for (auto key : keysUp)
			{
				sendMessage(key);
			}
			for (auto key : keysLongDown)
			{
				sendMessage(key);
			}
		}
	}

	void proccessing() {
		int msg = 0;
		while (msg = readMessage())
			update(msg);
	}

	void update(int key) {
		if (key == Keyboard::KEY_ESC)
			sendMessage(Keyboard::KEY_ENTER);
		else
			cout << Keyboard::toString(key) << endl;
	}
};

int main()
{	
	Application::instance().run();
}
