/********************************************************************************
** Form generated from reading UI file 'diagramform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGRAMFORM_H
#define UI_DIAGRAMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiagramForm
{
public:
    QPushButton *bttn_main;

    void setupUi(QWidget *DiagramForm)
    {
        if (DiagramForm->objectName().isEmpty())
            DiagramForm->setObjectName(QStringLiteral("DiagramForm"));
        DiagramForm->resize(650, 450);
        bttn_main = new QPushButton(DiagramForm);
        bttn_main->setObjectName(QStringLiteral("bttn_main"));
        bttn_main->setGeometry(QRect(280, 20, 99, 27));

        retranslateUi(DiagramForm);

        QMetaObject::connectSlotsByName(DiagramForm);
    } // setupUi

    void retranslateUi(QWidget *DiagramForm)
    {
        DiagramForm->setWindowTitle(QApplication::translate("DiagramForm", "TRex - Diagram", 0));
        bttn_main->setText(QApplication::translate("DiagramForm", "Back to main", 0));
    } // retranslateUi

};

namespace Ui {
    class DiagramForm: public Ui_DiagramForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMFORM_H
