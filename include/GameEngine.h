#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "Constants.h"
#include "Factory.h"
#include "GameHistory.h"
#include "Player.h"
#include "TileBag.h"

// GameEngine implements the state machine shown below.
//
// Note:
//  - Setters are only valid until state progresses beyond START
//  - Other methods represent state transitions and are therefore only valid
//    when the appropriate state is active
//
//                          +-------+
//                          |       |
//                          | START |
//                          |       |
//                          +-------+
//                              |
//                              |
//                  startGame() |
//                              |
//                              v
//                     +----------------+
//                     |                |
//                     | START_OF_ROUND |<-----------------+
//                     |                |                  |
//                     +----------------+                  |
//                              |                          |
//                              |                          |
//                   playTurn() |    +-------+             |
//                              |    |       |             |
//                              v    v       |             |
//                        +-----------+      |             |
//                        |           |      |             |
//                        | MID_ROUND |      | playTurn()  | startRound()
//                        |           |      |             |
//                        +-----------+      |             |
//                              |    |       |             |
//                              |    |       |             |
//          Factories are empty |    +-------+             |
//                              |                          |
//                              v                          |
//                      +--------------+                   |
//                      |              |                   |
//                      | END_OF_ROUND |-------------------+
//                      |              |
//                      +--------------+
//                              |
//                              |
//  All rounds have been played |
//                              |
//                              v
//                       +-------------+
//                       |             |
//                       | END_OF_GAME |
//                       |             |
//                       +-------------+
//

enum GameState {
  START,           // No turns played yet
  START_OF_ROUND,  // Ready to start a round
  MID_ROUND,  // In the middle of a round, ready to continue with the next turn
  END_OF_ROUND,  // At the end of a round, ready to transition to START_OF_ROUND
  END_OF_GAME,   // All rounds have been played
};

class GameEngine {
 private:
  GameHistory* game_history;
  GameState game_state;
  TileBag* tile_bag;
  std::vector<Player*> players;
  std::vector<Factory*> factories;
  Player* next_player;
  unsigned int rounds_played;

  void loadGameSetUp(const GameHistory* gameHistory);

  void initFactories();
  void fillFactories();

  void replayTurns();

  // return false when the movement failed.
  bool playerMovement(Player* player, const Turn* turn);
  void placeTilesToStorageRow(Player* player, const Turn* turn);
  void updateNextPlayer();
  bool checkEndOfRound();
  // move tile into grid for each player, and update points
  void moveTileAfterEachRound();
  void moveTileAfterEachRound(Player* player);

  void firstPlayerSetup();
  Player* getPlayerByName(const std::string playerName) const;
  void decideWinner();

 public:
  GameEngine();
  GameEngine(GameHistory* gameHistory);
  ~GameEngine();

  void addPlayer(std::string name);

  GameState getState() const;
  void startGame();
  void startRound();

  // Return value indicates whether turn is valid at this time
  bool playTurn(const Turn* turn);

  std::string getNextPlayerName() const;
  Mosaic* getMosaic(std::string player_name) const;
  std::vector<Factory*> getFactories() const;
  std::vector<Player*> getPlayers() const;

  void saveGame(std::string filename) const;
};

#endif  // GAMEENGINE_H
