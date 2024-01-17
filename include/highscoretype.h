#pragma once

#include <string>

struct scoreEntry
{
    std::string dateTimeString;
    int playerScore;
    std::string playerName;
    scoreEntry *next;
};
