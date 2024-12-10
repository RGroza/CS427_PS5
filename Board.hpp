#pragma once
#include <memory>
#include <vector>
#include "Pit.hpp"
#include "Player.hpp"

using namespace std;

class Board {
private:
    int numHouses;
    int numSeeds;
    unique_ptr<Pit[]> pitWarehouse;

public:
    Board(int h, int s, Player& north, Player& south);
    int getPitIndex(Player& player, int house);
    int getPitSeeds(int pit) const;
    int getHouseSeeds(Player& player, int house);
    void addSeed(int pit);
    void addSeeds(int pit, int s);
    int removeSeeds(int pit);
    bool isHouseEmpty(Player& player, int house);
    bool isPlayerHouse(Player& player, int pit);
    bool isStore(int pit);
    bool isOpponentStore(Player& player, int pit);
    int storePit(Player& player);
    bool isPlayerStore(Player& player, int pit);
    int getStoreSeeds(Player& player);
    void storeSeeds(Player& player, int seeds);
    void captureOppositePit(Player& player, int pit);
    void storeAllSeeds(Player& player);
    void saveSeedsState(vector<int>& seeds) const;
    void restoreSeedsState(const vector<int>& seeds);
    friend ostream& operator<<(ostream& os, const Board& board);
};
