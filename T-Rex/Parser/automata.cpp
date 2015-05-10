#include "automata.h"
#include <QMap>

using namespace std;

Edge::Edge(int state1, int state2, char c)
    :_state1(state1),_state2(state2),_c(c)
{
}

int Thompson::state_count=0;

void Automata::make_dot_file(ostream &osr)
{
    osr << "digraph G {" << endl;
    osr <<" rankdir = LR;" << endl;
    osr <<"node [shape = none];" << endl;
    osr << "-1;" << endl;
    osr <<" node [shape = circle];" << endl;
    int j;
    for (j=0; j<_stanja.length(); j++)
    {
        if(!_zavrsna.contains(_stanja[j]))
          osr << _stanja[j] << "[label=\"" << _stanja[j] << "\"];" << endl;
        else
          osr << _stanja[j] << "[label=\"" << _stanja[j] << "\" shape=\"doublecircle\"];" << endl;
    }
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

    QVector<Edge>::iterator iter = g.prelazi.begin();
    for (; iter!=g.prelazi.end(); iter++)
    {
        QMap<int, QVector<int>>::iterator i = g.epsilon_zatvorenja.begin();
        QMap<int, QVector<int>>::iterator j;
        for (; i!=g.epsilon_zatvorenja.end(); i++)
            for (j=i; j!=g.epsilon_zatvorenja.end(); j++)
                if (i.value().contains(iter->getState1()) &&
                    j.value().contains(iter->getState2()))
                   g.addEdge(i.key(),j.key(),iter->getC());
    }

    QMap<int, QVector<int>>::iterator it = g.epsilon_zatvorenja.begin();
    for (; it!= g.epsilon_zatvorenja.end(); it++)
    {
        g._stanja.append(it.key());
        if (it.value().contains(getLast()))
            g._zavrsna.append(it.key());
    }

    return g;
}
