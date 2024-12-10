#include "Kalah.hpp"
#include <iostream>

Kalah::Kalah(int h, int s) : numHouses(h), numSeeds(s),
                             north(Side::North, "North", 'N', h * s), south(Side::South, "South", 'S', h * s),
                             bd(h, s, north, south), currentPlayer(south),
                             gameOver(false), gameOutcome(Outcome::Undetermined) {}

bool Kalah::isValidMove(int move) {
    if (move <= 0 || move > numHouses) {
        cout << "Chosen house number " << move << " is invalid\nBad input -- please try again" << endl;
        return false;
    }
    if (bd.isHouseEmpty(currentPlayer, move)) {
        cout << "Can't choose an empty pit\nBad input -- please try again" << endl;
        return false;
    }
    return true;
}

bool Kalah::doMove(int move) {
    if (isValidMove(move)) {
        cout << endl << currentPlayer << " playing move " << move << endl;

        int pit = bd.getPitIndex(currentPlayer, move);
        int seeds = bd.removeSeeds(pit);

        // Sow seeds in pits CCW until we run out of seeds
        while (seeds > 0) {
            pit++;
            if (pit > 2 * numHouses + 1) {
                pit = 0;
            }

            if (!bd.isOpponentStore(currentPlayer, pit)) {
                bd.addSeed(pit);
                seeds--;
            }
        }

        // Check for condition to capture seeds
        if (bd.isPlayerHouse(currentPlayer, pit) && bd.getPitSeeds(pit) == 1) {
            // Last pit was empty before seed was added, player takes from opposite house
            bd.captureOppositePit(currentPlayer, pit);
        }

        // Check if one of the players has run out of seeds
        if (north.houseSeeds == 0) {
            endGame(south);
        }
        if (south.houseSeeds == 0) {
            endGame(north);
        }

        // Check if player has another turn
        if (!bd.isPlayerStore(currentPlayer, pit)) {
            // Switch sides if last pit is not the player's own store
            if (currentPlayer.side == Side::North) {
                currentPlayer = south;
            } else {
                currentPlayer = north;
            }
            cout << "Turn is over" << endl;
        } else {
            cout << currentPlayer << " gets another turn" << endl;
        }

        return true;
    }

    return false;
}

void Kalah::showBoard() {
    cout << endl << "----------" << endl << currentPlayer << "'s turn:" << endl;
    cout << bd << endl; // Use Board's operator<< function to print
    cout << "Please enter a pit number for " << currentPlayer << " (q to quit): ";
}

void Kalah::endGame(Player player) {
    bd.storeAllSeeds(player);
    gameOver = true;

    if (north.storeSeeds > south.storeSeeds) {
        gameOutcome = Outcome::NorthWin;
    } else if (north.storeSeeds < south.storeSeeds) {
        gameOutcome = Outcome::SouthWin;
    } else {
        gameOutcome = Outcome::Tie;
    }
}

bool Kalah::isGameOver() {
    return gameOver;
}

Outcome Kalah::getGameOutcome() {
    return gameOutcome;
}

Player Kalah::getCurrentPlayer() const {
    return currentPlayer;
}

void Kalah::saveState(Player& activePlayer, vector<int>& seeds) const {
    activePlayer = currentPlayer;
    bd.saveSeedsState(seeds);
}

void Kalah::restoreState(const Snapshot& ss) {
    currentPlayer = ss.getActivePlayer();
    if (currentPlayer.side == Side::North) {
        north = currentPlayer;
    } else {
        south = currentPlayer;
    }

    const vector<int>& seeds = ss.getSeedsState();
    for (int i = 0; i < numHouses; i++) {
        south.houseSeeds += seeds.at(i);
    }
    south.storeSeeds = seeds.at(numHouses);
    for (int i = numHouses + 1; i < 2 * numHouses + 1; i++) {
        north.houseSeeds += seeds.at(i);
    }
    north.storeSeeds = seeds.at(2 * numHouses + 1);

    printf("North: %d %d\n", north.houseSeeds, north.storeSeeds);
    printf("South: %d %d\n", south.houseSeeds, south.storeSeeds);

    bd.restoreSeedsState(seeds);
}

ostream& operator<<(ostream& os, const Kalah& kalah) {
    os << kalah.north << " (" << kalah.north.storeSeeds << "), ";
    os << kalah.south << " (" << kalah.south.storeSeeds << ")";
    return os;
}
