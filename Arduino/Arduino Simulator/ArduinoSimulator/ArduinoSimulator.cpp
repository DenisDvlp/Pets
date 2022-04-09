// ArduinoSimulator.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "ArduinoSimulator.h"
#include "Application.h"
#include <bitset>
#include <chrono>
#include <thread>

#ifdef ARDUINO_SIMULATOR

void delay(unsigned long ms) {
  std::chrono::milliseconds duration(ms);
  std::this_thread::sleep_for(duration);
}

unsigned long millis() {
  using namespace std::chrono;
  auto t = steady_clock::now().time_since_epoch();
  auto ms = duration_cast<milliseconds>(t).count();
  return static_cast<unsigned long>(ms);
}

#endif

static Application app;

#define MAX_LOADSTRING 100
#define MAX_ARDUINO_LOOP WM_USER + 1

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    // Цикл основного сообщения:
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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
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

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//

constexpr int size = 7;
constexpr int pixelInterval = 1;
constexpr int offsetLeft = 3;
constexpr int offsetTop = 3;
constexpr int displayWidth = 128;
constexpr int displayHeight = 64;
constexpr int width = displayWidth * (size + pixelInterval) + offsetLeft * 2;
constexpr int height = displayHeight * (size + pixelInterval) + offsetTop * 2;
constexpr int wndWidthShadow = 16;
constexpr int wndHeightShadow = 39;
HWND hwnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
    CW_USEDEFAULT, 0, width + wndWidthShadow, height + wndHeightShadow, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    return FALSE;
  }
  hwnd = hWnd;
  app.init(hWnd, { width, height });

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            void DisplaySimulator(HDC);
            DisplaySimulator(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

extern bool buttons[20] = {};

//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
void keyDown(HWND hwnd, WPARAM wParam) {
  //X
  if (wParam == 0x41) //A
  {
    buttons[0] = true;
  }
  //Y
  if (wParam == 0x44) //D
  {
    buttons[1] = true;
  }
  //A
  if (wParam == 0x53) //S
  {
    buttons[2] = true;
  }
  //B
  if (wParam == 0x57) //W
  {
    buttons[3] = true;
  }
}
//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
void keyUp(HWND hwnd, WPARAM wParam) {
  if (wParam == 0x41) //A
  {
    buttons[0] = false;
  }
  if (wParam == 0x44) //D
  {
    buttons[1] = false;
  }
  if (wParam == 0x53) //S
  {
    buttons[2] = false;
  }
  if (wParam == 0x57) //W
  {
    buttons[3] = false;
  }
}

void DisplaySimulator(HDC hdc) {
  // This is for double buffering, to avoid seeing the "live" drawing.
  HDC hdcMemory = CreateCompatibleDC(hdc);
  HBITMAP hbmp = CreateCompatibleBitmap(hdc, width, height);
  SelectObject(hdcMemory, hbmp);

  // Turn in on to see inactive pixels.
  constexpr bool drawInactivePixels = false;

  static const RECT bgR = { 0, 0, width, height };
  static const HBRUSH brushBkg = CreateSolidBrush(drawInactivePixels ? RGB(50, 50, 50) : RGB(50, 50, 255));
  FillRect(hdcMemory, &bgR, brushBkg);

  constexpr int NUM_PAGE = 8;
  Buffer buf = app.getBuffer();
  RECT r = {};
  int l = 0;
  std::bitset<CHAR_BIT> bits;
  static const HBRUSH brushOn = CreateSolidBrush(RGB(0, 0, 0));
  static const HBRUSH brushOff = CreateSolidBrush(RGB(50, 50, 255));

  for (int i = 0; i < NUM_PAGE; i++)
  {
    for (int j = 0; j < displayWidth; j++)
    {
      r.left = (size + pixelInterval) * j + offsetLeft;
      r.right = r.left + size;
      bits = buf.data[l++];
      for (int k = 0; k < CHAR_BIT; k++)
      {
        r.top = (size + pixelInterval) * (i * CHAR_BIT + k) + offsetTop;
        r.bottom = r.top + size;
        if(drawInactivePixels || bits[k])
          FillRect(hdcMemory, &r, bits[k] ? brushOn : brushOff);
      }
    }
  }

  BitBlt(hdc, 0, 0, width, height, hdcMemory, 0, 0, SRCCOPY);
  DeleteObject(hbmp);
  DeleteDC(hdcMemory);
}