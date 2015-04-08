#include "welcomeform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeForm w;
    w.show();

    return a.exec();
}
