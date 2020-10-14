#include "Turn.h"
#include <regex>
#include <sstream>

Turn::Turn(unsigned int factory, Tile* tile, unsigned int storage_row)
    : factory(factory), tile(tile), storage_row(storage_row) {}

Turn* Turn::parseCommand(std::string command, Constants* constant) {
  const std::regex turn_pattern(constant->getTURN_PATTERN());

  std::string turn_command;
  unsigned int factory;
  char turn_tile_char;
  unsigned int row;
  std::istringstream linestream(command);

  if (std::regex_match(command, turn_pattern)) {
    // this line is a valid turn specification
    linestream >> turn_command >> factory >> turn_tile_char >> row;
    return new Turn(factory, new Tile(turn_tile_char), row);
  } else {
    throw std::runtime_error("Received invalid turn specification: " + command);
  }
}

Turn::Turn(Turn& other) {
  this->factory = other.factory;
  this->tile = new Tile(*other.tile);
  this->storage_row = other.storage_row;
}

Turn::~Turn() {
  delete this->tile;
}

unsigned int Turn::getFactory() const {
  return this->factory;
}

Tile* Turn::getTile() const {
  return this->tile;
}

unsigned int Turn::getPatternLine() const {
  return this->storage_row;
}

std::string Turn::str() const {
  std::ostringstream oss;
  oss << "turn " << this->factory << " " << this->tile->getColourInitial()
      << " " << this->storage_row;
  return oss.str();
}