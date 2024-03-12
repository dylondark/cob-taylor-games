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
   FeedbackController();
    Q_INVOKABLE void submit(QString currentGame, QString submitText, QString playerName);

private:
    string filepath = ".";
    const string FILENAME = "/feedback.txt";

};

#endif // FEEDBACKCONTROLLER_H
