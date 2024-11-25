/*
    guessthelogocontroller.cpp

    Class definition for guessthelogocontroller.
*/

#include "guessthelogocontroller.h"
#include <random>
#include <algorithm>
#include "rapidcsv.h"
#include "utilities.h"
#include <QApplication>

/*
    Constructor for GuessthelogoController.
*/
GuessTheLogoController::GuessTheLogoController() : IMG_PATHS{"/gamefiles/GuessTheLogo/Type1/", "/gamefiles/GuessTheLogo/Type2/"}
{
    if (QApplication::arguments().length() > 1 && QApplication::arguments().at(1) == "-p")
        filepath = QApplication:: arguments().at(2).toStdString();

    /*
    load question data from files, package into question structs and store in questionVec
    trivia datafile must be csv with lines consisting of string, int, string, string, string, string, string
    all strings must be enclosed in quotation marks
    */
    GTLQuestion current;
    std::string strTemp;
    int questionType;
    rapidcsv::Document file;
    try
    {
        file = rapidcsv::Document(filepath + QUESTION_PATH);
    }
    catch (...)
    {
        Utilities::throwError(Utilities::FileOpenError);
    }
    for (unsigned x = 0; x < file.GetRowCount(); x++)
    {
        strTemp = file.GetCell<string>(0, x);
        current.m_question = QString(strTemp.c_str());

        current.m_correct = file.GetCell<int>(1, x);

        strTemp = file.GetCell<string>(2, x);
        current.m_ans1 = QString(strTemp.c_str());

        strTemp = file.GetCell<string>(3, x);
        current.m_ans2 = QString(strTemp.c_str());

        strTemp = file.GetCell<string>(4, x);
        current.m_ans3 = QString(strTemp.c_str());

        strTemp = file.GetCell<string>(5, x);
        current.m_ans4 = QString(strTemp.c_str());

        questionType = file.GetCell<int>(7,x);
        strTemp = file.GetCell<string>(6, x);
        current.m_img = QString(("file:")).append(filepath + IMG_PATHS[questionType - 1]).append(strTemp.c_str());

        questionVec.push_back(current);
    }

    // populate and randomize questionNums
    for (unsigned long long x = 0; x < questionVec.size(); x++)
        questionNums.push_back(x);
    std::shuffle(questionNums.begin(), questionNums.end(), std::default_random_engine{ std::random_device{}() });

    /*
    questions must be shown to the player in random order with no repeats,
    and the question order must be different every time the game is played (this object is constructed).
    the simplest way i figured to do this would be to create a vector of numbers 0 to questionVec.size() - 1 (questionNum)
    to use as the index for questionVec and randomly shuffle this vector. then iterate through this vector as the index
    every time we need to get a new question. see getQuestion()
    */
}

/*
    Gets the next random question and stores in currentQuestion.
*/
void GuessTheLogoController::randQuestion()
{
    static unsigned int index = 0;
    if (index >= questionNums.size())
        index = 0; // exceeding the amount of questions in questionVec will just loop back to the beginning. in the final game this should probably end the game or at least randomize the questions again
    currentQuestion = questionVec[questionNums[index++]];
}

/*
    Retrieves the current question stored in currentQuestion.
*/
GTLQuestion GuessTheLogoController::getQuestion()
{
    return currentQuestion;
}

/*
    Returns a list of ints 1-4 but in random order. used for randomizing answer buttons
*/
QVariantList GuessTheLogoController::randomizeFour()
{
    // shuffle 0-3
    static int nums[] = {0, 1, 2, 3};
    std::shuffle(std::begin(nums), std::end(nums), std::default_random_engine{ std::random_device{}() });

    // convert to qvariantlist for output in qml
    QVariantList out;
    for (int x : nums)
        out.append(x);

    return out;
}
