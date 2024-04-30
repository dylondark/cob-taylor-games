/*
    clickdetector.h

    Class declaration for clickdectector.
 */

#ifndef CLICKDETECTOR_H
#define CLICKDETECTOR_H

#include <QObject>

/*
    ClickDetector class

    This class provides a way to detect if a widget has been clicked. It gets installed onto a widget with installEventFilter()
    and the clickDetected() signal can be connected to a slot to monitor clicks on that widget.
 */
class ClickDetector : public QObject
{
    Q_OBJECT

public:

    /*
        Constructor for ClickDetector.
    */
    ClickDetector();

signals:

    /*
        Call when click is detected.
     */
    void clickDetected();

protected:

    /*
        Detects a click on object.

        QObject* obj: Object that click dectector.
        QEvent* event: Click event.
    */
    bool eventFilter(QObject*, QEvent*) override;
};

#endif // CLICKDETECTOR_H
