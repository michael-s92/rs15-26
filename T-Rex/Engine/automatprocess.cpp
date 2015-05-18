#include "automatprocess.h"
#include <QMessageBox>
#include <fstream>
#include <QGraphicsPixmapItem>
#include "graphview.h"

using namespace std;

AutomatProcess::AutomatProcess()
{
}

AutomatProcess::~AutomatProcess()
{

}

bool AutomatProcess::tomson_draw(QString regular, QGraphicsView* panel){


   try {
    parser = ParserEngine(regular);
    Thompson::state_count=0;
    Reg_node * reg_node = parser.getRegNode();
    ThompsonNodes thompsonNodes;
    reg_node->accept(thompsonNodes);
    Thompson t = thompsonNodes.getTh();

    fstream f;
    f.open("thompson.dot",fstream::out);
    t.make_dot_file(f);
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

bool AutomatProcess::glusko_draw(QString regular, QGraphicsView* panel){


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
     g.make_dot_file(f);
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

bool AutomatProcess::determi_draw(QString regular, QGraphicsView *panel)
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
     d.make_dot_file(f);
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


bool AutomatProcess::minimal_draw(QString regular, QGraphicsView *panel){

    return false;
}
