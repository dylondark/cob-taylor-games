/*
    debuglabel.h

    Class declaration for debug label
 */

#ifndef DEBUGLABEL_H
#define DEBUGLABEL_H

#include <QLabel>
#include <QObject>
#include <QString>

/*
   DebugLabel class

   Custom implementation of a QLabel, meant to be used as a label on the main menu with a secret activation method, that displays some important system
   and program information. This could just be an ordinary label controlled with a function in mainwindow, but putting it in its own class provides
   a little bit of organization.
 */
class DebugLabel : public QLabel
{
public:

    /*
        Constructor for Debug
    */
    DebugLabel(QWidget* parent);

    /*
        Updates each element in the given integer array

        int wh[]: Window width and height
    */
    void update(int wh[]);
};

#endif // DEBUGLABEL_H
