#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

#include "Parser/TreeNodes.hpp"
#include <fstream>

extern reg_node * parse(char * s);

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QSplashScreen *splash = new QSplashScreen;
   splash->setPixmap(QPixmap(":/my_files.qrc"));
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


   reg_node * reg = parse("(a|b)a");
   Thompson t = reg->execute_T();
   Gluskov g = t.make_gluskov();


  //   fstream f;
  // f.open("/home/igor/Desktop/min.dot",fstream::out);
  // t.make_dot_file(f);

  // f.close();
  // system("dot -Tjpeg /home/igor/Desktop/min.dot > /home/igor/Desktop/minx.jpeg");



   return a.exec();

}
