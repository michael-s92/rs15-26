#ifndef KRETANJE_H
#define KRETANJE_H

#include "graphview.h"

class Kretanje
{
public:
    Kretanje();
    Kretanje(int br_stanja);

private:
    int br_stanja;
    QVector<GraphNode *> nodes;
    QVector< QVector<GraphEdge *>> prelazi;
};

#endif // KRETANJE_H
