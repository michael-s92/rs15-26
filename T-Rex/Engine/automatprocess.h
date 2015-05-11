#ifndef AUTOMATPROCESS_H
#define AUTOMATPROCESS_H

#include <QString>
#include <QGraphicsView>
#include "parserengine.h"

class AutomatProcess
{
public:
    AutomatProcess();
    ~AutomatProcess();

    void tomson_draw(QString regular, QGraphicsView* panel);
    void glusko_draw(QString regular, QGraphicsView* panel);

private:
    ParserEngine parser;

};

#endif // AUTOMATPROCESS_H
