#ifndef _MENU_H_
#define _MENU_H_

//enum MenuOption { START = 1, STATS = 2, QUIT = 3 };
#define START 1
#define STATS 2
#define QUIT 3

class Menu {
 public:
  Menu();
  ~Menu();
  void ShowMenu();
  int getOption();

 private:
  int _userOption;
};

#endif  //_MENU_H
