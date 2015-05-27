#include "guibuilder.h"

#include <QPixmap>

QPushButton* GuiBuilder::createIconButton(QString path, QString info, int size, bool checkable, Qt::FocusPolicy policy){

    QPushButton *tmp = new QPushButton();

    tmp->setCheckable(checkable);
    tmp->setFocusPolicy(policy);
    tmp->setToolTip(info);

    tmp->setIcon(QIcon(path));
    tmp->setIconSize(QSize(size, size));

    return tmp;

}

QLineEdit* GuiBuilder::createLineEdit(QString info, QString text){

    QLineEdit* tmp = new QLineEdit(text);

    tmp->setToolTip(info);
    tmp->setPlaceholderText(info);

    return tmp;
}

void GuiBuilder::throwErrorMessage(QString msn, QString info){
    QMessageBox mBox;

    QPixmap pic(QPixmap(":/images/saddino.jpg")); //mozda zameniti sliku?
    mBox.setIconPixmap(pic.scaledToHeight(150, Qt::SmoothTransformation));
    mBox.setStandardButtons(QMessageBox::Ok);

    mBox.setWindowTitle("Greska!");

    mBox.setText(msn);
    mBox.setInformativeText(info);

    mBox.setModal(false);

    mBox.exec();
}

void GuiBuilder::throwInfoMessage(QString msn, QString info){
    QMessageBox mBox;

    QPixmap pic(QPixmap(":/images/infodino.png"));
    mBox.setIconPixmap(pic.scaledToHeight(150, Qt::SmoothTransformation));
    mBox.setStandardButtons(QMessageBox::Ok);

    mBox.setWindowTitle("Greska!");

    mBox.setText(msn);
    mBox.setInformativeText(info);

    mBox.setModal(false);

    mBox.exec();
}

bool GuiBuilder::leaveProgramDialog(){

    QMessageBox exitBox;
    exitBox.setWindowTitle("T-Rex");
    exitBox.setText(QObject::tr("Da li sigurno zelite da napustite program?"));
    QPixmap pic(QPixmap(":/msn/images/exitdino.jpg"));
    exitBox.setIconPixmap(pic.scaledToHeight(150, Qt::SmoothTransformation));
    exitBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    exitBox.setDefaultButton(QMessageBox::Yes);

    exitBox.setModal(false);

    if(exitBox.exec() == QMessageBox::Yes)
        return true;
    return false;
}
