/*
    clickdetector.cpp

    Class definition for clickdetector.
 */

#include "clickdetector.h"
#include <QEvent>

/*
    Constructor for ClickDetector.
 */
ClickDetector::ClickDetector()
{

}

/*
    Detects a click on object.

    QObject* obj: Object that click dectector.
    QEvent* event: Click event.
 */
bool ClickDetector::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
        emit clickDetected();

    return QObject::eventFilter(obj, event); // pass the event to the original obj
}
