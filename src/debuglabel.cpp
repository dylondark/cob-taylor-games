#include "debuglabel.h"
#include <QtSystemDetection>

DebugLabel::DebugLabel(QWidget* parent) : QLabel(parent)
{

}

void DebugLabel::update()
{
    // declare string & build info
    QString txt("Build: ");
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
#elif Q_OS_WINDOWS
    txt.append("Windows");
#elif Q_OS_MAC
    txt.append("MacOS");
#else
    txt.append("Unknown");
#endif

    setText(txt);
}
