#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Mosaic.h"

class Player {

 public:
  Player(std::string name, bool is_first_player);
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
  unsigned int score;
  Mosaic* mosaic;
  bool is_first_player;

};

#endif  // PLAYER_H
