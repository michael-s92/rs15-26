#include "editorframe.h"
#include "ui_editorframe.h"

#include "guibuilder.h"

#include <QFileDialog>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

EditorFrame::EditorFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EditorFrame)
{
    ui->setupUi(this);

    setElements();

    //konekcije za pretrazivanje teksta
    connect(loadFile, SIGNAL(clicked(bool)), this, SLOT(LoadFile()));
    connect(inputReg, SIGNAL(returnPressed()), this, SLOT(SearchText()));
    connect(chkNum, SIGNAL(toggled(bool)), this, SLOT(showNumMatched(bool)));

    connect(flagsBtn, SIGNAL(clicked(bool)), this, SLOT(ShowChangeFlagsBox(bool)));
}

void EditorFrame::ShowChangeFlagsBox(bool chk){

}

void EditorFrame::setElements(){

    textArea = ui->plainTextEdit;
    //textArea->setPlaceholderText("Unesite text koji pretrazujete ili ga ucitajte iz proizvoljnog fajla...");

    makeEditCover();

}

void EditorFrame::makeEditCover(){

    inputReg = GuiBuilder::createLineEdit("Mesto za unos regularnog izraza koji se trazi.");
    chkNum = new QCheckBox("Prikazi broj pronadjenih");
    loadFile = GuiBuilder::createIconButton(":/editor/images/loadfile.ico", "Ucitaj text koji pretrazujes iz file-a", 35, false);

    flagsBtn = GuiBuilder::createIconButton(":/editor/images/flags.ico", "Atributi pretrazivanja", 35);
    /*
     * treba postaviti da kad se klikne negde sa strane da dugme izgubi fokus i padajuci meni nestane
     * ili da se radi sa QDialog-zima pa da uopste nam ni ne treba chekable atribut, moze false
     */


    auto lay = ui->topLayout;
    QVBoxLayout *tmp = new QVBoxLayout();

    tmp->addWidget(inputReg);
    tmp->addWidget(chkNum);

    lay->addLayout(tmp, 1);
    lay->addWidget(flagsBtn);
    lay->addWidget(loadFile);

}

void EditorFrame::showNumMatched(bool ind){
    if(ind){
        SearchText();
    }
    else {
        chkNum->setText("Prikazi broj pronadjenih");
    }
}

EditorFrame::~EditorFrame()
{
    delete ui;
    delete loadFile; delete inputReg; delete chkNum;
}

void EditorFrame::LoadFile(){

    QString file = QFileDialog::getOpenFileName(this, "Izaberite fajl");

    if (!file.isEmpty())
        textArea->setPlainText(_eproc.readFile(file));

}

void EditorFrame::SearchText(){
    if(inputReg->text().compare("") != 0){
        QString rez("Pronadjeno: ");

        int num = _eproc.doMatch(inputReg->text(), textArea);

        if(num == -1)
            //ako hvatamo poruku o gresci, onda ovde je uhvatiti i prikazati u ovoj poruci dole
            GuiBuilder::throwErrorMessage("Trazeni regularni izraz je nevalidan.", "Proverite ispravnost regularnog izraza");
        else{
            rez += QString::number(num);
            if(chkNum->isChecked())
                chkNum->setText(rez);
        }
    }
    else
        GuiBuilder::throwErrorMessage("Uneti prvo regularni izraz.", "Polje za unos regularnog izraza je prazno.");
}
