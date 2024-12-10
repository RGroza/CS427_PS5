#include "Board.hpp"
#include <iostream>

Board::Board(int h, int s, Player& north, Player& south) : numHouses(h), numSeeds(s) {
    pitWarehouse = make_unique<Pit[]>(2 * h + 2);

    // Constructing pitWarehouse array from "S<numHouses>" to "N0" (CCW direction)
    // Pits for South player houses
    for (int i = 0; i < h; i++) {
        pitWarehouse[i] = Pit(&south, h - i, s, "S" + to_string(h - i),
                              &pitWarehouse[i + 1], &pitWarehouse[2 * h - i]);
    }
    // Pit for South player store
    pitWarehouse[h] = Pit(&south, 0, 0, "S0", &pitWarehouse[h + 1], nullptr);

    // Pits for North player houses
    for (int i = 0; i < h; i++) {
        pitWarehouse[h + 1 + i] = Pit(&north, h - i, s, "N" + to_string(h - i),
                                      &pitWarehouse[h + 2 + i], &pitWarehouse[h - 1 - i]);
    }
    // Pit for North player store
    pitWarehouse[2 * h + 1] = Pit(&north, 0, 0, "N0", &pitWarehouse[0], nullptr);
}

int Board::getPitIndex(Player& player, int house) {
    if (player.side == Side::North) {
        return 2 * numHouses + 1 - house;
    } else {
        return numHouses - house;
    }
}

int Board::getPitSeeds(int pit) const{
    return pitWarehouse[pit].getSeeds();
}

int Board::getHouseSeeds(Player& player, int house) {
    return pitWarehouse[getPitIndex(player, house)].getSeeds();
}

void Board::addSeed(int pit) {
    pitWarehouse[pit].addSeed();
}

void Board::addSeeds(int pit, int s) {
    pitWarehouse[pit].addSeeds(s);
}

int Board::removeSeeds(int pit) {
    return pitWarehouse[pit].removeSeeds();
}

bool Board::isHouseEmpty(Player& player, int house) {
    return getHouseSeeds(player, house) == 0;
}

bool Board::isPlayerHouse(Player& player, int pit) {
    if (player.side == Side::North) {
        return (pit > numHouses && pit < 2 * numHouses + 1);
    } else {
        return (pit >= 0 && pit < numHouses);
    }
}

bool Board::isStore(int pit) {
    return (pit == numHouses || pit == 2 * numHouses + 1);
}

bool Board::isOpponentStore(Player& player, int pit) {
    if (player.side == Side::North && pit == numHouses) {
        return true;
    }
    if (player.side == Side::South && pit == 2 * numHouses + 1) {
        return true;
    }
    return false;
}

int Board::storePit(Player& player) {
    if (player.side == Side::North) {
        return 2 * numHouses + 1;
    } else {
        return numHouses;
    }
}

bool Board::isPlayerStore(Player& player, int pit) {
    return (pit == storePit(player));
}

int Board::getStoreSeeds(Player& player) {
    return pitWarehouse[storePit(player)].getSeeds();
}

void Board::storeSeeds(Player& player, int seeds) {
    pitWarehouse[storePit(player)].addSeeds(seeds);
}

void Board::captureOppositePit(Player& player, int pit) {
    int oppositeSeeds = pitWarehouse[pit].getOpposite()->removeSeeds();
    if (oppositeSeeds > 0) {
        storeSeeds(player, oppositeSeeds + pitWarehouse[pit].removeSeeds());
    }
    cout << "Captured " << oppositeSeeds + 1 << " seeds" << endl;
}

void Board::storeAllSeeds(Player& player) {
    int start = 0;
    if (player.side == Side::North) {
        start = numHouses + 1;
    }
    for (int i = 0; i < numHouses; i++) {
        storeSeeds(player, pitWarehouse[start + i].removeSeeds());
    }
}

void Board::saveSeedsState(vector<int>& seeds) const {
    for (int i = 0; i < 2 * numHouses + 2; i++) {
        seeds.push_back(getPitSeeds(i));
    }
}

void Board::restoreSeedsState(const vector<int>& seeds) {
    for (int i = 0; i < 2 * numHouses + 2; i++) {
        addSeeds(i, seeds.at(i));
    }
}

ostream& operator<<(ostream& os, const Board& board) {
    // Print first line: North house labels
    os << "       ";
    for (int i = 0; i < board.numHouses; i++) {
        os << "    " << board.pitWarehouse[2 * board.numHouses - i].getLabel();
    }
    os << endl;
    // Print second line: North house seeds
    os << "        ";
    for (int i = 0; i < board.numHouses; i++) {
        os << "  " << board.pitWarehouse[2 * board.numHouses - i];
    }
    os << endl;
    // Print third line: North and South stores
    os << "  " << board.pitWarehouse[2 * board.numHouses + 1].getLabel() << " "
               << board.pitWarehouse[2 * board.numHouses + 1];
    for (int i = 0; i < 6 * board.numHouses; i++) {
        os << " ";
    }
    os << board.pitWarehouse[board.numHouses] << " "
       << board.pitWarehouse[board.numHouses].getLabel() << endl;
    // Print fourth line: South house seeds
    os << "        ";
    for (int i = 0; i < board.numHouses; i++) {
        os << "  " << board.pitWarehouse[i];
    }
    os << endl;
    // Print fifth line: South house labels
    os << "       ";
    for (int i = 0; i < board.numHouses; i++) {
        os << "    " << board.pitWarehouse[i].getLabel();
    }
    os << endl;
    return os;
}
