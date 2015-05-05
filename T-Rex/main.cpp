#include "welcomeform.h"
#include <QApplication>
#include <iostream>
#include <QLinkedList>

#include "Parser/TreeNodes.hpp"


extern reg_node * parse(char * s);

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   WelcomeForm w;
   w.show();

    reg_node * reg = parse("(a|b)*abb");
    Thompson t = reg->execute_T();

    QLinkedList<Edge> edges = t.getEdges();
    QLinkedList<Edge>::iterator i = edges.begin();
    for (; i!=edges.end(); i++)
    {
        std::cout << (*i).getState1() << " " << (*i).getState2() << " " << (char)(*i).getC() << std::endl;
    }



    return a.exec();
}
