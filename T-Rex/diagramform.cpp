#include "diagramform.h"
#include "ui_diagramform.h"

#include "mainwindow.h"

DiagramForm::DiagramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramForm)
{
    ui->setupUi(this);

}

DiagramForm::~DiagramForm()
{
    delete ui;
}

DiagramForm* DiagramForm::getDiagramForm(){
    static DiagramForm* _form = new DiagramForm();
    return _form;
}
