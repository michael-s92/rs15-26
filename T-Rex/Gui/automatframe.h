#ifndef AUTOMATFRAME_H
#define AUTOMATFRAME_H

#include <QFrame>
#include <QGraphicsView>
#include <QButtonGroup>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QSignalMapper>
#include <QTimer>
#include <QLabel>

#include "Engine/automatprocess.h"

namespace Ui {
class AutomatFrame;
}

class AutomatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AutomatFrame(QWidget *parent = 0);
    ~AutomatFrame();

public Q_SLOTS:
    void colorChanged(const QString cl);

private Q_SLOTS:
    void displaySimulator(bool display);
    void drawAutomata(int ind = 0, bool chk = false);
    void displayDetails(bool display);
    void simulatorPlay(const QString &action);
    void startPlay(const QString &action);

    void autoSimStart();

private:
    Ui::AutomatFrame *ui;

    QGraphicsView *platno;
    QButtonGroup* automatGroup;
    QCheckBox* simulator, *opis;
    QLineEdit *inputReg, *word;
    QPushButton *s_reset, *s_next, *s_previous, *s_start, *s_pause, *s_stop, *s_play;
    QWidget *sim;
    QPlainTextEdit *opisArea;

    QSignalMapper simulator_map, simulator_start;
    QTimer *simClock;
    QToolBar* option_automat;
    QLabel *procitano, *na_ulazu;
    QFrame *inSimFrame;

    AutomatProcess *_aproc;

    void setElements();
    void setSlotAndSignal();
    void setStyle();
    QWidget* makeAutomatWidget();
    QWidget* simulatorWidget();
    QPushButton* createSimButton(const char *name, const char *info);
    QWidget* makeReadWidget();

    void enabledSimulatorBtn(bool vr);
    void RadiAutoSim(bool radi);
};

#endif // AUTOMATFRAME_H
