#include "thompson.h"

using namespace std;

int Thompson::state_count_min=-1;
int Thompson::state_count_max=0;


void Thompson::make_dot_file(ostream &osr)
{
    osr << "digraph G {" << endl;
    osr <<" rankdir = LR;" << endl;
    osr <<"node [shape = none];" << endl;
    osr << "-1;" << endl;
    osr <<" node [shape = circle];" << endl;
    int j;
    for (j=0; j<state_count_max-state_count_min -2; j++)
        osr << j << "[label=\"" << j << "\"];" << endl;
    osr << j << "[label=\"" << j << "\" shape=\"doublecircle\"];" << endl;


    set_edges_count_zero();

    QLinkedList<Edge>::iterator i = _edges.begin();
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

void Thompson::set_edges_count_zero()
{
    QLinkedList<Edge>::iterator i = _edges.begin();
    for (;i!=_edges.end(); i++)
    {
        (*i).setState1((*i).getState1()-state_count_min-1);
        (*i).setState2((*i).getState2()-state_count_min-1);
    }
    state_count_max -= state_count_min;
    state_count_min = -1;
}
