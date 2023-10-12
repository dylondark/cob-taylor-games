#include "bgwidget.h"
#include <QPainter>

bgWidget::bgWidget(QWidget* parent) : QOpenGLWidget(parent)
{

}

bgWidget::~bgWidget()
{

}

void bgWidget::animate() // called by bgUpdate timer in mainwindow ctor
{
    update(); // this will call paintEvent to update the frame
}

void bgWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QLinearGradient bgGrad(500, 500, 1000, 1000);
    bgGrad.setSpread(QGradient::ReflectSpread);
    bgGrad.setColorAt(0, QColor(86, 136, 255)); // blue
    bgGrad.setColorAt(1, QColor(255, 177, 86)); // gold

    painter.fillRect(rect(), bgGrad);
}
