#include "thompson.h"

using namespace std;

int Thompson::state_count=0;


void Thompson::make_dot_file(ostream &osr)
{
    osr << "digraph G {" << endl;
    osr <<" rankdir = LR;" << endl;
    osr <<"node [shape = none];" << endl;
    osr << "-1;" << endl;
    osr <<" node [shape = circle];" << endl;
    int j;
    for (j=0; j<state_count-1; j++)
        osr << j << "[label=\"" << j << "\"];" << endl;
    osr << j << "[label=\"" << j << "\" shape=\"doublecircle\"];" << endl;

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

