#include "GameMenu.h"

GameMenu::GameMenu() {
  this->randomSeed = -1;
  this->constant = new Constants(1);
  ge = new GameEngine(randomSeed, constant);
}

GameMenu::GameMenu(int randomSeed, Constants* constant) {
  this->constant = constant;
  this->randomSeed = randomSeed;
  ge = new GameEngine(randomSeed, constant);
}

void GameMenu::newGame() {
  std::cout << "Starting a New Game" << std::endl;
  std::cout << std::endl;

  std::string player_name;
  int num_of_players = ge->getConstant()->getNUM_OF_PLAYERS();
  for (int i = 0; i != num_of_players; ++i) {
    std::cout << "Enter a name for player " << i + 1 << std::endl;
    std::cout << "> ";
    std::getline(std::cin, player_name);

    if (!std::cin.good()) {
      throw new std::invalid_argument("EOF");
    }

    std::cout << std::endl;
    this->ge->addPlayer(player_name);
  }

  std::cout << std::endl;
  std::cout << "Let's Play!" << std::endl;
  std::cout << std::endl;

  this->play();
}

void GameMenu::loadGame(std::string filename) {
  GameHistory* gh = GameHistory::loadFromFile(filename);
  this->ge = new GameEngine(gh);

  // Trigger executing turns
  this->ge->startGame();
}

void GameMenu::resumeGame(std::string filename) {
  this->loadGame(filename);

  std::cout << std::endl
            << "Azul game successfully loaded" << std::endl
            << std::endl;

  this->play();
}

void GameMenu::play() {
  if (this->ge->getState() == GameState::START) {
    this->ge->startGame();  // -> START_OF_ROUND
  }

  if (this->ge->getState() == GameState::MID_ROUND) {
    while (this->ge->getState() != GameState::END_OF_ROUND) {
      this->playTurn();
    }  // -> END_OF_ROUND
  }

  // All roads lead here (unless we've loaded a game that has already finished)
  if (this->ge->getState() == GameState::START_OF_ROUND ||
      this->ge->getState() == GameState::END_OF_ROUND) {
    while (this->ge->getState() != GameState::END_OF_GAME) {
      this->playRound();
    }  // -> END_OF_GAME
  }

  assert(this->ge->getState() == GameState::END_OF_GAME);

  std::cout << "=== GAME OVER ===" << std::endl << std::endl;

  this->printScores();
}

void GameMenu::playRound() {
  if (this->ge->getState() == GameState::END_OF_ROUND) {
    this->ge->startRound();
  }

  std::cout << "=== Start Round ===" << std::endl;
  while (this->ge->getState() != GameState::END_OF_ROUND &&
         this->ge->getState() != GameState::END_OF_GAME) {
    this->playTurn();
  }
  std::cout << "=== END OF ROUND ===" << std::endl << std::endl;
}

void GameMenu::playTurn() {
  std::string player_name = this->ge->getNextPlayerName();
  std::cout << "TURN FOR PLAYER: " << player_name << std::endl;

  this->printFactories();
  std::cout << std::endl;
  this->printMosaic(player_name);

  bool turn_success = false;
  std::string turn_command;
  Turn* turn;
  while (!turn_success) {
    std::cout << "> ";

    // trigger setting EOF bit
    std::cin.peek();

    if (!std::cin.good()) {
      throw new std::invalid_argument("EOF");
    }

    std::getline(std::cin, turn_command);

    try {
      turn = Turn::parseCommand(turn_command, constant);
      turn_success = this->ge->playTurn(turn);
      if (!turn_success) {
        std::cout << "Turn not possible at this time" << std::endl;
      }
    } catch (std::runtime_error& e) {
      if (turn_command.substr(0, 5) == "save ") {
        this->ge->saveGame(turn_command.substr(5));
        std::cout << "Game saved" << std::endl;
      } else {
        std::cout << "Invalid input" << std::endl;
      }
    }
  }

  std::cout << "Turn successful." << std::endl << std::endl;
}

void GameMenu::printFactories() const {
  std::cout << "Factories:" << std::endl;
  for (Factory* f : this->ge->getFactories()) {
    std::cout << f->str() << std::endl;
  }
}

void GameMenu::printMosaic(std::string player_name) const {
  std::cout << "Mosaic for " << player_name << ":" << std::endl;
  std::cout << this->ge->getMosaic(player_name)->str();
}

void GameMenu::printScores() const {
  std::cout << "Final Scores:" << std::endl;

  const Player* winner = nullptr;
  bool draw = false;

  for (const Player* player : this->ge->getPlayers()) {
    std::cout << player->getName() << ": " << player->getScore() << " ";
    if (!winner || player->getScore() > winner->getScore()) {
      winner = player;
    } else if (player->getScore() == winner->getScore()) {
      draw = true;
    }
  }

  if (winner) {
    if (draw) {
      std::cout << "It's a draw!" << std::endl;
    } else {
      std::cout << winner->getName() << " wins!" << std::endl;
    }
  } else {
    throw std::runtime_error("Error deciding winner");
  }
}

void GameMenu::testMode(std::string filename) {
  try {
    this->loadGame(filename);
    this->printFactories();

    for (const Player* player : this->ge->getPlayers()) {
      std::cout << std::endl;
      std::cout << "Score for " << player->getName();
      std::cout << ": " << player->getScore() << std::endl;
      this->printMosaic(player->getName());
    }
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}
