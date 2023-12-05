#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bgwidget.h"
#include <QPushButton>
#include <QFont>
#include "leaderboardhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lbGame1_pressed(); // ua trivia
    void on_lbGame2_pressed(); // guess the logo
    void on_lbGame3_pressed(); // checkers
    void on_lbGame4_pressed(); // zippy hopper
    void on_lbGame5_pressed(); // pong
    void on_lbGame6_pressed(); // tetris

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent*);
    void initLeaderboard();
    void scaleLeaderboard(int);
    void scaleMenu(int);
    void returnLBPagesToTop();
    std::vector<QWidget*> lbPages; // vector containing pointers to all leaderboard page objs. c++ will not let me use an array ptr for inexplicable reasons
    void setActiveLBButton(QPushButton*);
    QFont lbFont;
    LeaderboardHandler* lbHandler;
    const int targetW = 2160, targetH = 3840; // target res for the application, 2160x3840
};
#endif // MAINWINDOW_H
