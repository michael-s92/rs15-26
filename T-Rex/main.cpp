#include "Gui/mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

#include "Parser/TreeNodes.hpp"
#include <fstream>

#include "Parser/visitor_nodes.h"

extern Reg_node * parse(char * s);

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QSplashScreen *splash = new QSplashScreen;
   splash->setPixmap(QPixmap(":/my_files.qrc")); //staciti neku sliku koju cu ubaciti u Resources
   splash->show();
   /*
    * napraviti welcome screen i tu ga prikazivati
    * kako se uopste ubacuju slike u projekat i koriste?!
    */


   Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
   splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::red);
   MainWindow w;

   /*
    * primer rukovanja:
   splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);
   loadModules();
   */

   w.show();
   splash->finish(&w);
   delete splash;

/*
   Reg_node * reg = parse("(a|b)?");
   //Gluskov g = t.make_gluskov();


   fstream f;
   f.open("/home/igor/Desktop/min.dot",fstream::out);

   // f.open("/home/igor/Desktop/igor.txt",fstream::out);
   PrintNodes print_nodes(cout);
   reg->accept(print_nodes);
   cout << endl;
   ThompsonNodes thompson_nodes;
   reg->accept(thompson_nodes);
   Thompson t = thompson_nodes.getTh();

   t.make_dot_file(f);

   f.close();
   system("dot -Tjpeg /home/igor/Desktop/min.dot > /home/igor/Desktop/minnn.jpeg");
  */

   return a.exec();

}
