/*
    feedbackcontroller.cpp

    Class implamation for feedbackcontroller.cpp

 */

#include "feedbackcontroller.h"
#include <QApplication>
#include <QDateTime>
#include <fstream>
#include <iostream>

/*
    Constructor for FeedbackController
*/
FeedbackController::FeedbackController()
{
    // set filepath if cli argument is used
    if (QApplication::arguments().length() > 1 && QApplication::arguments().at(1) == "-p")
    {
        filepath = QApplication:: arguments().at(2).toStdString();
    }
}

/*
    Submits a feedback line and writes the file

    QString currentGame: String representation of the game
    QString submitText: Feedback submission text
    QString playerName: The player's user name
*/
void FeedbackController::submit(QString currentGame, QString submitText, QString playerName)
{
    QString line;

    // append game
    line.append(currentGame);
    line.append(", ");

    // append playername
    line.append(playerName);
    line.append(", ");

    // append time
    QDateTime currentDateTime = QDateTime::currentDateTime();
    line.append(currentDateTime.toString(Qt::TextDate));
    line.append(": ");

    // append message
    line.append(submitText);

    // open file
    std::ofstream of(filepath + FILENAME, std::ios_base::app);

    // if file failed to open
    if (!of.is_open())
    {
        std::cerr << "Feedback file failed to open!\n";
        return;
    }

    // write
    of << line.toStdString() << std::endl;

    of.close();
}
