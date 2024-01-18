#ifndef TRIVIACONTROLLER_H
#define TRIVIACONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

// documentation for using c++ with QML can be found at
// https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html

using std::string;
using std::vector;

struct Question
{
    Q_GADGET
public:
    QString m_question;
    QString m_ans1, m_ans2, m_ans3, m_ans4;
    QString m_img;
    Q_PROPERTY(QString question MEMBER m_question)
    Q_PROPERTY(QString ans1 MEMBER m_ans1)
    Q_PROPERTY(QString ans2 MEMBER m_ans2)
    Q_PROPERTY(QString ans3 MEMBER m_ans3)
    Q_PROPERTY(QString ans4 MEMBER m_ans4)
    Q_PROPERTY(QString img MEMBER m_img)
};

/* TriviaController
 *
 * This class is the controller class for the Trivia game. It is instantiated as an object in the QML file for the game and used in the QML.
 * Anything more than basic ui logic is located here. Specifically, this class loads the trivia question data from the filesystem, and
 * it contains methods that can be used within QML to obtain that question data in random order.
 */
class TriviaController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    TriviaController();
    Q_INVOKABLE Question getQuestion(); // retrieves the current question stored in currentQuestion
    Q_INVOKABLE void randQuestion(); // gets the next random question and stores in currentQuestion

private:
    const string questionPath = "./gamefiles/trivia/triviaquestions.txt";
    const string imgPath = "./gamefiles/trivia/images/";
    vector<Question> questionVec; // vector containing the question structs, to be populated by loadQuestions
    vector<int> questionNums;
    Question currentQuestion;
};

#endif // TRIVIACONTROLLER_H
