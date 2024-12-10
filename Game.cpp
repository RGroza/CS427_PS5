#include "Game.hpp"

Game::Game(int h, int s) : kalah(h, s), printBoard(true) {}

void Game::doMove(string token) {
    if (printBoard) {
        kalah.showBoard();
    }

    if (token == "q") {
        throw Quit();
    }

    try {
        int move = stoi(token);
        printBoard = kalah.doMove(move);
    } catch (const invalid_argument&) {
        cout << endl << "Bad input (" << token << ") must be an integer -- please try again" << endl;
    }
}

void Game::playGame(istringstream* iss) {
    try {
        if (iss == nullptr) {
            string line;
            while (getline(cin, line)) {
                if (cin.fail()) {
                    throw LowLevelStreamError("failed to read from stdin");
                }
                istringstream iss(line);
                playGame(&iss); // User input can either be a single move or mulitple moves
            }

            if (cin.eof()) {
                throw LowLevelStreamError("end of input reached");
            }
        } else {
            string token;
            while (*iss >> token && !kalah.isGameOver()) {
                if (iss->fail()) {
                    throw LowLevelStreamError("failed to read from input stream");
                }
                doMove(token);
            }

            // Query Kalah to check if game is over, print end game message
            if (kalah.isGameOver()) {
                cout << endl << "----------\nGame over -- " << kalah << "  -->  ";
                Outcome gameOutcome = kalah.getGameOutcome();
                if (gameOutcome == Outcome::NorthWin) {
                    cout << "North wins!" << endl;
                } else if (gameOutcome == Outcome::SouthWin) {
                    cout << "South wins!" << endl;
                } else {
                    cout << "Game is a tie!" << endl;
                }
                exit(EXIT_SUCCESS);
            }

            if (printBoard) {
                kalah.showBoard();
            }
        }

        printBoard = false;
    } catch (KalahIllegalMove& e) {
        e.print();
    } catch (GameException& e) {
        e.print();
        saveState();
        exit(EXIT_SUCCESS);
    }
}

void Game::saveState() const {
    try {
        Snapshot ss = Snapshot(kalah);
        ofstream file("kalah.state");
        ss.print(file);
    } catch (...) {
        fatal("A fatal error occurred while saving to a saved-game file");
    }
}

void Game::restoreState(const Snapshot& ss) {
    try {
        kalah.restoreState(ss);
    } catch (...) {
        fatal("A fatal error occurred while restoring from a saved-game file");
    }
}