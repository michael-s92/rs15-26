#include "automatframe.h"
#include "ui_automatframe.h"

#include "guibuilder.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QRadioButton>
#include <QMessageBox>

#include <QDebug>

AutomatFrame::AutomatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AutomatFrame)
{
    ui->setupUi(this);

    setElements();
    _aproc = new AutomatProcess(platno, opisArea);
    setSlotAndSignal();

}

void AutomatFrame::setSlotAndSignal(){

    connect(simulator, SIGNAL(clicked(bool)), this, SLOT(displaySimulator(bool)));

    //SIGNAL(QLineEdit::editingFinished())
    //nece da se opet aktivira signal kad se pritisne enter?!
    connect(inputReg, SIGNAL(returnPressed()), this, SLOT(drawAutomata()));
    connect(automatGroup, SIGNAL(buttonToggled(int,bool)), this, SLOT(drawAutomata(int, bool)));
    connect(opis, SIGNAL(clicked(bool)), this, SLOT(displayDetails(bool)));

    //konekcije za simulator
    connect(&simulator_map, SIGNAL(mapped(QString)), this, SLOT(simulatorPlay(QString)));

    connect(s_next, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_previous, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_start, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_pause, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_reset, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_play, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_stop, SIGNAL(clicked()), &simulator_map, SLOT(map()));

    simulator_map.setMapping(s_stop, "stop");
    simulator_map.setMapping(s_start, "start");
    simulator_map.setMapping(s_previous, "previuse");
    simulator_map.setMapping(s_next, "next");
    simulator_map.setMapping(s_pause, "pause");
    simulator_map.setMapping(s_reset, "reset");
    simulator_map.setMapping(s_play, "play");
    //-------------------------------

}

void AutomatFrame::simulatorPlay(const QString& action){
    qDebug() << "AutomatProcess::simulatorPlay() ->  " << action;
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
                draw = _aproc->tomson_draw(inputReg->text());
            if(ind == 2) //glusko je u pitanju
                draw = _aproc->glusko_draw(inputReg->text());
            if(ind == 3) //deterministicki je u pitanju
                draw = _aproc->determi_draw(inputReg->text());
            if(ind == 4) //minimalni je u pitanju
                draw = _aproc->minimal_draw(inputReg->text());

            if(!draw)
                GuiBuilder::throwErrorMessage("Neispravan regularni izraz.");
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
    delete s_reset; delete s_next; delete s_previous; delete s_start; delete s_pause; delete s_play; delete s_stop;
    delete sim;
    delete _aproc;
}

void AutomatFrame::setElements(){
    QVBoxLayout *lay = new QVBoxLayout();

    simulator = new QCheckBox("Kretanje reci kroz automat");
    simulator->setChecked(true);
    inputReg = GuiBuilder::createLineEdit("Polje za unos regularnog izraza.");
    sim = simulatorWidget();

    lay->addWidget(inputReg);
    lay->addWidget(makeAutomatWidget());
    lay->addWidget(simulator, Qt::AlignRight);
    lay->addWidget(sim);

    setLayout(lay);
}

QPushButton* AutomatFrame::createSimButton(const char *name, const char *info){

    QString path = QString(":/images/simulator/") + QString(name) + QString(".ico");
    return GuiBuilder::createIconButton(path, QString(info), 40);
}

QWidget* AutomatFrame::simulatorWidget(){
    QWidget* sim = new QWidget();

    word = GuiBuilder::createLineEdit("Polje za unos reci.");

    QHBoxLayout *lay = new QHBoxLayout();

    s_previous = createSimButton("back", "Vratite se slovo unazad");
    s_start = createSimButton("start", "Provucite rec kroz automat");
    s_next = createSimButton("next", "Uzmite sledece slovo iz reci");
    s_reset = createSimButton("reset", "Vratite se na pocetak reci");
    s_pause = createSimButton("pause", "Pauzirajte kretanje");
    s_play = createSimButton("play", "Pustite automacko provlacenje");
    s_stop = createSimButton("stop", "Zaustavite provlacenje");

    QButtonGroup *simgr = new QButtonGroup();
    simgr->addButton(s_previous);
    simgr->addButton(s_start);
    simgr->addButton(s_pause);
    simgr->addButton(s_next);
    simgr->addButton(s_reset);
    simgr->addButton(s_play);
    simgr->addButton(s_stop);

    lay->addWidget(word, 1);

    QToolBar *tmp = new QToolBar();
    tmp->setAttribute(Qt::WA_DeleteOnClose);


    tmp->addWidget(s_start);
    tmp->addWidget(s_stop);
    tmp->addSeparator();

    tmp->addWidget(s_previous);
    tmp->addWidget(s_next);
    tmp->addWidget(s_reset);
    tmp->addSeparator();

    tmp->addWidget(s_play);
    tmp->addWidget(s_pause);

    lay->addWidget(tmp);

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
    opisArea->setEnabled(false);

    lay->addWidget(option_automat, 0, Qt::AlignCenter);
    lay->addWidget(platno, 1);
    lay->addWidget(opisArea);

    form->setLayout(lay);
    return form;
}
