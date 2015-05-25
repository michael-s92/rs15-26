#ifndef THOMSON_H
#define THOMSON_H

#include <QVector>
#include <iostream>
#include <QMap>
#include <QLinkedList>
#include <QtWidgets>

class Gluskov;
class Deterministicki;
class Minimalni;

class Edge {

public:

    Edge();
    Edge(int state1, int state2, char c);

    int getState1() const;
    int getState2() const;
    int getC() const;

    // videti jos koliko ima smisla za ovu funkciju
    // nesto prakticnije
    bool equal1(int state, char c);
    bool operator == (const Edge & edge);

private:
    int _state1;
    int _state2;
    char _c;
};



class Automata
{

protected:
    int _start_state;
    QVector<int> _states;
    QVector<int> _accept_states;
    QVector<Edge> _edges;
    QVector<char> _alphabet;

public:
    Automata()
    {}
    Automata(int start_state);

    int getStart() const;
    QVector<int> getAcceptStates() const;
    QVector<Edge> getEdges() const;
    QVector<char> getAlphabet() const;
    QVector<int> getStates() const;

    void setStart(int start_state);
    void addAcceptState(int accept_state);
    void addEdge(int state1, int state2, char c);
    void addEdges(QVector<Edge> edges);
    void addChar(char c);
    void addAlphabet(QVector<char> alphabet);
    void addState(int state);

    void makeDotFile(std::ostream & osr);

    void plainTextAddAlphabet(QPlainTextEdit* opis);
    void plainTextAddStart(QPlainTextEdit* opis);
    void plainTextAddStates(QPlainTextEdit *opis);
    void plainTextAddAcceptStates(QPlainTextEdit *opis);
    void plainTextAddEdges(QPlainTextEdit *opis);

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
  Gluskov(const Thompson & t);
  Deterministicki makeDeterministicki();

private:
  QMap<int,QVector<int>> epsilon_zatvorenja;
  QLinkedList<int> kandidati;
  QVector<int> odredi_zatvorenje(int state);
  QMap<int, QVector<int>> epsilon_prelazi;
  QVector<Edge> prelazi_po_slovu;

};

class Deterministicki : public Automata
{
public:
    Deterministicki();
    Deterministicki(const Gluskov & g);
    Minimalni makeMinimalni();
    QVector<QVector<int>> getPrelazi() const;
    static int state_count;

private:
    QMap<int, QVector<int>> kandidati;
    QVector<QVector<int>> prelazi;
    QVector<Edge> prelazi_G;
    void dodajPrelaze(int i, const Gluskov & g);
};

class Minimalni : public Automata
{
public:
    Minimalni();
    Minimalni (const Deterministicki & d);
    static int state_count;

private:
    //QMultiMap<int, int> classes;
    QVector<QVector<int>> prelazi;
    QMap<int, QVector<int> > classes_map;
    QVector<int> classes;
};

void ispisi_mapu(QMap<int,QVector<int>> classes_map);
void ispisi_vektor(QVector<int> classes);

#endif // THOMSON_H
