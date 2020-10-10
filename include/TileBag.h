#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"

class TileBag {
 public:
  TileBag();
  ~TileBag();

  void addBack(Tile* tile);
  Tile* pop();
  unsigned int size() const;
  std::string getAllTileIni() const;

 private:
  LinkedList<Tile*>* tile_bag;
  Tile* getHeadTile();
  void removeFront();
  void clear();
};

#endif  // TILEBAG_H
