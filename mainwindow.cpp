#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// called on window resize (also at program start)
void MainWindow::resizeEvent(QResizeEvent*)
{
    // get current size of window
    int wh[2] = {this->size().width(), this->size().height()};
    // constrain by height if aspect ratio is wider than 9:16, width if narrower
    double ratio = (double)wh[0] / (double)wh[1];
    const double _9BY16 = 9.0 / 16.0; // should be 0.5625
    if (ratio >= _9BY16)
    {
        // aspect is wider or equal to 9:16
        ui->menuBox->setFixedSize(wh[1] * _9BY16, wh[1]);
    }
    else
    {
        // aspect is narrower than 9:16
        ui->menuBox->setFixedSize(wh[0], wh[0] / _9BY16);
    }
    // center widget
    ui->menuBox->move((wh[0] / 2) - (ui->menuBox->width() / 2), (wh[1] / 2) - (ui->menuBox->height() / 2));
    // set layout to same size as frame
    ui->verticalLayoutWidget->setGeometry(0, 0, ui->menuBox->width(), ui->menuBox->height());
}
