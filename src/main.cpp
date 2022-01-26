#include <iostream>

#include "GameMenu.h"
#include "Menu.h"

void printMenu();

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    Menu* menu = new Menu();
    menu->start();
    delete menu;
  } else if (argc == 3 && std::string(argv[1]) == "-t") {
    GameMenu* game = new GameMenu();
    game->testMode(argv[2]);
    delete game;
  } else if (argc == 3 && std::string(argv[1]) == "-s") {
    Menu* menu = new Menu(argv[2]);
    menu->start();
    delete menu;
  } else {
    std::cout << argv[0] << ": illegal arguments" << std::endl
              << "Help: "<< std::endl
              << "Testing mode: "<< argv[0] << " [-t save-game-file]"<< std::endl
              << "Add randomness: "<< argv[0] << " [-s random-seed]"<< std::endl;
  }

  return EXIT_SUCCESS;
}
