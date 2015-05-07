#include "thompson.h"
#include <QMap>

using namespace std;

int Thompson::state_count=0;

void Automata::make_dot_file(ostream &osr)
{
    osr << "digraph G {" << endl;
    osr <<" rankdir = LR;" << endl;
    osr <<"node [shape = none];" << endl;
    osr << "-1;" << endl;
    osr <<" node [shape = circle];" << endl;
    int j;
    for (j=0; j<Thompson::state_count-1; j++)
        osr << j << "[label=\"" << j << "\"];" << endl;
    osr << j << "[label=\"" << j << "\" shape=\"doublecircle\"];" << endl;

    QVector<Edge>::iterator i = _edges.begin();
    for (;i!=_edges.end(); i++)
    {
        osr << (*i).getState1() << "->" << (*i).getState2();
        if ((*i).getC()=='\0')
            osr <<"[label=\"&epsilon;\"];" << endl;
        else
          osr <<"[label=\"" << (char)(*i).getC() << "\"];" << endl;
    }

    osr << "-1 [label = \"\"];" << endl;
    osr << "-1 -> 0 [label = \"\"];" << endl;
    osr << "}";
}


Gluskov Thompson::make_gluskov()
{
    Gluskov g;
    QVector<Edge>::iterator i = _edges.begin();
    for (; i!=_edges.end(); i++)
    {
        if (i->getC()!='\0')
            g.prelazi << *i;
        else
        {
            if (g.epsilon_prelazi.find(i->getState1())==g.epsilon_prelazi.end())
              g.epsilon_prelazi[i->getState1()] = QVector<int>();
            g.epsilon_prelazi[i->getState1()] << i->getState2();
         }
    }


    for (int j=0; j<Thompson::state_count; j++)
    {
        if (g.kandidati.contains(j))
            g.epsilon_zatvorenja[j]=g.odredi_zatvorenje(j);
    }


    QMap<int, QVector<int>>::iterator j1=g.epsilon_zatvorenja.begin();
    for (; j1!=g.epsilon_zatvorenja.end(); j1++)
    {
        std::cout << j1.key() << ": ";
        QVector<int>::iterator k = j1.value().begin();
        for(; k!=(*j1).end(); k++)
        {
            std::cout << *k << " ";
        }
        std::cout << std::endl;
    }

    return g;
}
