#include "Application.hpp"

Application::Application(HINSTANCE hInstance)
    : window{L"main_window", hInstance} {}

void Application::run() {
    if(!window.open(L"Billiards by Denys Petrov 2024")){
        return;
    }
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

Application::~Application() {}
