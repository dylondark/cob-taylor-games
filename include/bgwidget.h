#ifndef BGWIDGET_H
#define BGWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include "imgqueue.h"

class bgWidget : public QOpenGLWidget
{

public:
    bgWidget(QWidget*);
    ~bgWidget();
    void setFrameInterval(int);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int elapsed = 0;
    int frameInterval = 17; // this value should be the same as the interval (in milliseconds) of the timer (bgUpdate in mainwindow) that is repainting this object
    const int LOOP_SECONDS; // the duration in seconds of the loop
    const int LOOP_MS; // the duration in milliseconds of the loop (calculated from LOOP_SECONDS)
    const int GRADIENT_LOOPS; // the amount of times the gradient will repeat in one loop of the animation. affects the speed of the gradient scroll
    void paintGradient(QPainter&);
    void paintImages(QPainter&);
    void setGradientColors(QLinearGradient&, const QColor[], int);
    std::vector<QPixmap> pictures = // contains qpixmaps containing all the images to use for the background
        {QPixmap(":/background/projecticons/controller1.png"),
        QPixmap(":/background/projecticons/controller3.png"),
        QPixmap(":/background/projecticons/aroo1.png"),
        QPixmap(":/background/projecticons/z4.png"),
        QPixmap(":/background/projecticons/roo1.png"),
        QPixmap(":/background/projecticons/zippy2.png"),
        QPixmap(":/background/projecticons/seal1.png")};
    imgQueue queue = imgQueue(pictures);
};

#endif // BGWIDGET_H
