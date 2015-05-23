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

    connect(&simulator_start, SIGNAL(mapped(QString)), this, SLOT(simulatorPlay(QString)));

    connect(s_start, SIGNAL(clicked()), &simulator_start, SLOT(map()));
    connect(s_stop, SIGNAL(clicked()), &simulator_start, SLOT(map()));
    simulator_start.setMapping(s_start, "start");
    simulator_start.setMapping(s_stop, "stop");

    connect(&simulator_map, SIGNAL(mapped(QString)), this, SLOT(startPlay(QString)));

    connect(s_next, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_previous, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_pause, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_reset, SIGNAL(clicked()), &simulator_map, SLOT(map()));
    connect(s_play, SIGNAL(clicked()), &simulator_map, SLOT(map()));

    simulator_map.setMapping(s_previous, "previuse");
    simulator_map.setMapping(s_next, "next");
    simulator_map.setMapping(s_reset, "reset");
    simulator_map.setMapping(s_play, "play");
    simulator_map.setMapping(s_pause, "pause");

}

void AutomatFrame::simulatorPlay(const QString& action){

    /*
     * Izbaciti poruku da nije moguce menjati nista dok se ne ugasi simulator
     * ili kako vec god to regulisati
     *
     * simulator regulisan
     */

    if(action.compare("start") == 0){
        if(word->text().compare("") == 0)
            GuiBuilder::throwErrorMessage("Prazan unos reci.", "Unesite prvo rec u simulator.");
        else
            enabledSimulatorBtn(false);
    }
    else if(action.compare("stop") == 0){
        enabledSimulatorBtn(true);
    }

}

void AutomatFrame::startPlay(const QString &action){
    //qDebug() << "AutomatProcess::startPlay() ->  " << action;

    int response;

    if(action.compare("previuse") == 0){
        response = _aproc->kreciSe(word, -1);
        if(response == -1)
            GuiBuilder::throwErrorMessage("Nije dostupno kretanje u tom smeru", "Dosli ste do pocetka reci.");
    }

    // milane cackao sam ti malo ovde
    // pa ti ispravi kako mislis da treba
    // naime treba da imaju i ova dva upozorenja
    // pa rekoh da stavim da se nadje <3

    else if(action.compare("next") == 0){
        response = _aproc->kreciSe(word, 1);
        if (response == -3)
           GuiBuilder::throwInfoMessage("Automat je blokiran.", "Nemoguc prelaz po oznacenom slovu");
        else if (response == -4)
           GuiBuilder::throwInfoMessage("Izabrani Automat mora biti deterministicki ili minimalni.", "Nemoguca simulacija kretanja");
        else if(response < 0){
            QString ishod;
            if(response == -1)
                ishod = "Rec nije prepoznata automatom.";
            if(response == -2)
                ishod = "Rec je prepoznata automatom.";
            GuiBuilder::throwInfoMessage("Dosli ste do kraja reci.", ishod);
        }
    }
    else if(action.compare("reset") == 0){
        response = _aproc->kreciSe(word, 0);
    }
    else if(action.compare("play") == 0){
        //ako je ukljucena simulacija da iskljuci sve dugmice sem "pause"
        //neka pokrene metodu i da ima nesto QTimer i slots za njega da poziva stalno
        //response = _aproc->kreciSe(word, 1);

        //mozda i pause dugme da bude onemoguceno u startu?!
    }
    else if(action.compare("pause") == 0){
        //zaustavlja simulaciju, znaci gasi tajmer
        //i staje u prepoznavanju reci tamo dokle je stigao
        //i ostali dugmici su slobodni opet

    }

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
    if(display)
        sim->show();
    else {
        sim->hide();
        enabledSimulatorBtn(true);
        //mozda iscrtati automat bez obelezih stanja i prelaza
    }

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

    enabledSimulatorBtn(true);
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

void AutomatFrame::enabledSimulatorBtn(bool vr){

    //dok radi simulator treba onemoguciti i da se bira automat i da se menja regularni izraz
    //onemoguciti i chkBox da se prikaze simulator

    //automatGroup -> buttons() pa iterator
    //inputReg->setEnabled(vr);

    /*
     * mozda kad se promeni automat da se rec resetuje na pocetak
     * ili da izadje automacki iz simulatora?
     */

    word->setEnabled(vr);

    s_start->setEnabled(vr);
    s_next->setEnabled(!vr);
    s_previous->setEnabled(!vr);
    s_stop->setEnabled(!vr);
    s_pause->setEnabled(!vr);
    s_reset->setEnabled(!vr);
    s_play->setEnabled(!vr);
}
