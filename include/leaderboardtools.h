/*
    leaderboardhandler.h

    Class declaration for leaderboardhandler.
 */

#ifndef LEADERBOARDTOOLS_H
#define LEADERBOARDTOOLS_H

#include "leaderboardhandler.h"
#include "utilities.h"

namespace
{
// totally not lifted from stackoverflow
/*
    Function to generate a random string of a given length.
*/
std::string randStr(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

    return tmp_s;
}
}

/*
    LeaderboardTools namespace

    This namespace provides some tools for generating and manipulating leaderboard data.
 */
// -- FOR DEVELOPMENT AND TESTING USE ONLY --
namespace LeaderboardTools
{

/*
    Generate leaderboard scores with a certain number of entries filled with random scores.
*/
void genRandScores(LeaderboardHandler* lbh, Utilities::game game, int entries)
{
    //srand(time(0));
    for (int x = 0; x < entries; x++)
        lbh->addScore(game, randStr(4), rand() % INT_MAX);
}

/*
    Genrandscores for all games.
*/
void genRandScores(LeaderboardHandler* lbh, int entries)
{
    for (int i = 0; i < 6; ++i)
        genRandScores(lbh, static_cast<Utilities::game>(i), entries);
}

/*
    Generates nicer test scores than genRandScores. more suitable for creating test files.
*/
void genTestScores(LeaderboardHandler* lbh, Utilities::game game, int entries)
{
    static const std::string GAME_STR[] = {"TRVA", "GTL", "CKRS", "ZHOP", "PONG", "TTRS"};
    for (int x = 0; x < entries; x++)
        lbh->addScore(game, GAME_STR[game] + std::to_string(x + 1), rand() % 1000);
}

/*
    Gentestscores for all games.
*/
void genTestScores(LeaderboardHandler* lbh, int entries)
{
    for (int i = 0; i < 6; ++i)
        genTestScores(lbh, static_cast<Utilities::game>(i), entries);
}
}

#endif // LEADERBOARDTOOLS_H
