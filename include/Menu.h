#ifndef MENU_H
#define MENU_H

#include "GameMenu.h"

class Menu {
 private:
  GameMenu* game;
  void welcomeMessage();
  void startingMenu();
  void printCredits();
  void newGame();
  void loadGame();
  void run(std::string& menuOption);
  void exit();

 public:
  Menu();
  ~Menu();

  void start();
};

#endif  // MENU_H