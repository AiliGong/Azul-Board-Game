#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <vector>

#include "Tile.h"

class Factory {


 public:
  Factory(int factory_num);
  ~Factory();

  void addTile(Tile* tile);
  std::vector<Tile*> getAllTiles() const;

  // get all tiles in that colour (tiles to be moved to player palette)
  std::vector<Tile*> popTiles(Colour colour);

  // clear the factory
  void removeAllTiles();

  std::string str() const;

  bool isEmpty() const;
  bool colourExists(Colour colour) const;

 private:
  std::vector<Tile*> tiles;
  int factory_num;
};

#endif  // FACTORY_H