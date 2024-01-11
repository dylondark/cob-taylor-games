#include "triviacontroller.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

TriviaController::TriviaController()
{
    // load question data from files, package into question structs and store in questionVec
    std::ifstream file(questionPath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Question current;
        string temp;
        iss >> temp;
        current.m_question = QString(temp.c_str());
        iss >> temp;
        current.m_ans1 = QString(temp.c_str());
        iss >> temp;
        current.m_ans2 = QString(temp.c_str());
        iss >> temp;
        current.m_ans3 = QString(temp.c_str());
        iss >> temp;
        current.m_ans4 = QString(temp.c_str());
        // images will also need to be done. later...
        questionVec.push_back(current);
    }
    file.close();

    // populate and randomize questionNums
    for (int x = 0; x < questionVec.size(); x++)
        questionNums.push_back(x);
    std::shuffle(questionNums.begin(), questionNums.end(), std::default_random_engine{ std::random_device{}() });
    /* questions must be shown to the player in random order with no repeats,
     * and the question order must be different every time the game is played (this object is constructed).
     * the simplest way i figured to do this would be to create a vector of numbers 0 to questionVec.size() - 1 (questionNum)
     * to use as the index for questionVec and randomly shuffle this vector. then iterate through this vector as the index
     * every time we need to get a new question. see getQuestion() */
}

void TriviaController::randQuestion()
{
    static int index = 0;
    if (index >= questionNums.size())
        index = 0; // exceeding the amount of questions in questionVec will just loop back to the beginning. in the final game this should probably end the game or at least randomize the questions again
    currentQuestion = questionVec[questionNums[index++]];
}

Question TriviaController::getQuestion()
{
    return currentQuestion;
}
