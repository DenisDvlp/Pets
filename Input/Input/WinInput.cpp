#include "Input.h"
#include <windows.h>

Input::Input(IInputListener * listener) :
  mListener(listener) 
{}

bool Input::getKeyState(byte key)
{
  return GetKeyState(key) & 1;
}

void Input::run() {

  if (!mListener) return;

  POINT mMousePos = { 0 };
  POINT mMousePosPrev = { 0 };
  bool mBuf[2][256] = { 0 };
  bool * mCurrent = mBuf[0];

  GetCursorPos(&mMousePosPrev);

  while (true) {

    // swap keystates
    mCurrent = mCurrent == mBuf[1] ? mBuf[0] : mBuf[1];

    // scan keys
    for (byte i = 1; i != 255; i++)
    {
      mCurrent[i] = static_cast<bool>(GetKeyState(i) & 128);
    }

    // mouse scan and notify
    GetCursorPos(&mMousePos);
    if (mMousePosPrev.x != mMousePos.x || mMousePosPrev.y != mMousePos.y)
    {
      mMousePosPrev = mMousePos;
      mListener->OnMouseMove(static_cast<short>(mMousePos.x), static_cast<short>(mMousePos.y));
    }

    // notify keys
    for (byte i = 1; i != 255; i++)
    {
      if (mBuf[0][i] != mBuf[1][i])
      {
        mListener->OnButton(i, mCurrent[i]);
      }
    }
  }
}