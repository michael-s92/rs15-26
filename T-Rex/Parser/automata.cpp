#include "automata.h"
#include <QMap>

using namespace std;

Edge::Edge()
{
}

Edge::Edge(int state1, int state2, char c)
    :_state1(state1),_state2(state2),_c(c)
{
}

int Edge::getState1() const
{
    return _state1;
}

int Edge::getState2() const
{
    return _state2;
}

int Edge::getC() const
{
    return _c;
}

void Edge::setState1(int state1)
{
    _state1 = state1;
}

void Edge::setState2(int state2)
{
    _state2 = state2;
}

bool Edge::equal1(int state, char c)
{
    if (state ==_state1 && c==_c)
        return true;
    return false;
}

int Thompson::state_count=0;

Automata::Automata(int first)
    :_first(first)
{}

int Automata::getFirst() const
{
    return _first;
}

QVector<int> Automata::getZavrsna() const
{
    return _zavrsna;
}

QVector<Edge> Automata::getEdges() const
{
    return _edges;
}

QVector<char> Automata::getSlova() const
{
    return _slova;
}

void Automata::setFirst(int first)
{
    _first=first;
}

void Automata::addZavrsno(int state)
{
    _zavrsna.append(state);

}

void Automata::addEdge(int state1, int state2, char c)
{
    Edge e(state1,state2,c);
    _edges << e;
}

void Automata::addEdges(QVector<Edge> edges)
{
    _edges << edges;
}

void Automata::addSlovo(char c)
{
    if (!_slova.contains(c))
        _slova.append(c);
}

void Automata::addSlova(QVector<char> slova)
{
    QVector<char>::iterator i = slova.begin();
    for (; i!=slova.end(); i++)
        if (!_slova.contains(*i))
        _slova.append(*i);
}

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


Thompson::Thompson()
{

}

Thompson::Thompson(int first, int last)
 : Automata(first)
   {
    _zavrsna.append(last);
}

int Thompson::getLast() const
{
  return _zavrsna[0];
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
        {
            j = g.epsilon_zatvorenja.begin();
            for (; j!=g.epsilon_zatvorenja.end(); j++)
                if (i.value().contains(iter->getState1()) &&
                    j.value().contains(iter->getState2()))
                   g.addEdge(i.key(),j.key(),iter->getC());
        }
    }

    QMap<int, QVector<int>>::iterator it = g.epsilon_zatvorenja.begin();
    for (; it!= g.epsilon_zatvorenja.end(); it++)
    {
        g._stanja.append(it.key());
        if (it.value().contains(getLast()))
            g._zavrsna.append(it.key());
    }
    g._slova = _slova;
    return g;
}


Gluskov::Gluskov()
 :Automata(0)
   {
       for (int i=0; i<Thompson::state_count; i++)
           kandidati << i;
   }

QVector<int> Gluskov::odredi_zatvorenje(int state)
{
    QVector<int> zatvorenje;
    kandidati.removeOne(state);
    zatvorenje << state;
    if (epsilon_prelazi.find(state)!=epsilon_prelazi.end())
    {
    QVector<int>::iterator i = epsilon_prelazi[state].begin();
    for (;i!=epsilon_prelazi[state].end(); i++)
        zatvorenje << odredi_zatvorenje(*i);
    }
    return zatvorenje;
}

Deterministicki Gluskov::makeDeterministicki()
{
  Deterministicki d;
  d._slova = _slova;
  d._first = 0;
  d.prelazi_G = _edges;
  d.dodajPrelaze(0);

  QVector<Edge> edges = d.getEdges();
  QVector<Edge>::iterator i = edges.begin();
  for (; i!=edges.end(); i++)
      cout << i->getState1() << " " << i->getState2() << " " << i->getC() << endl;
  return d;
}


int Deterministicki::state_count = 0;

Deterministicki::Deterministicki()
{
  QVector<int> start;
  start.append(0);
  kandidati[Deterministicki::state_count++] = start;
}

void Deterministicki::dodajPrelaze(int i)
{
    QVector<int> stanja = kandidati[i];

    QVector<char>::iterator i_slova = _slova.begin();
    for (; i_slova!=_slova.end(); i_slova++)
    {
        cout << *i_slova << endl;

        if (kandidati[i].size()==0)
        {
            addEdge(i,i,*i_slova);
            continue;
        }

        QVector<int>::iterator i_stanja = stanja.begin();
        for (; i_stanja!=stanja.end(); i_stanja++)
        {
           QVector<int> stanjaPoSlovu;
           cout << *i_stanja << endl;
           QVector<Edge>::iterator i_edges = prelazi_G.begin();
           for (; i_edges!=prelazi_G.end(); i_edges++)
           {
               cout << "Ivica" << endl;
               if (i_edges->equal1(*i_stanja, *i_slova))
                   stanjaPoSlovu.append(i_edges->getState2());
           }
           if (!kandidati.values().contains(stanjaPoSlovu))
           {
               cout << "State: " << state_count << endl;
               QVector<int>::iterator it = stanjaPoSlovu.begin();
               for (;it!=stanjaPoSlovu.end(); it++)
                   cout << *it;
               cout << "xxx" << endl;
               kandidati[state_count] = stanjaPoSlovu;
               addEdge(i,state_count,*i_slova);
               dodajPrelaze(state_count++);
           }
           else
               addEdge(i,kandidati.key(stanjaPoSlovu),*i_slova);
        }
    }



}


