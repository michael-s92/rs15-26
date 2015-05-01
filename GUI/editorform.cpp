#include "editorform.h"
#include "ui_editorform.h"

#include "mainwindow.h"

EditorForm::EditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorForm)
{
    ui->setupUi(this);

    connect(&back_to, SIGNAL(mapped(QString)), this, SLOT(goto_main(QString)));

    connect(ui->bttn_main, SIGNAL(clicked()), &back_to, SLOT(map()));
    back_to.setMapping(ui->bttn_main, "back_to_main");

    connect(ui->bttnLoad, SIGNAL(clicked(bool)), this, SLOT(LoadFile()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(SearchText()));
}

EditorForm::~EditorForm()
{
    delete ui;
}

EditorForm* EditorForm::getEditorForm(){
    static EditorForm* _form = new EditorForm();
    return _form;
}

void EditorForm::goto_main(QString msn){
    if(msn.toStdString().compare("back_to_main") == 0){
        MainWindow::getMainWindow()->show();
        this->hide();
    }
}


void EditorForm::LoadFile(){
    ui->plainTextEdit->setPlainText("load file");
}

void EditorForm::SearchText(){
    ui->plainTextEdit->appendPlainText("search text: " + ui->lineEdit->text());
}
