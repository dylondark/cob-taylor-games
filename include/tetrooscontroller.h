#ifndef TETROOSCONTROLLER_H
#define TETROOSCONTROLLER_H

#include <QObject>
#include <QQmlEngine>

class TetroosController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TetroosController(QObject *parent = nullptr);

signals:
};

#endif // TETROOSCONTROLLER_H
