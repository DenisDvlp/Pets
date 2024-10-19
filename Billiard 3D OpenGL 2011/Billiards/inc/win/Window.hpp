#pragma once
#include "Windows.hpp"
#include <string>

namespace win {

class Window {
  public:
    Window(HINSTANCE hInstance, std::wstring className, std::wstring caption);
    bool create();
    void show();
    void hide();
    void close();
    void swapBuffers();
    virtual ~Window();

  protected:
    virtual void onCreate();
    virtual void onMouseMove(const int x, const int y);
    virtual void onResize(const unsigned short width, const unsigned short height);
    virtual bool onClose();

  protected:
    bool onMessage(UINT message, WPARAM wParam, LPARAM lParam);
    static Window* getSelfPtr(HWND hwnd);
    static Window* storeSelfPtr(HWND hwnd, LPARAM lParam);
    static LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void destroy();
    void registerWindowClass();
    HINSTANCE m_handleInstance{};
    std::wstring m_className{};
    std::wstring m_caption{};
    HWND m_handleWindow{};
    HDC m_handleDeviceContext{};
};

} // namespace win
