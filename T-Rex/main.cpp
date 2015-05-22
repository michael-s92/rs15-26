#include "Gui/mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

// samo pokusavam jer i dalje se mucim


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

   return a.exec();

}
