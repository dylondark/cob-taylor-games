/*
    cliparser.cpp

    Handles terminal interactions with the software, specifically retrieving paths
    or windows popping out.
*/

#include "cliparser.h"
#include <QApplication>
#include <QDir>
#include <QString>

/*
    "-p" argument,
    Get the path if specified by the user--
    will return "." if no path is specified or path is invalid.
*/
QString CliParser::getPath()
{
    QString path;
    for(int i =0; i < QApplication::arguments().length(); ++i)
    {
        if(QApplication::arguments().at(i)=="-p" && i + 1 < QApplication::arguments().length())
        {
            // Extract the next argument as the path
            path = QApplication::arguments().at(i+1);
            QDir dir(path);

            // Check if the directory exists
            if(dir.exists())
            {
                return path; // Path is valid.
            }
        }
    }

    // If -p is never found or the path isn't valid, then
    path = QCoreApplication::applicationDirPath();
    return path; // return path of executable
}

/*
    "-w" argument,
    Get whether the user has specified to use pop out windows for the games.
*/
bool CliParser::getWindow()
{
    for(int i =0; i < QApplication::arguments().length(); ++i)
    {
        if (QApplication::arguments().at(i) == "-w")
        {
            return true;
        }
    }
    return false;
}
