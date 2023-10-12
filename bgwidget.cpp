#include "bgwidget.h"
#include <QPainter>
#include <iostream>

bgWidget::bgWidget(QWidget* parent) : QOpenGLWidget(parent), STATE_MS(5), LOOP_SECONDS(5), LOOP_MS(LOOP_SECONDS * 1000), GRADIENT_WIDTH(500)
{
    loopState = new QTimer(this);
    loopState->setTimerType(Qt::TimerType::PreciseTimer);
    connect(loopState, &QTimer::timeout, this, &bgWidget::updateTime);
    loopState->start(STATE_MS);
}

bgWidget::~bgWidget()
{
    delete loopState;
}

void bgWidget::animate() // called by bgUpdate timer in mainwindow ctor
{
    update(); // this will call paintEvent to update the frame
}

void bgWidget::updateTime()
{
    elapsed += STATE_MS;
    // reset elapsed when it has exceeded the time limit specified in LOOP_SECONDS
    if (elapsed >= LOOP_MS)
        elapsed = 0;
}

void bgWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // we want to go from the top left corner (0,0) down to the bottom right corner (this.height(), this.height()) twice per loop
    // we are only using the height of the widget because we are constrained by height and using width could change the angle of the gradient
    // the elapsed variable will determine where in this range we want to place the gradient on the current frame
    double percentElapsed = (double)elapsed / (double)LOOP_MS; // we do this by turning elapsed into a percentage of LOOP_MS. from 0% (0) to 100% (LOOP_MS)
    int pos = ((double)height() * percentElapsed) + 0.5; // add 0.5 for accurate rounding (otherwise compiler will round down)

    QLinearGradient bgGrad(pos, pos, pos + GRADIENT_WIDTH, pos + GRADIENT_WIDTH);
    bgGrad.setSpread(QGradient::ReflectSpread);
    bgGrad.setColorAt(0, QColor(86, 136, 255)); // blue
    bgGrad.setColorAt(1, QColor(255, 177, 86)); // gold

    painter.fillRect(rect(), bgGrad);
    painter.end();
}
