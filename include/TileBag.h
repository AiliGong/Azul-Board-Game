#ifndef TILEBAG_H
#define TILEBAG_H

#include "LinkedList.h"
#include "BoxLid.h"
#include "Constants.h"

const Colour tilecolour[6] = {Colour::DARK_BLUE, Colour::YELLOW,
                                              Colour::RED, Colour::BLACK,
                                              Colour::LIGHT_BLUE, Colour::ORANGE};
class TileBag {
 public:
  TileBag(); //TODO <<=======
  TileBag(TileBag &other);
  TileBag(int randomSeed, Constants* constant);
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
  Constants* constant;

};

#endif  // TILEBAG_H
