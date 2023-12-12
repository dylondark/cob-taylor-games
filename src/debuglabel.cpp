#include "debuglabel.h"

DebugLabel::DebugLabel(QWidget* parent) : QLabel(parent)
{

}

void DebugLabel::update()
{
    QString txt("Build: ");
    txt.append(BUILD_INFO_BRANCH);
    txt.append(" #");
    txt.append(BUILD_INFO_COMMIT);
    txt.append(", ");
    txt.append(BUILD_INFO_DATE);
    setText(txt);
}
