#include "BoxLid.h"

BoxLid::BoxLid(/* args */)
{
}

BoxLid::~BoxLid()
{
}

std::vector<Tile*> BoxLid::getTiles() {
    return tiles;
}

unsigned int BoxLid::size() const {
    return tiles.size();
}

void BoxLid::addBack(Tile* tile) {
    tiles.push_back(tile);
}

void BoxLid::clear() {
    tiles.clear();
}


