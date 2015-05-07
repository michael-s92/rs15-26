#include "editorform.h"
#include "ui_editorform.h"

#include "mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

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
    ui->plainTextEdit->setPlainText("");

    QString file = QFileDialog::getOpenFileName(this, "Izaberite fajl");

    if (!file.isEmpty()) {
        QFile data(file);
        if (data.open(QFile::ReadOnly)) {
            QTextStream in(&data);

            QString value;

            for(;;) {
                value = in.readLine();
                if (!value.isNull()) {
                    ui->plainTextEdit->appendPlainText(value);
                } else
                    break;

            }
        }
        data.close();
    }
}

#include <QRegExp>
void EditorForm::SearchText(){

    /*
     * ima greska! kad radi replace, on gubi deo onoga sto je ucitano, skracuje sadrzaj
     * druga stvar je sto ne treba da izbacuje matched kad nesto pronadje, nego da izbaci bas to sto je pronasao
     * ne radi pravilno cak ni prepoznavanje, mozda bolje ici liniju po liniju, ali to treba videti kako citati iz plain texta
     * i gde cuvati. Pogledati:
     * QRegExp::cap(int n = 0)
     * QRegExp::capturedTexts()
     * Ubaciti i flagove sa strane da korisnik bira: IgnoreCase, Multiline, Global
     */

    QRegExp mark(ui->lineEdit->text());
    QString content = ui->plainTextEdit->toPlainText();
    content.replace(mark, "<span style=\"color:#660033; font: italic bold\">MATCHED</span>");
    ui->plainTextEdit->setPlainText("");
    ui->plainTextEdit->appendHtml("<pre>" + content + "</pre>");

}
