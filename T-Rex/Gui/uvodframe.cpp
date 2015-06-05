#include "uvodframe.h"
#include "ui_uvodframe.h"

UvodFrame::UvodFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UvodFrame)
{
    ui->setupUi(this);

    ui->areaOsnovno->setPlainText("");
    ui->areaOsnovno->appendHtml("osnovno");

    ui->areaTabela->setPlainText("");
    ui->areaTabela->appendHtml("tabela");
}

UvodFrame::~UvodFrame()
{
    delete ui;
}
