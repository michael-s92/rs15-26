#include "automatprocess.h"
#include <QMessageBox>
#include <fstream>
#include <QGraphicsPixmapItem>
#include "graphview.h"

using namespace std;

AutomatProcess::AutomatProcess(QGraphicsView* p, QPlainTextEdit* o)
    :panel(p), opis(o)
{
}

AutomatProcess::~AutomatProcess()
{

}

bool AutomatProcess::tomson_draw(const QString &regular){

   try {
    parser = ParserEngine(regular);
    Thompson::state_count=0;
    Reg_node * reg_node = parser.getRegNode();
    ThompsonNodes thompsonNodes;
    reg_node->accept(thompsonNodes);
    Thompson t = thompsonNodes.getTh();

    fstream f;
    f.open("thompson.dot",fstream::out);
    t.makeDotFile(f);
    f.close();

    QGraphicsScene *scene = new GraphView("thompson.dot");

    panel->setRenderHint(QPainter::Antialiasing);
    panel->setRenderHint(QPainter::TextAntialiasing);
    panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    panel->setScene(scene);

    }
  catch (ParserException p)
    {
      return false;
    }

     return true;


}

bool AutomatProcess::glusko_draw(const QString& regular){


    try {
     parser = ParserEngine(regular);
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

     panel->setRenderHint(QPainter::Antialiasing);
     panel->setRenderHint(QPainter::TextAntialiasing);
     panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
     panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

     panel->setScene(scene);



     }
   catch (ParserException p)
     {
       return false;
     }

     return true;

 }

bool AutomatProcess::determi_draw(const QString& regular)
{

    try {
     parser = ParserEngine(regular);
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

     panel->setRenderHint(QPainter::Antialiasing);
     panel->setRenderHint(QPainter::TextAntialiasing);
     panel->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
     panel->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

     panel->setScene(scene);


     }
   catch (ParserException p)
     {
       return false;
     }

     return true;

 }


bool AutomatProcess::minimal_draw(const QString &regular){

    try {
        parser = ParserEngine(regular);
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


    }
    catch (ParserException p)
    {
        return false;
    }

    return true;

}
