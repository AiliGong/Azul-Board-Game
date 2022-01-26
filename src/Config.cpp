#include "Config.h"

Config::Config(unsigned int mode) {
    this->initialConfig(mode);
}

Config::Config(Config& other) {
    NUM_OF_TILECOLOUR = other.NUM_OF_TILECOLOUR;
    MOSAIC_GRID_DIM = other.MOSAIC_GRID_DIM;
    NUM_OF_TILE_EACH_COLOUR = other.NUM_OF_TILE_EACH_COLOUR;
    TOTAL_NUM_OF_TILE =other.TOTAL_NUM_OF_TILE;
    NUM_OF_FACTORIES = other.NUM_OF_FACTORIES;
    NUM_OF_ALL_FACTORIES = other.NUM_OF_ALL_FACTORIES;
    NUM_OF_TILES_EACH_FAC = other.NUM_OF_TILES_EACH_FAC;
    TOTAL_NUM_OF_GAME_ROUND = other.TOTAL_NUM_OF_GAME_ROUND;
    NUM_OF_PLAYERS = other.NUM_OF_PLAYERS;
    BROKEN_TILE_SOLT = other.BROKEN_TILE_SOLT;
    grey_mode = other.grey_mode;
    standard_mode = other.standard_mode;
    TILE_PATTERN = other.TILE_PATTERN;
    FACTORY_INDEX_PATTERN = other.FACTORY_INDEX_PATTERN;
    STORAGE_ROW_INDEX_PATTERN = other.STORAGE_ROW_INDEX_PATTERN;
    TURN_PATTERN = other.TURN_PATTERN;
    INITIAL_TILES_PATTERN = other.INITIAL_TILES_PATTERN;
    TILE_BAG_MIDDLE_PATTERN = other.TILE_BAG_MIDDLE_PATTERN;
    MANNUAL_MOVE_PATTERN =  other.MANNUAL_MOVE_PATTERN;
}

Config::~Config() {
    
}

void Config::initialConfig(unsigned int mode) {
    if (mode == 1) {
        this->standardMode();
    } else if ( mode == 2) {
        this->sixTileMode();
    } else if (mode == 3) {
        this->fiveTileGreyMode();
    } else if (mode == 4) {
        this->sixTileGreyMode();
    } 
}

void Config::standardMode() {
    NUM_OF_TILECOLOUR = 5;
    MOSAIC_GRID_DIM = NUM_OF_TILECOLOUR;

    NUM_OF_TILE_EACH_COLOUR = 20;
    TOTAL_NUM_OF_TILE = NUM_OF_TILECOLOUR * NUM_OF_TILE_EACH_COLOUR;
    NUM_OF_FACTORIES = 5;
    NUM_OF_ALL_FACTORIES = 6;
    NUM_OF_TILES_EACH_FAC = 4;
    TOTAL_NUM_OF_GAME_ROUND = 5;
    NUM_OF_PLAYERS = 2;
    BROKEN_TILE_SOLT = 7;
    grey_mode = false;
    standard_mode = true;

    TILE_PATTERN = "[RYBLU]";
    FACTORY_INDEX_PATTERN = "[0-" + std::to_string(NUM_OF_FACTORIES) + "]";
    STORAGE_ROW_INDEX_PATTERN = "[0-" + std::to_string(MOSAIC_GRID_DIM) + "]";
    TURN_PATTERN = "^turn " + FACTORY_INDEX_PATTERN + " " + TILE_PATTERN + " " +
                    STORAGE_ROW_INDEX_PATTERN + "$";
    INITIAL_TILES_PATTERN =
        "^(" + TILE_PATTERN + "){" + std::to_string(TOTAL_NUM_OF_TILE) + "}$";
    TILE_BAG_MIDDLE_PATTERN = "^@" + TILE_PATTERN + "+$";
    MANNUAL_MOVE_PATTERN =  "^%[1-" + std::to_string(MOSAIC_GRID_DIM) + "]$";
}

void Config::sixTileMode() {
    NUM_OF_TILECOLOUR = 6;
    MOSAIC_GRID_DIM = NUM_OF_TILECOLOUR;

    NUM_OF_TILE_EACH_COLOUR = 20;
    TOTAL_NUM_OF_TILE = NUM_OF_TILECOLOUR * NUM_OF_TILE_EACH_COLOUR;
    NUM_OF_FACTORIES = 5;
    NUM_OF_ALL_FACTORIES = 6;
    NUM_OF_TILES_EACH_FAC = 4;
    TOTAL_NUM_OF_GAME_ROUND = 5;
    NUM_OF_PLAYERS = 2;
    BROKEN_TILE_SOLT = 8;
    grey_mode = false;
    standard_mode = false;

    TILE_PATTERN = "[RYBLUO]";
    FACTORY_INDEX_PATTERN = "[0-" + std::to_string(NUM_OF_FACTORIES) + "]";
    STORAGE_ROW_INDEX_PATTERN = "[0-" + std::to_string(MOSAIC_GRID_DIM) + "]";
    TURN_PATTERN = "^turn " + FACTORY_INDEX_PATTERN + " " + TILE_PATTERN + " " +
                    STORAGE_ROW_INDEX_PATTERN + "$";
    INITIAL_TILES_PATTERN =
        "^(" + TILE_PATTERN + "){" + std::to_string(TOTAL_NUM_OF_TILE) + "}$";
    TILE_BAG_MIDDLE_PATTERN = "^@" + TILE_PATTERN + "+$";
    MANNUAL_MOVE_PATTERN =  "^%[1-" + std::to_string(MOSAIC_GRID_DIM) + "]$";

}

void Config::fiveTileGreyMode() {
    this->standardMode();
    this->grey_mode = true;
    standard_mode = false;

}

void Config::sixTileGreyMode() {
    this->sixTileMode();
    this->grey_mode = true;
}

unsigned int Config::getNUM_OF_TILECOLOUR() {
    return NUM_OF_TILECOLOUR;
}

unsigned int Config::getMOSAIC_GRID_DIM() {
    return MOSAIC_GRID_DIM;
}


unsigned int Config::getNUM_OF_TILE_EACH_COLOUR() {
    return NUM_OF_TILE_EACH_COLOUR;
}

unsigned int Config::getTOTAL_NUM_OF_TILE() {
    return TOTAL_NUM_OF_TILE;
}

unsigned int Config::getNUM_OF_FACTORIES() {
    return NUM_OF_FACTORIES;
}

unsigned int Config::getNUM_OF_ALL_FACTORIES() {
    return NUM_OF_ALL_FACTORIES;
}

unsigned int Config::getNUM_OF_TILES_EACH_FAC() {
    return NUM_OF_TILES_EACH_FAC;
}

unsigned int Config::getTOTAL_NUM_OF_GAME_ROUND() {
    return TOTAL_NUM_OF_GAME_ROUND;
}

unsigned int Config::getNUM_OF_PLAYERS() {
    return NUM_OF_PLAYERS;
}

unsigned int Config::getBROKEN_TILE_SOLT() {
    return BROKEN_TILE_SOLT;
}

bool Config::isGreyMode() {
    return grey_mode;
}

bool Config::isStandardMode() {
    return standard_mode;
}

std::string Config::getTILE_PATTERN() {
    return TILE_PATTERN;
}

std::string Config::getFACTORY_INDEX_PATTERN() {
    return FACTORY_INDEX_PATTERN;
}

std::string Config::getSTORAGE_ROW_INDEX_PATTERN() {
    return STORAGE_ROW_INDEX_PATTERN;
}

std::string Config::getTURN_PATTERN() {
    return TURN_PATTERN;
}

std::string Config::getINITIAL_TILES_PATTERN() {
    return INITIAL_TILES_PATTERN;
}

std::string Config::getMANNUAL_MOVE_PATTERN() {
    return MANNUAL_MOVE_PATTERN;
}

std::string Config::getTILE_BAG_MIDDLE_PATTERN() {
    return TILE_BAG_MIDDLE_PATTERN;
}