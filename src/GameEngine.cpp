#include "GameEngine.h"
#include "Tile.h"

#include <random>

GameEngine::GameEngine()
    : game_history(new GameHistory()),
      game_state(GameState::START),
      tile_bag(new TileBag()) {
  this->game_history->setInitialTiles(this->tile_bag);
}

GameEngine::GameEngine(GameHistory* gameHistory)
    : game_history(gameHistory), game_state(GameState::START) {
  this->loadGameSetUp(gameHistory);
}

GameEngine::~GameEngine() {
  for (int i = 0; i != players.size(); ++i) {
    delete players[i];
  }
  players.clear();

  // delete factory
  for (Factory* factory : factories) {
    delete factory;
  }
  factories.clear();

  // delete bag
  delete tile_bag;

  // delete game history
  delete game_history;
}

void GameEngine::loadGameSetUp(const GameHistory* gameHistory) {
  this->tile_bag = gameHistory->getInitialTiles();

  for (Player* player : gameHistory->getPlayers()) {
    bool first_player = this->players.size() == 0;
    this->players.push_back(player);

    if (first_player) {
      this->next_player = player;
    }
  }
}

void GameEngine::addPlayer(std::string name) {
  if (this->game_state != GameState::START) {
    throw std::runtime_error(
        "Players may only be added when game state is START");
  }

  for (Player* player : players) {
    if (player->getName() == name) {
      throw new std::invalid_argument("Player is alrady exists.");
    }
  }

  bool first_player = this->players.size() == 0;
  Player* player = new Player(name, first_player);
  this->players.push_back(player);
  this->game_history->addPlayer(name);

  if (first_player) {
    this->next_player = player;
  }
}

GameState GameEngine::getState() const {
  return this->game_state;
}

void GameEngine::startGame() {
  if (this->game_state != GameState::START) {
    throw std::runtime_error(
        "Game may only be started when game state is START");
  }

  if (this->tile_bag->size() == 0) {
    game_history->setInitialTiles(tile_bag);
  }

  this->initFactories();
  this->startRound();

  if (this->game_history->getTurns().size() > 0) {
    this->replayTurns();
  }
}

void GameEngine::initFactories() {
  // central factory
  Factory* fac = new Factory(0);
  fac->addTile(new Tile(Colour::FIRST_PLAYER));
  factories.push_back(fac);
  fac = nullptr;

  // add five factories
  for (int i = 1; i < NUM_OF_ALL_FACTORIES; ++i) {
    fac = new Factory(i);
    factories.push_back(fac);
    fac = nullptr;
  }

  this->fillFactories();
}

void GameEngine::replayTurns() {
  std::vector<const Turn*> turns = this->game_history->getTurns();
  int i = 0;

  while (i < turns.size() && this->game_state != GameState::END_OF_GAME) {
    while (i < turns.size() && this->game_state != GameState::END_OF_ROUND) {
      this->playTurn(turns[i]);
      ++i;
    }
    if (this->game_state == GameState::END_OF_ROUND) {
      this->startRound();
    }
  }
}

void GameEngine::startRound() {
  if (this->game_state != GameState::START &&
      this->game_state != GameState::END_OF_ROUND) {
    throw std::runtime_error(
        "Round may only be started when game state is START or END_OF_ROUND");
  }

  if (this->game_state == GameState::END_OF_ROUND) {
    this->fillFactories();
  }

  this->firstPlayerSetup();

  this->game_state = GameState::START_OF_ROUND;
}

void GameEngine::fillFactories() {
  // skips central factory
  for (int i = 1; i != NUM_OF_ALL_FACTORIES; ++i) {
    for (int j = 0; j != NUM_OF_TILES_EACH_FAC; ++j) {
      this->factories[i]->addTile(tile_bag->pop());  // add the head to factory
    }
  }
}

bool GameEngine::playTurn(const Turn* turn) {
  if (this->game_state == GameState::START_OF_ROUND) {
    this->game_state = GameState::MID_ROUND;
  }

  if (this->game_state != GameState::MID_ROUND) {
    throw std::runtime_error(
        "Turn may only be played when game state is MID_ROUND");
  }

  return this->playerMovement(this->next_player, turn);
}

bool GameEngine::playerMovement(Player* player, const Turn* turn) {
  unsigned int facNum = turn->getFactory();
  Colour colour = turn->getTile()->getColour();
  unsigned int row = turn->getPatternLine();

  bool factory_is_legal = factories[facNum]->colourExists(colour) &&
                          row <= MOSAIC_GRID_DIM && facNum <= NUM_OF_FACTORIES;
  bool row_is_legal = player->getMosaic()->isValidForColour(row, colour);

  if (factory_is_legal && row_is_legal) {
    placeTilesToStorageRow(player, turn);
    game_history->addTurn(turn);  // update histpry
    updateNextPlayer();
    game_state = GameState::MID_ROUND;
  }

  if (checkEndOfRound()) {
    ++rounds_played;

    bool game_over = rounds_played == TOTAL_NUM_OF_GAME_ROUND;
    if (game_over) {
      game_state = GameState::END_OF_GAME;
    } else {
      game_state = GameState::END_OF_ROUND;
      moveTileAfterEachRound();
    }
  }

  return factory_is_legal && row_is_legal;
}

void GameEngine::placeTilesToStorageRow(Player* player, const Turn* turn) {
  unsigned int facNum = turn->getFactory();
  Colour colour = turn->getTile()->getColour();
  unsigned int row = turn->getPatternLine();

  Mosaic* mosaic = player->getMosaic();
  Factory* factory = factories[facNum];

  // add tiles to mosaic
  for (Tile* tile : factory->popTiles(colour)) {
    if (row == 0) {
      mosaic->getBrokenTiles()->addTile(tile);
    } else {
      mosaic->addTileToStorage(tile, row);
    }
  }

  // if not central, add all other tiles to central
  if (facNum != 0) {
    for (Tile* tile : factory->getAllTiles()) {
      // add to central
      factories[0]->addTile(tile);
    }
    factory->removeAllTiles();
  } else {
    // check first player tile
    // if the first tile in the cental is the first player tile, add to broken
    // tiles
    bool first_tile_is_first_player =
        !factory->isEmpty() &&
        factory->getAllTiles()[0]->getColour() == Colour::FIRST_PLAYER;

    if (first_tile_is_first_player) {
      mosaic->getBrokenTiles()->addTile(factory->popTiles(FIRST_PLAYER)[0]);
      player->setFirstPlayer();
    }
  }
}

void GameEngine::updateNextPlayer() {
  int next_player_position = 0;

  for (int i = 0; i != players.size(); ++i) {
    if (players[i] == next_player) {
      next_player_position = i;
    }
  }

  if (++next_player_position > players.size() - 1) {
    next_player_position = 0;
  }

  next_player = players[next_player_position];
}

bool GameEngine::checkEndOfRound() {
  bool returnVal = true;
  for (Factory* fac : factories) {
    if (!fac->isEmpty()) {
      returnVal = false;
    }
  }

  return returnVal;
}

void GameEngine::moveTileAfterEachRound() {
  for (Player* player : this->players) {
    moveTileAfterEachRound(player);
  }
}

void GameEngine::moveTileAfterEachRound(Player* player) {
  // check each storage row, if full, then move and calculate point
  //
  //  for each row in the storageRow:
  //  if row is full, then
  //  move the right tile to grid, add others to bag
  //  get points for this movement
  //  end if
  //  end for each loop
  //
  //  deduct points for broken tile
  //  add tiles in broekenTiles back to bag
  //
  //  update points for player

  int points = 0;
  for (int i = 1; i != MOSAIC_GRID_DIM + 1; ++i) {
    if (player->getMosaic()->isStorageRowFull(i)) {
      Colour colour = player->getMosaic()->getStorageRowColour(i);
      for (Tile* tile : player->getMosaic()->moveTileToGrid(i)) {
        tile_bag->addBack(tile);
      }
      // update points
      points += player->getMosaic()->calScore(i, colour);
    }
  }

  // minus points lost in broken tiles
  points -= player->getMosaic()->getBrokenTiles()->calculateLostPoints();

  // add broken tiles back to bag
  for (Tile* tile : player->getMosaic()->getBrokenTiles()->getAllTiles()) {
    if (tile->getColour() == Colour::FIRST_PLAYER) {
      factories[0]->addTile(tile);
    } else {
      tile_bag->addBack(tile);
    }
  }
  player->getMosaic()->getBrokenTiles()->clear();

  player->updateScoreBy(points);

  player = nullptr;
}

std::string GameEngine::getNextPlayerName() const {
  return next_player->getName();
}

Mosaic* GameEngine::getMosaic(std::string player_name) const {
  return this->getPlayerByName(player_name)->getMosaic();
}

std::vector<Factory*> GameEngine::getFactories() const {
  return factories;
}

std::vector<Player*> GameEngine::getPlayers() const {
  return players;
}

void GameEngine::firstPlayerSetup() {
  // get the first palyer for this round
  for (Player* player : this->players) {
    if (player->isFirstPlayer()) {
      next_player = player;
    }
  }

  for (Player* player : this->players) {
    player->resetFirstPlayer();
  }
}

Player* GameEngine::getPlayerByName(const std::string playerName) const {
  int postion = -1;

  for (int i = 0; i != players.size(); ++i) {
    if (players[i]->getName() == playerName) {
      postion = i;
    }
  }
  if (postion == -1) {
    throw new std::invalid_argument("Player does not exists.");
  }
  return players[postion];
}

void GameEngine::saveGame(std::string filename) const {
  this->game_history->saveToFile(filename);
}
