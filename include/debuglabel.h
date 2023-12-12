#ifndef DEBUGLABEL_H
#define DEBUGLABEL_H

#include <QLabel>
#include <QObject>
#include <QString>

class DebugLabel : public QLabel
{

public:
    DebugLabel(QWidget*);

public slots:
    void update();
};

#endif // DEBUGLABEL_H
