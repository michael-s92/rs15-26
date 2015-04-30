/********************************************************************************
** Form generated from reading UI file 'automatform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMATFORM_H
#define UI_AUTOMATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutomatForm
{
public:
    QPushButton *bttn_main;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioTomson;
    QRadioButton *radioButton_2;
    QGraphicsView *graphicsView;
    QButtonGroup *AutomatGroup;

    void setupUi(QWidget *AutomatForm)
    {
        if (AutomatForm->objectName().isEmpty())
            AutomatForm->setObjectName(QStringLiteral("AutomatForm"));
        AutomatForm->resize(564, 406);
        bttn_main = new QPushButton(AutomatForm);
        bttn_main->setObjectName(QStringLiteral("bttn_main"));
        bttn_main->setGeometry(QRect(440, 10, 99, 27));
        widget = new QWidget(AutomatForm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(31, 52, 501, 341));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioTomson = new QRadioButton(widget);
        AutomatGroup = new QButtonGroup(AutomatForm);
        AutomatGroup->setObjectName(QStringLiteral("AutomatGroup"));
        AutomatGroup->addButton(radioTomson);
        radioTomson->setObjectName(QStringLiteral("radioTomson"));

        verticalLayout->addWidget(radioTomson);

        radioButton_2 = new QRadioButton(widget);
        AutomatGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);


        horizontalLayout->addLayout(verticalLayout);

        graphicsView = new QGraphicsView(widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(AutomatForm);

        QMetaObject::connectSlotsByName(AutomatForm);
    } // setupUi

    void retranslateUi(QWidget *AutomatForm)
    {
        AutomatForm->setWindowTitle(QApplication::translate("AutomatForm", "TRex - Automat", 0));
        bttn_main->setText(QApplication::translate("AutomatForm", "Back to main", 0));
        radioTomson->setText(QApplication::translate("AutomatForm", "Tomson", 0));
        radioButton_2->setText(QApplication::translate("AutomatForm", "RadioButton", 0));
    } // retranslateUi

};

namespace Ui {
    class AutomatForm: public Ui_AutomatForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATFORM_H
