#include "diagramframe.h"
#include "ui_diagramframe.h"

DiagramFrame::DiagramFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DiagramFrame)
{
    ui->setupUi(this);
}

DiagramFrame::~DiagramFrame()
{
    delete ui;
}
