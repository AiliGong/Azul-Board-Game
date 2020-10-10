#include "TileBag.h"
#include "Constants.h"

TileBag::TileBag()
{
  tile_bag = new LinkedList<Tile*>;

  Colour tilecolour[NUM_OF_TILECOLOUR] = {Colour::DARK_BLUE, Colour::YELLOW,
                                          Colour::RED, Colour::BLACK,
                                          Colour::LIGHT_BLUE};
  Tile* tile;
  for (int i = 0; i < TOTAL_NUM_OF_TILE; ++i) {
    tile = new Tile(tilecolour[i % NUM_OF_TILECOLOUR]);
    this->addBack(tile);
  }
}

TileBag::~TileBag(){
  delete tile_bag;
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
