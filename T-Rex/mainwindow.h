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

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    //Da li mi je potreban singlton?!?!
    static MainWindow* getMainWindow();

private Q_SLOTS:
    void go_to_form(int i);

private:

    Ui::MainWindow *ui;

    QSignalMapper switchForm;
};

#endif // MAINWINDOW_H
