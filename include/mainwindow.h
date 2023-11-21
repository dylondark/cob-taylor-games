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
    void setActiveLBButton(QPushButton*);
    QFont lbFont;
    LeaderboardHandler lbHandler;
};
#endif // MAINWINDOW_H
