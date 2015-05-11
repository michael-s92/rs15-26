#include "guibuilder.h"

QPushButton* GuiBuilder::createIconButton(QString path, QString info, int size, bool checkable, Qt::FocusPolicy policy){

    QPushButton *tmp = new QPushButton();

    tmp->setCheckable(checkable);
    tmp->setFocusPolicy(policy);
    tmp->setToolTip(info);

    tmp->setIcon(QIcon(path));
    tmp->setIconSize(QSize(size, size));

    return tmp;

}
