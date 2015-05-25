#include "automatprocess.h"
#include <QMessageBox>
#include <fstream>
#include <QGraphicsPixmapItem>
#include "AutomatParser/graphview.h"

// TO-DO
// DESTRUKTORI
// zameniti sve iteratore ugradjenim iteratorim u Qt-u
// prelaze po vise slova stopiti u jedan prelaz
// ispisati jos neke podatke o automatima
// definisati pravila za karakterske klase i repetitition
// izvrsiti prenumeraciju stanja

// bagovi
// kada se pojavi dialog box obezbediti blokadu ostalog
// kada ispisuje formalne podatke o grafu - ne radi scroll
// ako je rec koja se simulira duza?
// neki bag pravi kod bekslesa


using namespace std;

AutomatProcess::AutomatProcess(QGraphicsView* p, QPlainTextEdit* o, QLineEdit *rec, QLabel *pr, QLabel *nu)
    :panel(p), opis(o), kretanje(0), word(rec), procitano(pr), na_ulazu(nu)
{
    panel->setRenderHint(QPainter::Antialiasing);
    panel->setRenderHint(QPainter::TextAntialiasing);
    panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    na_ulazu->setStyleSheet("QLabel {color: green;}");
    procitano->setStyleSheet("QLabel {color: red;}");

}

AutomatProcess::~AutomatProcess()
{
    delete scene;
    delete kretanje;
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
        procitano->setText(word->text().left(count));
        na_ulazu->setText(word->text().right(word->text().length()-count));
        return kretanje->kreci_se_nazad();
    }
    else if (k==0 || kretanje->trenutno==-1)
    {
        count = 0;
        na_ulazu->setText(word->text());


        procitano->setText("");
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
        int ret = kretanje->kreci_se_napred(c);
        if (ret!=-3)
        {
        count ++;
        procitano->setText(word->text().left(count));
        na_ulazu->setText(word->text().right(word->text().length()-count));
        }
        return ret;
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
            if (scene!=0)
             scene->clearGraph();
            if (kretanje!=0)
                delete kretanje;
            kretanje=0;
            count = 0;
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

       if (scene!=0)
       {
           scene->clearGraph();
       }

       scene = new GraphView("thompson.dot");


       panel->setScene(scene);
       ispisi_podatke(t);
       if (kretanje!=0)
           delete kretanje;
       kretanje = 0;
       count =0;
       return true;
    }


bool AutomatProcess::glusko_draw(const QString& regular){

    opis->clear();
    try {
     parser = ParserEngine(regular);
    }
    catch (ParserException p)
        {
         if (scene!=0)
          scene->clearGraph();
         if (kretanje!=0)
             delete kretanje;
         kretanje=0;
         count = 0;
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

     if (scene!=0)
         scene->clearGraph();
     scene = new GraphView("gluskov.dot");
     panel->setScene(scene);

     if (kretanje!=0)
         delete kretanje;
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
        {
         if (scene!=0)
          scene->clearGraph();
         if (kretanje!=0)
             delete kretanje;
         kretanje=0;
         count = 0;
         return false;
        }
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

     if (scene!=0)
         scene->clearGraph();

     scene = new GraphView("deterministicki.dot");
     panel->setScene(scene);

     QList<QGraphicsItem*> items = scene->items();
     if (kretanje!=0)
         delete kretanje;
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
        {
         if (scene!=0)
          scene->clearGraph();
         if (kretanje!=0)
             delete kretanje;
         kretanje=0;
         count =0;
         return false;
        }
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

     if (scene!=0)
         scene->clear();
     scene = new GraphView("minimalni.dot");
     panel->setScene(scene);

     QList<QGraphicsItem*> items = scene->items();
     if (kretanje!=0)
         delete kretanje;
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


