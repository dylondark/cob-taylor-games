#ifndef LEADERBOARDHANDLER_H
#define LEADERBOARDHANDLER_H
#include <QStackedWidget>

class LeaderboardHandler
{
public:
    LeaderboardHandler(QStackedWidget* lbObj);
    ~LeaderboardHandler();
    enum game {Trivia = 0, GuessTheLogo = 1, Checkers = 2, Hopper = 3, Pong = 4, Tetris = 5};
    void addScore(game, std::string, int); // add score to memory buffer
    void loadScores(game); // load scores from file into memory buffer for specified game
    void loadScores(); // calls loadScores(game) for all games
    void writeScores(game); // writes scores from memory buffer to file for specified game
    void writeScores(); // calls writeScores(game) for all games
    void refreshlb(game); // refreshes the leaderboard page of specified game with new values based on current memory
    void refreshlb(); // calls refreshlb(game) for all games (refreshes all pages)

private:
    QStackedWidget* lbObj; // ptr to the stack widget containing all the "pages" of the leaderboard
    std::map<std::string, int> scoreLists[6]; // 6 maps holding scores for the 6 games. key is their playername, int is their high score
    // a function for sorting scores high to low may be a good idea since the scores will need to be sorted when being placed in the leaderboard
    // however im not totally sure what it would look like or if it even necessary to be its own function yet
    const std::string FILEPATH = "./datafiles/"; // path where the data files can be found. currently it is a folder inside wherever the executable is named "datafiles"
    const std::string FILENAMES[6] = {"trivia.txt", "guessthelogo.txt", "checkers.txt", "hopper.txt", "pong.txt", "tetris.txt"}; // names of the datafiles
};

#endif // LEADERBOARDHANDLER_H
