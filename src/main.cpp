#include <iostream>

#include "GameMenu.h"
#include "Menu.h"

void printMenu();

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    Menu* menu = new Menu();
    menu->start();
  } else if (argc == 3 && std::string(argv[1]) == "-t") {
    GameMenu* game = new GameMenu();
    game->testMode(argv[2]);
  } else if (argc == 3 && std::string(argv[1]) == "-s") {
    Menu* menu = new Menu(argv[2]);
    menu->start();
  } else {
    std::cout << argv[0] << ": illegal arguments" << std::endl
              << "usage: " << argv[0] << " [-t save-game-file]";
  }

  return EXIT_SUCCESS;
}
