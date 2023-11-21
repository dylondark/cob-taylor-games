#include "leaderboardhandler.h"
#include <fstream>
#include <iostream>

LeaderboardHandler:: LeaderboardHandler(QStackedWidget* lbObj)
{
    this->lbObj = lbObj;
}

LeaderboardHandler:: ~LeaderboardHandler()
{
    //Destructor implementation here
}

void LeaderboardHandler::addScore(game selectedGame, std::string playerName, int score)
{
    // check if a score for this player already exists
    if (scoreLists[selectedGame].find(playerName) == scoreLists[selectedGame].end())
        // it does not exist already, add it
        scoreLists[selectedGame][playerName] = score;
    else if (scoreLists[selectedGame][playerName] < score)
        // it does exist, so only add it if the new score is higher
        scoreLists[selectedGame][playerName] = score;
}

void LeaderboardHandler::loadScores(game selectedGame)
{
    // TODO: if this function fails it needs to end the program and notify the user with a dialog window or something.
    // if this fails and the program continues it could overwrite the scores with nothing, causing data loss.

    std::ifstream file(FILEPATH + FILENAMES[selectedGame]); //Substitute all caps words for their respective files

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << FILENAMES[selectedGame] << std::endl;
        return;
    }

    scoreLists[selectedGame].clear(); // Clear existing scores

    std::string playerName;
    int score;

    while (file >> playerName >> score) {
        scoreLists[selectedGame][playerName] = score;
    }

    file.close();
}

void LeaderboardHandler::loadScores() {
    for (int i = 0; i < 6; ++i) {
        loadScores(static_cast<game>(i));
    }
}

void LeaderboardHandler:: writeScores(game selectedGame)
{
    std::ofstream outFile(FILEPATH + FILENAMES[selectedGame]); //Substitute all caps words for their respective files

    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing: " << FILENAMES[selectedGame] << std::endl;
        return;
    }

    for (const auto& entry : scoreLists[selectedGame]) {
        outFile << entry.first << " " << entry.second << "\n";
    }

    outFile.close();
}

void LeaderboardHandler::writeScores() {
    // Calls writeScores(game) for all games
    for (int i = 0; i < 6; ++i) {
        writeScores(static_cast<game>(i));
    }
}
