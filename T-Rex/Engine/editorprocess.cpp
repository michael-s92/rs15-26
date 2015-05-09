#include "editorprocess.h"

#include <QFile>
#include <QTextStream>

EditorProcess::EditorProcess()
{

}

EditorProcess::~EditorProcess()
{

}

QString& EditorProcess::readFile(const QString &file){

    buffer = "";

    QFile data(file);
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);

        QString value;
        for(;;) {
            value = in.readLine();
            if (!value.isNull()) {
                buffer += value + "\n";
            } else
                break;
            }

    }

    data.close();

    return buffer;
}

int EditorProcess::doMatch(QString what, QPlainTextEdit* area){

    /*
     * ima greska! kad radi replace, on gubi deo onoga sto je ucitano, skracuje sadrzaj
     * druga stvar je sto ne treba da izbacuje matched kad nesto pronadje, nego da izbaci bas to sto je pronasao
     * ne radi pravilno cak ni prepoznavanje, mozda bolje ici liniju po liniju, ali to treba videti kako citati iz plain texta
     * i gde cuvati. Pogledati:
     * QRegExp::cap(int n = 0)
     * QRegExp::capturedTexts()
     * Ubaciti i flagove sa strane da korisnik bira: IgnoreCase, Multiline, Global
     * markira se pomocu html taga. ceo kod nece imati smisla ako se ucitava html tekst, tagovi ce izgubiti vrednost
     */

    QRegExp mark(what);
    buffer = area->toPlainText();
    buffer.replace(mark, "<span style=\"color:#660033; font: italic bold\">MATCHED</span>");
    area->setPlainText("");
    area->appendHtml("<pre>" + buffer + "</pre>");

    //povratna vrednost je broj prepoznatih
    return 0;
}
