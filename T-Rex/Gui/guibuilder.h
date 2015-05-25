#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

namespace GuiBuilder {

QPushButton* createIconButton(QString path, QString info, int size, bool checkable = true, Qt::FocusPolicy policy = Qt::NoFocus);
QLineEdit* createLineEdit(QString info, QString text = "");
void throwErrorMessage(QString msn, QString info = "");
void throwInfoMessage(QString msn, QString info = "");
bool leaveProgramDialog();

}


#endif // GUIBUILDER_H
