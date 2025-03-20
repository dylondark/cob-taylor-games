/*
    leaderboardhandler.cpp

    class definition for the leaderboardhandler.
*/

#include "leaderboardhandler.h"
#include <QApplication>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <cmath>
#include <set>

/*
    Handles adding to the leaderboard.

    QStackedWidget* lbObj: pointer to data about the addition.
*/
LeaderboardHandler:: LeaderboardHandler(QStackedWidget* lbObj)
{
    if (QApplication::arguments().length() > 1 && QApplication::arguments().at(1) == "-p")
        filepath = QApplication::arguments().at(2).toStdString() + "/leaderboard/";

    this->lbObj = lbObj;
}

/*
    Handles destructing/deleting the object.
*/
LeaderboardHandler:: ~LeaderboardHandler()
{
    delete lbObj;
}

/*
    Adds score to memory buffer.

    game selectedGame: game to add score to
    string playerName: the name connected with the score
    int score: the score the player achieved.
*/
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

/*
    Loads scores from file into memory buffer for specified game.

    game selectedGame: game to load scores from.
*/
void LeaderboardHandler::loadScores(game selectedGame)
{
    std::ifstream file(filepath + FILENAMES[selectedGame]); //Substitute all caps words for their respective files

    if (!file.is_open())
    {
        Utilities::throwError(Utilities::FileOpenError, QString(FILENAMES[selectedGame].c_str()).prepend("/leaderboard/"));
    }

    scoreLists[selectedGame].clear(); // Clear existing scores

    std::string playerName;
    int score;

    while (file >> playerName >> score)
        scoreLists[selectedGame][playerName] = score;

    file.close();
}

/*
    Calls loadScores(game) for all games.
*/
void LeaderboardHandler::loadScores() {
    for (int i = 0; i < 6; ++i)
        loadScores(static_cast<game>(i));
}

/*
    Writes scores from memory buffer to file for specified game.

    game selectedGame: specified game.
*/
void LeaderboardHandler:: writeScores(game selectedGame)
{
    std::ofstream outFile(filepath + FILENAMES[selectedGame]); //Substitute all caps words for their respective files

    if (!outFile.is_open())
    {
        Utilities::throwError(Utilities::FileWriteError, QString(FILENAMES[selectedGame].c_str()).prepend("/leaderboard/"));
    }

    for (const auto& entry : scoreLists[selectedGame])
        outFile << entry.first << " " << entry.second << "\n";

    outFile.close();
}

/*
    Calls writeScores(game) for all games.
*/
void LeaderboardHandler::writeScores() {
    // Calls writeScores(game) for all games
    for (int i = 0; i < 6; ++i)
        writeScores(static_cast<game>(i));
}

struct LeaderboardHandler::sortcomp
{
    template <typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second)
            return l.second < r.second;
        return l.first < r.first;
    }
};

/*
    Refreshes the leaderboard page of specified game with new values based on current memory.

    game selectedGame: the game who's data is being refreshed on the leaderboard.
*/
void LeaderboardHandler::refreshlb(game selectedGame)
{
    QListWidget* list[] = {(QListWidget*)(lbObj->widget(selectedGame)->children()[1]), (QListWidget*)(lbObj->widget(selectedGame)->children()[2]), (QListWidget*)(lbObj->widget(selectedGame)->children()[3])};
    int place = 1;

    // clear current lists
    for (auto listitem : list)
        listitem->clear();

    // sort the map into this set
    std::set<std::pair<std::string, int>, sortcomp> sortset(scoreLists[selectedGame].begin(), scoreLists[selectedGame].end());

    auto item = sortset.crbegin();
    if (item == sortset.crend())
    {
        list[0]->addItem("No scores yet...");
        return;
    }

    int itemIndex;
    for (int count = 0; count < MAX_ENTRIES; count++)
    {
        itemIndex = count / (MAX_ENTRIES / 3);

        // build string
        QString listItemTxt;
        listItemTxt.append(item->first);
        listItemTxt.append(" - ");
        listItemTxt.append((std::to_string(item->second)));

        // create listwidgetitem
        QListWidgetItem* lsitem = new QListWidgetItem(list[itemIndex]);
        lsitem->setIcon(genNumIcon(place++));
        lsitem->setText(listItemTxt);

        // add to list
        list[itemIndex]->addItem(lsitem);

        if (++item == sortset.crend())
            break;
    }
}

/*
    Calls refreshlb(game) for all games (refreshes all pages).
*/
void LeaderboardHandler::refreshlb()
{
    for (int i = 0; i < 6; ++i)
        refreshlb(static_cast<game>(i));
}

QIcon LeaderboardHandler::genNumIcon(int num)
{
    QPixmap pix(100, 100);
    pix.fill(Qt::transparent); // required or else strange things happen to the pixmap...
    QPainter painter(&pix);

    // funny oneliner to calculate scale values
    int digits = num > 0 ? (int) log10 ((double) num) + 1 : 1, lPos = 10, dPos = 90 / (1 + (0.18 * (digits - 1))), size = 60 / (1 + (0.7 * (digits - 1)));

    painter.setFont(QFont("1UP!", size));
    painter.drawText(lPos, dPos, QString(std::to_string(num).c_str()));

    painter.end();
    return QIcon(pix);
}


