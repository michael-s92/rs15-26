#include "welcomeform.h"
#include <QApplication>
#include <iostream>

#include "Parser/TreeNodes.hpp"

extern reg_node * parse(char * s);

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   WelcomeForm w;
   w.show();

    int b;
    reg_node * reg = parse("a|b*");

    return a.exec();
}
