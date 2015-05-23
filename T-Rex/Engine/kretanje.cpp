#include "kretanje.h"

#include <iostream>

Kretanje::Kretanje()
{

}

Kretanje::Kretanje(Automata & a, QList<QGraphicsItem*> & items)
{

   trenutno = -1;
   alphabet = a.getAlphabet();
   zavrsna = a.getAcceptStates();
   br_stanja = a.getStates().length();

   nodes.resize(br_stanja+1);
   prelazi.resize(br_stanja+1);
   for (int i=0; i< prelazi.length(); i++)
       prelazi[i].resize(alphabet.length()+1);

   QList<QGraphicsItem*>::iterator i = items.begin();
   for (; i!=items.end(); i++)
   {
       GraphItem * j = (GraphItem*)(*i);
       if (j->ind()==0)
       {
          int state = ((GraphNode*)j)->state;
          nodes[state+1] = (GraphNode*)j;
       }
       else
       {
           int state1 = ((GraphEdge*)j)->state1;
           char c = ((GraphEdge*)j)->c;
           int x = alphabet.indexOf(c);
           prelazi[state1+1][x+1]=(GraphEdge*)j;
       }
   }
}

int Kretanje::kreci_se_napred(char c)
{
    istorija.back()->setPen(QPen(Qt::black));
    nodes[trenutno+1]->setBrush(QBrush(Qt::green));
    int i = alphabet.indexOf(c);
    if (i==-1)
        return -3;
    istorija.append(prelazi[trenutno+1][i+1]);
    trenutno = prelazi[trenutno+1][i+1]->state2;
    QPen pen(Qt::blue);
    pen.setWidth(3);
    istorija.back()->setPen(pen);
    nodes[trenutno+1]->setBrush(QBrush(Qt::blue));
    return 0;
}

int Kretanje::kreci_se_nazad()
{
    nodes[trenutno+1]->setBrush(QBrush(Qt::green));
    istorija.back()->setPen(QPen(Qt::black));
    trenutno = istorija.back()->state1;
    istorija.pop_back();
    nodes[trenutno+1]->setBrush(QBrush(Qt::blue));
    QPen pen(Qt::blue);
    pen.setWidth(3);
    istorija.back()->setPen(pen);
    return 0;
}

int Kretanje::postavi_na_pocetak()
{
    if (trenutno!=-1)
    {
        istorija.back()->setPen(QPen(Qt::black));
        nodes[trenutno+1]->setBrush(QBrush(Qt::green));
    }
    QPen pen(Qt::blue);
    pen.setWidth(3);
    prelazi[0][0]->setPen(pen);
    nodes[1]->setBrush(QBrush(Qt::blue));
    trenutno=0;
    istorija.clear();
    istorija.append(prelazi[0][0]);
    return 0;
}

