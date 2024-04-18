/*
    bgwidget.h

    Class declaration for bgWidget.
*/

#ifndef BGWIDGET_H
#define BGWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include "imgqueue.h"

/*
    bgWidget class

    This is a custom implementation of the QOpenGLWidget. QOpenGLWidget is a generic widget (so, doesn't come with any specialized features like a label, button etc would)
    that provides GPU acceleration through openGL for everything drawn on it. This is naturally useful for drawing a fancy scrolling background animation on, because
    it offloads some of that animation work from the CPU to the GPU, making it more efficient. This custom widget specifically includes the code to draw said background
    animation onto itself. It just needs to be added to the window and a QTimer object needs to be connected to the animate() slot in order to run the animation. This is done
    in mainwindow class (see initbg() in mainwindow.cpp).
 */
class bgWidget : public QOpenGLWidget
{
public:
    /*
        Constructor for bgWidget.
    */
    bgWidget(QWidget*);

    /*
        Destructor for bgWidget.
    */
    ~bgWidget();

    /*
        Setter for frameInterval.
        This MUST be used to set the same interval value as the timer that is connected to this object.
        TODO: Find a better way to enforce frameInterval being set to the same value as the interval of the timer connected to this object.

        int ms: Milliseconds value to set
    */
    void setFrameInterval(int ms);

public slots:

    /*
        Slot function that is called to trigger the drawing of a new frame.
    */
    void animate();

protected:

    /*
        Runs the paint operations for the current frame.

        QPaintEvent* event: Contains event parameters (required to be present by Qt).
    */
    void paintEvent(QPaintEvent* event) override;

private:

    // The duration (in seconds) of the loop.
    const int LOOP_SECONDS;

    // The duration in milliseconds of the loop (calculated from LOOP_SECONDS).
    const int LOOP_MS;

    // The amount of times the gradient will repeat in one loop of the animation. Affects the speed of the gradient scroll.
    const int GRADIENT_LOOPS;

    // Tracks how many milliseconds have passed since the last loop reset.
    int elapsed = 0;

    // The interval (in milliseconds) between frame repaints.
    int frameInterval = 17;

    // Contains QPixmaps containing all the images to use for the background.
    std::vector<QPixmap> pictures =
        {QPixmap(":/menu/menufiles/projecticons/controller1.png"),
         QPixmap(":/menu/menufiles/projecticons/controller3.png"),
         QPixmap(":/menu/menufiles/projecticons/aroo1.png"),
         QPixmap(":/menu/menufiles/projecticons/z4.png"),
         QPixmap(":/menu/menufiles/projecticons/roo1.png"),
         QPixmap(":/menu/menufiles/projecticons/zippy2.png"),
         QPixmap(":/menu/menufiles/projecticons/seal1.png")};

    // Queue that contains the images to be painted on the background.
    imgQueue queue = imgQueue(pictures);

    /*
        Paints the gradient onto the background.

        QPainter& painter: Painter object that is currently painting the background.
    */
    void paintGradient(QPainter& painter);

    /*
        Paints the images onto the background.

        QPainter& painter: Painter object that is currently painting the background.
    */
    void paintImages(QPainter& painter);

    /*
        Sets the colors of the gradient to be used on the background.
        Colors are evenly spread out.

        QLinearGradient& gradient: Gradient object
        const QColor colors[]: Array of QColors containing the colors to be used on the background (can be any size).
        int size: Size of colors[].
    */
    void setGradientColors(QLinearGradient& gradient, const QColor colors[], int size);
};

#endif // BGWIDGET_H
