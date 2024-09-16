/*
    mainwindow.h

    Class declaration for MainWindow.
*/

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
namespace Ui { class MainWindow; } // Qt generated code
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

    /*
        Constructor for MainWindow.
    */
    MainWindow(QWidget *parent = nullptr);

    /*
        Destructor for MainWindow.
    */
    ~MainWindow();

private slots:

    /*
        Press handler for Trivia leaderboard button.
    */
    void on_lbGame1_pressed();

    /*
        Press handler for GuessTheLogo leaderboard button.
    */
    void on_lbGame2_pressed();

    /*
        Press handler for Tetroos leaderboard button.
    */
    void on_lbGame3_pressed();

    /*
        Press handler for Hopper leaderboard button.
    */
    void on_lbGame4_pressed();

    /*
        Press handler for Pong leaderboard button.
    */
    void on_lbGame5_pressed();

    /*
        Press handler for Checkers leaderboard button.
    */
    void on_lbGame6_pressed();

    /*
        Switches to the next leaderboard page.
        Intended to be called automatically by a timer.
    */
    void switchLB();

    /*
        Called when anywhere on the leaderboard has been clicked.
        Refreshes the delay period before starting the automatic page switching
    */
    void lbClicked();

    /*
        Called when the title image has been clicked.
        Increments click counter for toggling the debug label.
    */
    void titleClicked();

    /*
        Called on a regular timer.
        Toggles the debug label if the title image has been clicked more than 5 times since the last time this function was ran.
    */
    void titleClickTimeout();

    /*
        Handles closing the application when the key shortcut to close the application has been invoked.
    */
    void closeKeyDetected();

    /*
        Press handler for Trivia game button.
    */
    void on_btnGame1_pressed();

    /*
        Press handler for GuessTheLogo game button.
    */
    void on_btnGame2_pressed();

    /*
        Press handler for Tetroos game button.
    */
    void on_btnGame3_pressed();

    /*
        Press handler for Hopper game button.
    */
    void on_btnGame4_pressed();

    /*
        Press handler for Pong game button.
    */
    void on_btnGame5_pressed();

    /*
        Press handler for Checkers game button.
    */
    void on_btnGame6_pressed();

    /*
        Handles exiting the current game.
        MUST be connected to the quit signal of the current running game in showGame().
    */
    void exitGame();

    /*
        Handles entering the user's score from the current running game into the leaderboard system.
        MUST be connected to the enterScore signal of the current running game in showGame().
    */
    void enterScore(int, QString, int);

private:

    /*
        The base of the paths. Should be the location of the folder containing the gamefiles folder.
        By default it is "." which (should) mean "wherever the game executable was launched from" but this doesn't always work (ahem, mac).
        Will be set to whatever path is specified with the -p CLI parameter if it is used.
    */
    const QString filepath;

    // Target resolution for the application, 2160x3840.
    const int targetW = 2160, targetH = 3840;

    // Seconds, to be used for lbSwitchTimer interval.
    const int lbSwitchInterval = 5;

    // How many times to update the background per second.
    const int FPS = 60;

    // Contains all of the UI objects defined in the designer (mainwindow.ui).
    Ui::MainWindow* ui;

    // Object that handles saving scores to and updating the leaderboard.
    LeaderboardHandler* lbHandler;

    // Timer that calls switchLB() to automatically switch leaderboard pages.
    QTimer* lbSwitchTimer;

    // Timer that calls titleClickTimeout() to check if the conditions are right to toggle the debug label.
    QTimer* titleClickTimer;

    // Timer that triggers the drawing of the next frame of the menu background.
    QTimer* bgUpdateTimer;

    // Amount of times the title image has been clicked since the last run of titleClickTimeout().
    int titleClicks = 0;

    // Object that detects when any part of the leaderboard has been clicked and calls lbClicked().
    ClickDetector* lbDetector;

    // Pointer to the quickwidget of the current game (if there is a game running).
    QPointer<QObject> gameWidget;

    // Vector containing pointers to all leaderboard page objects.
    std::vector<QWidget*> lbPages;

    // Contains the font for the leaderboard buttons set in mainwindow.ui.
    QFont lbFont;

    /*
        Called when the window is resized.
        Contains scaling operations for UI elements.

        QResizeEvent* event: Pointer to resize event generated by Qt.
    */
    void resizeEvent(QResizeEvent* event);

    /*
        Initialization operations for the background.
    */
    void initbg();

    /*
        Initialization operations for the debug label.
    */
    void initDebug();

    /*
        Initialization operations for the leaderboard.
    */
    void initLeaderboard();

    /*
        Initialization operations for registering QML controllers.
    */
    void initQML();

    /*
        Contains scaling operations for the leaderboard UI elements.
        TODO: Remove height parameter and get the height inside the function.

        int height: Current height of the window.
    */
    void scaleLeaderboard(int height);

    /*
        Contains scaling operations for the menu UI elements.
        TODO: Remove height parameter and get the height inside the function.
        TODO: Ensure that all operations dealing with menu scaling are inside this function and not resizeEvent().

        int height: Current height of the window.
    */
    void scaleMenu(int height);

    /*
        Applies an icon to a button.

        QPushButton* btn: Pointer to button to apply image to.
        const std::string& iconpath: Path to the icon to apply to the button.
    */
    void setBtnIcon(QPushButton* btn, const std::string& iconpath);

    /*
        Scrolls all leaderboard pages to the top.
        TODO: Remove this function since it isn't needed anymore.
    */
    void returnLBPagesToTop();

    /*
        Makes UI adjustments to the leaderboard buttons to indicate that the passed button is "active".

        QPushButton* btn: Button to be set as active.
    */
    void setActiveLBButton(QPushButton* btn);

    /*
        Starts a game.

        Utilities::game game: Game to start.
    */
    void showGame(Utilities::game game);

};
#endif // MAINWINDOW_H
