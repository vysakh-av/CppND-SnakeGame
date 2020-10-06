#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
class Player {
 public:
  Player();
  Player(std::string name, std::string country, int score);
  ~Player();
  std::string GetPlayerName();
  std::string SetPlayerName(std::string name);
  std::string GetPlayerCountry();
  std::string SetPlayerCountry(std::string country);
  int GetPlayerScore();
  int SetPlayerScore(int score);

 private:
  std::string _name;
  std::string _country;
  int _score;
};

#endif  // _PLAYER_H_
