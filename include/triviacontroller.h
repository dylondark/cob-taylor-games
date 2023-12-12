#ifndef TRIVIACONTROLLER_H
#define TRIVIACONTROLLER_H

#include <QObject>

// documentation for using c++ with QML can be found at
// https://doc.qt.io/qt-6/qtqml-cppintegration-contextproperties.html

using std::string;
using std::vector;
class TriviaController : public QObject
{
    Q_OBJECT
public:
    TriviaController();

private:
    struct question
    {
        string question;
        string ans1, ans2, ans3, ans4;
    };
    void loadQuestions(); // loads questions from the file specified by questionPath into questionVec
    const string questionPath = "./gamefiles/triviaquestions.txt";
    vector<question> questionVec; // vector containing the question structs, to be populated by loadQuestions
    question getQuestion(); // returns a random question obj with NO REPEATS. may need some fail condition if this is called when there are no original questions left
    // the following lines do the same as the lines above except for answers instead of questions
    void loadAnswers();
    const string answerPath = ""; //* TO DO: add in file path *
    vector<question> answerVec;
    question getAnswer();

};

#endif // TRIVIACONTROLLER_H
