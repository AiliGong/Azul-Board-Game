#include "Menu.h"

#include <iostream>
#include <stdexcept>

#include "GameHistory.h"
#include "GameMenu.h"

Menu::Menu() {}

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
    loadGame();
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
  this->game = new GameMenu();
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