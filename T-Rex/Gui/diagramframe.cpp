#include "diagramframe.h"
#include "ui_diagramframe.h"

#include "guibuilder.h"
#include "dragwidget.h"
#include "acceptwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

DiagramFrame::DiagramFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DiagramFrame)
{
    ui->setupUi(this);

    makePanel();
    makeShow();
}

DiagramFrame::~DiagramFrame()
{
    delete ui;
}

void DiagramFrame::makeShow(){

    auto lay = ui->bottomLayout;

    regex = new QLineEdit();
    regex->setToolTip("Rezultat konstrukcije");
    regex->setEnabled(false);

    makeReg = GuiBuilder::createIconButton(":/diagram/images/makeReg.ico", "Generisi regularni izraz", 35, false);
    cleanDiagram = GuiBuilder::createIconButton(":/diagram/images/clearDiagram.ico", "Ocisti radnu povrsinu", 35, false);

    lay->addWidget(cleanDiagram);
    lay->addWidget(makeReg);
    lay->addWidget(regex);

}

void DiagramFrame::makePanel(){

    auto lay = ui->centralLayout;

    lay->addWidget(new DragWidget);
    lay->addWidget(new AcceptWidget, 1);

}
