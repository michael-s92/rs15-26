#include "automatframe.h"
#include "ui_automatframe.h"

#include "guibuilder.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QRadioButton>
#include <QMessageBox>

AutomatFrame::AutomatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AutomatFrame)
{
    ui->setupUi(this);

    setElements();
    setSlotAndSignal();
}

void AutomatFrame::setSlotAndSignal(){

    connect(simulator, SIGNAL(clicked(bool)), this, SLOT(displaySimulator(bool)));

    //SIGNAL(QLineEdit::editingFinished())
    connect(inputReg, SIGNAL(returnPressed()), this, SLOT(drawAutomata()));
    connect(automatGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(drawAutomata(int, bool)));
    connect(opis, SIGNAL(clicked(bool)), this, SLOT(displayDetails(bool)));

    //konekcije za simulator

    //-------------------------------
}

void AutomatFrame::displayDetails(bool display){
    display ? opisArea->show() : opisArea->hide();
}

void AutomatFrame::drawAutomata(int ind, bool chk){
    if(inputReg->text().compare("") != 0){
        if(ind == 0){
            int c = automatGroup->checkedId();
            if(c == -1){
                QMessageBox::about(this, "Automat?", "Niste izabrali koji automat zelite da iscrtate.");
            }
            else
                drawAutomata(c, chk);
        }
        else if(chk){
            bool draw = false;
            if(ind == 1) //tomson je u pitanju
                draw = _aproc.tomson_draw(inputReg->text(), platno, opisArea);
            if(ind == 2) //glusko je u pitanju
                draw = _aproc.glusko_draw(inputReg->text(), platno, opisArea);
            if(ind == 3) //deterministicki je u pitanju
                draw = _aproc.determi_draw(inputReg->text(), platno, opisArea);
            if(ind == 4) //minimalni je u pitanju
                draw = _aproc.minimal_draw(inputReg->text(), platno, opisArea);

            if(!draw)
                GuiBuilder::throwErrorMessage("Neispravan rularni izraz.");
        }
    }
    else
        GuiBuilder::throwErrorMessage("Unesite regularni izraz u polje predvidjeno za njega.");
}

void AutomatFrame::displaySimulator(bool display){
    display ? sim->show() : sim->hide();
}

AutomatFrame::~AutomatFrame()
{
    delete ui;

    delete platno;
    delete automatGroup;
    delete simulator;
    delete inputReg; delete word;
    delete s_reset; delete s_next; delete s_previous; delete s_start;
    delete sim;
}

void AutomatFrame::setElements(){
    QVBoxLayout *lay = new QVBoxLayout();

    QLabel *cover = new QLabel("Automat");
    simulator = new QCheckBox("Kretanje reci kroz automat");
    simulator->setChecked(true);
    inputReg = GuiBuilder::createLineEdit("Polje za unos regularnog izraza.");
    sim = simulatorWidget();

    lay->addWidget(cover);
    lay->addWidget(inputReg);
    lay->addWidget(makeAutomatWidget());
    lay->addWidget(simulator, Qt::AlignRight);
    lay->addWidget(sim);

    setLayout(lay);
}

QPushButton* AutomatFrame::createSimButton(const char *name, const char *info){

    QString path = QString(":/images/simulator/") + QString(name) + QString(".ico");
    return GuiBuilder::createIconButton(path, QString(info), 35);
}

QWidget* AutomatFrame::simulatorWidget(){
    QWidget* sim = new QWidget();

    word = GuiBuilder::createLineEdit("Polje za unos reci koju pustamo kroz automat.");

    QHBoxLayout *lay = new QHBoxLayout();

    s_previous = createSimButton("back", "Vratite se slovo unazad");
    s_start = createSimButton("play", "Provucite rec kroz automat");
    s_next = createSimButton("next", "Uzmite sledece slovo iz reci");
    s_reset = createSimButton("reset", "Vratite se na pocetak reci");

    QButtonGroup *simgr = new QButtonGroup();
    simgr->addButton(s_previous);
    simgr->addButton(s_start);
    simgr->addButton(s_next);
    simgr->addButton(s_reset);

    lay->addWidget(word, 1);
    lay->addWidget(s_previous);
    lay->addWidget(s_start);
    lay->addWidget(s_next);
    lay->addWidget(s_reset);

    sim->setLayout(lay);
    return sim;
}

QWidget* AutomatFrame::makeAutomatWidget(){
    QWidget* form = new QWidget();
    QHBoxLayout *lay = new QHBoxLayout();

    QToolBar* option_automat = new QToolBar();
    option_automat->setOrientation(Qt::Vertical);
    automatGroup = new QButtonGroup();

    //ovde se dodaju nove kontrole za iscrtavanje automata
    QRadioButton *tomsonBox = new QRadioButton("Tomson");
    QRadioButton *gluskoBox = new QRadioButton("Glusko");
    QRadioButton *deterBox = new QRadioButton("deterministicki");
    QRadioButton *minimalBox = new QRadioButton("minimalni");

    option_automat->addWidget(tomsonBox);
    option_automat->addWidget(gluskoBox);
    option_automat->addWidget(deterBox);
    option_automat->addWidget(minimalBox);

    option_automat->addSeparator();
    opis = new QCheckBox("Opisi automat");
    opis->setChecked(true);
    option_automat->addWidget(opis);

    automatGroup->addButton(tomsonBox, 1);
    automatGroup->addButton(gluskoBox, 2);
    automatGroup->addButton(deterBox, 3);
    automatGroup->addButton(minimalBox, 4);
    //-------------------------------------

    platno = new QGraphicsView();
    //podesiti je minimalnu duzinu mozda, ali tek kad se vidi koliko ispis zaista zauzima
    opisArea = new QPlainTextEdit();

    lay->addWidget(option_automat, 0, Qt::AlignCenter);
    lay->addWidget(platno, 1);
    lay->addWidget(opisArea);

    form->setLayout(lay);
    return form;
}
