#ifndef PROFANITYCHECKER_H
#define PROFANITYCHECKER_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml/qqmlregistration.h>
#include <vector>
#include <string>

class ProfanityChecker : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    ProfanityChecker();
    Q_INVOKABLE bool check(QString word);

private:
    std::vector<QString> words;
    std::string filepath = ".";
    const std::string FILENAME = "/profanitycheck/profanitywords.txt";
};

#endif // PROFANITYCHECKER_H
