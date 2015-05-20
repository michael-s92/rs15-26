#include "automata.h"
#include <QMap>
#include <QtAlgorithms>

// TO-DO
// sve iteratore zameniti ugradjenim iteratorima


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

bool Edge::equal1(int state, char c)
{
    if (state ==_state1 && c==_c)
        return true;
    return false;
}

Automata::Automata(int start_state)
    :_start_state(start_state)
{}

int Automata::getStart() const
{
    return _start_state;
}

QVector<int> Automata::getAcceptStates() const
{
    return _accept_states;
}

QVector<Edge> Automata::getEdges() const
{
    return _edges;
}

QVector<char> Automata::getAlphabet() const
{
    return _alphabet;
}

QVector<int> Automata::getStates() const
{
    return _states;
}

void Automata::setStart(int start_state)
{
    _start_state=start_state;
}

void Automata::addAcceptState(int accept_state)
{
    _accept_states.append(accept_state);

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

void Automata::addChar(char c)
{
    if (!_alphabet.contains(c))
        _alphabet.append(c);
}

void Automata::addAlphabet(QVector<char> alphabet)
{
    QVector<char>::iterator i = alphabet.begin();
    for (; i!=alphabet.end(); i++)
        if (!_alphabet.contains(*i))
            _alphabet.append(*i);
}

void Automata::addState(int state)
{
   _states.append(state);
}

void Automata::makeDotFile(ostream &osr)
{
    osr << "digraph G {" << endl;
    osr <<" rankdir = LR;" << endl;
    osr <<"node [shape = none];" << endl;
    osr << "-1;" << endl;
    osr <<" node [shape = circle];" << endl;
    int j;
    for (j=0; j<_states.size(); j++)
    {
        if(!_accept_states.contains(_states[j]))
          osr << _states[j] << "[label=\"" << _states[j] << "\"];" << endl;
        else
          osr << _states[j] << "[label=\"" << _states[j] << "\" shape=\"doublecircle\"];" << endl;
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

int Thompson::state_count=0;


Thompson::Thompson()
{

}

Thompson::Thompson(int start_state, int last)
 : Automata(start_state)
{
  _accept_states.append(last);
}

int Thompson::getLast() const
{
  return _accept_states[0];
}


Gluskov Thompson::make_gluskov()
{
    Gluskov g(*this);
    return g;
}


Gluskov::Gluskov(const Thompson & t)
 :Automata(0)
   {
       for (int i=0; i<Thompson::state_count; i++)
           kandidati << i;
       QVector<Edge> edges_T = t.getEdges();
       QVector<Edge>::iterator i = edges_T.begin();
       for (; i!=edges_T.end(); i++)
       {
           if (i->getC()!='\0')
               prelazi_po_slovu << *i;
           else
               epsilon_prelazi[i->getState1()] << i->getState2();
       }

       for (int j=0; j<Thompson::state_count; j++)
       {
           if (kandidati.contains(j))
               epsilon_zatvorenja[j]=odredi_zatvorenje(j);
       }

       QVector<Edge>::iterator iter = prelazi_po_slovu.begin();
       for (; iter!=prelazi_po_slovu.end(); iter++)
       {
           QMap<int, QVector<int>>::iterator i = epsilon_zatvorenja.begin();
           QMap<int, QVector<int>>::iterator j;
           for (; i!=epsilon_zatvorenja.end(); i++)
           {
               j = epsilon_zatvorenja.begin();
               for (; j!=epsilon_zatvorenja.end(); j++)
                   if (i.value().contains(iter->getState1()) &&
                       j.value().contains(iter->getState2()))
                      addEdge(i.key(),j.key(),iter->getC());
           }
       }

       QMap<int, QVector<int>>::iterator it = epsilon_zatvorenja.begin();
       for (; it!= epsilon_zatvorenja.end(); it++)
       {
           addState(it.key());
           if (it.value().contains(t.getLast()))
               addAcceptState(it.key());
       }
       addAlphabet(t.getAlphabet());
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
  Deterministicki d(*this);
  return d;
}


int Deterministicki::state_count = 0;

Deterministicki::Deterministicki(const Gluskov & g)
{
  QVector<int> start;
  start.append(0);
  kandidati[Deterministicki::state_count++] = start;
  addAlphabet(g.getAlphabet());
  qSort(_alphabet);
  setStart(0);
  prelazi_G = g.getEdges();
  dodajPrelaze(0,g);

  prelazi.resize(state_count);
  for (int i=0; i<state_count; i++)
      prelazi[i].resize(_alphabet.length());

  QVector<Edge>::iterator i = _edges.begin();
  for (; i!=_edges.end(); i++)
  {
      int index = _alphabet.indexOf(i->getC());
      prelazi[i->getState1()][index] = i->getState2();
  }

  QMap<int, QVector<int>>::iterator i11 = kandidati.begin();
  for (; i11!=kandidati.end();i11++)
  {
      QVector<int>::iterator i22 = i11->begin();
      cout << i11.key() << " - ";
      for (; i22!=i11->end(); i22++)
              cout << *i22 << " ";
      cout << endl;
  }

}


void Deterministicki::dodajPrelaze(int i, const Gluskov & g)
{
    QVector<int> stanja = kandidati[i];
    addState(i);

    QVector<int>::iterator i1 = stanja.begin();
    for (; i1!=stanja.end(); i1++)
    if (g.getAcceptStates().contains(*i1))
    {
        addAcceptState(i);
        break;
    }

    QVector<char>::iterator i_slova = _alphabet.begin();
    for (; i_slova!=_alphabet.end(); i_slova++)
    {
        if (kandidati[i].size()==0)
        {
            addEdge(i,i,*i_slova);
            continue;
        }

        QVector<int> stanjaPoSlovu;

        QVector<int>::iterator i_stanja = stanja.begin();
        for (; i_stanja!=stanja.end(); i_stanja++)
        {
           QVector<Edge>::iterator i_edges = prelazi_G.begin();
           for (; i_edges!=prelazi_G.end(); i_edges++)
           {
               if (i_edges->equal1(*i_stanja, *i_slova))
               {
                   if (!stanjaPoSlovu.contains(i_edges->getState2()))
                   stanjaPoSlovu.append(i_edges->getState2());
               }
           }
        }
           QVector<int>::iterator ixx = stanjaPoSlovu.begin();
           for (; ixx!=stanjaPoSlovu.end(); ixx++)
           {
               cout << *ixx << " ";
           }
           cout << endl << "xxxxxxxxxxxxxxxxxx" << endl;

           if (!kandidati.values().contains(stanjaPoSlovu))
           {
               kandidati[state_count] = stanjaPoSlovu;
               addEdge(i,state_count,*i_slova);
               dodajPrelaze(state_count++,g);
           }
           else
               addEdge(i,kandidati.key(stanjaPoSlovu),*i_slova);
    }
}

Minimalni Deterministicki::makeMinimalni()
{
    Minimalni m(*this);
    return m;
}

QVector<QVector<int>> Deterministicki::getPrelazi() const
{
    return prelazi;
}


int Minimalni::state_count = 2;



Minimalni::Minimalni(const Deterministicki &d)
{
   QVector<QVector<int>> prelaziD = d.getPrelazi();
   _alphabet = d.getAlphabet();

   for (int i=d.getStates().length()-1; i>=0; i--)
   if (d.getAcceptStates().contains(i))
       classes.insertMulti(1,i);
   else
       classes.insertMulti(0,i);

   bool ind_promene = 1;
   while(ind_promene)
   {
     ind_promene=0;

     QMultiMap<int,int>::iterator i_map = classes.begin();
     for (; i_map!=classes.end();)
     {
        QMultiMap<int,int>::iterator j_map = i_map++;
        while((j_map.key()==i_map.key()))
         {
          for (int j=0; j<prelaziD[0].length(); j++)
          {
             int state1=prelaziD[j_map.value()][j];
             int state2=prelaziD[i_map.value()][j];

             if (classes.key(state1)!=classes.key(state2))
             {
                 int remove_key = i_map.key();
                 int value = i_map.value();
                 classes.remove(remove_key,value);
                 classes.insertMulti(state_count,value);

                 ind_promene=1;
                 break;
             }
          }
          i_map++;
        }
        if (ind_promene==1)
        {
            state_count++;
            break;
        }
     }
   }

   prelazi.resize(state_count);
   for (int i=0; i< prelazi.length(); i++)
       prelazi[i].resize(_alphabet.length());

   for (int i=0; i < prelazi.length(); i++)
   {
       addState(i);
       QList<int> stanja = classes.values(i);
       QList<int>::iterator it = stanja.begin();
       for (; it!=stanja.end(); it++)
       {
           if (d.getAcceptStates().contains(*it))
               if (!_accept_states.contains(i))
                   addAcceptState(i);
       }
       for (int j=0; j < prelazi[0].length(); j++)
       {
           int state = prelaziD[classes.value(i)][j];
           prelazi[i][j] = classes.key(state);
           addEdge(i,prelazi[i][j],_alphabet[j]);
       }
   }


}
