#include "automatprocess.h"
#include <QMessageBox>
#include <fstream>
#include <QGraphicsPixmapItem>
#include "graphview.h"

using namespace std;

AutomatProcess::AutomatProcess(QGraphicsView* p, QPlainTextEdit* o)
    :panel(p), opis(o)
{
    panel->setRenderHint(QPainter::Antialiasing);
    panel->setRenderHint(QPainter::TextAntialiasing);
    panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

AutomatProcess::~AutomatProcess()
{

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

       QList<QGraphicsItem *> items = scene->items();
       QList<QGraphicsItem *>::iterator i = items.begin();
       for (; i!=items.end(); i++)
       {
       GraphItem *j = (GraphItem *)(*i);
       if (j->ind()==0)
           j->setPen(QPen(Qt::red));
       else
           j->setPen(QPen(Qt::blue));
       }




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


