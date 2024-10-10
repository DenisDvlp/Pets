#include "Application.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE /*hprev*/, LPSTR /*cmdline*/, int /*show*/) {
    Application app(hInstance);
    app.run();
    return 0;
}
