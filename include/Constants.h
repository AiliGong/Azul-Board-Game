#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const unsigned int MOSAIC_GRID_DIM = 5;

const unsigned int NUM_OF_TILECOLOUR = 5;
const unsigned int NUM_OF_TILE_EACH_COLOUR = 20;
const unsigned int TOTAL_NUM_OF_TILE =
    NUM_OF_TILECOLOUR * NUM_OF_TILE_EACH_COLOUR;
const unsigned int NUM_OF_FACTORIES = 5;
const unsigned int NUM_OF_ALL_FACTORIES = 6;
const unsigned int NUM_OF_TILES_EACH_FAC = 4;
// const unsigned int TOTAL_NUM_OF_GAME_ROUND =  5; // FIXME
const unsigned int TOTAL_NUM_OF_GAME_ROUND = 5;
const unsigned int NUM_OF_PLAYERS = 2;

// Any single tile indicator
const std::string TILE_PATTERN = "[RYBLU]";

const std::string FACTORY_INDEX_PATTERN =
    "[0-" + std::to_string(NUM_OF_FACTORIES) + "]";

const std::string STORAGE_ROW_INDEX_PATTERN =
    "[0-" + std::to_string(MOSAIC_GRID_DIM) + "]";

// Literal "turn" followed by valid factory index (0 represents the broken
// tile row), tile indicator, and storage row index, all separated by spaces
const std::string TURN_PATTERN = "^turn " + FACTORY_INDEX_PATTERN + " " +
                                 TILE_PATTERN + " " +
                                 STORAGE_ROW_INDEX_PATTERN + "$";

// Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
const std::string INITIAL_TILES_PATTERN =
    "^(" + TILE_PATTERN + "){" + std::to_string(TOTAL_NUM_OF_TILE) + "}$";

#endif  // CONSTANTS_H