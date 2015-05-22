#ifndef KRETANJE_H
#define KRETANJE_H

#include "graphview.h"
#include "Parser/automata.h"

class Kretanje
{
public:
    Kretanje();
    Kretanje(int br_stanja, QList<QGraphicsItem*> & items);

private:
    int br_stanja;
    QVector<GraphNode *> nodes;
    QVector< QVector<GraphEdge *>> prelazi;
    QList<GraphEdge> istorija;
};

#endif // KRETANJE_H
