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

  protected:
    void registerWindowClass();
    static LRESULT CALLBACK windowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    std::wstring m_className{};
    std::wstring m_caption{};
    HINSTANCE m_hInstance{};
    HWND m_hWnd{};
};
