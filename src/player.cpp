#include "player.h"

Player::Player() : _name("PlayerX"), _country("PlayerCountryX"), _score(0) {}

Player::Player(std::string name, std::string country, int score)
    : _name(name), _country(country), _score(score) {}

Player::~Player() {}
std::string Player::GetPlayerName() { return _name; }

std::string Player::SetPlayerName(std::string name) { _name = name; }

std::string Player::GetPlayerCountry() { return _country; }

std::string Player::SetPlayerCountry(std::string country) {
  _country = country;
}

int Player::GetPlayerScore() { return _score; }

int Player::SetPlayerScore(int score) { _score = score; }