#include "Tile.h"
#include <stdexcept>

#include <iostream>

Tile::Tile(Colour colour) {
  this->colour = colour;
}

Tile::Tile(const Tile& other) {
  this->colour = other.colour;
}
Tile::~Tile() {}

Colour Tile::getColour() const {
  return colour;
}

std::string Tile::getColourInitial() const {
  std::string tileInitial = "";

  if (colour == Colour::RED) {
    tileInitial = RED_INI;
  } else if (colour == Colour::YELLOW) {
    tileInitial = YELLOW_INI;
  } else if (colour == Colour::DARK_BLUE) {
    tileInitial = DARK_BLUE_INI;
  } else if (colour == Colour::LIGHT_BLUE) {
    tileInitial = LIGHT_BLUE_INI;
  } else if (colour == Colour::BLACK) {
    tileInitial = BLACK_INI;
  } else if (colour == Colour::ORANGE) {
    tileInitial = ORANGE_INI;
  } else if (colour == Colour::FIRST_PLAYER) {
    tileInitial = FIRST_PLAYER_INI;
  } else {
    // Should be unreachable
    throw std::runtime_error("Invalid tile indicator character");
  }
  return tileInitial;
}

Tile::Tile(char tileIndicator) {
  if (tileIndicator == RED_INI)
    this->colour = Colour::RED;
  else if (tileIndicator == YELLOW_INI)
    this->colour = Colour::YELLOW;
  else if (tileIndicator == DARK_BLUE_INI)
    this->colour = Colour::DARK_BLUE;
  else if (tileIndicator == LIGHT_BLUE_INI)
    this->colour = Colour::LIGHT_BLUE;
  else if (tileIndicator == BLACK_INI)
    this->colour = Colour::BLACK;
  else if (tileIndicator == ORANGE_INI)
    this->colour = Colour::ORANGE;  
  else if (tileIndicator == FIRST_PLAYER_INI)
    this->colour = Colour::FIRST_PLAYER;
  else if (tileIndicator == NONE_INI)
    this->colour = Colour::NONE;
  else {
    throw std::runtime_error("Invalid tile indicator character");
  }
}