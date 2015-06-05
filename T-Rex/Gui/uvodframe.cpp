#include "uvodframe.h"
#include "ui_uvodframe.h"

UvodFrame::UvodFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UvodFrame)
{
    ui->setupUi(this);

    ui->areaOsnovno->setPlainText("");
    ui->areaOsnovno->appendHtml("U računarstvu i informatici, regularni izraz (još i pravilan izraz, ispravan izraz - engl. skr. regexp ili regex,"
                                "u množini regexps, regexes ili regexen) je niska koja opisuje ili sparuje skup niski, u skladu s određenim sintaksnim pravilima.<p>"
                                "Regularne izraze koriste mnogi tekst editori i pomoćni programi za pretragu i manipulaciju teksta.<p>"
                                "Mnogi programski jezici podržavaju regularne izraze za manipulisanje niskama.<p>"
                                "Na primer, Perl i Tcl imaju moćan motor za regularne izraze ugrađen direktno u sintaksu.<p>"
                                "Skup pomoćnih programa (uključujući uređivač sed i filter grep) koji se standardno distribuira sa UNIX distribucijama je mnogo učinio na promociji i popularizaciji koncepta regularnih izraza.");

}

UvodFrame::~UvodFrame()
{
    delete ui;
}
