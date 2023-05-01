#include "Input.h"
#include <iostream>


class InputListener : public IInputListener
{
public:
  virtual void OnMouseMove(word x, word y) override
  {
    std::cout << x << "\t" << y << "\n";
  }
  virtual void OnButton(byte key, bool pressed) override
  {
    std::cout << int(key) << "\t" << pressed << "\n";
  }
};

int main()
{
  InputListener listener;
  Input input(&listener);
  input.run();
}