#include "uvodframe.h"
#include "ui_uvodframe.h"

UvodFrame::UvodFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UvodFrame)
{
    ui->setupUi(this);
}

UvodFrame::~UvodFrame()
{
    delete ui;
}
