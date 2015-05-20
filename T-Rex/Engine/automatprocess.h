#ifndef AUTOMATPROCESS_H
#define AUTOMATPROCESS_H

#include <QString>
#include <QGraphicsView>
#include <QPlainTextEdit>
#include "parserengine.h"
#include "Parser/TreeNodes.hpp"
#include "Parser/visitor_nodes.h"

class AutomatProcess
{
public:
    AutomatProcess();
    ~AutomatProcess();

    bool tomson_draw(QString regular, QGraphicsView* panel, QPlainTextEdit* opis);
    bool glusko_draw(QString regular, QGraphicsView* panel, QPlainTextEdit* opis);
    bool determi_draw(QString regular, QGraphicsView* panel, QPlainTextEdit* opis);
    bool minimal_draw(QString regular, QGraphicsView* panel, QPlainTextEdit* opis);


private:
    ParserEngine parser;

};

#endif // AUTOMATPROCESS_H
