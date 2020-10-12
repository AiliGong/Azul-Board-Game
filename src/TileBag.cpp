#include "TileBag.h"
#include "Constants.h"
#include <random>
#include <iostream>

TileBag::TileBag() {
  tile_bag = new LinkedList<Tile*>;
}

TileBag::TileBag(int randomSeed) {
  this->randomSeed = randomSeed;  
  this->initialTiledBag();
}

TileBag::~TileBag() {
  delete tile_bag;
}

void TileBag::initialTiledBag() {
  tile_bag = new LinkedList<Tile*>;
  if (randomSeed < 0) {
    this->initialStandardBag();
  } else {
    this->initialRandomizedBag();
  }
}

void TileBag::initialStandardBag() {
  Tile* tile;
  for (int i = 0; i < TOTAL_NUM_OF_TILE; ++i) {
    tile = new Tile(tilecolour[i % NUM_OF_TILECOLOUR]);
    this->addBack(tile);
  }
}

void TileBag::initialRandomizedBag() {
  std::vector<Tile*> allTiles;
  Tile* tile;
  for (int i = 0; i != TOTAL_NUM_OF_TILE; ++i) {
      tile = new Tile(tilecolour[i % NUM_OF_TILECOLOUR]);
      allTiles.push_back(tile);
  }
  fillBag(allTiles);
}

void TileBag::addBack(Tile* tile) {
  tile_bag->add_back(tile);
}

void TileBag::removeFront() {
  tile_bag->remove_front();
}

void TileBag::clear() {
  tile_bag->clear();
}

unsigned int TileBag::size() const {
  return tile_bag->getSize();
}

std::string TileBag::getAllTileIni() const {
      std::string returnVal = "";

      if (tile_bag->getHead() != nullptr) {
        Node<Tile*>* temp = tile_bag->getHead();
        returnVal += temp->getValue()->getColourInitial();
        while (temp->getNext() != nullptr) {
          temp = temp->getNext();
          returnVal += temp->getValue()->getColourInitial();
        }
        temp = nullptr;
      }

    return returnVal;
}

Tile* TileBag::getHeadTile() {
  return tile_bag->getHead()->getValue();
}

Tile* TileBag::pop() {
  Tile* returnTile = tile_bag->getHead()->getValue();
  this->removeFront();
  return returnTile;
}

void TileBag::fillBag(BoxLid* box_lid) {
  if (size() > 0) {
    throw new std::logic_error("Tile bag is not empty.");
  }
  fillBag(box_lid->getTiles());
  box_lid->clear();
}

void TileBag::fillBag(std::vector<Tile*> tiles_to_add) {
  if (randomSeed >= 0 ) {
    std::shuffle(tiles_to_add.begin(), tiles_to_add.end(), 
                std::default_random_engine(randomSeed));
  }
  
  for (Tile* tile : tiles_to_add) {
    tile_bag->add_back(tile);
  }
}

