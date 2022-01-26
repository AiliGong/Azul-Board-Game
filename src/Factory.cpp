#include "Factory.h"

Factory::Factory(int factory_num) {
  this->factory_num = factory_num;
}

Factory::~Factory() {
  for (Tile* tile : tiles) {
        delete tile;
    }
    tiles.clear();
}

void Factory::addTile(Tile* tile) {
  tiles.push_back(tile);
}

std::vector<Tile*> Factory::getAllTiles() const {
  return tiles;
}

std::vector<Tile*> Factory::popTiles(Colour colour) {
  // copy all tiles in colour
  std::vector<Tile*> tiles_to_return;
  for (unsigned int i = 0; i != tiles.size(); ++i) {
    if (tiles[i]->getColour() == colour) {
      tiles_to_return.push_back(tiles[i]);
      tiles[i] = nullptr;
    }
  }

  // copy all none null tiles
  std::vector<Tile*> temp;
  for (unsigned int i = 0; i != tiles.size(); ++i) {
    if (tiles[i] != nullptr) {
      temp.push_back(tiles[i]);
    }
  }
  tiles.clear();
  tiles = temp;

  return tiles_to_return;
}

void Factory::removeAllTiles() {
  tiles.clear();
}

std::string Factory::str() const {
  std::string output = std::to_string(factory_num) + ":";

  for (Tile* tile : tiles) {
    output += " " + tile->getColourInitial();
  }
  return output;
}

bool Factory::isEmpty() const {
  return tiles.size() == 0;
}

bool Factory::colourExists(Colour colour) const {
  int count = 0;
  bool returnVal = false;

  for (Tile* tile : tiles) {
    if (tile->getColour() == colour) {
      count++;
    }
  }

  if (count > 0) {
    returnVal = true;
  }

  return returnVal;
}