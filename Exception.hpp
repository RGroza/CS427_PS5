#pragma once
#include "tools.hpp"

// Base exception class for Kalah
class KalahIllegalMove {
public:
    int move;
    KalahIllegalMove(int m) : move(m) {}
    virtual ~KalahIllegalMove() = default;
    virtual void print() {
        cerr << "\nIllegal move occurred" << move;
        pr();
    }
    void pr() {
        cerr << "\nBad input -- please try again" << endl;
    }
};

// Derived exception classes for Kalah
class InvalidHouseNumber : public KalahIllegalMove {
public:
    InvalidHouseNumber(int m) : KalahIllegalMove(m) {}
    ~InvalidHouseNumber() override = default;
    inline void print() override {
        cerr << "\nChosen house number " << move << " is invalid";
        pr();
    }
};

class InvalidEmptyPit : public KalahIllegalMove {
public:
    InvalidEmptyPit(int m) : KalahIllegalMove(m) {}
    ~InvalidEmptyPit() override = default;
    inline void print() override {
        cerr << "\nCan't choose an empty pit";
        pr();
    }
};

// Base exception class for Game
class GameException {
public:
    GameException() = default;
    virtual ~GameException() = default;
    virtual void print() {
        cerr << "\nAn error occured in Game";
        pr();
    }
    void pr() {
        cerr << " -- saving and quitting" << endl;
    }
};

// Derived exception classes for Game
class LostConnection : public GameException {
public:
    LostConnection() = default;
    ~LostConnection() override = default;
    inline void print() override {
        cerr << "\nLost connection with the user";
        pr();
    }
};

class LowLevelStreamError : public GameException {
public:
    string message;
    LowLevelStreamError(const string& msg) : message(msg) {}
    ~LowLevelStreamError() override = default;
    inline void print() override {
        cerr << "\nLow-level stream error (" << message << ")";
        pr();
    }
};

class Quit : public GameException {
public:
    Quit() = default;
    ~Quit() override = default;
    inline void print() override {
        cerr << "\nDetected quit action (q)";
        pr();
    }
};

class Fatal : public GameException {
public:
    string message;
    Fatal(const string& msg) : message(msg) {}
    ~Fatal() override = default;
    inline void print() override {
        fatal("Fatal error occurred: " + message);
    }
};
