#include <iostream>
#include "controller.h"
#include "game.h"
#include "menu.h"
#include "renderer.h"
#include "result.h"

static void GetPlayerNameFromConsole(std::promise<std::string> &&prms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::string name;
  std::cout << "Hello, Welcome to the Sname Game \n";
  std::cout << "Please enter your name: \t";
  std::cin >> name;
  prms.set_value(name);
}

static std::string GetPlayerCountryFromConsole() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::string country;
  std::cout << "\n Please enter your country: \t";
  std::cin >> country;
  return country;
}
static void RunGame() {
  /** Read Player details. */
  Result result;
  // Read name - Spawn a thread and retreive it using promise -future.
  std::promise<std::string> prms;
  std::future<std::string> ftrName = prms.get_future();
  std::thread getNameThread(GetPlayerNameFromConsole, std::move(prms));

  auto status = ftrName.wait_for(std::chrono::milliseconds(1000));
  if (status == std::future_status::ready)  // result is ready
  {
    // set player name
    result.GetCurrentPlayer()->SetPlayerName(ftrName.get());
    std::cout << "Player name = " << result.GetCurrentPlayer()->GetPlayerName()
              << std::endl;
  } else {
    std::cout << "User not eneterd his name \n";
    result.GetCurrentPlayer()->SetPlayerName("Unknown");
  }

  // Read country name - Use a aync task to read it.
  std::future<std::string> ftrCountry =
      std::async(std::launch::async, GetPlayerCountryFromConsole);
  status = ftrCountry.wait_for(std::chrono::milliseconds(1000));
  if (status == std::future_status::ready)  // result is ready
  {
    // set player country name
    result.GetCurrentPlayer()->SetPlayerCountry(ftrCountry.get());
    std::cout << "Player name = "
              << result.GetCurrentPlayer()->GetPlayerCountry() << std::endl;
  } else {
    std::cout << "User not eneterd his name \n";
    result.GetCurrentPlayer()->SetPlayerCountry("Unknown");
  }

  // Start game.
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  // Update Result.
  result.GetCurrentPlayer()->SetPlayerScore(game.GetScore());
  result.AddResult();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
}

int main() {
  Menu menu;
  Result result;
  while (true) {
    menu.ShowMenu();
    int opt = menu.getOption();
    switch (opt) {
      case MenuOption::START: {
        break;
      }
      case MenuOption::STATS: {
        result.PrintResult();
        continue;
      }
      case MenuOption::QUIT: {
        std::cout << "End game \n";
        exit(1);
      }
    }

    RunGame();
  }
  return 0;
}