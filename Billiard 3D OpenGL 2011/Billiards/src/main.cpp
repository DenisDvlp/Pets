#include "win/Application.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE /*hprev*/, LPSTR /*cmdline*/, int /*show*/) {
    win::Application app(hInstance);
    app.run();
    return 0;
}
