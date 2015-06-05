#include "Gui/mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

#include <unistd.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   a.setOrganizationName("RS15-26");
   a.setApplicationName("T-Rex");

   QSplashScreen *splash = new QSplashScreen;
   QPixmap pick(":/images/icon/cover.jpg");
   splash->setPixmap(pick); //staciti neku sliku koju cu ubaciti u Resources

   splash->show();


   /*
    * napraviti welcome screen i tu ga prikazivati
    * kako se uopste ubacuju slike u projekat i koriste?!
    */

   //Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
   //splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::red);
   MainWindow w;

   /*
    * primer rukovanja:
   splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);
   loadModules();
   */

   a.processEvents();
   sleep(5);

   w.show();
   splash->finish(&w);
   delete splash;

   return a.exec();

}
