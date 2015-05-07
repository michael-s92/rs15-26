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

    ui->stackedWidget->addWidget(UvodForm::getUvodForm());
    ui->stackedWidget->addWidget(EditorForm::getEditorForm());
    ui->stackedWidget->addWidget(AutomatForm::getAutomatForm());
    ui->stackedWidget->addWidget(DiagramForm::getDiagramForm());

    connect(&switchForm, SIGNAL(mapped(int)), this, SLOT(go_to_form(int)));

    connect(ui->bttn_uvod, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_uvod, 0);

    connect(ui->bttn_editor, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_editor, 1);

    connect(ui->bttn_automat, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_automat, 2);

    connect(ui->bttn_diagram, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(ui->bttn_diagram, 3);

    /*
     * napraviti neku novu formu, da inicijalno nju prikazije
     * ne mora da ima mehanizam povratka na nju
     * ui->stackedWidget->setCurrentIndex();
     */
}

void MainWindow::go_to_form(int i){
    ui->stackedWidget->setCurrentIndex(i);
}


MainWindow::~MainWindow()
{
    delete ui;
}


MainWindow* MainWindow::getMainWindow(){
    static MainWindow* _main = new MainWindow();
    return _main;
}
