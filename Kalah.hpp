#pragma once
#include "Board.hpp"
#include "Player.hpp"
#include "Snapshot.hpp"
#include "Exception.hpp"

using namespace std;

enum class Outcome { SouthWin, NorthWin, Tie, Undetermined };

class Kalah {
private:
    int numHouses;
    int numSeeds;
    Player north;
    Player south;
    Board bd;
    Player currentPlayer;
    bool gameOver;
    Outcome gameOutcome;

public:
    Kalah(int h, int s);
    bool isValidMove(int move);
    bool doMove(int move);
    void showBoard();
    void endGame(Player player);
    bool isGameOver();
    Outcome getGameOutcome();
    Player getCurrentPlayer() const;
    void saveState(Player& activePlayer, vector<int>& seeds) const;
    void restoreState(const Snapshot& ss);
    friend ostream& operator<<(ostream& os, const Kalah& kalah);
};
