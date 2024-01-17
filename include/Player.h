#pragma once
#include "Pieces.h"

#include <iostream>

class Player
{
private:
    std::string name;
    int diff;
    int score;
    vector<CustomShape> pieces;

public:
    Player() : name(""), score(0), diff(0){};
    Player(std::string name) : name(name), score(0), diff(0){};
    void set_name(std::string name) { this->name = name; }
    void set_score(int score) { this->score = score; }
    std::string get_name() { return name; }
    int get_score() { return score; }
    void set_diff(int diff) { this->diff = diff; }
    int get_diff() { return diff; }
    void saveCustomPieces(vector<CustomShape> &pieces)
    {
        this->pieces = pieces;
    }
    vector<CustomShape> getCustomPieces()
    {
        return pieces;
    }
};