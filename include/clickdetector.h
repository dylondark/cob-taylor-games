#ifndef CLICKDETECTOR_H
#define CLICKDETECTOR_H

#include <QObject>

class ClickDetector : public QObject
{
    Q_OBJECT
public:
    ClickDetector();

signals:
    void clickDetected();

protected:
    bool eventFilter(QObject*, QEvent*) override;
};

#endif // CLICKDETECTOR_H
