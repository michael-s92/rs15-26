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

    //fali konektor za flagsBtn
}

void EditorFrame::setElements(){

    textArea = new QPlainTextEdit();
    textArea->setPlaceholderText("Unesite text koji pretrazujete ili ga ucitajte iz proizvoljnog fajla...");

    QVBoxLayout* layoutB = new QVBoxLayout();
    QLabel *name = new QLabel("Editor");

    layoutB->addWidget(name);
    layoutB->addWidget(makeEditCover());
    layoutB->addWidget(makeMatchingFrame());
    layoutB->addWidget(textArea, 1); //drugi argument je strech factor

    this->setLayout(layoutB);

}

QWidget* EditorFrame::makeMatchingFrame(){

    inputReg = GuiBuilder::createLineEdit("Mesto za unos regularnog izraza koji se trazi.");

    chkNum = new QCheckBox("Prikazi broj pronadjenih");

    QWidget *_cover = new QWidget();

    QHBoxLayout *_lay = new QHBoxLayout();

    _lay->addWidget(inputReg, 1);
    _lay->addWidget(chkNum);

    _cover->setLayout(_lay);

    return _cover;
}

QWidget *EditorFrame::makeEditCover(){

    /*
     * Ovde treba dodati dugme za aktivaciju kontejnera sa flagovima
     * povezati sa glavnim menu bar da i tu moze da se ukljucuje iskljucuje taj box
     * imamo dugme i tek kad ga pritisnemo ispod njega se pojavi box sa flagovima
     * i dok ga opet ne pritisnemo on stoji tu
     */

    loadFile = GuiBuilder::createIconButton(":/editor/images/loadfile.ico", "Ucitaj text koji pretrazujes iz file-a", 35);
    loadFile->setCheckable(false);

    flagsBtn = GuiBuilder::createIconButton(":/editor/images/flags.ico", "Atributi pretrazivanja", 35);

    QWidget *cover = new QWidget();

    QHBoxLayout *lay = new QHBoxLayout();

    //stilizovati coverLabel

    lay->addWidget(new QLabel(), 1);
    lay->addWidget(flagsBtn);
    lay->addWidget(loadFile);


    cover->setLayout(lay);
    return cover;
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
    delete loadFile; delete inputReg; delete textArea;
    delete chkNum;
}

void EditorFrame::LoadFile(){

    QString file = QFileDialog::getOpenFileName(this, "Izaberite fajl");

    if (!file.isEmpty())
        textArea->setPlainText(_eproc.readFile(file));

}

void EditorFrame::SearchText(){
    if(inputReg->text().compare("") != 0){
        QString rez("Pronadjeno: ");
        rez += QString::number(_eproc.doMatch(inputReg->text(), textArea));
        if(chkNum->isChecked())
            chkNum->setText(rez);
    }
    else
        GuiBuilder::throwErrorMessage("Uneti prvo regularni izraz.", "Polje za unos regularnog izraza je prazno.");
}
