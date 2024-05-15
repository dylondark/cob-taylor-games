/*
    guessthelogocontroller.h

    class declaration for guessthelogocontroller.
*/

#ifndef GUESSTHELOGOCONTROLLER_H
#define GUESSTHELOGOCONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>

/*
    documentation for using c++ with QML can be found at
    https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html
*/

using std::string;
using std::vector;

struct GTLQuestion
{
    Q_GADGET
public:
    QString m_question;
    int m_correct; // number of correct question 1-4
    QString m_ans1, m_ans2, m_ans3, m_ans4;
    QString m_img;
    Q_PROPERTY(QString question MEMBER m_question)
    Q_PROPERTY(int correct MEMBER m_correct);
    Q_PROPERTY(QString ans1 MEMBER m_ans1)
    Q_PROPERTY(QString ans2 MEMBER m_ans2)
    Q_PROPERTY(QString ans3 MEMBER m_ans3)
    Q_PROPERTY(QString ans4 MEMBER m_ans4)
    Q_PROPERTY(QString img MEMBER m_img)
};

/* GuessTheLogoController

    This class is the controller class for the Trivia game. It is instantiated as an object in the QML file for the game and used in the QML.
    Anything more than basic ui logic is located here. Specifically, this class loads the trivia question data from the filesystem, and
    it contains methods that can be used within QML to obtain that question data in random order.
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
    string filepath = ".";
    const string QUESTION_PATH = "/gamefiles/GuessTheLogo/GTL.csv";
    const string IMG_PATHS[2];
    vector<GTLQuestion> questionVec; // vector containing the question structs, to be populated by loadQuestions
    vector<int> questionNums;
    GTLQuestion currentQuestion;
};

#endif // GUESSTHELOGOCONTROLLER_H
