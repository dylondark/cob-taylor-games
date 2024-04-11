#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QPushButton>
#include <QFont>
#include "clickdetector.h"
#include "leaderboardhandler.h"
#include "utilities.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; } // QT Generated code
QT_END_NAMESPACE

using Utilities::game;

/*
   MainWindow class

   This is the class for the actual Qt window that the program is displayed in. This class is sort of the "central hub" of the program and is the most important.
   This class is how you generally deal with the ui (outside of QML which is separate and only for the games) since this class owns the the ui object of which all
   widgets in the window are a child of. However, some objects like the LeaderboardHandler object lbHandler have pointers to widgets that they are designated control
   over, and those objects can do ui operations on those specific widgets as well (lbHandler owns a pointer to the stack widget which is a parent of all the leaderboard
   pages, so that it can refresh the leaderboard pages with its own internal data). Primarily, operations for the main menu are carried out here, like creating the QML
   widgets for the games and displaying them over the screen, and destroying those widgets to return to the main menu.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_lbGame1_pressed(); // ua trivia

    void on_lbGame2_pressed(); // guess the logo

    void on_lbGame3_pressed(); // tetroos

    void on_lbGame4_pressed(); // zippy hopper

    void on_lbGame5_pressed(); // pong

    void on_lbGame6_pressed(); // checkers

    void switchLB();

    void lbClicked();

    void titleClicked();

    void titleClickTimeout();

    void closeKeyDetected();

    void on_btnGame1_pressed();

    void on_btnGame2_pressed();

    void on_btnGame3_pressed();

    void on_btnGame4_pressed();

    void on_btnGame5_pressed();

    void on_btnGame6_pressed();

    void exitGame();

    void enterScore(int, QString, int); // Game number specification, name string, score int.

private:

    const int targetW = 2160, targetH = 3840; // target res for the application, 2160x3840

    const int lbSwitchInterval = 5; // seconds, to be used for lbSwitchTimer interval

    const int FPS = 60; // how many times to update the background per second

    LeaderboardHandler* lbHandler;

    QTimer* lbSwitchTimer;

    QTimer* titleClickTimer;

    QTimer* bgUpdateTimer;

    int titleClicks = 0;

    ClickDetector* lbDetector;

    Ui::MainWindow *ui;

    QQuickWidget* gameWidget;

    std::vector<QWidget*> lbPages; // vector containing pointers to all leaderboard page objs. c++ will not let me use an array ptr for inexplicable reasons

    QFont lbFont;

    void resizeEvent(QResizeEvent* event);

    void initbg();

    void initDebug();

    void initLeaderboard();

    void initQML();

    void scaleLeaderboard(int height);

    void scaleMenu(int height);

    void setBtnIcon(QPushButton* btn, const std::string& iconpath);

    void returnLBPagesToTop();

    void setActiveLBButton(QPushButton* btn);

    void showGame(Utilities::game);

};
#endif // MAINWINDOW_H
