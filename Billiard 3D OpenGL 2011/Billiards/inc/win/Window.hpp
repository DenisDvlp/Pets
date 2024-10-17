#pragma once
#include "Windows.hpp"
#include <string>

namespace win {

class Window {
  public:
    Window(std::wstring className, std::wstring caption, HINSTANCE hInstance);
    bool create();
    void show();
    void hide();
    void close();
    void swapBuffers();
    const std::wstring& getClassName();
    const std::wstring& getCaption();
    ~Window();

    virtual bool onMessage(UINT message, WPARAM wParam, LPARAM lParam);

  protected:
    void registerWindowClass();
    void createOpenGlRenderingContext();
    void destroyOpenGlRenderingContext();
    static Window* getSelfPtr(HWND hwnd);
    static Window* storeSelfPtr(HWND hwnd, LPARAM lParam);
    static LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    std::wstring m_className{};
    std::wstring m_caption{};
    HINSTANCE m_handleInstance{};
    HWND m_handleWindow{};
    HDC m_handleDeviceContext{};
    HGLRC m_handleOpenGlRenderingContext{};
};

} // namespace win
