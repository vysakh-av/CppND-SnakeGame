#include <iostream>
#include "menu.h"

Menu::Menu() : _userOption(0) {}
Menu::~Menu() {}

void Menu::ShowMenu() {
  int opt;
  std::cout << "WELCOME TO SNAME GAME \n"
            << "===========================\n"
            << "1. Start Game \n"
            << "2. Statistics \n"
            << "3. Quit Game \n"
            << "=================================\n";
  std::cout << "Please enter one of the options from menu: \t";
  while (std::cin >> opt) {
    if (opt == MenuOption::START || opt == MenuOption::STATS ||
        opt == MenuOption::QUIT) {
      std::cout << "Invalid option: Please select option from 1-3 \n";
    } else {
      break;
    }
  }

  if (std::cin.fail()) {
    std::cout
        << "Looks like  we have received a wrong input from user, exit \n";
    opt = MenuOption::QUIT;
  }

  // Set option value.
  _userOption = std::move(opt);
}

int Menu::getOption() { return _userOption; }