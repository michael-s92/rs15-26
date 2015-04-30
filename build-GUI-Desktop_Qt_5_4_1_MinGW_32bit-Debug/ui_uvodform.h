/********************************************************************************
** Form generated from reading UI file 'uvodform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UVODFORM_H
#define UI_UVODFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UvodForm
{
public:
    QPushButton *bttn_main;

    void setupUi(QWidget *UvodForm)
    {
        if (UvodForm->objectName().isEmpty())
            UvodForm->setObjectName(QStringLiteral("UvodForm"));
        UvodForm->resize(400, 300);
        bttn_main = new QPushButton(UvodForm);
        bttn_main->setObjectName(QStringLiteral("bttn_main"));
        bttn_main->setGeometry(QRect(290, 20, 99, 27));

        retranslateUi(UvodForm);

        QMetaObject::connectSlotsByName(UvodForm);
    } // setupUi

    void retranslateUi(QWidget *UvodForm)
    {
        UvodForm->setWindowTitle(QApplication::translate("UvodForm", "TRex - Uvod", 0));
        bttn_main->setText(QApplication::translate("UvodForm", "Back to main", 0));
    } // retranslateUi

};

namespace Ui {
    class UvodForm: public Ui_UvodForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UVODFORM_H
