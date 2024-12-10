#include "Snapshot.hpp"
#include "Kalah.hpp"
#include "tools.hpp"

Snapshot::Snapshot(istream& in, int houses, char label) :
        activePlayer((label == 'N') ? Side::North : Side::South,
                     (label == 'N') ? "North" : "South",
                      label, 0),
        houses(houses) {
    read(in);
}

Snapshot::Snapshot(const Kalah& kg) : activePlayer(kg.getCurrentPlayer()) {
    kg.saveState(activePlayer, seeds);
}

Player Snapshot::getActivePlayer() const {
    return activePlayer;
}

const vector<int>& Snapshot::getSeedsState() const {
    return seeds;
}

ostream& Snapshot::print(ostream& out) const {
    out << (seeds.size() - 2) / 2 << " " << activePlayer.label;
    for (int s : seeds) {
        out << " " << s;
    }
    return out;
}

istream& Snapshot::read(istream& in) {
    string token;
    for (int i = 0; i < 2 * houses + 2; i++) {
        if (in >> token) {
            try {
                int s = stoi(token);
                seeds.push_back(s);
            } catch (const invalid_argument&) {
                fatal("File read error: token is not an integer");
            } catch (const out_of_range&) {
                fatal("File read error: token is out of integer range");
            }
        } else {
            fatal("File read error: insufficient tokens");
        }
    }
    return in;
}
