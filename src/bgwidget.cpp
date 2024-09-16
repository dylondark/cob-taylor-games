/*
    bgwidget.cpp

    Class definition for bgWidget.
*/

#include "bgwidget.h"
#include <QPainter>
#include "cliparser.h"

/*
    Constructor for bgWidget.
*/
bgWidget::bgWidget(QWidget* parent)
    : QOpenGLWidget(parent), filepath(CliParser::getPath()), LOOP_SECONDS(60), LOOP_MS(LOOP_SECONDS * 1000), GRADIENT_LOOPS(2)
{

}

/*
    Destructor for bgWidget.
*/
bgWidget::~bgWidget()
{

}

/*
    Setter for frameInterval.
    This MUST be used to set the same interval value as the timer that is connected to this object.
    TODO: Find a better way to enforce frameInterval being set to the same value as the interval of the timer connected to this object.

    int ms: Milliseconds value to set
*/
void bgWidget::setFrameInterval(int ms)
{
    frameInterval = ms;
}

/*
    Slot function that is called to trigger the drawing of a new frame.
*/
void bgWidget::animate()
{
    repaint(); // This will call paintEvent to update the frame
}

/*
    Runs the paint operations for the current frame.

    QPaintEvent* event: Contains event parameters (required to be present by Qt).
*/
void bgWidget::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    /*
        This block of code as well as frameInterval exists in order to (ideally) decouple the speed of the animation from the framerate.
        The state of the animation will be determined by the state of elapsed.
        Elapsed should track how many milliseconds have passed since the last loop reset,
        and it will be reset every time it exceeds the time limit for the loop specified in LOOP_SECONDS.
        If frameInterval is the same as the interval period specified in the timer that calls this function,
        then the speed of the animation should never change when you change the framerate/timer interval.
        Although this can break down if you set the framerate too high/the interval too low due to the precision of timers being inconsistent at really low intervals.
        60fps is probably the highest you would ever need and it works fine, at least on Linux.
    */
    elapsed += frameInterval;
    // Reset elapsed when it has exceeded the time limit specified in LOOP_SECONDS
    if (elapsed >= LOOP_MS)
        elapsed = 0;

    // Set up the painter object (this will paint the animation onto the widget)
    static QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing); // Use antialiasing if possible

    // Run paint operations
    paintGradient(painter);
    paintImages(painter);

    // Stop painting
    painter.end();
}

/*
    Paints the gradient onto the background.

    QPainter& painter: Painter object that is currently painting the background.
*/
void bgWidget::paintGradient(QPainter& painter)
{
    /*
        We want to go from the top left corner (0,0) down to the bottom right corner (this.height(), this.height()) multiple times per loop.
        We are only using the height of the widget because we are constrained by height and using width could change the angle of the gradient.
        The elapsed variable will determine where in this range we want to place the gradient on the current frame.
    */
    static const int GRADIENT_LOOP_MS = LOOP_MS / GRADIENT_LOOPS; // The millisecond limit for one loop of the gradient
    const double PERCENT_ELAPSED = (double)elapsed / ((double)GRADIENT_LOOP_MS); // Elapsed becomes a percentage of GRADIENT_LOOP_MS
    // If/when elapsed becomes greater than GRADIENT_LOOP_MS it will go over 100% and get set to a pos off screen which will still reflect and look proper
    const int POS = (((double)height() * 2) * PERCENT_ELAPSED) + 0.5; // Add 0.5 for accurate rounding (otherwise compiler will round down)

    // Set up the gradient
    QLinearGradient bgGrad(POS, POS, POS + height(), POS + height());
    bgGrad.setSpread(QGradient::ReflectSpread);
    // Define colors for the gradient in this array
    static const QColor COLORS[] = {QColor(0x3f51b1), QColor(0x5a55ae), QColor(0x7b5fac), QColor(0x8f6aae), QColor(0xa86aa4), QColor(0xcc6b8e), QColor(0xf18271), QColor(0xf3a469), QColor(0xf7c978)};
    setGradientColors(bgGrad, COLORS, sizeof(COLORS) / sizeof(COLORS[0]));

    // Paint gradient onto the widget
    painter.fillRect(rect(), bgGrad);
}

/*
    Paints the images onto the background.

    QPainter& painter: Painter object that is currently painting the background.
*/
void bgWidget::paintImages(QPainter& painter)
{
    // Calculate dimensions of image and pass value to the queue object (the queue needs to know the dimensions for proper scaling)
    const int IMAGE_DIM = height() / 30; // Width and height of the images, must scale with screen size
    queue.imageDim = IMAGE_DIM; // Ensure new images in the queue will scale to this size as well

    // Get queue length and calculate range
    static const int QUEUE_LENGTH = queue.getLength();
    const int RANGE = ((double)height() + IMAGE_DIM) / QUEUE_LENGTH + 0.5; // This is the distance that each individual image will travel on the background

    // Calculate percentage
    const double PERCENT_ELAPSED = std::fmod(((double)elapsed / ((double)LOOP_MS / QUEUE_LENGTH)), 1); // Percentage needs to go from 0 to 1 length times
    static double lastElapsed = 0.0; // Save the PERCENT_ELAPSED from the last time this function was ran

    // Calculate image position
    const int POS = (RANGE * PERCENT_ELAPSED) - IMAGE_DIM + 0.5; // Current positon to draw the image (before offsets)

    // How many "rows" of images will be drawn
    static const int IMAGE_ROWS = 9;

    // Shift when the last element has moved offscreen
    // We detect this by checking if PERCENT_ELAPSED is less than it was the last time this func was called
    if (PERCENT_ELAPSED < lastElapsed)
        queue.shift();
    lastElapsed = PERCENT_ELAPSED;

    // Loop through the rows
    int offset;
    for (int x = 0; x < IMAGE_ROWS; x++)
    {
        // Calculate the offset for the current row
        offset = (((width() * 3) / IMAGE_ROWS) * x) - (width() * 2); // Draw lines from -(width() * 2) to width()

        // Paint the images in the row
        for (int y = 0; y < QUEUE_LENGTH; y++)
            painter.drawPixmap(POS + (y * RANGE) + offset, POS + (y * RANGE), IMAGE_DIM, IMAGE_DIM, queue.next()); // Paint the current image
    }
}

/*
    Sets the colors of the gradient to be used on the background.
    Colors are evenly spread out.

    QLinearGradient& gradient: Gradient object
    const QColor colors[]: Array of QColors containing the colors to be used on the background (can be any size).
    int size: Size of colors[].
*/
void bgWidget::setGradientColors(QLinearGradient& gradient, const QColor colors[], int size)
{
    // Index of the current color in the array
    int index = 0;

    // Calculate the interval between colors
    const double INTERVAL = (1.0 / (size - 1));

    // Apply gradient colors
    for (double count = 0.0; count <= 1.0; count += INTERVAL)
        gradient.setColorAt(count, colors[index++]);
}
