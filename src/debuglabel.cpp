/*
    debuglabel.cpp

    Class implementation for debug label.
*/

#include "debuglabel.h"
#include <QtSystemDetection>
#include <QOpenGLContext>

/*
    Constructor for Debug
*/
DebugLabel::DebugLabel(QWidget* parent) : QLabel(parent)
{

}

/*
    Updates each element in the given integer array

    int wh[]: Window width and height
*/
void DebugLabel::update(int wh[])
{
    QString txt("You've found the debug!");

    // get build info
    txt.append(" Build: ");
    txt.append(BUILD_INFO_BRANCH);
    txt.append(" #");
    txt.append(BUILD_INFO_COMMIT);
    txt.append(", ");
    txt.append(BUILD_INFO_DATE);

    // determine OS
    txt.append(" OS: ");
#ifdef Q_OS_LINUX
    txt.append("Linux, ");

    // check existence of WAYLAND_DISPLAY envvar to determine if we are on wayland or x11
    if (qgetenv("WAYLAND_DISPLAY") != "")
        txt.append("Wayland");
    else
        txt.append("X11");
#elif defined Q_OS_WINDOWS
    txt.append("Windows");
#elif defined Q_OS_MAC
    txt.append("MacOS");
#else
    txt.append("Unknown");
#endif

    // get resolution
    txt.append(" Res: ");
    txt.append(std::to_string(wh[0]));
    txt.append("x");
    txt.append(std::to_string(wh[1]));

    // get opengl info
#ifndef Q_OS_WINDOWS // fix for windows at some point??
    txt.append(" OGL Info: ");
    //txt.append(glGetString(GL_VERSION));
    txt.append(reinterpret_cast<const char*>(glGetString(GL_VERSION)));


    setText(txt);
#endif
}
