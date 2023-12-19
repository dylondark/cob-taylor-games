#include "leaderboardhandler.h"
#include <QPainter>
#include <fstream>
#include <iostream>
#include <cmath>
#include <set>

LeaderboardHandler:: LeaderboardHandler(QStackedWidget* lbObj)
{
    this->lbObj = lbObj;
}

LeaderboardHandler:: ~LeaderboardHandler()
{
    delete lbObj;
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
    std::ifstream file(FILEPATH + FILENAMES[selectedGame]); //Substitute all caps words for their respective files

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << FILENAMES[selectedGame] << std::endl <<
            "Please ensure that this file is present, not corrupt, and has sufficient read/write permissions." << std::endl;
        std::terminate();
        /*
         * this failing must end the program because if the program fails to read in a file and continues to save back to that file,
         * it could overwrite the data in that file causing data loss, assuming the file is even writable, which if it isnt then it will cause further error anyway.
         * putting terminate() here is (hopefully) going to be a temporary solution. i would like to have some organized exception system that
         * can notify the user with a nice dialog window or something, but i just tried for 2 hours to implement that and it seems to be biting off more
         * than i can chew at the moment, so this is a reminder to (hopefully) come back and implement that at some point!
         */
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

struct LeaderboardHandler::sortcomp
{
    template <typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
    }
};

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

void LeaderboardHandler::refreshlb()
{
    for (int i = 0; i < 6; ++i) {
        refreshlb(static_cast<game>(i));
    }
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
