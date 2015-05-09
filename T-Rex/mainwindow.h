#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>

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
    void napustiProgram();
    void updateStatusBar(QString& s);

private:

    Ui::MainWindow *ui;

    QButtonGroup *bttnGroup;
    QToolBar *bttnBar;
    QPushButton *bUvod, *bEditor, *bAutomat, *bDiagram;
    QLabel *lStatus;

    QSignalMapper switchForm;

    QPushButton* createButton(const char *name, const char *info);
    void createButtonGroup();
    void createMainView();
    void createStatusBar();
    void setUpMenuActions();

};

#endif // MAINWINDOW_H
