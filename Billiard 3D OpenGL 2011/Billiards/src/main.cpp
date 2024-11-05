#include "core/Application.hpp"

int WinMain(HINSTANCE hInstance, HINSTANCE /*hprev*/, LPSTR /*cmdline*/, int /*show*/) {
    core::Application{hInstance};
    return 0;
}
