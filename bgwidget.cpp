#include "bgwidget.h"
#include <QPainter>

bgWidget::bgWidget(QWidget* parent) : QOpenGLWidget(parent)
{

}

bgWidget::~bgWidget()
{

}

void bgWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRadialGradient bgGrad(width() / 2, height() / 2, width());
    bgGrad.setColorAt(0.0, QColor(200, 200, 200));
    bgGrad.setColorAt(1.0, QColor(100, 100, 100));

    painter.fillRect(rect(), bgGrad);
}
