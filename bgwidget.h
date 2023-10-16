#ifndef BGWIDGET_H
#define BGWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>

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
    void setGradientColors(QLinearGradient&, const QColor[], int);

};

#endif // BGWIDGET_H
