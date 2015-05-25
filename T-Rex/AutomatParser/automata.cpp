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

bool Edge::operator ==(const Edge &edge)
{
    return edge.getState1()==_state1 && edge.getState2()==_state2 && edge.getC()==_c;
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
    if (!_edges.contains(e))
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
    osr << "-1 -> 0 [label = \" \"];" << endl;
    osr << "}";
}

void Automata::plainTextAddAlphabet(QPlainTextEdit *opis)
{
        QString text_style = "style = '";
        text_style.append("color: red;'");
        QString text("<div " + text_style +">");
        text.append("&Sigma; = { ");
        for (int i=0; i< _alphabet.length()-1; i++)
        {
            text.append(_alphabet[i]);
            text.append(", ");
        }
        if (_alphabet.length()>0)
          text.append(_alphabet.last());
        text.append(" }");
        text.append("</div>");
        opis->appendHtml(text);
}

void Automata::plainTextAddStart(QPlainTextEdit *opis)
{
        QString text_style = "style = '";
        text_style.append("color: orange;'");
        QString text("<div " + text_style +">");
        text.append("S = { ");
        text.append(QString::number(_start_state));
        text.append(" }");
        text.append("</div>");
        opis->appendHtml(text);
}


void Automata::plainTextAddStates(QPlainTextEdit *opis)
{
        QString text_style = "style = '";
        text_style.append("color: green;'");
        QString text("<div " + text_style +">");
        text.append("Q = { ");
        for (int i=0; i< _states.length()-1; i++)
        {
            text.append(QString::number(_states[i]));
            text.append(", ");
        }
        if (_states.length()>0)
          text.append(QString::number(_states.last()));
        text.append(" }");
        text.append("</div>");
        opis->appendHtml(text);
}

void Automata::plainTextAddAcceptStates(QPlainTextEdit *opis)
{
        QString text_style = "style = '";
        text_style.append("color: blue;'");
        QString text("<div " + text_style +">");
        text.append("F = { ");
        for (int i=0; i< _accept_states.length()-1; i++)
        {
            text.append(QString::number(_accept_states[i]));
            text.append(", ");
        }
        if (_accept_states.length()>0)
           text.append(QString::number(_accept_states.last()));
        text.append(" }");
        text.append("</div>");
        opis->appendHtml(text);
}

void Automata::plainTextAddEdges(QPlainTextEdit *opis)
{
        QString text_style = "style = '";
        text_style.append("color: black;'");
        QString text("<div " + text_style +">");
        text.append("&Delta; = { ");
        for (int i=0; i< _edges.length()-1; i++)
        {
            text.append("( ");
            text.append(QString::number(_edges[i].getState1()));
            text.append(", ");
            if (_edges[i].getC()!='\0')
                 text.append(_edges[i].getC());
            else
                text.append("&epsilon;");
            text.append(", ");
            text.append(QString::number(_edges[i].getState2()));
            text.append(" ),<br>");
        }
        if (_edges.length()>0)
        {
            text.append("( ");
            text.append(QString::number(_edges.last().getState1()));
            text.append(", ");
            if (_edges.last().getC()!='\0')
               text.append(_edges.last().getC());
            else
               text.append("&epsilon;");
            text.append(", ");
            text.append(QString::number(_edges.last().getState2()));
            text.append(" ), ");
        }
        text.append(" }");
        text.append("</div>");
        opis->appendHtml(text);
}



int Thompson::state_count=0;


Thompson::Thompson()
{

}

Thompson::Thompson(int start_state, int last)
 : Automata(start_state)
{
  _accept_states.append(last);
  for (int i=0; i<=last; i++)
      _states.append(i);
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


Gluskov::Gluskov()
{

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
           QVector<int> obradjeni;
           if (kandidati.contains(j))
               epsilon_zatvorenja[j]=odredi_zatvorenje(j,obradjeni);
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

QVector<int> Gluskov::odredi_zatvorenje(int state, QVector<int> obradjeni)
{
    QVector<int> zatvorenje;
    kandidati.removeOne(state);
    obradjeni.append(state);
    zatvorenje << state;
    if (epsilon_prelazi.find(state)!=epsilon_prelazi.end())
    {
    QVector<int>::iterator i = epsilon_prelazi[state].begin();
    for (;i!=epsilon_prelazi[state].end(); i++)
        if (!obradjeni.contains(*i))
          zatvorenje << odredi_zatvorenje(*i, obradjeni);
    }
    cout << "3" << endl;
    return zatvorenje;
}

Deterministicki Gluskov::makeDeterministicki()
{
  Deterministicki d(*this);
  return d;
}


int Deterministicki::state_count = 0;

Deterministicki::Deterministicki()
{

}

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



Minimalni::Minimalni()
{

}




Minimalni::Minimalni(const Deterministicki &d)
{
   QVector<QVector<int>> prelaziD = d.getPrelazi();
   _alphabet = d.getAlphabet();
   _start_state=0;

   classes.resize(d.getStates().length());

   if (d.getAcceptStates().length()!=d.getStates().length())
   {
       for (int i=0; i<d.getStates().length(); i++)
            if (d.getAcceptStates().contains(i))
            {
            classes[i]=1;
            classes_map[1].append(i);
            }
       else
            {
            classes[i]=0;
            classes_map[0].append(i);
            }

   bool ind_promene = 1;
   bool ind_state = 0;
   while(ind_promene)
   {
     ind_promene=0;
     int br_iteracija = state_count;
     for (int i=0; i< br_iteracija; i++)
     {
        ind_state = false;

        if (classes_map[i].length()==1)
            continue;
        for (int j=1; j<classes_map[i].length(); j++)
        {
            for (int k=0; k<_alphabet.length(); k++)
            {
               int state1=prelaziD[classes_map[i][0]][k];
               int state2=prelaziD[classes_map[i][j]][k];
               if (classes[state1]!=classes[state2])
               {
                   classes_map[state_count].append(classes_map[i][j]);
                   ind_promene=1;
                   ind_state = 1;
                   break;
               }
            }
        }
        if (ind_state==1)
        {
            QVector<int>::iterator it= classes_map[state_count].begin();
            for (; it!=classes_map[state_count].end();it++)
            {
              classes[*it]=state_count;
              classes_map[i].remove(classes_map[i].indexOf(*it));
            }
            state_count++;
        }
     }
   }

   }
   else
   {
      state_count=1;
      for (int i=0; i<d.getAcceptStates().length(); i++)
      {
          classes[i]=0;
          classes_map[0].append(i);
      }
   }


   prelazi.resize(state_count);
   for (int i=0; i< prelazi.length(); i++)
       prelazi[i].resize(_alphabet.length());

   for (int i=0; i< d.getStates().length(); i++)
   {
       if (d.getAcceptStates().contains(i))
           addAcceptState(classes[i]);
   }

   for (int i=0; i < prelazi.length(); i++)
   {
       addState(i);
   }

   for (int i=0; i < prelaziD.length(); i++)
   {
       for (int j=0; j < prelaziD[0].length(); j++)
       {
           int state = prelaziD[i][j];
           prelazi[classes[i]][j] = classes[state];
           addEdge(classes[i],prelazi[classes[i]][j],_alphabet[j]);
       }
   }
}




void ispisi_mapu(QMap<int,QVector<int>> classes_map)
{
    QMap<int, QVector<int>>::iterator ix = classes_map.begin();
    for (; ix!=classes_map.end(); ix++)
    {
        cout << ix.key() << ": ";
        QVector<int> a = ix.value();
        QVector<int>::iterator iy= a.begin();
        for (; iy!=a.end(); iy++)
            cout << *iy << " ";
        cout << endl;
    }
}


void ispisi_vektor(QVector<int> classes)
{
    QVector<int>::iterator ix = classes.begin();
    for (; ix!=classes.end(); ix++)
        cout << *ix << " ";
    cout << endl;
}



