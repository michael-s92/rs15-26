#include "automatprocess.h"
#include <QMessageBox>
#include <fstream>
#include <QGraphicsPixmapItem>
#include "graphview.h"

using namespace std;

AutomatProcess::AutomatProcess(QGraphicsView* p, QPlainTextEdit* o, QLineEdit *rec, QLabel *pr, QLabel *nu)
    :panel(p), opis(o), kretanje(0), word(rec), procitano(pr), na_ulazu(nu)
{
    panel->setRenderHint(QPainter::Antialiasing);
    panel->setRenderHint(QPainter::TextAntialiasing);
    panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

AutomatProcess::~AutomatProcess()
{
    //destruktor ne treba nista da ima jer sve prosledjujemo po adresi
    //i pravimo kopiju samo adrese
}
int AutomatProcess::kreciSe(int k)
{
    if (kretanje!=0)
    {
    QString text = word->text();
    if (k==-1)
    {
        if (count==0)
            return -1;
        count --;
        return kretanje->kreci_se_nazad();

    }
    else if (k==0 || kretanje->trenutno==-1)
    {
        count = 0;
        return kretanje->postavi_na_pocetak();
    }
    else
    {
        if (count == text.length())
        {
        if ((kretanje->zavrsna).contains(kretanje->trenutno))
            return -2;
        else
            return -1;
        }
        char c = text.toStdString().at(count);
        count ++;
        return kretanje->kreci_se_napred(c);
    }
    }
    else
        return -4;

}

bool AutomatProcess::tomson_draw(const QString &regular){

        opis->clear();
        try {
             parser = ParserEngine(regular);
            }
        catch (ParserException p)
           {
             return false;
           }
       Thompson::state_count=0;
       Reg_node * reg_node = parser.getRegNode();
       ThompsonNodes thompsonNodes;
       reg_node->accept(thompsonNodes);
       Thompson t = thompsonNodes.getTh();
       fstream f;
       f.open("thompson.dot",fstream::out);
       t.makeDotFile(f);
       f.close();

       QGraphicsScene * scene = new GraphView("thompson.dot");

       panel->setScene(scene);
       ispisi_podatke(t);
       kretanje = 0;
       count = 0;
       return true;
    }


bool AutomatProcess::glusko_draw(const QString& regular){

    opis->clear();
    try {
     parser = ParserEngine(regular);
    }
    catch (ParserException p)
    {
        return false;
    }
     Thompson::state_count=0;
     Reg_node * reg_node = parser.getRegNode();
     ThompsonNodes thompsonNodes;
     reg_node->accept(thompsonNodes);
     Thompson t = thompsonNodes.getTh();
     Gluskov g = t.make_gluskov();

     fstream f;
     f.open("gluskov.dot",fstream::out);
     g.makeDotFile(f);
     f.close();

     QGraphicsScene *scene = new GraphView("gluskov.dot");
     panel->setScene(scene);

     kretanje = 0;
     count = 0;

     ispisi_podatke(g);
     return true;

}

bool AutomatProcess::determi_draw(const QString& regular)
{
    opis->clear();
    try {
     parser = ParserEngine(regular);
    }
    catch (ParserException p)
    {
        return false;
    }
     Thompson::state_count=0;
     Reg_node * reg_node = parser.getRegNode();
     ThompsonNodes thompsonNodes;
     reg_node->accept(thompsonNodes);
     Thompson t = thompsonNodes.getTh();
     Gluskov g = t.make_gluskov();
     Deterministicki::state_count = 0;
     Deterministicki d = g.makeDeterministicki();
     fstream f;
     f.open("deterministicki.dot",fstream::out);
     d.makeDotFile(f);
     f.close();


     QGraphicsScene *scene = new GraphView("deterministicki.dot");
     panel->setScene(scene);

     QList<QGraphicsItem*> items = scene->items();
     kretanje = new Kretanje(d, items);
     count = 0;

     ispisi_podatke(d);

     return true;

 }


bool AutomatProcess::minimal_draw(const QString &regular){

    opis->clear();
    try {
     parser = ParserEngine(regular);
    }
    catch (ParserException p)
      {
        return false;
      }
     Thompson::state_count=0;
     Reg_node * reg_node = parser.getRegNode();
     ThompsonNodes thompsonNodes;
     reg_node->accept(thompsonNodes);
     Thompson t = thompsonNodes.getTh();
     Gluskov g = t.make_gluskov();
     Deterministicki::state_count = 0;
     Deterministicki d = g.makeDeterministicki();
     Minimalni::state_count = 2;
     Minimalni m = d.makeMinimalni();
     fstream f;
     f.open("minimalni.dot",fstream::out);
     m.makeDotFile(f);
     f.close();

     QGraphicsScene *scene = new GraphView("minimalni.dot");

     panel->setRenderHint(QPainter::Antialiasing);
     panel->setRenderHint(QPainter::TextAntialiasing);
     panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
     panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

     panel->setScene(scene);

     QList<QGraphicsItem*> items = scene->items();
     kretanje = new Kretanje(m, items);
     count = 0;

     ispisi_podatke(m);

     return true;

 }



void AutomatProcess::ispisi_podatke(Automata & a)
{
    a.plainTextAddAlphabet(opis);
    a.plainTextAddStart(opis);
    a.plainTextAddStates(opis);
    a.plainTextAddAcceptStates(opis);
    a.plainTextAddEdges(opis);
}


