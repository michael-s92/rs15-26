/********************************************************************************
** Form generated from reading UI file 'editorform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORFORM_H
#define UI_EDITORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorForm
{
public:
    QPushButton *bttn_main;
    QPushButton *bttnLoad;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *EditorForm)
    {
        if (EditorForm->objectName().isEmpty())
            EditorForm->setObjectName(QStringLiteral("EditorForm"));
        EditorForm->resize(650, 450);
        bttn_main = new QPushButton(EditorForm);
        bttn_main->setObjectName(QStringLiteral("bttn_main"));
        bttn_main->setGeometry(QRect(31, 40, 111, 21));
        bttnLoad = new QPushButton(EditorForm);
        bttnLoad->setObjectName(QStringLiteral("bttnLoad"));
        bttnLoad->setGeometry(QRect(31, 68, 111, 21));
        layoutWidget = new QWidget(EditorForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 60, 461, 371));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        plainTextEdit = new QPlainTextEdit(layoutWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        retranslateUi(EditorForm);

        QMetaObject::connectSlotsByName(EditorForm);
    } // setupUi

    void retranslateUi(QWidget *EditorForm)
    {
        EditorForm->setWindowTitle(QApplication::translate("EditorForm", "TRex - Editor", 0));
        bttn_main->setText(QApplication::translate("EditorForm", "Back to main", 0));
        bttnLoad->setText(QApplication::translate("EditorForm", "Ucitaj text", 0));
    } // retranslateUi

};

namespace Ui {
    class EditorForm: public Ui_EditorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORFORM_H
