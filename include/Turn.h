#ifndef TURN_H
#define TURN_H

#include <string>

#include "Config.h"
#include "Tile.h"

class Turn {
 public:
  Turn(unsigned int factory, Tile* tile, unsigned int storage_row);
  Turn(const Turn& other);
  ~Turn();

  static Turn* parseCommand(std::string command, Config* config);

  unsigned int getFactory() const;
  Tile* getTile() const;
  unsigned int getPatternLine() const;

  std::string str() const;

 private:
  int factory;
  Tile* tile;
  int storage_row;
};

#endif  // TURN_H