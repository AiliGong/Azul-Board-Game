#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Mosaic.h"
#include "Constants.h"

class Player {

 public:
  Player(std::string name, bool is_first_player, Constants* constant);
  ~Player();
  void setScore(unsigned int score);
  void updateScoreBy(int points);
  int getScore() const;
  std::string getName() const;
  Mosaic* getMosaic() const;
  void setFirstPlayer();
  void resetFirstPlayer();
  bool isFirstPlayer();
  void resetScore();

 private:
  std::string name;
  int score;
  Mosaic* mosaic;
  bool is_first_player;
  Constants* constant;

};

#endif  // PLAYER_H
