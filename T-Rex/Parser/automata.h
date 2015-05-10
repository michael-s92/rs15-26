#ifndef THOMSON_H
#define THOMSON_H

#include <QVector>
#include <iostream>
#include <QMap>
#include <QLinkedList>

class Gluskov;

class Edge {

public:

    Edge()
    {}

    Edge(int state1, int state2, char c);

    int getState1() const
    {
        return _state1;
    }

    int getState2() const
    {
        return _state2;
    }

    int getC() const
    {
        return _c;
    }

    void setState1(int state1)
    {
        _state1 = state1;
    }


    void setState2(int state2)
    {
        _state2 = state2;
    }

private:
    int _state1;
    int _state2;
    char _c;
};


class Automata
{
public:
    QVector<int> _stanja;
    int _first;
    QVector<int> _zavrsna;
    QVector<Edge> _edges;

public:
    Automata()
    {}
    Automata(int first)
     :_first(first)
    {}

    int getFirst() const
    {
        return _first;
    }

    QVector<int> getZavrsna() const
    {
        return _zavrsna;
    }

    QVector<Edge> getEdges() const
    {
        return _edges;
    }

    void setFirst(int first)
    {
        _first=first;
    }

    void addZavrsno(int state)
    {
        _zavrsna.append(state);
    }

    void addEdge(int state1, int state2, char c)
    {
        Edge e(state1,state2,c);
        _edges << e;
    }

    void addEdges(QVector<Edge> edges)
    {
        _edges << edges;
    }

    void make_dot_file(std::ostream & osr);

};


class Thompson : public Automata
{
public:
    Thompson()
    {}
    Thompson(int first, int last)
     : Automata(first)
    {
       _zavrsna.append(last);
    }

    int getLast() const
    {
        return _zavrsna[0];
    }

    Gluskov make_gluskov();


static int state_count;

};



class Gluskov : public Automata
{
public:
  Gluskov()
   :Automata(0)
  {
      for (int i=0; i<Thompson::state_count; i++)
          kandidati << i;
  }

  QMap<int, QVector<int>> epsilon_prelazi;
  QVector<Edge> prelazi;
  QMap<int,QVector<int>> epsilon_zatvorenja;
  QLinkedList<int> kandidati;

  QVector<int> odredi_zatvorenje(int state)
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

};



#endif // THOMSON_H
