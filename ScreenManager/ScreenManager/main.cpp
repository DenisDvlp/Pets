#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "ScreenManager.h"
#include "Screens.h"

int main()
{
  //test 1
  /*StateManager &ss = StateManager::instance();

  State *root = new StateRoot();
  State *s1 = new State1();
  State *s2 = new State2();

  ss.add(0, root);
  ss.add(1, s1);
  ss.add(2, s2);
  ss.add(3, new State3());
  ss.add(4, new State4());
  ss.add(5, new State5());
  ss.add(6, new State6());
  ss.add(7, new State7());
  ss.add(8, new State8());

  std::cout << "-----------" << std::endl;
  ss.open(3, 0, 1, 4);
  std::cout << "-----------" << std::endl;
  ss.open(4, 0, 2, 5, 8);
  std::cout << "-----------" << std::endl;
  ss.close(2);
  std::cout << "-----------" << std::endl;
  ss.open(1, 5);*/

  //test 2
  ScreenManager &ss = ScreenManager::instance();

  Screen *root = new ScreenRoot();
  Screen *s1 = new Screen1();
  Screen *s2 = new Screen2();

  ss.add(SCR_ROOT, root);
  ss.add(SCR_MEDIA, s1);
  ss.add(SCR_RADIO, s2);
  ss.add(SCR_PHONE, new Screen3());
  ss.add(SCR_MEDIA_ERROR, new Screen4());
  ss.add(SCR_MEDIA_STANDART, new Screen5());
  ss.add(SCR_RADIO_ERROR, new Screen6());
  ss.add(SCR_RADIO_STANDART, new Screen7());
  ss.add(SCR_PHONE_ERROR, new Screen6());
  ss.add(SCR_PHONE_STANDART, new Screen7());
  ss.add(SCR_AES, new Screen6());
  ss.add(SCR_AT, new Screen7());

  std::cout << "-----------" << std::endl;
  ss.open(2, SCR_RADIO, SCR_RADIO_ERROR);
  ss.print();
  std::cout << "-----------" << std::endl;
  ss.open(2, SCR_MEDIA, SCR_AES);
  ss.print();
  std::cout << "-----------" << std::endl;
  ss.open(SCR_AES);
  ss.print();
  std::cout << "-----------" << std::endl;
  ss.close(SCR_MEDIA);
  ss.print();
  std::cout << "-----------" << std::endl;
  ss.close(SCR_AT);
  ss.print();
}