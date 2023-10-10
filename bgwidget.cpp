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
    painter.fillRect(rect(), Qt::GlobalColor::blue);
}
