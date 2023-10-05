#ifndef BGWIDGET_H
#define BGWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets/QOpenGLWidget>

class bgWidget : public QOpenGLWidget
{

public:
    bgWidget();
    ~bgWidget();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int elapsed = 0;
};

#endif // BGWIDGET_H
