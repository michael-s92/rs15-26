#include "welcomeform.h"
#include "ui_welcomeform.h"

#include <QTimer>
#include "mainwindow.h"

WelcomeForm::WelcomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeForm)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onload()));
    timer->setSingleShot(true);
    timer->start(2000);

}

void WelcomeForm::onload(){

    MainWindow::getMainWindow()->show();
    this->hide();

}

WelcomeForm::~WelcomeForm()
{
    delete ui;
}
