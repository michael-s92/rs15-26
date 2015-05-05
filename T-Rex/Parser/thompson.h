#ifndef THOMSON_H
#define THOMSON_H

#include <QLinkedList>
#include <iostream>

class Edge {

public:
    Edge(int state1, int state2, char c)
        :_state1(state1),_state2(state2),_c(c)
    {
    }

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

private:
    int _state1;
    int _state2;
    char _c;
};


class Thompson
{
public:
    Thompson(int first, int last)
     :_first(first),_last(last)
    {

    }

    int getFirst() const
    {
        return _first;
    }

    int getLast() const
    {
        return _last;
    }

    QLinkedList<Edge> getEdges() const
    {
        return _edges;
    }

    void addEdge(int state1, int state2, char c)
    {
        Edge e(state1,state2,c);
        _edges << (e);
    }

    void addEdges(QLinkedList<Edge> edges)
    {
        _edges << edges;
     //   QLinkedList<Edge>::iterator i = edges.begin();
     //   for (; i!=edges.end(); i++)
     //      _edges->append(*i);
    }

static int state_count_min;
static int state_count_max;

private:
 int _first;
 int _last;
 QLinkedList<Edge> _edges;

};


#endif // THOMSON_H
