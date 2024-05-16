/*
    feedbackcontroller.h

    Class declaration for feedbackcontroller.h
*/

#ifndef FEEDBACKCONTROLLER_H
#define FEEDBACKCONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>
#include <string>

using std::string;

class FeedbackController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    /*
        Constructor for FeedbackController
    */
    FeedbackController();

    /*
        Submits a feedback line and writes the file

        QString currentGame: String representation of the game
        QString submitText: Feed back submission text
        QString playerName: The player's user name
    */
    Q_INVOKABLE void submit(QString currentGame, QString submitText, QString playerName);

private:

    // Declares a variable named filepath of type string and initializes it with the value
    string filepath = ".";

    // Name of the output file
    const string FILENAME = "/feedback.txt";

};

#endif // FEEDBACKCONTROLLER_H
