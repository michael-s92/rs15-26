#include "automatframe.h"
#include "ui_automatframe.h"

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

    //konekcije za simulator

    //-------------------------------
}

void AutomatFrame::drawAutomata(int ind, bool chk){

    if(ind == 0){
        int c = automatGroup->checkedId();
        if(c == -1){
            QMessageBox::about(this, "Automat?", "Niste izabrali koji automat zelite da iscrtate.");
        }
        else
            drawAutomata(c, chk);
    }
    else if(chk){
        if(ind == 1) //tomson je u pitanju
            _aproc.tomson_draw(inputReg->text(), platno);
        if(ind == 2) //glusko je u pitanju
            _aproc.glusko_draw(inputReg->text(), platno);
    }

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
    inputReg = new QLineEdit("Unesite regularni izraz...");
    sim = simulatorWidget();

    lay->addWidget(cover);
    lay->addWidget(inputReg);
    lay->addWidget(makeAutomatWidget());
    lay->addWidget(simulator, Qt::AlignRight);
    lay->addWidget(sim);

    setLayout(lay);
}

QPushButton* AutomatFrame::createSimButton(const char *name, const char *info){

    QPushButton *tmp = new QPushButton();

    tmp->setCheckable(true);
    tmp->setFocusPolicy(Qt::NoFocus); //sta ce mi?!
    tmp->setToolTip(info);

    std::string ikonica(":/images/simulator/"+std::string(name)+".jpg");
    tmp->setIcon(QIcon(&ikonica[0]));
    tmp->setIconSize(QSize(30,30));

    return tmp;
}

QWidget* AutomatFrame::simulatorWidget(){
    QWidget* sim = new QWidget();

    word = new QLineEdit("Unesite rec koju provlacimo kroz automat...");

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

    option_automat->addWidget(tomsonBox);
    option_automat->addWidget(gluskoBox);

    automatGroup->addButton(tomsonBox, 1);
    automatGroup->addButton(gluskoBox, 2);
    //-------------------------------------

    platno = new QGraphicsView();

    lay->addWidget(option_automat);
    lay->addWidget(platno);

    form->setLayout(lay);
    return form;
}
