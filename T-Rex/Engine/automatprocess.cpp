#include "automatprocess.h"
#include <QMessageBox>

AutomatProcess::AutomatProcess()
{
}

AutomatProcess::~AutomatProcess()
{

}

bool AutomatProcess::tomson_draw(QString regular, QGraphicsView* panel){

   try {
    parser = ParserEngine(regular);
    }
  catch (ParserException p)
    {
      return false;
    }

    return true;

}

bool AutomatProcess::glusko_draw(QString regular, QGraphicsView* panel){


    //test verzija
    return false;
}
