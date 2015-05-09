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

    QVBoxLayout* layoutB = new QVBoxLayout();

    layoutB->addWidget(makeEditCover());
    layoutB->addSpacing(1);
    layoutB->addWidget(makeInputCover());
    layoutB->addSpacing(1);
    layoutB->addWidget(textArea, 1); //drugi argument je strech factor

    this->setLayout(layoutB);

}

QWidget* EditorFrame::makeInputCover(){
    inputReg = new QLineEdit("Unesite regulatni izlaz...");
    inputReg->setToolTip("Mesto za unos regularnog izraza koji se rpetrazuje");
    matched_num = new QLabel();

    QWidget *_cover = new QWidget();

    QHBoxLayout *_lay = new QHBoxLayout();

    _lay->addWidget(inputReg, 1);
    _lay->addWidget(matched_num);

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

    loadFile = new QPushButton("Ucitajte fajl");

    QWidget *cover = new QWidget();

    QHBoxLayout *lay = new QHBoxLayout();

    QLabel *coverLabel= new QLabel("Editor");

    //stilizovati coverLabel

    lay->addWidget(coverLabel, 1);
    lay->addWidget(loadFile);

    cover->setLayout(lay);
    return cover;
}

void EditorFrame::showNumMatched(bool ind){
    if(ind)
        matched_num->show();
    else
        matched_num->hide();
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
    QString rez("Pronadjeno: ");
    rez += QString::number(_eproc.doMatch(inputReg->text(), textArea));
    matched_num->setText(rez);
}
