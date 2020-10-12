#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
#include "BoxLid.h"
#include "Constants.h"

const Colour tilecolour[NUM_OF_TILECOLOUR] = {Colour::DARK_BLUE, Colour::YELLOW,
                                              Colour::RED, Colour::BLACK,
                                              Colour::LIGHT_BLUE};
class TileBag {
 public:
  TileBag(int randomSeed);
  ~TileBag();


  void addBack(Tile* tile);
  Tile* pop();
  unsigned int size() const;
  std::string getAllTileIni() const;
  void fillBag(BoxLid* box_lid);


 private:
  void initialTiledBag();
  void initialStandardBag();
  void initialRandomizedBag();
  LinkedList<Tile*>* tile_bag;
  int randomSeed;
  Tile* getHeadTile();
  void removeFront();
  void clear();
  void fillBag(std::vector<Tile*> tiles_to_add);


};

#endif  // TILEBAG_H
