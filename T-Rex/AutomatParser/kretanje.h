#ifndef KRETANJE_H
#define KRETANJE_H

#include "graphview.h"
#include "AutomatParser/automata.h"


class Kretanje
{
public:
    Kretanje();
    Kretanje(Automata & a, QList<QGraphicsItem*> & items);

    int kreci_se_napred(char c);
    int kreci_se_nazad();
    int postavi_na_pocetak();

    int trenutno;
    QVector<int> zavrsna;

private:
    int br_stanja;
    QVector<char> alphabet;
    QVector<GraphNode *> nodes;
    QVector< QVector<GraphEdge *>> prelazi;
    QList<GraphEdge*> istorija;


};

#endif // KRETANJE_H
