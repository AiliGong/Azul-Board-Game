#ifndef MOSAIC_H
#define MOSAIC_H

#include <string>

#include "BrokenTile.h"
#include "Tile.h"

const int defaultPattern[5][5] = {{0, 1, 2, 3, 4},
                                  {4, 0, 1, 2, 3},
                                  {3, 4, 0, 1, 2},
                                  {2, 3, 4, 0, 1},
                                  {1, 2, 3, 4, 0}};
const int sixTilePattern[6][6] = {{0, 1, 2, 3, 4, 5},
                                  {5, 0, 1, 2, 3, 4},
                                  {4, 5, 0, 1, 2, 3},
                                  {3, 4, 5, 0, 1, 2},
                                  {2, 3, 4, 5, 0, 1},
                                  {1, 2, 3, 4, 5, 0}};

class Mosaic {
 public:
  Mosaic(unsigned int grid_dim, unsigned int broken_tile_slot);
  ~Mosaic();

  // add a tile to the strorage row, tile will be added to brokenTiles if line
  // is full
  void addTileToStorage(Tile* tileToBeAdded, unsigned const int row);

  // move one tile to the grid and return all other tiles
  std::vector<Tile*> moveTileToGrid(unsigned const int row);
  std::vector<Tile*> moveTileToGrid(unsigned const int row,   
                                          unsigned const int col);
                                          

  // clear the stroage row, set to nullptr
  void clearOneStorageRow(unsigned const int row);

  // check if it is valid to place a certain colour to the storage row
  // return false if this colour is already tiled in the gird
  // or other colour already is placed in the storage row
  bool isValidForColour(unsigned const int row, Colour colour);

  // return the colour of tiles, return Colour::NONE is row is empty
  Colour getStorageRowColour(unsigned const int row) const;
  std::string str() const;

  // calcluate the point for placing the tile into mosaicGrid[row][col]
  unsigned int calScore(unsigned const int row, Colour colour) const;

  BrokenTile* getBrokenTiles() const;

  bool isStorageRowFull(unsigned const int row);
  bool gridSpotAvailable(unsigned const int row, unsigned const int col);
  unsigned int calScore(unsigned const int row, unsigned const int col) const;

 private:
  // std::vector<std::vector<Tile*>> storageRows;
  // std::vector<std::vector<Tile*>> mosaicGrid;
  Tile** storageRows[6];
  Tile* mosaicGrid[6][6];
  BrokenTile* brokenTiles;
  unsigned int grid_dim;
  unsigned int broken_tile_slot;

  void initialMosaic();
  unsigned int checkStorageRowSize(unsigned const int row) const;
  bool storageRowIsEmpty(unsigned const int row) const;
  unsigned int findCol(unsigned const int row, Colour colour) const;
  unsigned int findColFive(unsigned const int row, Colour colour) const;
  unsigned int findColSix(unsigned const int row, Colour colour) const;

};

#endif  // MOSAIC_H
