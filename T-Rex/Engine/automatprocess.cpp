#include "automatprocess.h"
#include <QMessageBox>

AutomatProcess::AutomatProcess()
{
}

AutomatProcess::~AutomatProcess()
{

}

void AutomatProcess::tomson_draw(QString regular, QGraphicsView* panel){

   try {
    parser = ParserEngine(regular);
    }
  catch (ParserException p)
    {
      QMessageBox::about(0,"information","Nekorekta regularni izraz");
    }

}

void AutomatProcess::glusko_draw(QString regular, QGraphicsView* panel){

}
