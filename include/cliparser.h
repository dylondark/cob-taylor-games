/*
    cliparser.h

    Header for cli parsing function declarations.
*/


#ifndef CLIPARSER_H
#define CLIPARSER_H

#include <QString>

namespace CliParser
{
/*
    "-p" argument,
    Get the path if specified by the user--
    will return "." if no path is specified or path is invalid.
*/
QString getPath();

/*
    "-w" argument, gets whether the user has specified to use pop out windows for the games.
*/
bool getWindow();
}

#endif // CLIPARSER_H
