#include "bgwidget.h"
#include <QPainter>
#include <iostream>

bgWidget::bgWidget(QWidget* parent) : QOpenGLWidget(parent), LOOP_SECONDS(5), LOOP_MS(LOOP_SECONDS * 1000)
{

}

bgWidget::~bgWidget()
{

}

void bgWidget::setFrameInterval(int ms)
{
    frameInterval = ms;
}

void bgWidget::animate() // called by bgUpdate timer in mainwindow ctor
{
    repaint(); // this will call paintEvent to update the frame
}

void bgWidget::paintEvent(QPaintEvent *event)
{
    // this block of code as well as frameInterval exists in order to (ideally) decouple the speed of the animation from the framerate.
    // the state of the animation will be determined by the state of elapsed.
    // elapsed should track how many milliseconds have passed since the last loop reset,
    // and it will be reset every time it exceeds the time limit for the loop specified in LOOP_SECONDS.
    // if frameInterval is the same as the interval period specified in the timer that calls this function,
    // then the speed of the animation should never change when you change the framerate/timer interval.
    // although this can break down if you set the framerate too high/the interval too low due to the precision of timers being inconsistent at really low intervals.
    // 60fps is probably the highest you would ever need and it works fine, at least on linux.
    elapsed += frameInterval;
    // reset elapsed when it has exceeded the time limit specified in LOOP_SECONDS
    if (elapsed >= LOOP_MS)
        elapsed = 0;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // we want to go from the top left corner (0,0) down to the bottom right corner (this.height(), this.height()) twice per loop
    // we are only using the height of the widget because we are constrained by height and using width could change the angle of the gradient
    // the elapsed variable will determine where in this range we want to place the gradient on the current frame
    double percentElapsed = (double)elapsed / (double)LOOP_MS; // we do this by turning elapsed into a percentage of LOOP_MS. from 0% (0) to 100% (LOOP_MS)
    int pos = (((double)height() * 2) * percentElapsed) + 0.5; // add 0.5 for accurate rounding (otherwise compiler will round down)

    QLinearGradient bgGrad(pos, pos, pos + height(), pos + height());
    bgGrad.setSpread(QGradient::ReflectSpread);
    bgGrad.setColorAt(0, QColor(86, 136, 255)); // blue
    bgGrad.setColorAt(1, QColor(255, 177, 86)); // gold

    painter.fillRect(rect(), bgGrad);
    painter.end();
}
