#include "kretanje.h"

#include <iostream>

Kretanje::Kretanje()
{

}

Kretanje::Kretanje(int br_stanja, QList<QGraphicsItem*> & items)
 :br_stanja(br_stanja)
{
   nodes.resize(br_stanja+1);
   prelazi.resize(br_stanja+1);
   for (int i=0; i< prelazi.length(); i++)
       prelazi[i].resize(br_stanja);

   QList<QGraphicsItem*>::iterator i = items.begin();
   for (; i!=items.end(); i++)
   {
       GraphItem * j = (GraphItem*)(*i);
       if (j->ind()==0)
       {
          int state = ((GraphNode*)j)->state;
         // std::cout << "stanje " << state << std::endl;
          nodes[state+1] = (GraphNode*)j;
       }
       else
       {
           int state1 = ((GraphEdge*)j)->state1;
           int state2 = ((GraphEdge*)j)->state2;
          //std::cout << "ivica " << state1 << " " << state2<< std::endl;
           prelazi[state1+1][state2]=(GraphEdge*)j;
       }
   }
   prelazi[0][0]->setPen(QPen(Qt::green));
}

