//Main.cpp
#include "DApplication.h"
#include "DButton.h"

int main()
{
    auto button = new DButton(nullptr);
    button->size(10, 10);
    button->position(10, 10);
    button->setMainColor(DColors::RED);
    DApplication app;
    app.addView(button);
    app.run();
}