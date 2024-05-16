/*
    profanitychecker.cpp

    Class definition for profanitychecker.
 */

#include "profanitychecker.h"
#include <fstream>
#include <QApplication>

/*
    Constructor for Profanitychecker.
 */
ProfanityChecker::ProfanityChecker()
{
    // TODO: make this a utility function
    if (QApplication::arguments().length() > 1 && QApplication::arguments().at(1) == "-p")
        filepath = QApplication:: arguments().at(2).toStdString();

    // load file
    std::string line;
    std::ifstream fin(filepath + FILENAME);
    while (std::getline(fin, line))
        words.push_back(QString(line.c_str()).toUpper());

    fin.close();
}

/*
    Returns true if word is good, false if word is bad.

    QString word: word to check.
*/
bool ProfanityChecker::check(QString word)
{
    // remove spaces and ensure uppercase
    word = word.remove(' ');
    word = word.toUpper();

    // check the word against words array
    for (const QString& checkWord : words)
    {
        if (word.contains(checkWord))
            return false;
    }

    return true;
}
