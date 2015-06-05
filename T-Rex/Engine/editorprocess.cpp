#include "editorprocess.h"

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <QStringList>

EditorProcess::EditorProcess(QPlainTextEdit *textArea)
    :tArea(textArea)
{

}

EditorProcess::~EditorProcess()
{

}

void EditorProcess::readFile(const QString &file){

    tArea->setPlainText("");

    QFile data(file);
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);

        QString value;
        for(;;) {
            value = in.readLine();
            if (!value.isNull()) {
                tArea->appendPlainText(value + "\n");
            } else
                break;
            }

    }

    data.close();

}

int EditorProcess::doMatch(QString what, bool _ignorecaseFlag, bool _globalFlag, bool _multilineFlag){

    //iskoristiti flagove:
    //bool _ignorecaseFlag, bool _globalFlag, bool _multilineFlag

    /*
     * ima greska! kad radi replace, on gubi deo onoga sto je ucitano,
     * skracuje sadrzaj (mozda buffer ne moze sve da prihvati?!)
     * (predlog: niz stringova, svaka linija jedan clan niza)
     * druga stvar je sto ne treba da izbacuje matched kad nesto pronadje, nego da izbaci bas to sto je pronasao
     * ne radi pravilno cak ni prepoznavanje, mozda bolje ici liniju po liniju,
     * ali to treba videti kako citati iz plain texta
     * i gde cuvati. Pogledati:
     * QRegExp::cap(int n = 0)
     * QRegExp::capturedTexts()
     * Ubaciti i flagove sa strane da korisnik bira: IgnoreCase, Multiline, Global
     * markira se pomocu html taga. ceo kod nece imati smisla ako se ucitava html tekst,
     * tagovi ce izgubiti vrednost
     */


    //Preporucuje se nova klasa: QRegularExpression

    /*
     * koriscene backreference za prepoznavanje sta je pronadjeno
     * koliko je to dobro, ako neko u regularnom izrazu ih i sam koristi?
     */

    QRegularExpression mark("(" + what + ")");

    /*
     * da li je regularan izraz validan!
     * povratna vrednost je broj prepoznatih reci
     * ili -1 u slucaju da je regularni izraz neispravan
     */
    qint32 found = 0;

    if(mark.isValid()){

        if(_ignorecaseFlag)
            mark.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

        QString buffer;
        QStringList bufferArray = tArea->toPlainText().split("\n");

        if(_multilineFlag){
            //obradjujemo sve linije
            if(_globalFlag){
                //obradjujemo sva pojavljivanja
                bufferArray = bufferArray.replaceInStrings(mark, "<span style=\"color:#660033; font: italic bold\">\\1</span>");
            }
            else{
                //obradjujemo samo prvo pojavljivanje

            }
        }
        else{
            //samo prvu liniju obradjujemo
            if(_globalFlag){
                //obradjujemo sva pojavljivanja
                bufferArray.first().replace(mark, "<span style=\"color:#660033; font: italic bold\">\\1</span>");
            }
            else{
                //obradjujemo samo prvo pojavljivanje

            }
        }

        //kad se popune if-ovi gore ovo izbrisati
        //buffer.replace(mark, "<span style=\"color:#660033; font: italic bold\">\\1</span>");

        //da bi radilo

        tArea->setPlainText("");
        tArea->appendHtml("<pre>" + bufferArray.join("\n") + "</pre>");

        found = 0;
    }
    else{
        //mozda ovu poruku vratiti nekako EditorFrame-u da je on izbaci u GuiBuilder::throwErrorMessage???
        qDebug() << "EditorProcess::doMatch() ->   " << mark.errorString();
        found = -1;
    }

    return found;
}
