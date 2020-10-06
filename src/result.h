#ifndef _RESULT_H_
#define _RESULT_H_
#include <future>
#include <memory>
#include <mutex>
#include <vector>
#include "player.h"

class Result {
 public:
  Result();
  ~Result();

  // Rule of Five
  Result(const Result &src) = delete;
  Result &operator=(const Result &src) = delete;
  Result(const Result &&src) = delete;
  Result &operator=(const Result &&src) = delete;
  void AddResult();
  void PrintResult();
  std::shared_ptr<Player> GetCurrentPlayer();

 private:
  bool isResultFileExists();
  std::shared_ptr<Player> _player;
  std::mutex _mutex;
  const std::string _gameResultFile = "output.txt";
};

#endif