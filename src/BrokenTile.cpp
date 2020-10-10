#include "BrokenTile.h"


BrokenTile::BrokenTile() {
}

BrokenTile::~BrokenTile() {
    for (Tile* tile : broken_tiles) {
        delete tile;
        tile = nullptr; 
    }
}

void BrokenTile::addTile(Tile* tile) {
    broken_tiles.push_back(tile);
}

unsigned int BrokenTile::calculateLostPoints() const {
    unsigned int points = 0;
    unsigned int size = broken_tiles.size();
    int pointsArray[] = {1, 2, 4, 6, 8, 11, 14};

    if (size <= 7 && size > 0) {
        points = pointsArray[size-1];
    } else if (size > 7) {
        points = pointsArray[6];
    }
    
    return points;
}

void BrokenTile::clear() {
    for (Tile* tile : broken_tiles) {
        tile = nullptr; //set the pointer to null, 
                        //tiles need to be added backed to the bag
    }

    broken_tiles.clear();
}

unsigned int BrokenTile::getSize() const {
    return broken_tiles.size();
}

std::vector<Tile*> BrokenTile::getAllTiles() {
    return broken_tiles;
}

std::string BrokenTile::str() {
    
    std::string output = "broken:";

    if (!broken_tiles.empty()) {
        for (Tile* tile : broken_tiles) {
            output += " " + tile->getColourInitial();
        }
    }
    output += "\n";
    return output;
}
