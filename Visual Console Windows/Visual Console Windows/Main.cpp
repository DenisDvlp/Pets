//Main.cpp
#include "DApplication.h"
#include "DButton.h"
#include "Utils.h"

int main()
{
    DButton *buttons[6] = {
      new DButton(Key::CTRL_L),
      new DButton(Key::CTRL_R),
      new DButton(Key::ALT_L),
      new DButton(Key::ALT_R),
      new DButton(Key::SHIFT_L),
      new DButton(Key::SHIFT_R),
    };
    DApplication app;
    for (auto b : buttons) {
        b->size(15, 7);
        b->setMainColor(utils::random(-4000000000, 4000000000));
        b->setClickColor(DColors::DARK_BLUE);
        app.addView(b);
    }
    buttons[0]->position(10, 10);
    buttons[1]->position(40, 10);
    buttons[2]->position(20, 10);
    buttons[3]->position(30, 10);
    buttons[4]->position(10, 5);
    buttons[5]->position(40, 5);
    app.run();
}