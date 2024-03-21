#ifndef CLIPARSER_H
#define CLIPARSER_H

#include <optional>
#include <QString>

namespace CliParser
{
// -p argument
// get the path if specified by the user
// will return "." if no path is specified or path is invalid
QString getPath();

// -w argument
// get whether the user has specified to use pop out windows for the games
bool getWindow();
}

#endif // CLIPARSER_H
