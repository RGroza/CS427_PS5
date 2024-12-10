#include <iomanip>
#include "Pit.hpp"

Pit::Pit() : owner(nullptr), number(0), seeds(0), label(""), next(nullptr), opposite(nullptr) {}

Pit::Pit(Player* p, int n, int s, const string& l, Pit* next, Pit* opposite) :
    owner(p), number(n), seeds(s), label(l), next(next), opposite(opposite) {}

int Pit::getSeeds() {
    return seeds;
}

Pit* Pit::getOpposite() {
    return opposite;
}

void Pit::addSeed() {
    seeds++;
    if (opposite == nullptr) {
        owner->storeSeeds++;
    } else {
        owner->houseSeeds++;
    }
}

void Pit::addSeeds(int s) {
    seeds += s;
    if (opposite == nullptr) {
        owner->storeSeeds += s;
    } else {
        owner->houseSeeds += s;
    }
}

int Pit::removeSeeds() {
    int s = seeds;
    seeds = 0;
    owner->houseSeeds -= s;
    return s;
}

string Pit::getLabel() {
    return label;
}

ostream& operator<<(ostream& os, const Pit& pit) {
    os << "[" << setw(2) << pit.seeds << "]";
    return os;
}
