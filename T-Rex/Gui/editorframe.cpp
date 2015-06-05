#include "editorframe.h"
#include "ui_editorframe.h"

#include "guibuilder.h"

#include <QFileDialog>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

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

    //inicijalni flagovi
    _icFlag = _ignoreCase->isChecked();
    _gFlag = _global->isChecked();
    _mFlag = _multiline->isChecked();

}

void EditorFrame::setElements(){

    textArea = ui->plainTextEdit;
    _eproc = new EditorProcess(textArea);
    //textArea->setPlaceholderText("Unesite text koji pretrazujete ili ga ucitajte iz proizvoljnog fajla...");

    QString content("Ovde unosite tekst koji hocete da pretrazujete.\n"
                    "Naravno taj tekst moze biti bilo sta! Razni datumi, brojevi, slova i oznake.\n"
                    "Isto tako tekst mozete ucitati i iz proizvoljnog file pritiskom na odgovarajuce dugme.");
    textArea->setPlainText(content);

    makeEditCover();

}

QToolButton* EditorFrame::makeFlagsBtn(){

    QToolButton* btn = new QToolButton();
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setIcon(QIcon(":/editor/images/flags.ico"));
    btn->setIconSize(QSize(40,40));
    btn->setToolTip("Atributi pretrazivanja");

    QMenu* options = new StayOpenMenu(btn);
    btn->setMenu(options);

    _ignoreCase = createAction("IgnoreCase", options);
    _global = createAction("Global", options);
    _multiline = createAction("Multiline", options);

    _multiline->setChecked(true);
    _global->setChecked(true);

    options->addAction(_ignoreCase);
    options->addAction(_global);
    options->addAction(_multiline);

    connect(_ignoreCase, SIGNAL(triggered(bool)), this, SLOT(ActIgnoreCase(bool)));
    connect(_multiline, SIGNAL(triggered(bool)), this, SLOT(ActMultiline(bool)));
    connect(_global, SIGNAL(triggered(bool)), this, SLOT(ActGlobal(bool)));

    return btn;
}

void EditorFrame::ActIgnoreCase(bool chk){
    _icFlag = chk;
    SearchText();
}

void EditorFrame::ActMultiline(bool chk){
    _mFlag = chk;
    SearchText();
}

void EditorFrame::ActGlobal(bool chk){
    _gFlag = chk;
    SearchText();
}

QAction* EditorFrame::createAction(const QString &title, QObject* parent){
    QAction *action = new QAction(title, parent);
    action->setCheckable(true);
    return action;
}


EditorFrame::StayOpenMenu::StayOpenMenu(QWidget *parent)
    : QMenu(parent), m_inhibitClose(false)
{
}

void EditorFrame::StayOpenMenu::mousePressEvent(QMouseEvent * event)
{
    QMenu::mousePressEvent(event);
    m_inhibitClose = true;
}

void EditorFrame::StayOpenMenu::closeEvent(QCloseEvent * event) {
    if (m_inhibitClose) {
        event->ignore();
        m_inhibitClose = false;
    } else {
        QMenu::closeEvent(event);
        event->accept();
    }
}

void EditorFrame::makeEditCover(){

    inputReg = GuiBuilder::createLineEdit("Mesto za unos regularnog izraza koji se trazi.");
    chkNum = new QCheckBox("Prikazi broj pronadjenih");
    loadFile = GuiBuilder::createIconButton(":/editor/images/loadfile.ico", "Ucitaj text koji pretrazujes iz file-a", 35, false);

    auto lay = ui->topLayout;
    QVBoxLayout *tmp = new QVBoxLayout();

    tmp->addWidget(inputReg);
    //tmp->addWidget(chkNum);

    lay->addLayout(tmp, 1);

    lay->addWidget(makeFlagsBtn());
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
        _eproc->readFile(file);

}

void EditorFrame::SearchText(){
    if(inputReg->text().compare("") != 0){

        QString rez("Pronadjeno: ");

        int num = _eproc->doMatch(inputReg->text(), _icFlag, _gFlag, _mFlag);

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
