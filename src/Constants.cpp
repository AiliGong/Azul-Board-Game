#include "Constants.h"

Constants::Constants(unsigned int mode) {
    this->initialConstants(mode);
}

Constants::~Constants() {

}

void Constants::initialConstants(unsigned int mode) {
    if (mode == 1) {
        this->standardMode();
    } else if ( mode == 2) {
        this->sixTileMode();
    } else if (mode == 3) {
        this->greyMode();
    } else {
        throw new std::logic_error("Invalid mode.");
    }
}

void Constants::standardMode() {
    NUM_OF_TILECOLOUR = 5;
    MOSAIC_GRID_DIM = NUM_OF_TILECOLOUR;

    NUM_OF_TILE_EACH_COLOUR = 20;
    TOTAL_NUM_OF_TILE = NUM_OF_TILECOLOUR * NUM_OF_TILE_EACH_COLOUR;
    NUM_OF_FACTORIES = 5;
    NUM_OF_ALL_FACTORIES = 6;
    NUM_OF_TILES_EACH_FAC = 4;
    TOTAL_NUM_OF_GAME_ROUND = 5;
    NUM_OF_PLAYERS = 2;

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
}

void Constants::sixTileMode() {

}

void Constants::greyMode() {

}

unsigned int Constants::getNUM_OF_TILECOLOUR() {
    return NUM_OF_TILECOLOUR;
}

unsigned int Constants::getMOSAIC_GRID_DIM() {
    return MOSAIC_GRID_DIM;
}


unsigned int Constants::getNUM_OF_TILE_EACH_COLOUR() {
    return NUM_OF_TILE_EACH_COLOUR;
}

unsigned int Constants::getTOTAL_NUM_OF_TILE() {
    return TOTAL_NUM_OF_TILE;
}

unsigned int Constants::getNUM_OF_FACTORIES() {
    return NUM_OF_FACTORIES;
}

unsigned int Constants::getNUM_OF_ALL_FACTORIES() {
    return NUM_OF_ALL_FACTORIES;
}

unsigned int Constants::getNUM_OF_TILES_EACH_FAC() {
    return NUM_OF_TILES_EACH_FAC;
}

unsigned int Constants::getTOTAL_NUM_OF_GAME_ROUND() {
    return TOTAL_NUM_OF_GAME_ROUND;
}

unsigned int Constants::getNUM_OF_PLAYERS() {
    return NUM_OF_PLAYERS;
}


// Any single tile indicator
std::string Constants::getTILE_PATTERN() {
    return TILE_PATTERN;
}


std::string Constants::getFACTORY_INDEX_PATTERN() {
    return FACTORY_INDEX_PATTERN;
}


std::string Constants::getSTORAGE_ROW_INDEX_PATTERN() {
    return STORAGE_ROW_INDEX_PATTERN;
}


// Literal "turn" followed by valid factory index (0 represents the broken
// tile row), tile indicator, and storage row index, all separated by spaces
std::string Constants::getTURN_PATTERN() {
    return TURN_PATTERN;
}


// Exactly TOTAL_NUM_OF_TILE tile indicators, without separators
std::string Constants::getINITIAL_TILES_PATTERN() {
    return INITIAL_TILES_PATTERN;
}
