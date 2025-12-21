#include "framework.h"
#include "resource.h"
#include "Application.hpp"
#include "Display.hpp"
#include <chrono>
#include <thread>
#include <algorithm>

static Application app;

#define MAX_LOADSTRING 100
#define MAX_ARDUINO_LOOP WM_USER + 1

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, 0, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    HBRUSH brsh = CreateSolidBrush(RGB(50, 50, 255));
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARDUINOSIMULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = brsh;
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND hwnd;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

constexpr int wndWidthShadow = 16;
constexpr int wndHeightShadow = 39;
  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
    CW_USEDEFAULT, 0, Display::canvasWidth + wndWidthShadow, Display::canvasHeight + wndHeightShadow,
    nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    return FALSE;
  }
  hwnd = hWnd;
  app.init();

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_ACTIVATE:
    {
      SetTimer(hWnd, 0, USER_TIMER_MINIMUM, NULL);
      break;
    }
    case WM_TIMER:
    {
      PostMessage(hWnd, MAX_ARDUINO_LOOP, 7, 8);
      break;
    }
    case MAX_ARDUINO_LOOP:
    {
      app.update();
      InvalidateRect(hwnd, NULL, 0);
      break;
    }
    case WM_KEYDOWN:
    {
      void keyDown(HWND hwnd, WPARAM);
      keyDown(hWnd, wParam);
      break;
    }
    case WM_KEYUP:
    {
      void keyUp(HWND hwnd, WPARAM);
      keyUp(hWnd, wParam);
      break;
    }
    case WM_PAINT:
    {
      app.draw();
      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

extern bool buttons[20] = {};

static constexpr WPARAM BUTTON_1 = 0x41; //A
static constexpr WPARAM BUTTON_2 = 0x44; //D
static constexpr WPARAM BUTTON_3 = 0x53; //S
static constexpr WPARAM BUTTON_4 = 0x57; //W

//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
void keyDown(HWND hwnd, WPARAM wParam) {
  //X
  if (wParam == BUTTON_1) //A
  {
    buttons[0] = true;
  }
  //Y
  if (wParam == BUTTON_2) //D
  {
    buttons[1] = true;
  }
  //A
  if (wParam == BUTTON_3) //S
  {
    buttons[2] = true;
  }
  //B
  if (wParam == BUTTON_4) //W
  {
    buttons[3] = true;
  }
}
//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
void keyUp(HWND hwnd, WPARAM wParam) {
  if (wParam == BUTTON_1) //A
  {
    buttons[0] = false;
  }
  if (wParam == BUTTON_2) //D
  {
    buttons[1] = false;
  }
  if (wParam == BUTTON_3) //S
  {
    buttons[2] = false;
  }
  if (wParam == BUTTON_4) //W
  {
    buttons[3] = false;
  }
}
