#ifndef DEBUGLABEL_H
#define DEBUGLABEL_H

#include <QLabel>
#include <QObject>
#include <QString>

class DebugLabel : public QLabel
{

public:
    DebugLabel(QWidget*);
    void update(int[]);
};

#endif // DEBUGLABEL_H
