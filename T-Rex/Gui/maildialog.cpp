#include "maildialog.h"
#include "ui_maildialog.h"

#include "guibuilder.h"

#include <QDesktopServices>
#include <QDebug>

MailDialog::MailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Podrska!"));
    setModal(false);
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(sendMail()));
}

MailDialog::~MailDialog()
{
    delete ui;
}

void MailDialog::sendMail(){

    //iz nekog razloga ne radi, iako je preuzeto iz Qt-ove dokumentacije

    /*
     * Slanje mail sa:
     * Test - naslov
     * Just a test - poruka
     * user@foo.com = mail
     * mailto:user@foo.com?subject=Test&body=Just a test
     */

    QString ourMail = "m.stefanovic992@gmail.com";
    QString contest = "mailto:" + ourMail + "?subject=" + ui->lineNaslov->text()
            + "&body=" + ui->textMsg->toPlainText() + "\nreplyto:" + ui->lineReply->text();

    qDebug() << contest;

    bool anw = QDesktopServices::openUrl(QUrl(contest, QUrl::StrictMode));

    if(!anw)
        GuiBuilder::throwErrorMessage(tr("Proverite internet konekciju ili ispravnost podrazumevanog web pretrazivaca."));
    else
        GuiBuilder::throwInfoMessage(tr("Poruka je poslata."));

    close();
}
