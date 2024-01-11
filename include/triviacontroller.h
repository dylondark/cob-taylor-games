#ifndef TRIVIACONTROLLER_H
#define TRIVIACONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

// documentation for using c++ with QML can be found at
// https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html

using std::string;
using std::vector;

struct question
{
    Q_GADGET
public:
    QString m_question;
    QString m_ans1, m_ans2, m_ans3, m_ans4;
    QString m_img;
    Q_PROPERTY(QString question MEMBER m_question)
};

class TriviaController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    TriviaController();
    Q_INVOKABLE question getQuestion(); // returns a random question obj with NO REPEATS. may need some fail condition if this is called when there are no original questions left

private:
    const string questionPath = "./gamefiles/trivia/triviaquestions.txt";
    const string imgPath = "./gamefiles/trivia/images/";
    vector<question> questionVec; // vector containing the question structs, to be populated by loadQuestions
};

#endif // TRIVIACONTROLLER_H
