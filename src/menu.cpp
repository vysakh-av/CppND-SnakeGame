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
  std::cin >> opt;

  // Set option value.
  _userOption = std::move(opt);
}

int Menu::getOption() { return _userOption; }