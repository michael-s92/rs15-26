#ifndef THOMSON_H
#define THOMSON_H

#include <QVector>
#include <iostream>
#include <QMap>
#include <QLinkedList>

class Gluskov;
class Deterministicki;

class Edge {

public:

    Edge();
    Edge(int state1, int state2, char c);

    int getState1() const;
    int getState2() const;
    int getC() const;

    void setState1(int state1);
    void setState2(int state2);

    bool equal1(int state, char c);

private:
    int _state1;
    int _state2;
    char _c;
};



class Automata
{
    //TO-DO
    //prebaciti u protected

public:
    QVector<int> _stanja;
    int _first;
    QVector<int> _zavrsna;
    QVector<Edge> _edges;
    QVector<char> _slova;

public:
    Automata()
    {}
    Automata(int first);

    int getFirst() const;
    QVector<int> getZavrsna() const;
    QVector<Edge> getEdges() const;
    QVector<char> getSlova() const;
    void setFirst(int first);
    void addZavrsno(int state);
    void addEdge(int state1, int state2, char c);
    void addEdges(QVector<Edge> edges);
    void addSlovo(char c);
    void addSlova(QVector<char> slova);

    void make_dot_file(std::ostream & osr);
};


class Thompson : public Automata
{
public:
    Thompson();
    Thompson(int first, int last);

    int getLast() const;
    Gluskov make_gluskov();

static int state_count;
};



class Gluskov : public Automata
{ 
 //TO-DO
 // ne treba sve da bude public
public:
  Gluskov();
  QMap<int, QVector<int>> epsilon_prelazi;
  QVector<Edge> prelazi;
  QMap<int,QVector<int>> epsilon_zatvorenja;
  QLinkedList<int> kandidati;

  QVector<int> odredi_zatvorenje(int state);
  Deterministicki makeDeterministicki();
};

class Deterministicki : public Automata
{
public:
    Deterministicki();
    QMap<int, QVector<int>> kandidati;
    QVector<Edge> prelazi_G;
    void dodajPrelaze(int i);

  static int state_count;
};



#endif // THOMSON_H
