#ifndef DEBUGLABEL_H
#define DEBUGLABEL_H

#include <QLabel>
#include <QObject>
#include <QString>

class DebugLabel : public QLabel
{
    Q_OBJECT
public:
    DebugLabel();

public slots:
    void update();
};

#endif // DEBUGLABEL_H
