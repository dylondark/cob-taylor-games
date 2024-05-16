/*
    profanitychecker.h

    Class declaration for profanitychecker.
 */

#ifndef PROFANITYCHECKER_H
#define PROFANITYCHECKER_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <vector>
#include <string>

/*
    ProfanityChecker class

    It’s an object that takes a player’s name and checks it against a list of bad words, and then returns whether it’s good or not.
 */
class ProfanityChecker : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:

    /*
        Constructor for ProfanityChecker.
     */
    ProfanityChecker();

    /*
        Returns true if word is good, false if word is bad.

        QString word: word to check.
    */
    Q_INVOKABLE bool check(QString word);

private:

    // Stores the profane words to check against
    std::vector<QString> words;

    // Path of the game folder
    std::string filepath = ".";

    // Path to the database file
    const std::string FILENAME = "/profanitycheck/profanitywords.txt";
};

#endif // PROFANITYCHECKER_H
