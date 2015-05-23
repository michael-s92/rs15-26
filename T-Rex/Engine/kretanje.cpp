#include "kretanje.h"

#include <iostream>

Kretanje::Kretanje()
{

}

Kretanje::Kretanje(Automata & a, QList<QGraphicsItem*> & items)
{

   trenutno = -1;
   alphabet = a.getAlphabet();
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

