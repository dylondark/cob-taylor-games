#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <QIcon>
#include <QListWidget>
#include "leaderboardtools.h"
#include <QScrollBar>
#include <QShortcut>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initbg();
    initLeaderboard();
    initDebug();

    // install close shortcut ctrl+q
    QShortcut* closeShortcut = new QShortcut(QKeySequence("ctrl+q"), this);
    connect(closeShortcut, &QShortcut::activated, this, &MainWindow::closeKeyDetected);
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
    setBtnIcon(ui->btnGame1, ":/menu/Logos-Buttons/trivia.png");
    setBtnIcon(ui->btnGame2, ":/menu/Logos-Buttons/GuessTheLogoNEW.png");
    setBtnIcon(ui->btnGame3, ":/menu/Logos-Buttons/ComingSoon2.png");
    setBtnIcon(ui->btnGame4, ":/menu/Logos-Buttons/ComingSoon2.png");
    setBtnIcon(ui->btnGame5, ":/menu/Logos-Buttons/ComingSoon2.png");
    setBtnIcon(ui->btnGame6, ":/menu/Logos-Buttons/ComingSoon2.png");

    scaleMenu(wh[1]);
    scaleLeaderboard(wh[1]);

    ui->lblDebug->setGeometry(5, wh[1] - 20, wh[0], ui->lblDebug->height());
    ui->lblDebug->update(wh);
}

void MainWindow::setBtnIcon(QPushButton* btn, std::string iconpath)
{
    btn->setIcon(QIcon(QPixmap(iconpath.c_str()).scaled(btn->width(), btn->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btn->setIconSize(btn->size());
}

void MainWindow::scaleMenu(int height)
{
    // calculate scaling values
    const int borderWidth = 12 * ((double)height / targetH), curveWidth = 72 * ((double)height / targetH);

    QString sheet("QFrame#canvas { background-color: rgba(0, 0, 0, 0); } QPushButton, QFrame#lbFrame { border: ");
    sheet.append(std::to_string(borderWidth));
    sheet.append("px solid black; border-radius: ");
    sheet.append(std::to_string(curveWidth));
    sheet.append("px; background-color: rgba(255, 255, 255, 150);}");

    // apply to canvas
    ui->canvas->setStyleSheet(sheet);

    // apply to leaderboard spacers
    ui->lbHorSpacer1->setMinimumWidth(borderWidth);
    ui->lbHorSpacer2->setMinimumWidth(borderWidth);
    ui->lbHorSpacer3->setMinimumWidth(borderWidth);
    ui->lbHorSpacer4->setMinimumWidth(borderWidth);
    ui->lbHorSpacer5->setMinimumWidth(borderWidth);
    ui->lbVerSpacer1->setMinimumHeight(borderWidth);
    ui->lbVerSpacer2->setMinimumHeight(borderWidth);
}

void MainWindow::initLeaderboard()
{
    // init leaderboardhandler
    lbHandler = new LeaderboardHandler(ui->lbValues);

    // fill lbPages
    lbPages.insert(lbPages.end(), {ui->lbPage1, ui->lbPage2, ui->lbPage3, ui->lbPage4, ui->lbPage5, ui->lbPage6});

    // create timer to switch leaderboard pages
    lbSwitchTimer = new QTimer(this);
    connect(lbSwitchTimer, &QTimer::timeout, this, &MainWindow::switchLB);
    lbSwitchTimer->start(lbSwitchInterval * 1000);

    // set layout for lbframe
    ui->lbFrame->setLayout(ui->lbVertLayout);

    // get the font for lbGame1 set in the designer
    lbFont = ui->lbGame1->font();

    // switch leaderboard to page 1
    setActiveLBButton(ui->lbGame1);

    // init click detection
    lbDetector = new ClickDetector();
    connect(lbDetector, &ClickDetector::clickDetected, this, &MainWindow::lbClicked);
    QPushButton* lbButtons[] = {ui->lbGame1, ui->lbGame2, ui->lbGame3, ui->lbGame4, ui->lbGame5, ui->lbGame6};
    // add detector to all buttons
    for (auto button : lbButtons)
        button->installEventFilter(lbDetector);
    // add detector to lbframe
    ui->lbFrame->installEventFilter(lbDetector);

    // set the layouts for the leaderboard pages and add listwidgets
    for (auto page : lbPages)
    {
        // set layout and add widget in the layout
        page->setLayout(new QHBoxLayout());
        QListWidget* newList1 = new QListWidget();
        page->layout()->addWidget(newList1);
        QListWidget* newList2 = new QListWidget();
        page->layout()->addWidget(newList2);
        QListWidget* newList3 = new QListWidget();
        page->layout()->addWidget(newList3);
        // click detection
        connect(newList1, &QListWidget::itemPressed, this, &MainWindow::lbClicked);
        newList1->verticalScrollBar()->installEventFilter(lbDetector);
        connect(newList2, &QListWidget::itemPressed, this, &MainWindow::lbClicked);
        newList2->verticalScrollBar()->installEventFilter(lbDetector);
        connect(newList3, &QListWidget::itemPressed, this, &MainWindow::lbClicked);
        newList3->verticalScrollBar()->installEventFilter(lbDetector);
    }

    // load and display!
    lbHandler->loadScores();
    lbHandler->refreshlb();
}

void MainWindow::scaleLeaderboard(int height)
{
    // number of times i have wasted hours trying to solve a problem in this particular function because i overlooked something extremely simple: 2

    // calculate scaling values
    const int iconSize = 90 * ((double)height / targetH), fontSize = iconSize / 2, scrollSize = iconSize; // I HATE INTEGER DIVISION I HATE INTEGER DIVISION
    // assemble font stylesheet str
    QString fontSheet("\n QListWidget, QPushButton { font: "); // widget classes have to be specified manually because they just couldnt make it easy and let you exclude widgets from a class
    fontSheet.append(std::to_string(fontSize));
    fontSheet.append("px; } \n");
    // title font needs to be larger from the rest and bold
    QString titleSheet("\n QLabel#lbLabel  { font: 700 "); // 700 means bold i guess?
    titleSheet.append(std::to_string(fontSize * 2));
    titleSheet.append("px; } \n");
    QString buttonSheet("\n QPushButton {	background-color: transparent;	border-width: 0px;	border-radius: 0px; } \n");
    QString scrollSheet("\n QScrollBar { width: ");
    scrollSheet.append(std::to_string(scrollSize));
    scrollSheet.append("px; } \n");

    ui->lbFrame->setStyleSheet(titleSheet + fontSheet + buttonSheet + scrollSheet);
    // TODO: try to make scroll icons larger

    // scale leaderboard icons
    for (auto page : lbPages)
    {
        ((QListWidget*)page->children()[1])->setIconSize(QSize(iconSize, iconSize));
        ((QListWidget*)page->children()[2])->setIconSize(QSize(iconSize, iconSize));
        ((QListWidget*)page->children()[3])->setIconSize(QSize(iconSize, iconSize));
    }
}

// debug label init operations
void MainWindow::initDebug()
{
    // install a clickdetector to title for activating the debug label
    ClickDetector* titleDetector = new ClickDetector;
    ui->lblTitle->installEventFilter(titleDetector);
    connect(titleDetector, &ClickDetector::clickDetected, this, &MainWindow::titleClicked);

    // title click timer
    titleClickTimer = new QTimer(this);
    titleClickTimer->setSingleShot(true);
    connect(titleClickTimer, &QTimer::timeout, this, &MainWindow::titleClickTimeout);
    ui->lblDebug->hide(); // hide the debug label by default
}

// background widget init operations
void MainWindow::initbg()
{
    // send background to back
    ui->background->lower();

    // create timer that will update the background object
    QTimer *bgUpdate = new QTimer(this);
    bgUpdate->setTimerType(Qt::PreciseTimer); // precise timer could potentially improve frametimes
    connect(bgUpdate, &QTimer::timeout, ui->background, &bgWidget::animate);
    const int FPS = 60; // how many times to update the background per second
    bgUpdate->start(1000 / FPS); // this takes milliseconds per frame
    ui->background->setFrameInterval(1000 / FPS); // its important that this is set with the same value as the timer. see paintEvent() in bgwidget.cpp for explanation
}

// ua trivia
void MainWindow::on_lbGame1_pressed()
{
    ui->lbValues->setCurrentIndex(0);
    setActiveLBButton(ui->lbGame1);
    returnLBPagesToTop();
}

// guess the logo
void MainWindow::on_lbGame2_pressed()
{
    ui->lbValues->setCurrentIndex(1);
    setActiveLBButton(ui->lbGame2);
    returnLBPagesToTop();
}

// checkers
void MainWindow::on_lbGame3_pressed()
{
    ui->lbValues->setCurrentIndex(2);

    setActiveLBButton(ui->lbGame3);
    returnLBPagesToTop();
}

// zippy hopper
void MainWindow::on_lbGame4_pressed()
{
    ui->lbValues->setCurrentIndex(3);
    setActiveLBButton(ui->lbGame4);
    returnLBPagesToTop();
}

// pong
void MainWindow::on_lbGame5_pressed()
{
    ui->lbValues->setCurrentIndex(4);
    setActiveLBButton(ui->lbGame5);
    returnLBPagesToTop();
}

// tetris
void MainWindow::on_lbGame6_pressed()
{
    ui->lbValues->setCurrentIndex(5);
    setActiveLBButton(ui->lbGame6);
    returnLBPagesToTop();
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

void MainWindow::returnLBPagesToTop()
{
    for (auto page : lbPages)
    {
        QListWidget* listwidget = (QListWidget*)(page->children()[1]);
        listwidget->scrollToItem(listwidget->item(0));
    }
}

void MainWindow::switchLB()
{
    lbSwitchTimer->setInterval(lbSwitchInterval * 1000);

    // wouldve liked to do this with a for loop and a function ptr array but c++ was like nah bro
    switch (ui->lbValues->currentIndex())
    {
    case 0:
        on_lbGame2_pressed();
        break;
    case 1:
        on_lbGame3_pressed();
        break;
    case 2:
        on_lbGame4_pressed();
        break;
    case 3:
        on_lbGame5_pressed();
        break;
    case 4:
        on_lbGame6_pressed();
        break;
    case 5:
        on_lbGame1_pressed();
        break;
    }
}

void MainWindow::lbClicked()
{
    lbSwitchTimer->stop();
    lbSwitchTimer->start(lbSwitchInterval * 2000); // wait double the interval before resuming
}

void MainWindow::titleClicked()
{
    titleClickTimer->stop();
    titleClickTimer->start(2000); // 2 seconds for click timeout
    titleClicks++;
}

void MainWindow::titleClickTimeout()
{
    if (titleClicks >= 5)
    {
        // toggle the debug label
        ui->lblDebug->isHidden() ? ui->lblDebug->show() : ui->lblDebug->hide();
    }
    titleClicks = 0;
}

void MainWindow::closeKeyDetected()
{
    this->close();
}
