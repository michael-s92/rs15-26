#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "uvodform.h"
#include "editorform.h"
#include "automatform.h"
#include "diagramform.h"

#include <QPushButton>
#include <QDockWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/images/icon/prog.jpg"));
    this->setWindowTitle("T-Rex");

    createStatusBar();
    setUpMenuActions();
    createMainView();
    createButtonGroup();

}

void MainWindow::updateStatusBar(QString& s){
    lStatus->setText(s);
}

 void MainWindow::createStatusBar(){

     lStatus = new QLabel("");
     lStatus->setMinimumSize(lStatus->sizeHint());
     ui->statusBar->addWidget(lStatus, 1);

 }

void MainWindow::setUpMenuActions(){

    connect(ui->actionNapusti_program, SIGNAL(triggered()), this, SLOT(napustiProgram()));
    connect(ui->actionAbout_T_Rex, SIGNAL(triggered()), this, SLOT(about_app()));

}

void MainWindow::about_app(){
    QMessageBox::about(this, tr("About T-Rex"),
    tr("<h2>T-Rex 0.1</h2>"
    "<p>Copyright &copy; 2015 Software Inc."
    "<p>T-Rex is a small application that "
    "help us understand and learn regular expressions."
    "<p>Implement in Qt."));
}

void MainWindow::napustiProgram(){
    /*
     * Mozda pre napustanja programa izbaciti korisniku "dovidjenja" poruku
     * ili ga pitati da li zaista zeli da napusti program
     */

    QApplication::exit();
}

void MainWindow::createMainView(){

}

QPushButton* MainWindow::createButton(const char *name, const char *info){

    QPushButton *tmp = new QPushButton();

    tmp->setCheckable(true);
    tmp->setFocusPolicy(Qt::NoFocus); //sta ce mi?!
    tmp->setToolTip(info);

    std::string ikonica(":/images/icon/"+std::string(name)+".png");
    tmp->setIcon(QIcon(&ikonica[0]));
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
    //popunjavanje okvira -> ideja prebaciti ovo u create main view
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
