/*
   leaderboardhandler.h

   Class declration for leaderboardhandler.
*/

#ifndef LEADERBOARDHANDLER_H
#define LEADERBOARDHANDLER_H
#include <QStackedWidget>
#include <QListWidget>
#include "utilities.h"

using Utilities::game;

/*
    LeaderboardHandler class

    This class is meant to be the "controller" object for the leaderbard on the main menu. It stores, facilitates adding to, loads, and saves the leaderboard data.
    It can also modify the contents of the leaderboard widgets through a pointer to their parent object, stored in lbObj. This is used so that this object can also
    be responsible for refreshing the data in the leaderboard widgets.
*/

class LeaderboardHandler
{

public:

    /*
        Handles adding to the leaderboard.

        QStackedWidget* lbObj: pointer to data about the addition.
    */
    LeaderboardHandler(QStackedWidget* lbObj);

    /*
        Handles destructing/deleting the object.
    */
    ~LeaderboardHandler();

    /*
        Adds score to memory buffer.

        game selectedGame: game to add score to
        string playerName: the name connected with the score
        int score: the score the player achieved.
    */
    void addScore(game, std::string, int);

    /*
        Loads scores from file into memory buffer for specified game.

        game selectedGame: game to load scores from.
    */
    void loadScores(game);

    /*
        Calls loadScores(game) for all games.
    */
    void loadScores();

    /*
        Writes scores from memory buffer to file for specified game.

        game selectedGame: specified game.
    */
    void writeScores(game);

    /*
        Calls writeScores(game) for all games.
    */
    void writeScores();

    /*
        Refreshes the leaderboard page of specified game with new values based on current memory.

        game selectedGame: the game who's data is being refreshed on the leaderboard.
    */
    void refreshlb(game);

    /*
        Calls refreshlb(game) for all games (refreshes all pages).
    */
    void refreshlb();

private:

    // Pointer to the stack widget containing all the "pages" of the leaderboard
    QStackedWidget* lbObj;

    // 6 maps holding scores for the 6 games. key is their playername, int is their high score
    std::map<std::string, int> scoreLists[6];

    // Used for map sort
    struct sortcomp;

    // Path where the data files can be found. currently it is a folder inside wherever the executable is named "datafiles"
    std::string filepath = "./leaderboard/";

    // Names of the datafiles
    const std::string FILENAMES[6] = {"trivia.txt", "guessthelogo.txt", "tetroos.txt", "hopper.txt", "pong.txt", "maze.txt"};

    // Generates an icon containing a number for the leaderboard images
    QIcon genNumIcon(int num);

    // Max number of entries on each leaderboard page. should be multiple of 3 for best results.
    const int MAX_ENTRIES = 24;

};

#endif // LEADERBOARDHANDLER_H
