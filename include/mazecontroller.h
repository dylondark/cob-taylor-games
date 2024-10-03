/*
    mazecontroller.h

    Class declaration for MazeController.
*/

#ifndef MAZECONTROLLER_H
#define MAZECONTROLLER_H

#include <QObject>
#include <QQuickPaintedItem>

class MazeController : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
public:

    /*
        Constructor for MazeController.
    */
    explicit MazeController();

    /*
        Destructor for MazeController.
    */
    ~MazeController();
};

#endif // MAZECONTROLLER_H
