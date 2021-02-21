//Key.h
#pragma once
#include "DTypes.h"
#include <xstring>

enum class Key : byte
{
  NONE = 0,

  MOUSE_L,
  MOUSE_R,
  MOUSE_M,

  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,

  SQUARE_BRACKET_L,
  SQUARE_BRACKET_R,
  SEMICOLON,
  QUOTES,
  COMA,
  DOT,
  BACKSLASH,
  SLASH,

  _0,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,

  APOSTROPHE,
  UNDERSCORE,
  ASSIGN,
  BACKSPACE,

  NUM_0,
  NUM_1,
  NUM_2,
  NUM_3,
  NUM_4,
  NUM_5,
  NUM_6,
  NUM_7,
  NUM_8,
  NUM_9,

  MULTIPLY,
  PLUS,
  MINUS,
  DIVIDE,
  PERIOD,

  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,

  SHIFT,
  SHIFT_L,//empty
  SHIFT_R,//empty
  CTRL,
  ALT,
  CTRL_L,//empty
  CTRL_R,//empty
  ALT_L,//empty
  ALT_R,//empty
  WIN_L,
  WIN_R,
  BREAK,
  MENU,
  TAB,
  CAPSLOCK,
  NUMLOCK,
  SCROLLLOCK,

  ENTER,
  ESCAPE,
  SPACE,
  END,
  HOME,
  INSERT,
  DELETE,
  PAGE_UP,
  PAGE_DOWN,

  ARROW_UP,
  ARROW_DOWN,
  ARROW_LEFT,
  ARROW_RIGHT,

  SIZE
};

std::string toString(Key key);