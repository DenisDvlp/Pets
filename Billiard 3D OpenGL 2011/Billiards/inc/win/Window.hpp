#include "Windows.hpp"
#include <string>

class Window final {
  public:
    Window(std::wstring className, std::wstring caption, HINSTANCE hInstance);
    bool create();
    void show();
    void hide();
    void close();
    const std::wstring& getClassName();
    const std::wstring& getCaption();
    ~Window();

    bool onMessage(UINT message, WPARAM wParam, LPARAM lParam);

  public:
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
