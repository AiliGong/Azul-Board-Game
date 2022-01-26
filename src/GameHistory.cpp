#include "GameHistory.h"
#include "Config.h"
#include "GameEngine.h"
#include "Mosaic.h"
#include "Turn.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

GameHistory::GameHistory() {
  this->read_from_file = false;
}

GameHistory::GameHistory(GameHistory& other) {
  this->initial_tiles = new TileBag(*other.initial_tiles);
  this->player_names = other.player_names;
  this->turns = other.turns;
}

GameHistory* GameHistory::loadFromFile(std::string filename) {
  std::ifstream savefile(filename);
  if (!savefile) {
    throw std::runtime_error("Unable to load file: " + filename);
  }

  GameHistory* gh = new GameHistory();
  gh->read_from_file = true;

  gh->initial_tiles = new TileBag();

  gh->readSaveFile(savefile);
  savefile.close();
  return gh;
}

GameHistory::~GameHistory() {
  delete this->initial_tiles;

  for (const Turn* turn : this->turns) {
    delete turn;
  }
  turns.clear();

  delete config;

  for (TileBag* tileBag : this->tile_bags_in_game) {
    delete tileBag;
  }
}

void GameHistory::addTurn(const Turn* turn) {
  this->turns.push_back(turn);
}

void GameHistory::addPlayer(std::string player_name) {
  if (!this->player_names.emplace(player_name).second) {
    throw std::runtime_error("Received duplicate player name");
  }
}

void GameHistory::writeSaveFile(std::ostream& out) const { 
  if (random_seed < 0 && this->config->isStandardMode()) {
    this->writeSaveFileStandard(out);
  } else {
    this->writeSaveFileAdvanced(out);
  }
}

void GameHistory::writeSaveFileStandard(std::ostream& out) const {
  out << this->initial_tiles->getAllTileIni() << std::endl;
  
  for (std::string player_name : this->player_names) {
    out << player_name << std::endl;
  }

  for (const Turn* turn : this->turns) {
    out << turn->str() << std::endl;
  }
}

void GameHistory::writeSaveFileAdvanced(std::ostream& out) const {
  //using my own format
  out << "#myformat" << std::endl;
  out << this->random_seed << std::endl;
  out << this->config->getNUM_OF_TILECOLOUR() << std::endl;
  out << this->config->isGreyMode() << std::endl;
  
  for (std::string player_name : this->player_names) {
    out << player_name << std::endl;
  }
  
  //initial tile bag
  out << this->initial_tiles->getAllTileIni() << std::endl;

  //bags in the middle of the game
  for(TileBag* tile_bag : tile_bags_in_game) {
      out << "@" << tile_bag->getAllTileIni() << std::endl;
  }

  //mannual move in grey mode
  for (int move : this->mannual_moves) {
    out << "%" << move << std::endl;
  }

  //turns
  for (const Turn* turn : this->turns) {
    out << turn->str() << std::endl;
  } 
}
void GameHistory::saveToFile(std::string filename) const {
  // TODO: error handling
  std::ofstream savefile;
  savefile.open(filename);
  this->writeSaveFile(savefile);
  savefile.close();
}

void GameHistory::readSaveFile(std::istream& file) {
  std::string line;

  // first line contains space-separated tile colour indicators
  std::getline(file, line);
  if (line == "#myformat") {
    this->readSaveFileAdvanced(file);
  } else {
    this->config = new Config(1); 
    this->random_seed = -1;
    this->initial_tiles->setConfig(config);
    this->initial_tiles->setRandomSeed(random_seed);
    const std::regex initial_tiles_pattern(this->config->getINITIAL_TILES_PATTERN());
    std::smatch initial_tiles_match;

    if (!std::regex_match(line, initial_tiles_match, initial_tiles_pattern)) {
      throw std::runtime_error("Invalid initial tiles specification");
    }

    std::stringstream initial_tiles_stream(line);
    char tile_char;
    while (initial_tiles_stream >> tile_char) {
      this->initial_tiles->addBack(new Tile(tile_char));
    }

    // then 2 player names (anything that's not a valid turn)
    unsigned int num_players = 0;
    const std::regex turn_pattern(config->getTURN_PATTERN());
    while (num_players != config->getNUM_OF_PLAYERS() && std::getline(file, line)) {
      if (!std::regex_match(line, turn_pattern)) {
        this->addPlayer(line);
        ++num_players;
      } else {
        throw std::runtime_error(
            "Received turn specification while reading player names");
      }
    }

    if (num_players != config->getNUM_OF_PLAYERS()) {
      throw std::runtime_error("Received fewer player names than expected");
    }

    // then any number of turns
    while (std::getline(file, line)) {
      Turn* turn = Turn::parseCommand(line, config);
      this->addTurn(turn);
    }
  }
}

void GameHistory::readSaveFileAdvanced(std::istream& file) {
  std::string line;
  
  std::getline(file, line);
  
  this->setRandomSeed(std::stoi(line));
  
  std::getline(file, line);
  int num_of_tile_colour = std::stoi(line);

  std::getline(file, line);
  bool is_grey_mode = std::stoi(line);
  if(is_grey_mode) {
    if (num_of_tile_colour == 5) {
      this->config = new Config(3);
    } else if (num_of_tile_colour ==6) {
      this->config = new Config(4);
    } else {
      throw new std::invalid_argument("Invalid file.");
    }
  } else {
    this->config = new Config(2);
  }

  this->initial_tiles->setConfig(config);
  this->initial_tiles->setRandomSeed(random_seed);
  // two player names
  int num_players = 0;
  const std::regex turn_pattern(config->getTURN_PATTERN());
  while (num_players != config->getNUM_OF_PLAYERS() && std::getline(file, line)) {
    if (!std::regex_match(line, turn_pattern)) {
      this->addPlayer(line);
      ++num_players;
    } else {
      throw std::runtime_error(
          "Received turn specification while reading player names");
    }
  }

  if (num_players != config->getNUM_OF_PLAYERS()) {
    throw std::runtime_error("Received fewer player names than expected");
  }
  //initial bag
  std::getline(file, line);
  std::stringstream initial_tiles_stream(line);
  char tile_char;
  while (initial_tiles_stream >> tile_char) {
    this->initial_tiles->addBack(new Tile(tile_char));
  }
  
  const std::regex move_pattern(config->getMANNUAL_MOVE_PATTERN());
  const std::regex bags_in_middle(config->getTILE_BAG_MIDDLE_PATTERN());

  TileBag* tileBag;
  while (std::getline(file, line)) {
    if (std::regex_match(line, move_pattern)) {
      int col = std::stoi(line.substr(1,1));
      mannual_moves.push_back(col);
    } else if (std::regex_match(line, bags_in_middle)) {
      tileBag = new TileBag();
      tileBag->setConfig(config);
      tileBag->setRandomSeed(random_seed);
      std::stringstream tile_bag_stream(line.substr(1,line.size()-1));
      char tile_char;
      while (tile_bag_stream >> tile_char) {
        this->initial_tiles->addBack(new Tile(tile_char));
      }
      this->tile_bags_in_game.push_back(tileBag);
    } else {
          Turn* turn = Turn::parseCommand(line, config);
      this->addTurn(turn);
    }
  }
}

void GameHistory::print() const {
  this->writeSaveFile(std::cout);
}

void GameHistory::print(std::ostream& out) const {
  this->writeSaveFile(out);
}

void GameHistory::setInitialTiles(TileBag* tiles) {
  this->initial_tiles = new TileBag(*tiles);
}

TileBag* GameHistory::getInitialTiles() const {
  return this->initial_tiles;
}

std::vector<Player*> GameHistory::getPlayers() const {
  std::vector<Player*> players = std::vector<Player*>();

  for (std::string name : this->player_names) {
    players.push_back(new Player(name, false, config));
  }

  players[0]->setFirstPlayer();

  return players;
}

std::vector<const Turn*> GameHistory::getTurns() const {
  return this->turns;
}

void GameHistory::setRandomSeed(int random_seed) {
  this->random_seed = random_seed;
}

void GameHistory::addTileBagInGame(TileBag* tile_bag) {
  tile_bags_in_game.push_back(tile_bag);
}

Config* GameHistory::getConfig() const {
  return config;
}

void GameHistory::setConfig(Config* config) {
  this->config = config;
}

int GameHistory::getRandomSeed() const {
  return random_seed;
}

bool GameHistory::readFromFile() const {
  return read_from_file;
}

void GameHistory::resetAfterLoading() {
  // delete turns
  for (const Turn* turn : this->turns) {
    delete turn;
  }
  turns.clear();

  //grey mode movement
  mannual_moves.clear();
}

void GameHistory::addMannaulMove(const unsigned int move) {
  this->mannual_moves.push_back(move);
}

std::vector<int> GameHistory::getMannualMoves() {
  return mannual_moves;
}
std::vector<TileBag*> GameHistory::getBagsInTheMiddle() {
  return tile_bags_in_game;
}
