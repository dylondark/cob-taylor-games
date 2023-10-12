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

public slots:
    void animate();

private slots:
    void updateTime();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int elapsed = 0;
    QTimer *loopState;
    const int STATE_MS; // how many milliseconds between updating the state of the background
    const int LOOP_SECONDS; // the duration in seconds of the loop
    const int LOOP_MS; // the duration in milliseconds of the loop (calculated from LOOP_SECONDS)
    const int GRADIENT_WIDTH; // the width in pixels of the gradient

};

#endif // BGWIDGET_H
