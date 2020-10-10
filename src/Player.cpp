#include "Player.h"

Player::Player(std::string name, bool is_first_player) {
  this->name = name;
  score = 0;
  mosaic = new Mosaic();
  this->is_first_player = is_first_player;
}

Player::~Player() {
  delete mosaic;
}

void Player::setScore(unsigned int score) {
  this->score = score;
}

void Player::updateScoreBy(int points) {
  score += points;

  if (score < 0) {
    score = 0;
  }
}

int Player::getScore() const {
  return score;
}

std::string Player::getName() const {
  return name;
}

Mosaic* Player::getMosaic() const {
  return mosaic;
}

void Player::setFirstPlayer() {
  is_first_player = true;
}

void Player::resetFirstPlayer() {
  is_first_player = false;
}

bool Player::isFirstPlayer() {
  return is_first_player;
}

void Player::resetScore() {
  score = 0;
}