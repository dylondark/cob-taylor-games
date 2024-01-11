#ifndef TRIVIACONTROLLER_H
#define TRIVIACONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

// documentation for using c++ with QML can be found at
// https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html

using std::string;
using std::vector;
class TriviaController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    TriviaController();

private:
    struct question
    {
        string question;
        string ans1, ans2, ans3, ans4;
        string img;
    };
    const string questionPath = "./gamefiles/trivia/triviaquestions.txt";
    const string imgPath = "./gamefiles/trivia/images/";
    vector<question> questionVec; // vector containing the question structs, to be populated by loadQuestions
    question getQuestion(); // returns a random question obj with NO REPEATS. may need some fail condition if this is called when there are no original questions left
};

#endif // TRIVIACONTROLLER_H
