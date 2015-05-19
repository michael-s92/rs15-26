#include "diagramframe.h"
#include "ui_diagramframe.h"

#include "guibuilder.h"
#include "dragwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

DiagramFrame::DiagramFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DiagramFrame)
{
    ui->setupUi(this);

    setElements();
}

DiagramFrame::~DiagramFrame()
{
    delete ui;
}

void DiagramFrame::setElements(){
    QVBoxLayout *lay = new QVBoxLayout();

    lay->addWidget(new QLabel("Diagram"));
    lay->addWidget(makePanel(), 1);
    lay->addWidget(makeShow());

    setLayout(lay);
}

QWidget* DiagramFrame::makePanel(){

    QWidget *tmp = new QWidget();

    QHBoxLayout *hlay = new QHBoxLayout();

    hlay->addWidget(new DragWidget);
    hlay->addWidget(new DragWidget, 1);

    tmp->setLayout(hlay);
    return tmp;
}


QWidget* DiagramFrame::makeShow(){

    QWidget* tmp = new QWidget();
    QHBoxLayout *hlay = new QHBoxLayout();

    regex = new QLineEdit();
    regex->setToolTip("Rezultat konstrukcije");
    regex->setEnabled(false);

    //makeReg = GuiBuilder::createIconButton();
    makeReg = new QPushButton("Make");

    hlay->addWidget(makeReg);
    hlay->addWidget(regex);

    tmp->setLayout(hlay);
    return tmp;
}
