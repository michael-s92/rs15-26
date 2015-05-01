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

    //reagujem samo na ENTER, opstiji slucaj je editingFinished()
    connect(ui->lineEdit, SIGNAL(returnPressed()),this, SLOT(draw_automata()));
    connect(ui->AutomatGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(draw_automata()));

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

//samo za test iostream, iskljuciti je posle
#include <iostream>
#include <QString>
void AutomatForm::draw_automata(){

    //uzimamo regularni izraz
    QString reg = ui->lineEdit->text();

    //samo ispisuje sta je cekirano
    //tu bi sad na zahtev trebalo da se poziva da se pravi automat
    //i da se iscrtava
    if(ui->radioTomson->isChecked())
        std::cout << "Tomson: " << reg.toStdString() << std::endl;
    else
        std::cout << "drugo: " << reg.toStdString() << std::endl;
}
