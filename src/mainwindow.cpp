/*
    mainwindow.cpp

    Class definition for MainWindow.
*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <QIcon>
#include <QListWidget>
#include "cliparser.h"
#include "feedbackcontroller.h"
#include "guessthelogocontroller.h"
#include "profanitychecker.h"
#include "tetrooscontroller.h"
#include "pongcontroller.h"
#include <QScrollBar>
#include <QShortcut>
#include <QKeySequence>
#include <QStackedLayout>
#include <QQmlContext>
#include <QQuickView>
#include <triviacontroller.h>

/*
    Constructor for MainWindow.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , filepath(CliParser::getPath())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set default application font
    QApplication::setFont(QFont("Open Sans"));

    // init operations
    initbg();
    initLeaderboard();
    initDebug();
    initQML();

    // install close shortcut ctrl+q
    QShortcut* closeShortcut = new QShortcut(QKeySequence("ctrl+q"), this);
    connect(closeShortcut, &QShortcut::activated, this, &MainWindow::closeKeyDetected);
}

/*
    Destructor for MainWindow.
*/
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

/*
    Initialization operations for the debug label.
*/
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

/*
    Initialization operations for the leaderboard.
*/
void MainWindow::initbg()
{
    // send background to back
    ui->background->lower();

    // apply new stacking layout to background
    ui->canvas->setLayout(new QStackedLayout());

    // create timer that will update the background object
    bgUpdateTimer = new QTimer(this);
    bgUpdateTimer->setTimerType(Qt::PreciseTimer); // precise timer could potentially improve frametimes
    connect(bgUpdateTimer, &QTimer::timeout, ui->background, &bgWidget::animate);
    bgUpdateTimer->start(1000 / FPS); // this takes milliseconds per frame
    ui->background->setFrameInterval(1000 / FPS); // its important that this is set with the same value as the timer. see paintEvent() in bgwidget.cpp for explanation
}

/*
    Initialization operations for registering QML controllers.
*/
void MainWindow::initQML()
{
    // all qml controller classes must be "registered" as qml types so they can be instantiated and accessed in the qml files.
    // use "import QMLControllers"
    qmlRegisterType<TriviaController>("QMLControllers", 1, 0, "TriviaController");
    qmlRegisterType<GuessTheLogoController>("QMLControllers", 1, 0, "GuessTheLogoController");
    qmlRegisterType<TetroosController>("QMLControllers", 1, 0, "TetroosController");
    qmlRegisterType<FeedbackController>("QMLControllers", 1, 0, "FeedbackController");
    qmlRegisterType<ProfanityChecker>("QMLControllers", 1, 0, "ProfanityChecker");
    qmlRegisterType<PongController>("QMLControllers", 1, 0, "PongController");
    // all qml controllers will eventually be registered here
}

/*
    Destructor for MainWindow.
*/
MainWindow::~MainWindow()
{
    delete ui;
    delete lbHandler;
}

/*
    Called when the window is resized.
    Contains scaling operations for UI elements.

    QResizeEvent* event: Pointer to resize event generated by Qt.
*/
void MainWindow::resizeEvent([[maybe_unused]] QResizeEvent* event)
{
    // get current size of window
    int wh[2] = {this->size().width(), this->size().height()};

    // canvas scaling
    double ratio = (double)wh[0] / (double)wh[1]; // constrain by height if aspect ratio is wider than 9:16, width if narrower
    const double _9BY16 = 9.0 / 16.0; // should be 0.5625
    if (ratio >= _9BY16)
        // aspect is wider or equal to 9:16
        ui->canvas->setFixedSize(wh[1] * _9BY16, wh[1]);
    else
        // aspect is narrower than 9:16
        ui->canvas->setFixedSize(wh[0], wh[0] / _9BY16);

    // center canvas
    ui->canvas->move((wh[0] / 2) - (ui->canvas->width() / 2), (wh[1] / 2) - (ui->canvas->height() / 2));

    // set layout to same size as canvas
    ui->verticalLayoutWidget->setGeometry(0, 0, ui->canvas->width(), ui->canvas->height());

    // set background over entire window
    ui->background->setGeometry(0, 0, wh[0], wh[1]);

    // scale and reapply title image
    ui->lblTitle->setPixmap(QPixmap(filepath + "/menufiles/title_splash.png").scaled(ui->lblTitle->width(), ui->lblTitle->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // apply button images
    setBtnIcon(ui->btnGame1, QString(filepath + "/menufiles/trivia.png").toStdString());// UATrivia
    setBtnIcon(ui->btnGame2, QString(filepath + "/menufiles/GuessTheLogoNEW.png").toStdString());//GuessTheLogo
    setBtnIcon(ui->btnGame3, QString(filepath + "/menufiles/TetroosPreview.png").toStdString());//Tetroos
    setBtnIcon(ui->btnGame4, QString(filepath + "/menufiles/HopperPreview.png").toStdString()); //ZippyHop
    setBtnIcon(ui->btnGame5, QString(filepath + "/menufiles/Pong.png").toStdString());//pong
    setBtnIcon(ui->btnGame6, QString(filepath + "/menufiles/CheckersPreview.png").toStdString());//checkers

    // scale functions
    scaleMenu(wh[1]);
    scaleLeaderboard(wh[1]);

    // scale debug
    ui->lblDebug->setGeometry(5, wh[1] - 20, wh[0], ui->lblDebug->height());
    ui->lblDebug->update(wh);
}

/*
    Applies an icon to a button.

    QPushButton* btn: Pointer to button to apply image to.
    const std::string& iconpath: Path to the icon to apply to the button.
*/
void MainWindow::setBtnIcon(QPushButton* btn, const std::string& iconpath)
{
    btn->setIcon(QIcon(QPixmap(iconpath.c_str()).scaled(btn->width(), btn->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    btn->setIconSize(btn->size());
}

/*
    Contains scaling operations for the menu UI elements.
    TODO: Remove height parameter and get the height inside the function.
    TODO: Ensure that all operations dealing with menu scaling are inside this function and not resizeEvent().

    int height: Current height of the window.
*/
void MainWindow::scaleMenu(int height)
{
    // calculate scaling values
    const double hScale = ((double)height / targetH);
    const int borderWidth = 12 * hScale, curveWidth = 72 * hScale;

    // assemble stylesheets string
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

    // scale layout margins
    ui->buttonGrid->setContentsMargins(0, 40 * hScale, 0, 40 * hScale);
    ui->buttonGrid->setSpacing(60 * hScale);
    ui->menuLayout->setContentsMargins(60 * hScale, 30 * hScale, 60 * hScale, 30 * hScale);
}

/*
    Contains scaling operations for the leaderboard UI elements.
    TODO: Remove height parameter and get the height inside the function.

    int height: Current height of the window.
*/
void MainWindow::scaleLeaderboard(int height)
{
    // number of times i have wasted hours trying to solve a problem in this particular function because i overlooked something extremely simple: 2

    // calculate scaling values
    const double hScale = (double)height / targetH;
    const int iconSize = 90 * hScale, fontSize = iconSize / 2; // I HATE INTEGER DIVISION I HATE INTEGER DIVISION

    // assemble font stylesheet str
    QString fontSheet("\n QListWidget, QPushButton { font: "); // widget classes have to be specified manually because they just couldnt make it easy and let you exclude widgets from a class
    fontSheet.append(std::to_string(fontSize));
    fontSheet.append("px; } \n");

    // assemble stylesheet strings
    QString titleSheet("\n QLabel#lbLabel  { font: 700 "); // 700 means bold i guess?
    titleSheet.append(std::to_string(fontSize * 2));
    titleSheet.append("px; } \n");
    QString buttonSheet("\n QPushButton {	background-color: transparent;	border-width: 0px;	border-radius: 0px; } \n");
    QString scrollSheet("\n QScrollBar { width: 0px; }"); // hide scroll bars

    // apply the stylesheet
    ui->lbFrame->setStyleSheet(titleSheet + fontSheet + buttonSheet + scrollSheet);

    // scale leaderboard icons
    for (auto page : lbPages)
    {
        page->layout()->setContentsMargins(15 * hScale, 15 * hScale, 15 * hScale, 15 * hScale);
        ((QListWidget*)page->children()[1])->setIconSize(QSize(iconSize, iconSize));
        ((QListWidget*)page->children()[2])->setIconSize(QSize(iconSize, iconSize));
        ((QListWidget*)page->children()[3])->setIconSize(QSize(iconSize, iconSize));
    }
}

/*
    Press handler for Trivia leaderboard button.
*/
void MainWindow::on_lbGame1_pressed()
{
    ui->lbValues->setCurrentIndex(0);
    setActiveLBButton(ui->lbGame1);
    returnLBPagesToTop();
}

/*
    Press handler for GuessTheLogo leaderboard button.
*/
void MainWindow::on_lbGame2_pressed()
{
    ui->lbValues->setCurrentIndex(1);
    setActiveLBButton(ui->lbGame2);
    returnLBPagesToTop();
}

/*
    Press handler for Tetroos leaderboard button.
*/
void MainWindow::on_lbGame3_pressed()
{
    ui->lbValues->setCurrentIndex(2);
    setActiveLBButton(ui->lbGame3);
    returnLBPagesToTop();
}

/*
    Press handler for Hopper leaderboard button.
*/
void MainWindow::on_lbGame4_pressed()
{
    ui->lbValues->setCurrentIndex(3);
    setActiveLBButton(ui->lbGame4);
    returnLBPagesToTop();
}

/*
    Press handler for Pong leaderboard button.
*/
void MainWindow::on_lbGame5_pressed()
{
    ui->lbValues->setCurrentIndex(4);
    setActiveLBButton(ui->lbGame5);
    returnLBPagesToTop();
}

/*
    Press handler for Checkers leaderboard button.
*/
void MainWindow::on_lbGame6_pressed()
{
    ui->lbValues->setCurrentIndex(5);
    setActiveLBButton(ui->lbGame6);
    returnLBPagesToTop();
}

/*
    Makes UI adjustments to the leaderboard buttons to indicate that the specified button is "active".

    QPushButton* btn: Button to be set as active.
*/
void MainWindow::setActiveLBButton(QPushButton* btn)
{
    QPushButton* lbBtns[] = {ui->lbGame1, ui->lbGame2, ui->lbGame3, ui->lbGame4, ui->lbGame5, ui->lbGame6};

    // clear all buttons
    for (auto cbtn : lbBtns)
    {
        cbtn->setFont(lbFont);
        cbtn->setStyleSheet("");
    }

    // apply underline and bold and set to specified button
    QFont activeFont = lbFont;
    btn->setStyleSheet("font: bold;"); // button stylesheets must be manipulated to add bold since it doesnt work when you set it in the font for some reason
    activeFont.setUnderline(true);
    btn->setFont(activeFont);
}

/*
    Scrolls all leaderboard pages to the top.
    TODO: Remove this function since it isn't needed anymore.
*/
void MainWindow::returnLBPagesToTop()
{
    for (auto page : lbPages)
    {
        QListWidget* listwidget = (QListWidget*)(page->children()[1]);
        listwidget->scrollToItem(listwidget->item(0));
    }
}

/*
    Switches to the next leaderboard page.
    Intended to be called automatically by a timer.
*/
void MainWindow::switchLB()
{
    lbSwitchTimer->setInterval(lbSwitchInterval * 1000);

    // choose which function to make active
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

/*
    Called when anywhere on the leaderboard has been clicked.
    Refreshes the delay period before starting the automatic page switching
*/
void MainWindow::lbClicked()
{
    lbSwitchTimer->stop();
    lbSwitchTimer->start(lbSwitchInterval * 2000); // wait double the interval before resuming
}

/*
    Called when the title image has been clicked.
    Increments click counter for toggling the debug label.
*/
void MainWindow::titleClicked()
{
    titleClickTimer->stop();
    titleClickTimer->start(2000); // 2 seconds for click timeout
    titleClicks++;
}

/*
    Called on a regular timer.
    Toggles the debug label if the title image has been clicked more than 5 times since the last time this function was ran.
*/
void MainWindow::titleClickTimeout()
{
    if (titleClicks >= 5)
        // toggle the debug label
        ui->lblDebug->isHidden() ? ui->lblDebug->show() : ui->lblDebug->hide();

    titleClicks = 0;
}

/*
    Handles closing the application when the key shortcut to close the application has been invoked.
*/
void MainWindow::closeKeyDetected()
{
    this->close();
}

/*
    Handles entering the user's score from the current running game into the leaderboard system.
    MUST be connected to the enterScore signal of the current running game in showGame().
*/
void MainWindow::enterScore(int game, QString userName, int score)
{
    Utilities::game gameEnum = static_cast<Utilities::game>(game);
    lbHandler->addScore(gameEnum, userName.toStdString(), score);
    lbHandler->writeScores(gameEnum);
    lbHandler->refreshlb(gameEnum);
}

/*
    Starts a game.

    Utilities::game game: Game to start.
*/
void MainWindow::showGame(game game)
{
    if (CliParser::getWindow())
    {
        // assign create the game widget and assign to pointer
        gameWidget = new QQuickView(Utilities::getGameQML(game));

        // create pointer with proper type for easy usage
        QPointer<QQuickView> currentView = qobject_cast<QQuickView*>(gameWidget);

        // set size parameters for the window
        currentView->setResizeMode(QQuickView::SizeRootObjectToView); // size the internal qml view to the same size as the window
        currentView->setBaseSize(this->size()); // set window size to the size of the main window
        currentView->rootContext()->setContextProperty("filepath", QString("file:///").append(filepath)); // embed filepath as QString context property

        // connect the required signals and slots
        connect((QObject*)currentView->rootObject(), SIGNAL(quit()), this, SLOT(exitGame()));
        connect((QObject*)currentView->rootObject(), SIGNAL(saveScore(int,QString,int)), this, SLOT(enterScore(int,QString,int)));

        // show the window
        currentView->showFullScreen();
    }
    else
    {
        // create new widget and store in gamewidget pointer
        gameWidget = new QQuickWidget(Utilities::getGameQML(game), this);

        // create pointer with proper type for easy usage
        QPointer<QQuickWidget> currentWidget = qobject_cast<QQuickWidget*>(gameWidget);

        // set size mode
        currentWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        currentWidget->rootContext()->setContextProperty("filepath", QString("file:///").append(filepath));

        // connect the required signals and slots
        connect((QObject*)currentWidget->rootObject(), SIGNAL(quit()), this, SLOT(exitGame()));
        connect((QObject*)currentWidget->rootObject(), SIGNAL(saveScore(int,QString,int)), this, SLOT(enterScore(int,QString,int)));

        // add the widget to the window
        ui->canvas->layout()->addWidget(currentWidget);
    }

    // stop menu timers, for performance]
    lbSwitchTimer->stop();
    titleClickTimer->stop();
    bgUpdateTimer->stop();
}

/*
    Handles exiting the current game.
    MUST be connected to the quit signal of the current running game in showGame().
*/
void MainWindow::exitGame()
{
    if (CliParser::getWindow())
    {
        // create pointer with proper type for easy usage
        QPointer<QQuickView> currentView = qobject_cast<QQuickView*>(gameWidget);

        // close and purge the window
        currentView->close();
        currentView->deleteLater();
    }
    else
    {
        // create pointer with proper type for easy usage
        QPointer<QQuickWidget> currentWidget = qobject_cast<QQuickWidget*>(gameWidget);

        // remove the widget
        ui->canvas->layout()->removeWidget(currentWidget);
        currentWidget->close();
        currentWidget->deleteLater();
    }

    // restart the timers
    lbSwitchTimer->start();
    titleClickTimer->start();
    bgUpdateTimer->start();
}

/*
    Press handler for Trivia game button.
*/
void MainWindow::on_btnGame1_pressed()
{
    showGame(game::Trivia);
}

/*
    Press handler for GuessTheLogo game button.
*/
void MainWindow::on_btnGame2_pressed()
{
    showGame(game::GuessTheLogo);
}

/*
    Press handler for Tetroos game button.
*/
void MainWindow::on_btnGame3_pressed()
{
    showGame(game::Tetroos);
}

/*
    Press handler for Hopper game button.
*/
void MainWindow::on_btnGame4_pressed()
{
    showGame(game::Hopper);
}

/*
    Press handler for Pong game button.
*/
void MainWindow::on_btnGame5_pressed()
{
    showGame(game::Pong);
}

/*
    Press handler for Checkers game button.
*/
void MainWindow::on_btnGame6_pressed()
{
    showGame(game::Checkers);
}
