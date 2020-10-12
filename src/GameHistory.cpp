#include "GameHistory.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Mosaic.h"
#include "Turn.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

GameHistory::GameHistory() {
  // values initialised by readSaveFile()
}

GameHistory::GameHistory(TileBag* initial_tiles,
                         std::set<std::string> player_names)
    : initial_tiles(initial_tiles), player_names(player_names) {}

GameHistory::GameHistory(GameHistory& other) {
  this->initial_tiles = new TileBag(*other.initial_tiles);
  this->player_names = other.player_names;
  this->turns = other.turns;
}

GameHistory* GameHistory::loadFromFile(std::string filename) {
  // TODO: handle file errors
  std::ifstream savefile(filename);
  if (!savefile) {
    throw std::runtime_error("Unable to load file: " + filename);
  }

  GameHistory* gh = new GameHistory();

  //TODO add random seed
  gh->initial_tiles = new TileBag(0);
  gh->readSaveFile(savefile);
  savefile.close();
  return gh;
}

GameHistory::~GameHistory() {
  delete this->initial_tiles;

  for (const Turn* turn : this->turns) {
    delete turn;
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
  out << this->initial_tiles->getAllTileIni() << std::endl;

  for (std::string player_name : this->player_names) {
    out << player_name << std::endl;
  }

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
  const std::regex initial_tiles_pattern(INITIAL_TILES_PATTERN);
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
  int num_players = 0;
  const std::regex turn_pattern(TURN_PATTERN);
  while (num_players != NUM_OF_PLAYERS && std::getline(file, line)) {
    if (!std::regex_match(line, turn_pattern)) {
      this->addPlayer(line);
      ++num_players;
    } else {
      throw std::runtime_error(
          "Received turn specification while reading player names");
    }
  }

  if (num_players != NUM_OF_PLAYERS) {
    throw std::runtime_error("Received fewer player names than expected");
  }

  // then any number of turns
  while (std::getline(file, line)) {
    Turn* turn = Turn::parseCommand(line);
    this->addTurn(turn);
  }
}

void GameHistory::print() const {
  this->writeSaveFile(std::cout);
}

void GameHistory::print(std::ostream& out) const {
  this->writeSaveFile(out);
}

void GameHistory::setInitialTiles(const TileBag* tiles) {
  this->initial_tiles = new TileBag(*tiles);
}

TileBag* GameHistory::getInitialTiles() const {
  return this->initial_tiles;
}

std::vector<Player*> GameHistory::getPlayers() const {
  std::vector<Player*> players = std::vector<Player*>();

  for (std::string name : this->player_names) {
    players.push_back(new Player(name, false));
  }

  players[0]->setFirstPlayer();

  return players;
}

std::vector<const Turn*> GameHistory::getTurns() const {
  return this->turns;
}
