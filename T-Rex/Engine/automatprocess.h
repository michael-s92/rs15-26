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
    AutomatProcess(QGraphicsView* p, QPlainTextEdit* o);
    ~AutomatProcess();

    bool tomson_draw(const QString& regular);
    bool glusko_draw(const QString &regular);
    bool determi_draw(const QString &regular);
    bool minimal_draw(const QString &regular);

    void ispisi_podatke(Automata & a);

private:
    ParserEngine parser;

    QGraphicsView* panel;
    QPlainTextEdit* opis;

};


#endif // AUTOMATPROCESS_H
