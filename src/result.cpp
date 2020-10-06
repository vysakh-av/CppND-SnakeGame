#ifdef _WIN32
#include <io.h>
#define access _access_s
#else
#include <unistd.h>
#endif
#include <fstream>
#include <iomanip>
#include <iostream>
#include "result.h"

Result::Result() { _player = std::make_shared<Player>(); }
Result::~Result() {}

bool Result::isResultFileExists() {
  return access(_gameResultFile.c_str(), 0) == 0;
}

void Result::AddResult() {
  if (_player == nullptr) {
    std::cout << "Player details not found, not adding any result \n";
    return;
  }

  std::ofstream resultFile;
  if (!isResultFileExists()) {
    std::cout << "File is opening for updating first time, add header \n";
    std::unique_lock<std::mutex> fileLock(_mutex);
    resultFile.open(_gameResultFile);
    if (!resultFile) {
      std::cout << "Failed to open file \n";
    } else {
      resultFile << "Name" << std::setw(10) << "Country" << std::setw(10)
                 << "Points" << std::setw(10) << "\n";
      resultFile << _player->GetPlayerName() << std::setw(10)
                 << _player->GetPlayerCountry() << std::setw(10)
                 << _player->GetPlayerScore() << "\n";
    }
    resultFile.close();
    fileLock.unlock();
  } else {
    std::unique_lock<std::mutex> fileLock(_mutex);
    resultFile.open(_gameResultFile, std::ios_base::app);
    if (!resultFile) {
      std::cout << "Failed to open file \n";
    } else {
      resultFile << "Name" << std::setw(10) << "Country" << std::setw(10)
                 << "Points" << std::setw(10) << "\n";
      resultFile << _player->GetPlayerName() << std::setw(10)
                 << _player->GetPlayerCountry() << std::setw(10)
                 << _player->GetPlayerScore() << "\n";
    }
    resultFile.close();
    fileLock.unlock();
  }
}

void Result::PrintResult() {
  std::unique_lock<std::mutex> fileLock(_mutex);
  std::string line;
  std::ifstream resultFile(_gameResultFile);
  if (resultFile.is_open()) {
    while (std::getline(resultFile, line)) {
      std::cout << line;
    }
    resultFile.close();
    fileLock.unlock();
  } else {
    std::cout << "Failed to open file \n";
    fileLock.unlock();
  }
}

std::shared_ptr<Player> Result::GetCurrentPlayer() {
  return std::move(_player);
}