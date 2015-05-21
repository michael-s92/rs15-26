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

private Q_SLOTS:
    void displaySimulator(bool display);
    void drawAutomata(int ind = 0, bool chk = false);
    void displayDetails(bool display);
    void simulatorPlay(const QString &action);
    void startPlay(const QString &action);

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

    AutomatProcess *_aproc;

    void setElements();
    void setSlotAndSignal();
    QWidget* makeAutomatWidget();
    QWidget* simulatorWidget();
    QPushButton* createSimButton(const char *name, const char *info);

    void enabledSimulatorBtn(bool vr);

};

#endif // AUTOMATFRAME_H
