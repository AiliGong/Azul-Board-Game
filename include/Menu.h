#ifndef MENU_H
#define MENU_H

#include "GameMenu.h"

class Menu {
 private:
  GameMenu* game;
  int randomSeed;
  void welcomeMessage();
  void startingMenu();
  void printCredits();
  void newGame();
  void loadGame();
  void run(std::string& menuOption);
  void exit();
  void newGameMenu();

 public:
  Menu();
  Menu(const char* randomSeed);

  ~Menu();

  void start();
};

#endif  // MENU_H