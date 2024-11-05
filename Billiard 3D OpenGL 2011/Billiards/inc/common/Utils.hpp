#include "win/Windows.hpp"
#include <string>

#define ASSERT_BOX(TEXT) MessageBox(nullptr, L##TEXT, L"Assertion", MB_OK | MB_ICONEXCLAMATION)
