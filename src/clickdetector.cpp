#include "clickdetector.h"
#include <QEvent>

ClickDetector::ClickDetector() {}

bool ClickDetector::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
        emit clickDetected();

    return QObject::eventFilter(obj, event); // pass the event to the original obj
}
