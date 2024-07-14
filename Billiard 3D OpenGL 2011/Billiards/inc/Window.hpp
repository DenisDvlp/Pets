
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

class Window {
  public:
    Window(std::wstring name, HINSTANCE hInstance);
    bool open(const std::wstring& caption);
    ~Window();

    bool OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

  protected:
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message,
                                            WPARAM wParam, LPARAM lParam);
    std::wstring name;
    HINSTANCE hInstance;
    HWND hwnd;
};
