#ifndef TILE_H
#define TILE_H

#include <string>

enum Colour {
  RED,
  YELLOW,
  DARK_BLUE,
  LIGHT_BLUE,
  BLACK,
  FIRST_PLAYER,
  NONE,
};

const char RED_INI  = 'R';
const char YELLOW_INI  = 'Y';
const char DARK_BLUE_INI  = 'B';
const char LIGHT_BLUE_INI  = 'L';
const char BLACK_INI  = 'U';
const char FIRST_PLAYER_INI  = 'F';
const char NONE_INI  =  '.';

class Tile {
public:
  Tile(Colour colour);
  Tile(char tileIndicator);
  Tile(const Tile& other);
  ~Tile();
  Colour getColour() const;
  std::string getColourInitial() const;

private: 
  Colour colour;

};

#endif  // TILE_H
