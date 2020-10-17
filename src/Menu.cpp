#include "Menu.h"

#include <iostream>
#include <stdexcept>

#include "GameHistory.h"
#include "GameMenu.h"

Menu::Menu() {
  this->randomSeed = -1;
}

Menu::Menu(const char* randomSeed) {
  this->randomSeed = atoi(randomSeed);
}

Menu::~Menu() {
  delete this->game;
}

void Menu::start() {
  this->welcomeMessage();
  std::string menuOption;

  do {
    this->startingMenu();
    std::cout << "> ";
    std::getline(std::cin, menuOption);
    this->run(menuOption);
  } while (std::cin.good() && menuOption != "4");
}

void Menu::welcomeMessage() {
  std::cout << std::endl;
  std::cout << " █████╗ ███████╗██╗   ██╗██╗" << std::endl;
  std::cout << "██╔══██╗╚══███╔╝██║   ██║██║ " << std::endl;
  std::cout << "███████║  ███╔╝ ██║   ██║██║     " << std::endl;
  std::cout << "██╔══██║ ███╔╝  ██║   ██║██║     " << std::endl;
  std::cout << "██║  ██║███████╗╚██████╔╝███████╗" << std::endl;
  std::cout << "╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚══════╝" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << "\tWelcome to AZUL!" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << std::endl;
}

void Menu::startingMenu() {
  std::cout << std::endl;
  std::cout << "Menu" << std::endl;
  std::cout << "----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits (Show student information)" << std::endl;
  std::cout << "4. Quit" << std::endl;
  std::cout << std::endl;
}

void Menu::exit() {
  std::cout << "Goodbye" << std::endl;
}

void Menu::run(std::string& menuOption) {
  if (menuOption == std::string("1")) {
    try {
      newGame();
    } catch (std::invalid_argument*) {
      exit();
      menuOption = "4";
    }
  } else if (menuOption == std::string("2")) {
    try {
      loadGame();
    } catch (std::invalid_argument*) {
      exit();
      menuOption = "4";
    }
  } else if (menuOption == std::string("3")) {
    printCredits();
  } else if (menuOption == std::string("4")) {
    exit();
  } else {
    if (std::cin.good()) {
      std::cout << "Invalid input" << std::endl;
    } else {
      exit();
    }
  }
}

void Menu::printCredits() {
  std::cout << std::endl;
  std::cout << "----------------------------------" << std::endl;
  std::cout << "Name: Aili Gong" << std::endl;
  std::cout << "Student ID: s3443647" << std::endl;
  std::cout << "Email: s3443647@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;

  std::cout << "Name: Catherine Thomas" << std::endl;
  std::cout << "Student ID: s3784710" << std::endl;
  std::cout << "Email: s3784710@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;

  std::cout << "Name: Sam Mellor" << std::endl;
  std::cout << "Student ID: s3491308" << std::endl;
  std::cout << "Email: s3491308@student.rmit.edu.au" << std::endl;
  std::cout << "----------------------------------" << std::endl;
}

void Menu::newGame() {
  std::string modeOption;

  bool validInput = false;
  
  while (!validInput) {
    this->newGameMenu();
    std::cout << "> ";
    std::getline(std::cin, modeOption);
    if (modeOption == std::string("1") || modeOption == std::string("2") ||
        modeOption == std::string("3") ||modeOption == std::string("4")) {
      validInput = true;
    } else {
      if (std::cin.good()) {
        std::cout << "Invalid input" << std::endl;
      } else {
        throw new std::invalid_argument("EOF");
      }
    }
  }

  if (game != nullptr) { 
    delete game;
  }

  Config* config = new Config(stoi(modeOption));
  this->game = new GameMenu(randomSeed, config);
  this->game->newGame();
}

void Menu::loadGame() {
  std::cout << "Enter the filename from which to load a game " << std::endl;
  std::cout << "> ";

  std::string filename;
  std::getline(std::cin, filename);

  this->game = new GameMenu();
  this->game->resumeGame(filename);
}

void Menu::newGameMenu() {
  std::cout << std::endl;
  std::cout << "Please choose game mode" << std::endl;
  std::cout << "----" << std::endl;
  std::cout << "1. Standard Mode" << std::endl;
  std::cout << "2. Six Tile Colour Mode" << std::endl;
  std::cout << "3. Five Tile Grey Mode" << std::endl;
  std::cout << "4. Six Tile Grey Mode" << std::endl;
  std::cout << std::endl;
}