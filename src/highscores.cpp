
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <fstream>
#include "highscoretype.h"
#include "highscores.h"
#include "constants.h"

scoreEntry *head;
scoreEntry *tail;
using namespace std;

template <typename... Args>
std::string formatString(const std::string &format, Args... args)
{
        size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
        if (size <= 0)
        {
                throw std::runtime_error("Error during formatting.");
        }

        std::unique_ptr<char[]> buf(new char[size]);

        snprintf(buf.get(), size, format.c_str(), args...);

        return std::string(buf.get(), buf.get() + size - 1);
}

string getCurrentDateTime()
{
        time_t timeObject = time(0);
        tm *currentLocalTime = localtime(&timeObject);

        string output = "[ ";
        output += formatString("%02d/", currentLocalTime->tm_mon + 1);
        output += formatString("%02d ", currentLocalTime->tm_mday);
        output += formatString("%02d:", currentLocalTime->tm_hour);
        output += formatString("%02d:", currentLocalTime->tm_min);
        output += formatString("%02d ]", currentLocalTime->tm_sec);
        return output;
}

void appendRecordToTable(string currentLocalTimeString, int score, string playerName)
{
        scoreEntry *newRecord = new scoreEntry;
        newRecord->dateTimeString = currentLocalTimeString;
        newRecord->playerScore = score;
        newRecord->playerName = playerName;
        newRecord->next = nullptr;

        if (!head)
        {
                head = tail = newRecord;
        }
        else
        {
                tail->next = newRecord;
                tail = newRecord;
        }
}

void showHistory()
{
        scoreEntry *current = head;

        while (current)
        {
                std::cout << "Date/Time: " << current->dateTimeString
                          << ", Score: " << current->playerScore
                          << ", Player Name: " << current->playerName << std::endl;
                current = current->next;
        }
}

int readHistoryFile()
{
        scoreEntry *current = head;
        scoreEntry *next;

        while (current != nullptr)
        {
                next = current->next;
                delete current;
                current = next;
        }

        std::ifstream file(HISTORY_FILENAME);

        if (!file.is_open())
        {
                std::cerr << "Error opening history file." << std::endl;
                return -1; // Unable to open the file
        }

        std::string line;
        int highestScore = -1;

        while (getline(file, line))
        {
                std::stringstream ss(line);
                std::string dateTimeString, scoreString, playerName;

                getline(ss, dateTimeString, ',');
                getline(ss, scoreString, ',');
                getline(ss, playerName, ',');

                int score = std::stoi(scoreString);

                if (score > highestScore)
                {
                        highestScore = score;
                }

                appendRecordToTable(dateTimeString, score, playerName);
        }

        file.close();

        return highestScore;
}

bool writeToHistoryTextFile(string dateTimeString, int playerScore, string playerName)
{
        std::ofstream file(HISTORY_FILENAME, std::ios::app);

        if (!file.is_open())
        {
                std::cerr << "Error opening history text file." << std::endl;
                return false;
        }

        file << dateTimeString
             << "," << playerScore
             << "," << playerName << std::endl;

        file.close();
        return true;
}

void gameFinished(int playerScore, std::string playerName)
{
        extern scoreEntry *head;
        extern scoreEntry *tail;

        std::string currentDateTime = getCurrentDateTime();

        if (playerScore > 0)
        {
                appendRecordToTable(currentDateTime, playerScore, playerName);

                if (!writeToHistoryTextFile(currentDateTime, playerScore, playerName))
                {
                        std::cerr << "Error saving high score to file." << std::endl;
                }

                std::cout << "Congratulations! New high score: " << playerScore << std::endl;
        }
        else
        {
                std::cout << "Game Over. Your score: " << playerScore << std::endl;
        }

        showHistory();
}

vector<scoreEntry> getTopScores()
{
        if (readHistoryFile())
        {
                std::cout << "Error reading history file." << std::endl;
        }
        else
        {

                vector<scoreEntry> topScores;

                scoreEntry *current = head;

                while (current != nullptr)
                {
                        topScores.push_back(*current);
                        current = current->next;
                }

                std::sort(topScores.begin(), topScores.end(), [](const scoreEntry &a, const scoreEntry &b)
                          { return a.playerScore > b.playerScore; });
                return topScores;
        }
        return {};
}

vector<scoreEntry> GetHistoryScoreSorted()
{
        vector<scoreEntry> historyVector;

        std::ifstream file(HISTORY_FILENAME);

        if (!file.is_open())
        {
                std::cerr << "Error opening history file." << std::endl;
                return historyVector;
        }

        std::string line;

        while (getline(file, line))
        {
                std::stringstream ss(line);
                std::string dateTimeString, scoreString, playerName;

                getline(ss, dateTimeString, ',');
                getline(ss, scoreString, ',');
                getline(ss, playerName, ',');

                int score = std::stoi(scoreString);

                scoreEntry entry;
                entry.dateTimeString = dateTimeString;
                entry.playerScore = score;
                entry.playerName = playerName;

                historyVector.push_back(entry);
        }

        file.close();

        std::sort(historyVector.begin(), historyVector.end(), [](const scoreEntry &a, const scoreEntry &b)
                  { return a.playerScore > b.playerScore; });

        return historyVector;
}