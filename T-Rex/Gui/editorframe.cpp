#include "editorframe.h"
#include "ui_editorframe.h"

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
}

void EditorFrame::setElements(){

    textArea = new QPlainTextEdit("Unesite text koji pretrazujete ili ga ucitajte iz proizvoljnog fajla...");
    inputReg = new QLineEdit("Unesite regulatni izlaz...");
    inputReg->setToolTip("Mesto za unos regularnog izraza koji se rpetrazuje");


    QVBoxLayout* layoutB = new QVBoxLayout();

    layoutB->addWidget(makeEditCover());
    layoutB->addSpacing(1);
    layoutB->addWidget(inputReg); //da li u produzetku ovoga da stoji labela koja ce da ispisuje koliko je pronadjeno?
    layoutB->addSpacing(1);
    layoutB->addWidget(textArea, 1); //drugi argument je strech factor

    this->setLayout(layoutB);

}

QFrame* EditorFrame::makeEditCover(){

    /*
     * Ovde treba dodati dugme za aktivaciju kontejnera sa flagovima
     * povezati sa glavnim menu bar da i tu moze da se ukljucuje iskljucuje taj box
     * imamo dugme i tek kad ga pritisnemo ispod njega se pojavi box sa flagovima
     * i dok ga opet ne pritisnemo on stoji tu
     */

    loadFile = new QPushButton("Ucitajte fajl");

    QFrame *cover = new QFrame();

    QHBoxLayout *lay = new QHBoxLayout();

    QLabel *coverLabel= new QLabel("Editor");

    //stilizovati coverLabel

    lay->addWidget(coverLabel, 1);
    lay->addWidget(loadFile);

    cover->setLayout(lay);
    return cover;
}

EditorFrame::~EditorFrame()
{
    delete ui;
    delete loadFile; delete inputReg; delete textArea;
}

void EditorFrame::LoadFile(){

    QString file = QFileDialog::getOpenFileName(this, "Izaberite fajl");

    if (!file.isEmpty())
        textArea->setPlainText(_eproc.readFile(file));

}

void EditorFrame::SearchText(){

    int num = _eproc.doMatch(inputReg->text(), textArea);

}
