#ifndef BGWIDGET_H
#define BGWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include "imgqueue.h"


/* bgWidget class
 *
 * This is a custom implementation of the QOpenGLWidget. QOpenGLWidget is a generic widget (so, doesn't come with any specialized features like a label, button etc would)
 * that provides GPU acceleration through openGL for everything drawn on it. This is naturally useful for drawing a fancy scrolling background animation on, because
 * it offloads some of that animation work from the CPU to the GPU, making it more efficient. This custom widget specifically includes the code to draw said background
 * animation onto itself. It just needs to be added to the window and a QTimer object needs to be connected to the animate() slot in order to run the animation. This is done
 * in mainwindow class (see initbg() in mainwindow.cpp).
 */
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
