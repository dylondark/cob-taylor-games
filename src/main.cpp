#include "mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <iostream>
#include <QStyleFactory>
#include <QQuickWindow>

// Provides the "entry point" for the application.
// This function only configures and sets up the environment for the main window.
// "Init" operations for the program should be placed in the mainwindow constructor unless they really need to be here.
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard")); //Enable virtual keyboard environment variable

    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion")); // setting fusion qstyle should make the application look the same regardless of os
    MainWindow w;

    // set qtquick to use OpenGL (Fixes mac)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    // get list of screens
    QList<QScreen *> screens = QGuiApplication::screens();

    // if there is a screen that has portrait aspect ratio (ideally 9:16), open on that window
    int screen = 0;
    std::cout << "screens: " << screens.size() << "\n"; // log amount of screens in terminal
    for (int x = 0; x < screens.size(); x++)
    {
        std::cout << x << ": " << screens[x]->availableSize().width() << "x" << screens[x]->availableSize().height() << "\n"; // log screen size in terminal
        if (screens[x]->availableSize().width() < screens[x]->availableSize().height())
        {
            screen = x;
            break; // this will use the first portrait monitor if multiple are present
        }
    }
    std::cout << "using screen: " << screen << "\n";
    //w.setWindowFlag(Qt::FramelessWindowHint); // set window to be borderless
    w.move(screens[screen]->availableGeometry().center()); // set screen
    w.showFullScreen();

    return a.exec();
}
