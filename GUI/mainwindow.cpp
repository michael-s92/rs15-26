#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uvodform.h"
#include "editorform.h"
#include "automatform.h"
#include "diagramform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&switchForm, SIGNAL(mapped(QString)), this, SLOT(go_to_form(QString)));

    connect(ui->bttn_uvod, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_uvod, "uvod");

    connect(ui->bttn_editor, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_editor, "editor");

    connect(ui->bttn_automat, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_automat, "automat");

    connect(ui->bttn_diagram, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_diagram, "diagram");

}

MainWindow::~MainWindow()
{
    delete ui;
}


MainWindow* MainWindow::getMainWindow(){
    static MainWindow* _main = new MainWindow();
    return _main;
}

void MainWindow::go_to_form(QString fname){
    std::string temp = fname.toStdString();
    if(temp.compare("uvod") == 0)
        UvodForm::getUvodForm()->show();
    else if(temp.compare("editor") == 0)
        EditorForm::getEditorForm()->show();
    else if(temp.compare("automat") == 0)
        AutomatForm::getAutomatForm()->show();
    else if(temp.compare("diagram") == 0)
        DiagramForm::getDiagramForm()->show();
    this->hide();
}
