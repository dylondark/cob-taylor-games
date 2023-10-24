#include "bgwidget.h"
#include <QPainter>
#include <iostream>

bgWidget::bgWidget(QWidget* parent) : QOpenGLWidget(parent), LOOP_SECONDS(60), LOOP_MS(LOOP_SECONDS * 1000), GRADIENT_LOOPS(2)
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

    // set up the painter object (this will paint the animation onto the widget)
    static QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing); // use antialiasing if possible

    paintGradient(painter);
    paintImages(painter);

    painter.end();
}

void bgWidget::paintGradient(QPainter& painter)
{
    // we want to go from the top left corner (0,0) down to the bottom right corner (this.height(), this.height()) multiple times per loop
    // we are only using the height of the widget because we are constrained by height and using width could change the angle of the gradient
    // the elapsed variable will determine where in this range we want to place the gradient on the current frame
    static const int GRADIENT_LOOP_MS = LOOP_MS / GRADIENT_LOOPS; // the millisecond limit for one loop of the gradient
    const double PERCENT_ELAPSED = (double)elapsed / ((double)GRADIENT_LOOP_MS); // elapsed becomes a percentage of GRADIENT_LOOP_MS
    // if/when elapsed becomes greater than GRADIENT_LOOP_MS it will go over 100% and get set to a pos off screen which will still reflect and look proper
    const int POS = (((double)height() * 2) * PERCENT_ELAPSED) + 0.5; // add 0.5 for accurate rounding (otherwise compiler will round down)

    // set up the gradient
    QLinearGradient bgGrad(POS, POS, POS + height(), POS + height());
    bgGrad.setSpread(QGradient::ReflectSpread);
    // define colors for the gradient in this array
    static const QColor COLORS[] = {QColor(0x3f51b1), QColor(0x5a55ae), QColor(0x7b5fac), QColor(0x8f6aae), QColor(0xa86aa4), QColor(0xcc6b8e), QColor(0xf18271), QColor(0xf3a469), QColor(0xf7c978)};
    //static const QColor COLORS[] = {Qt::yellow, Qt::blue, Qt::red, Qt::white, Qt::green}; // good pallete for testing
    setGradientColors(bgGrad, COLORS, sizeof(COLORS) / sizeof(COLORS[0]));
    painter.fillRect(rect(), bgGrad); // paint gradient onto the widget
}

void bgWidget::paintImages(QPainter& painter)
{
    static const int IMAGE_DIM = height() / 20; // width and height of the images, must scale with screen size
    queue.imageDim = IMAGE_DIM; // ensure new images in the queue will scale to this size as well
    const int RANGE = ((double)height() + IMAGE_DIM) / queue.getLength() + 0.5; // this is the distance that each individual image will travel
    const double PERCENT_ELAPSED = std::fmod(((double)elapsed / ((double)LOOP_MS / queue.getLength())), 1); // percentage needs to go from 0 to 1 length times
    static double lastElapsed = 0.0;
    const int POS = (RANGE * PERCENT_ELAPSED) - IMAGE_DIM + 0.5;
    static const int IMAGE_ROWS = 12; // how many "rows" of images will be drawn
    // shift when the last element has moved offscreen
    // we detect this by checking if PERCENT_ELAPSED is less than it was the last time this func was called
    if (PERCENT_ELAPSED < lastElapsed)
        queue.shift();
    lastElapsed = PERCENT_ELAPSED;
    // draw each image in queue
    int offset;
    for (int x = 0; x < IMAGE_ROWS; x++)
    {
        offset = (((width() * 3) / IMAGE_ROWS) * x) - (width() * 2); // draw lines from -(width() * 2) to width()
        for (int y = 0; y < queue.getLength(); y++)
        {
            painter.drawPixmap(POS + (y * RANGE) + offset, POS + (y * RANGE), IMAGE_DIM, IMAGE_DIM, queue.next()); // paint the image
        }
    }
}

// takes a gradient byref and an array of colors and equally spaces the colors onto the gradient
void bgWidget::setGradientColors(QLinearGradient& gradient, const QColor colors[], int size)
{
    int index = 0;
    const double INTERVAL = (1.0 / (size - 1));
    for (double count = 0.0; count <= 1.0; count += INTERVAL)
        gradient.setColorAt(count, colors[index++]);
}
