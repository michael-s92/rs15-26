#include "diagramform.h"
#include "ui_diagramform.h"

#include "mainwindow.h"

DiagramForm::DiagramForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramForm)
{
    ui->setupUi(this);

    connect(&back_to, SIGNAL(mapped(QString)), this, SLOT(goto_main(QString)));

    connect(ui->bttn_main, SIGNAL(clicked()), &back_to, SLOT(map()));
    back_to.setMapping(ui->bttn_main, "back_to_main");
}

DiagramForm::~DiagramForm()
{
    delete ui;
}

DiagramForm* DiagramForm::getDiagramForm(){
    static DiagramForm* _form = new DiagramForm();
    return _form;
}

void DiagramForm::goto_main(QString msn){
    if(msn.toStdString().compare("back_to_main") == 0){
        MainWindow::getMainWindow()->show();
        this->hide();
    }
}
