#ifndef KRETANJE_H
#define KRETANJE_H

#include "graphview.h"
#include "Parser/automata.h"


class Kretanje
{
public:
    Kretanje();
    Kretanje(Automata & a, QList<QGraphicsItem*> & items);

    QVector<GraphNode *> nodes;
    QVector< QVector<GraphEdge *>> prelazi;
    QList<GraphEdge> istorija;
    int trenutno;

    int brojac;
    int ukupno;
    QString rec;

private:
    int br_stanja;
    QVector<char> alphabet;

};

#endif // KRETANJE_H
