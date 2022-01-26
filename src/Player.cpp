#include "Player.h"

Player::Player(std::string name, bool is_first_player, Config* config) {
  this->name = name;
  score = 0;
  this->is_first_player = is_first_player;
  this->config = config;
  mosaic = new Mosaic(config->getMOSAIC_GRID_DIM(), config->getBROKEN_TILE_SOLT());
}

Player::~Player() {
  delete mosaic;
}

void Player::setScore(unsigned int score) {
  this->score = score;
}

void Player::updateScoreBy(int points) {
  
  if ((score + points) < 0) {
    score = 0;
  } else {
    score += points;
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