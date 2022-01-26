#include "Mosaic.h"
#include <stdexcept>
#include <string>

Mosaic::Mosaic(unsigned int grid_dim, unsigned int broken_tile_slot) {
  this->grid_dim = grid_dim;
  this->broken_tile_slot = broken_tile_slot;
  this->initialMosaic();
}

Mosaic::~Mosaic() {
//delete grid
for (unsigned int i = 0; i < grid_dim; i++) {
  for (unsigned int j = 0; j < grid_dim; j++) {
    if (mosaicGrid[i][j] != nullptr) {
      delete mosaicGrid[i][j];
      mosaicGrid[i][j] = nullptr;
    }
  }
}

  //delete storage rows
  for (unsigned int i = 0; i < grid_dim; i++) {
    for (unsigned int j = 0; j < i + 1; j++) {
      if (storageRows[i][j] != nullptr) {
        delete storageRows[i][j];
        storageRows[i][j] = nullptr;
      }
    }
  }

  //delete broken tiles
  delete brokenTiles;
}

void Mosaic::initialMosaic() {
  // std::vector<std::vector<Tile*>> a(5, std::vector<Tile*>(5, nullptr));
  // mosaicGrid = a;
  for (unsigned int i = 0; i < grid_dim; i++) {
    for (unsigned int j = 0; j < grid_dim; j++) {
      mosaicGrid[i][j] = nullptr;
    }
  }

  for (unsigned int i = 0; i < grid_dim; i++) {
    storageRows[i] = new Tile*[i + 1];
    for (unsigned int j = 0; j < i + 1; j++) {
      storageRows[i][j] = nullptr;
    }
  }

  brokenTiles = new BrokenTile(broken_tile_slot);  
}


void Mosaic::addTileToStorage(Tile* tileToBeAdded, unsigned const int row) {
  unsigned int rowSize = checkStorageRowSize(row);

  // if line is full, transfer the ownership to brokenTile
  if (rowSize == row) {
    brokenTiles->addTile(tileToBeAdded);
  } else {
    storageRows[row - 1][rowSize] = tileToBeAdded;
  }
}

std::vector<Tile*> Mosaic::moveTileToGrid(unsigned const int row) {
  std::vector<Tile*> tilesToBeAddedToBag;

  if (!isStorageRowFull(row)) {
    throw std::logic_error("this row is not full");
  }

  Colour tileColour = storageRows[row - 1][row - 1]->getColour();
  unsigned int col = findCol(row, tileColour);

  // transfer the ownership of the rightmost tile
  mosaicGrid[row - 1][col - 1] = storageRows[row - 1][0];

  // return other tiles, need to be added into bag
  for (unsigned int i = 1; i != row; ++i) {
    tilesToBeAddedToBag.push_back(storageRows[row - 1][i]);
  }

  clearOneStorageRow(row);

  return tilesToBeAddedToBag;
} 

std::vector<Tile*> Mosaic::moveTileToGrid(unsigned const int row,   
                                          unsigned const int col) {
  std::vector<Tile*> tilesToBeAddedToBag;

  if (!isStorageRowFull(row)) {
    throw std::logic_error("this row is not full");
  }

  // transfer the ownership of the rightmost tile
  mosaicGrid[row - 1][col - 1] = storageRows[row - 1][0];

  // return other tiles, need to be added into bag
  for (unsigned int i = 1; i != row; ++i) {
    tilesToBeAddedToBag.push_back(storageRows[row - 1][i]);
  }

  clearOneStorageRow(row);

  return tilesToBeAddedToBag;
}


void Mosaic::clearOneStorageRow(unsigned const int row) {
  for (unsigned int i = 0; i != row; ++i) {
    storageRows[row - 1][i] = nullptr;
  }
}

bool Mosaic::isValidForColour(unsigned const int row, Colour colour) {
  bool returnVal = true;

  if (row != 0) {
    if (storageRowIsEmpty(row)) {
      // check grid
      for (unsigned int i = 0; i != grid_dim; ++i) {
        if (mosaicGrid[row - 1][i] != nullptr &&
            mosaicGrid[row - 1][i]->getColour() == colour) {
          returnVal = false;
        }
      }
    } else {
      // check storage row
      returnVal = (getStorageRowColour(row) == colour);
    }
  }

  return returnVal;
}

Colour Mosaic::getStorageRowColour(unsigned const int row) const {
  Colour colour = Colour::NONE;
  if (!storageRowIsEmpty(row)) {
      colour = storageRows[row-1][0]->getColour();
  }
  return colour;
}

std::string Mosaic::str() const {
  std::string returnVal = "";
  for (unsigned int i = 0; i != grid_dim; ++i) {
    returnVal += (std::to_string(i + 1) + ": ");

    for (unsigned int m = 0; m < grid_dim - i - 1; ++m) {
      returnVal += "  ";
    }

    for (int n = i; n >= 0; n--) {
      if (storageRows[i][n] == nullptr) {
        returnVal += ". ";
      } else {
        returnVal += storageRows[i][n]->getColourInitial() + " ";
      }
    }
    returnVal += "|| ";

    for (unsigned int r = 0; r != grid_dim; ++r) {
      if (mosaicGrid[i][r] == nullptr) {
        returnVal += ". ";
      } else {
        returnVal += mosaicGrid[i][r]->getColourInitial() + " ";
      }
    }
    returnVal += "\n";
  }

  returnVal += brokenTiles->str();

  return returnVal;
}

unsigned int Mosaic::calScore(unsigned const int row, Colour colour) const {
  unsigned int col = findCol(row, colour);
  return calScore(row, col);
}

unsigned int Mosaic::calScore(unsigned const int row,
                              unsigned const int col) const {
  int score = 0;

  int h_score = 0;
  // horizontal - left
  int l = col - 1;
  while (mosaicGrid[row - 1][l - 1] != nullptr && l > 0) {
    h_score++;
    l--;
  }

  // horizontal - right
  unsigned int r = col + 1;
  while (mosaicGrid[row - 1][r - 1] != nullptr && r <= grid_dim) {
    h_score++;
    r++;
  }

  int v_score = 0;
  // vertical - above
  int a = row - 1;
  while (mosaicGrid[a - 1][col - 1] != nullptr && a > 0) {
    v_score++;
    a--;
  }

  // vertical - down
  unsigned int d = row + 1;
  while (mosaicGrid[d - 1][col - 1] != nullptr && d <= grid_dim) {
    v_score++;
    d++;
  }

  if (h_score == 0 || v_score == 0) {
    score = h_score + v_score + 1;
  } else {
    score = h_score + v_score + 2;
  }

  return score;
}

BrokenTile* Mosaic::getBrokenTiles() const {
  return brokenTiles;
}

bool Mosaic::isStorageRowFull(unsigned const int row) {
  return checkStorageRowSize(row) == row;
}

// private
unsigned int Mosaic::checkStorageRowSize(unsigned const int row) const {
  unsigned int returnVal = 0;
  for (unsigned int i = 0; i != row; ++i) {
    if (storageRows[row - 1][i] != nullptr) {
      ++returnVal;
    }
  }
  return returnVal;
}

// private
bool Mosaic::storageRowIsEmpty(unsigned const int row) const {
  bool returnVal = true;
  for (unsigned int i = 0; i != row; ++i) {
    if (storageRows[row - 1][i] != nullptr) {
      returnVal = false;
    }
  }
  return returnVal;
}

// private
unsigned int Mosaic::findCol(unsigned const int row, Colour colour) const {
  unsigned int col = 0;

  if (this->grid_dim == 5) {
    col = findColFive(row, colour);
  } else if (this->grid_dim == 6) {
    col = findColSix(row, colour);
  }
  return col;
}

unsigned int Mosaic::findColFive(unsigned const int row, Colour colour) const {
  unsigned int col = 0;
  for (unsigned int i = 0; i != grid_dim; ++i) {
    if (defaultPattern[row - 1][i] == colour) {
      col = i + 1;
    }
  }
  return col;
}
unsigned int Mosaic::findColSix(unsigned const int row, Colour colour) const {
  unsigned int col = 0;
  for (unsigned int i = 0; i != grid_dim; ++i) {
    if (sixTilePattern[row - 1][i] == colour) {
      col = i + 1;
    }
  }
  return col;
}


bool Mosaic::gridSpotAvailable(unsigned const int row, unsigned const int col) {
  bool returnVal = true;

  if (row > grid_dim || col > grid_dim || row == 0 || col == 0) {
    returnVal = false;
  } else {
    if (mosaicGrid[row-1][col-1] != nullptr) {
      returnVal = false;
    }
  }
  return returnVal;
}