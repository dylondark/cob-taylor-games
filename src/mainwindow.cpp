#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QPixmap>
#include <QIcon>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lbHandler = new LeaderboardHandler(ui->lbValues); // init lbhandler
    ui->background->lower(); // send background to back
    lbFont = ui->lbGame1->font(); // get the font for lbGame1 set in the designer
    setActiveLBButton(ui->lbGame1);

    // create timer that will update the background object
    QTimer *bgUpdate = new QTimer(this);
    bgUpdate->setTimerType(Qt::PreciseTimer); // precise timer could potentially improve frametimes
    connect(bgUpdate, &QTimer::timeout, ui->background, &bgWidget::animate);
    const int FPS = 60; // how many times to update the background per second
    bgUpdate->start(1000 / FPS); // this takes milliseconds per frame
    ui->background->setFrameInterval(1000 / FPS); // its important that this is set with the same value as the timer. see paintEvent() in bgwidget.cpp for explanation

    ui->lbFrame->setLayout(ui->lbVertLayout);

    initLeaderboard();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete lbHandler;
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
        ui->canvas->setFixedSize(wh[1] * _9BY16, wh[1]);
    }
    else
    {
        // aspect is narrower than 9:16
        ui->canvas->setFixedSize(wh[0], wh[0] / _9BY16);
    }
    // center widget
    ui->canvas->move((wh[0] / 2) - (ui->canvas->width() / 2), (wh[1] / 2) - (ui->canvas->height() / 2));
    // set layout to same size as frame
    ui->verticalLayoutWidget->setGeometry(0, 0, ui->canvas->width(), ui->canvas->height());
    // set background over entire window
    ui->background->setGeometry(0, 0, wh[0], wh[1]);

    // scale and reapply title image
    ui->lblTitle->setPixmap(QPixmap(":/menu/Logos-Buttons/title.png").scaled(ui->lblTitle->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // apply button images
    // trivia
    ui->btnGame1->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/trivia.png").scaled(ui->btnGame1->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame1->setIconSize(ui->btnGame1->size());
    // guess the logo
    ui->btnGame2->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/guessthelogo.png").scaled(ui->btnGame2->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame2->setIconSize(ui->btnGame2->size());
    // coming soon
    ui->btnGame3->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/comingsoon.png").scaled(ui->btnGame3->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame3->setIconSize(ui->btnGame3->size());
    ui->btnGame4->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/comingsoon.png").scaled(ui->btnGame4->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame4->setIconSize(ui->btnGame4->size());
    ui->btnGame5->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/comingsoon.png").scaled(ui->btnGame5->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame5->setIconSize(ui->btnGame5->size());
    ui->btnGame6->setIcon(QIcon(QPixmap(":/menu/Logos-Buttons/comingsoon.png").scaled(ui->btnGame6->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    ui->btnGame6->setIconSize(ui->btnGame6->size());
}

void MainWindow::initLeaderboard()
{
    QWidget* pages[] = {ui->lbPage1, ui->lbPage2, ui->lbPage3, ui->lbPage4, ui->lbPage5, ui->lbPage6};

    // set the layouts for the leaderboard pages and add listwidgets
    for (auto page : pages)
    {
        // set layout and add widget in the layout
        page->setLayout(new QVBoxLayout());
        page->layout()->addWidget(new QListWidget());
        // set properties for the widget
        ((QListWidget*)page->children()[1])->setIconSize(QSize(100, 100));
        ((QListWidget*)page->children()[1])->setStyleSheet("font: 50px;");
        // add test item
        ((QListWidget*)page->children()[1])->addItem(new QListWidgetItem(QIcon(QString(":/background/projecticons/roo1.png")), page->objectName()));
    }
}

// ua trivia
void MainWindow::on_lbGame1_pressed()
{
    ui->lbValues->setCurrentIndex(0);
    setActiveLBButton(ui->lbGame1);
}

// guess the logo
void MainWindow::on_lbGame2_pressed()
{
    ui->lbValues->setCurrentIndex(1);
    setActiveLBButton(ui->lbGame2);
}

// checkers
void MainWindow::on_lbGame3_pressed()
{
    ui->lbValues->setCurrentIndex(2);
    setActiveLBButton(ui->lbGame3);
}

// zippy hopper
void MainWindow::on_lbGame4_pressed()
{
    ui->lbValues->setCurrentIndex(3);
    setActiveLBButton(ui->lbGame4);
}

// pong
void MainWindow::on_lbGame5_pressed()
{
    ui->lbValues->setCurrentIndex(4);
    setActiveLBButton(ui->lbGame5);
}

// tetris
void MainWindow::on_lbGame6_pressed()
{
    ui->lbValues->setCurrentIndex(5);
    setActiveLBButton(ui->lbGame6);
}

// sets bold and underline for only the specified button, removes for any others
void MainWindow::setActiveLBButton(QPushButton* btn)
{
    // apply to all buttons
    ui->lbGame1->setFont(lbFont);
    ui->lbGame2->setFont(lbFont);
    ui->lbGame3->setFont(lbFont);
    ui->lbGame4->setFont(lbFont);
    ui->lbGame5->setFont(lbFont);
    ui->lbGame6->setFont(lbFont);

    // apply underline and bold and set to specified button
    QFont activeFont = lbFont;
    activeFont.setBold(true);
    activeFont.setUnderline(true);
    btn->setFont(activeFont);
}
