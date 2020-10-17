#ifndef GAME_H
#define GAME_H

#include <cassert>
#include <iostream>

#include "GameEngine.h"
#include "Config.h"

class GameMenu {
 private:
  GameEngine* ge;
  int randomSeed;
  Config* config;
  // load a saved game
  void loadGame(std::string filename);

  void printFactories() const;
  void printMosaic(std::string player_name) const;
  void printScores() const;
  void moveTileAfterRound();
  void moveTileManually();
  void moveTileManually(Player* player);


 public:
  GameMenu();
  GameMenu(int randomSeed, Config* config);
  ~GameMenu();

  // start a new game
  void newGame();

  // resume a saved game
  void resumeGame(std::string filename);

  // play through rounds until the game ends
  void play();

  // play through a round
  void playRound();

  // play a single turn
  void playTurn();

  // run a saved game in test mode
  void testMode(std::string filename);
};

#endif  // GAME_H
