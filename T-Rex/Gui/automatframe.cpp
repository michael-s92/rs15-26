#include "automatframe.h"
#include "ui_automatframe.h"

AutomatFrame::AutomatFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::AutomatFrame)
{
    ui->setupUi(this);
}

AutomatFrame::~AutomatFrame()
{
    delete ui;
}
