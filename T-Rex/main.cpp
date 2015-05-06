#include "welcomeform.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <QLinkedList>

#include "Parser/TreeNodes.hpp"


extern reg_node * parse(char * s);

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
 //  WelcomeForm w;
 //  w.show();

   reg_node * reg = parse("a|b");
   Thompson t = reg->execute_T();
   fstream f;
   //f.open("/home/igor/Desktop/min.dot",fstream::out);
   t.make_dot_file(f);

   f.close();
  // system("dot -Tjpeg /home/igor/Desktop/min.dot > /home/igor/Desktop/min.jpeg");

    return a.exec();
}
