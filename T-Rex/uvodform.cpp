#include "uvodform.h"
#include "ui_uvodform.h"

#include "mainwindow.h"

UvodForm::UvodForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UvodForm)
{
    ui->setupUi(this);

    connect(&back_to, SIGNAL(mapped(QString)), this, SLOT(goto_main(QString)));

    connect(ui->bttn_main, SIGNAL(clicked()), &back_to, SLOT(map()));
    back_to.setMapping(ui->bttn_main, "back_to_main");
}

UvodForm::~UvodForm()
{
    delete ui;
}

UvodForm* UvodForm::getUvodForm(){
    static UvodForm* _form = new UvodForm();
    return _form;
}

void UvodForm::goto_main(QString msn){
    if(msn.toStdString().compare("back_to_main") == 0){
        MainWindow::getMainWindow()->show();
        this->hide();
    }
}
