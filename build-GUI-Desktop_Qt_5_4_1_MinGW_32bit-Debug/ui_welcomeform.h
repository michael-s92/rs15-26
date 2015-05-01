/********************************************************************************
** Form generated from reading UI file 'welcomeform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEFORM_H
#define UI_WELCOMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeForm
{
public:
    QLabel *_label;

    void setupUi(QWidget *WelcomeForm)
    {
        if (WelcomeForm->objectName().isEmpty())
            WelcomeForm->setObjectName(QStringLiteral("WelcomeForm"));
        WelcomeForm->setWindowModality(Qt::NonModal);
        WelcomeForm->resize(650, 450);
        _label = new QLabel(WelcomeForm);
        _label->setObjectName(QStringLiteral("_label"));
        _label->setGeometry(QRect(160, 30, 191, 211));
        _label->setPixmap(QPixmap(QString::fromUtf8(":/new/welcome_form_files/FormFiles/WelcomeForm_files/dino0.jpg")));
        _label->setScaledContents(true);

        retranslateUi(WelcomeForm);

        QMetaObject::connectSlotsByName(WelcomeForm);
    } // setupUi

    void retranslateUi(QWidget *WelcomeForm)
    {
        WelcomeForm->setWindowTitle(QApplication::translate("WelcomeForm", "T-Rex", 0));
        _label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WelcomeForm: public Ui_WelcomeForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEFORM_H
