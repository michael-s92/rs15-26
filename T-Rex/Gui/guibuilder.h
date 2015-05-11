#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <QPushButton>

namespace GuiBuilder {

QPushButton* createIconButton(QString path, QString info, int size, bool checkable = true, Qt::FocusPolicy policy = Qt::NoFocus);

}


#endif // GUIBUILDER_H
