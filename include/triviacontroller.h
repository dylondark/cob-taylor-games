#ifndef TRIVIACONTROLLER_H
#define TRIVIACONTROLLER_H

#include <QObject>

// documentation for using c++ with QML can be found at
// https://doc.qt.io/qt-6/qtqml-cppintegration-contextproperties.html

class TriviaController : public QObject
{
    Q_OBJECT
public:
    TriviaController();
};

#endif // TRIVIACONTROLLER_H
