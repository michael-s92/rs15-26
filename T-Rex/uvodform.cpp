#include "uvodform.h"
#include "ui_uvodform.h"

#include "mainwindow.h"

UvodForm::UvodForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UvodForm)
{
    ui->setupUi(this);

}

UvodForm::~UvodForm()
{
    delete ui;
}

UvodForm* UvodForm::getUvodForm(){
    static UvodForm* _form = new UvodForm();
    return _form;
}
