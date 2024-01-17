#pragma once

#include "constants.h"
#include "highscoretype.h"

extern scoreEntry *head;
extern scoreEntry *tail;

#include <string>

using namespace std;

template <typename... Args>
std::string formatString(const std::string &format, Args... args);

string getCurrentDateTime();

void appendRecordToTable(string currentLocalTimeString, int score, string playerName);

void showHistory();

int readHistoryFile();

bool writeToHistoryTextFile(string dateTimeString, int playerScore, string playerName);

void gameFinished(int playerScore, std::string playerName);

vector<scoreEntry> getTopScores();

vector<scoreEntry> GetHistoryScoreSorted();
