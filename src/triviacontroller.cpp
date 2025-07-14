/*
    triviacontroller.cpp

    Class definition for TriviaController.
*/

#include "triviacontroller.h"
#include <random>
#include <algorithm>
#include "rapidcsv.h"
#include "utilities.h"
#include <QApplication>

/*
    Constructor for TriviaController.
*/
TriviaController::TriviaController()
{
    // parse -p CLI argument and set filepath if applicable
    if (QApplication::arguments().length() > 1 && QApplication::arguments().at(1) == "-p")
    {
        filepath = QApplication:: arguments().at(2).toStdString();
    }

    // load question data from files, package into question structs and store in questionVec
    // trivia datafile must be csv with lines consisting of string, int, string, string, string, string, string
    // all strings must be enclosed in quotation marks
    TriviaQuestion current;
    std::string strTemp;
    rapidcsv::Document file;
    try
    {
        file = rapidcsv::Document(filepath + QUESTION_PATH);
    }
    catch (...)
    {
        Utilities::throwError(Utilities::FileOpenError, QUESTION_PATH.c_str());
    }
    for (unsigned x = 0; x < file.GetRowCount(); x++)
    {
        // get question text
        strTemp = file.GetCell<string>(0, x);
        current.m_question = QString(strTemp.c_str());

        // get correct question number
        current.m_correct = file.GetCell<int>(1, x);

        // get first answer
        strTemp = file.GetCell<string>(2, x);
        current.m_ans1 = QString(strTemp.c_str());

        // second answer
        strTemp = file.GetCell<string>(3, x);
        current.m_ans2 = QString(strTemp.c_str());

        // third answer
        strTemp = file.GetCell<string>(4, x);
        current.m_ans3 = QString(strTemp.c_str());

        // fourth answer
        strTemp = file.GetCell<string>(5, x);
        current.m_ans4 = QString(strTemp.c_str());

        // get image filename
        strTemp = file.GetCell<string>(6, x);
        current.m_img = QString(("file:")).append(filepath + IMG_PATH).append(strTemp.c_str());

        // add to questions vector
        questionVec.push_back(current);
    }

    // populate and randomize questionNums
    for (int x = 0; x < (int)questionVec.size(); x++)
        questionNums.push_back(x);
    std::shuffle(questionNums.begin(), questionNums.end(), std::default_random_engine{ std::random_device{}() });
    /*
        Questions must be shown to the player in random order with no repeats,
        and the question order must be different every time the game is played (this object is constructed).
        The simplest way I figured to do this would be to create a vector of numbers 0 to questionVec.size() - 1 (questionNum)
        to use as the index for questionVec and randomly shuffle this vector. Then iterate through this vector as the index
        every time we need to get a new question. See getQuestion().
    */
}

/*
    Gets the next random question and stores in currentQuestion.
*/
void TriviaController::randQuestion()
{
    static int index = 0;

    // loop back around if index has gone higher than the amount of questions
    // this should never happen in production since there should be more questions in the database than will be shown in any one play of the game
    if (index >= (int)questionNums.size())
        index = 0;

    // retrieve random question
    currentQuestion = questionVec[questionNums[index++]];
}

/*
    Retrieves the current question stored in currentQuestion.
*/
TriviaQuestion TriviaController::getQuestion()
{
    return currentQuestion;
}

/*
    Returns a list of ints 1-4 but in random order. used for randomizing answer buttons
*/
QVariantList TriviaController::randomizeFour()
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
