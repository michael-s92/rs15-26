#include "automatform.h"
#include "ui_automatform.h"

#include "mainwindow.h"

AutomatForm::AutomatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomatForm)
{
    ui->setupUi(this);

    connect(&back_to, SIGNAL(mapped(QString)), this, SLOT(goto_main(QString)));

    connect(ui->bttn_main, SIGNAL(clicked()), &back_to, SLOT(map()));
    back_to.setMapping(ui->bttn_main, "back_to_main");
}

AutomatForm::~AutomatForm()
{
    delete ui;
}

AutomatForm* AutomatForm::getAutomatForm(){
    static AutomatForm* _form = new AutomatForm();
    return _form;
}

void AutomatForm::goto_main(QString msn){
    if(msn.toStdString().compare("back_to_main") == 0){
        MainWindow::getMainWindow()->show();
        this->hide();
    }
}
