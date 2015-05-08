#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uvodform.h"
#include "editorform.h"
#include "automatform.h"
#include "diagramform.h"

#include <QPushButton>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createButtonGroup();

}

QPushButton* MainWindow::createButton(const char *name, const char *info){

    QPushButton *tmp = new QPushButton();

    std::string ikonica(":/images/icon/"+std::string(name)+".png");
    const char* b = &ikonica[0];

    tmp->setCheckable(true);
    tmp->setFocusPolicy(Qt::NoFocus); //sta ce mi?!
    tmp->setToolTip(info);

    tmp->setIcon(QIcon(b));
    tmp->setIconSize(QSize(50,50));

    return tmp;

}

void MainWindow::createButtonGroup(){

    bttnGroup = new QButtonGroup();
    bttnBar = new QToolBar(tr("Celine"));

    bttnBar->setOrientation(Qt::Vertical);

    bUvod = createButton("uvod", "Uvod u svet regularnih izraza");
    bEditor = createButton("editor", "Pronadji regularne izraze u tekstu");
    bAutomat = createButton("automat", "Konstruisi automat za regularni izraz");
    bDiagram = createButton("diagram", "Sastavi regularni izraz");

    bttnGroup->addButton(bUvod);
    bttnGroup->addButton(bEditor);
    bttnGroup->addButton(bAutomat);
    bttnGroup->addButton(bDiagram);

    bttnBar->addWidget(bUvod);
    bttnBar->addWidget(bEditor);
    bttnBar->addWidget(bAutomat);
    bttnBar->addWidget(bDiagram);

    QDockWidget *content = new QDockWidget();// argument konstruktora: tr("Celine")
    content->setWidget(bttnBar);
    content->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, content);


    //Ubacivanje u okvir sta sve prikazujemo
    ui->stackedWidget->addWidget(UvodForm::getUvodForm());
    ui->stackedWidget->addWidget(EditorForm::getEditorForm());
    ui->stackedWidget->addWidget(AutomatForm::getAutomatForm());
    ui->stackedWidget->addWidget(DiagramForm::getDiagramForm());

    //postavljanje dogadjaja
    connect(&switchForm, SIGNAL(mapped(int)), this, SLOT(go_to_form(int)));

    connect(bUvod, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bUvod, 0);

    connect(bEditor, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bEditor, 1);

    connect(bAutomat, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bAutomat, 2);

    connect(bDiagram, SIGNAL(clicked()), &switchForm, SLOT(map()));
    switchForm.setMapping(bDiagram, 3);

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
