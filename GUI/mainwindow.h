#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*
     * orginalno:
    explicit MainWindow(QWidget *parent = 0);
     * prebaceno je u private zbog singltona,
     * ako ne bude radilo ukloniti ga iz prive i vratiti ovde
    */
    ~MainWindow();

    static MainWindow* getMainWindow();

private Q_SLOTS:
    void go_to_form(QString fname);

private:
    //prebaceno iz private:
    explicit MainWindow(QWidget *parent = 0);

    Ui::MainWindow *ui;

    QSignalMapper switchForm;
};

#endif // MAINWINDOW_H
