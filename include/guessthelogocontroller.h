/*
    guessthelogocontroller.h

    class declaration for guessthelogocontroller.
*/

#ifndef GUESSTHELOGOCONTROLLER_H
#define GUESSTHELOGOCONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>

using std::string;
using std::vector;

struct GTLQuestion
{
    Q_GADGET
public:
    // The question text.
    QString m_question;

    // number of correct questions 1-4
    int m_correct;

    // The text for the 4 possible answers.
    QString m_ans1, m_ans2, m_ans3, m_ans4;

    // The path of the image for the current question.
    QString m_img;

    // Properties to make these data members accessible in QML.
    Q_PROPERTY(QString question MEMBER m_question)
    Q_PROPERTY(int correct MEMBER m_correct);
    Q_PROPERTY(QString ans1 MEMBER m_ans1)
    Q_PROPERTY(QString ans2 MEMBER m_ans2)
    Q_PROPERTY(QString ans3 MEMBER m_ans3)
    Q_PROPERTY(QString ans4 MEMBER m_ans4)
    Q_PROPERTY(QString img MEMBER m_img)
};

/*
    GuessTheLogoController

    This class is the controller class for the Trivia game. It is instantiated as an object in the QML file for the game and used in the QML.
    Anything more than basic ui logic is located here. Specifically, this class loads the trivia question data from the filesystem, and
    it contains methods that can be used within QML to obtain that question data in random order.

    Documentation for using c++ with QML can be found at:
    https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html
*/
class GuessTheLogoController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:

    /*
        Constructor for GuessTheLogoController.
    */
    GuessTheLogoController();

    /*
        Retrieves the current question stored in currentQuestion.
    */
    Q_INVOKABLE GTLQuestion getQuestion();

    /*
        Gets the next random question and stores in currentQuestion.
    */
    Q_INVOKABLE void randQuestion();

    /*
        Returns a list of ints 1-4 but in random order. used for randomizing answer buttons
    */
    Q_INVOKABLE QVariantList randomizeFour();

private:

    /*
        The base of the paths. Should be the location of the folder containing the gamefiles folder.
        By default it is "." which (should) mean "wherever the game executable was launched from" but this doesn't always work (ahem, mac).
        Will be set to whatever path is specified with the -p CLI parameter if it is used.
    */
    string filepath = ".";

    // The path to the question data file.
    const string QUESTION_PATH = "/gamefiles/GuessTheLogo/GTL.csv";

    /*
        The paths to the folders containing the images for the game.
        The code appends the image location of the question onto this string to get the entire image path for the current question's image.
    */
    const string IMG_PATHS[2];

    // Vector containing the question structs, to be populated by loadQuestions.
    vector<GTLQuestion> questionVec;

    // Contains a randomized list of the question numbers.
    vector<int> questionNums;

    // Current question assigned by randQuestion(). To be passed to QML via getQuestion().
    GTLQuestion currentQuestion;

};

#endif // GUESSTHELOGOCONTROLLER_H
