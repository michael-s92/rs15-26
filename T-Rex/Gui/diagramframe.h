#ifndef DIAGRAMFRAME_H
#define DIAGRAMFRAME_H

#include <QFrame>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class DiagramFrame;
}

class DiagramFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DiagramFrame(QWidget *parent = 0);
    ~DiagramFrame();

private:
    Ui::DiagramFrame *ui;

    QLineEdit* regex;
    QPushButton* makeReg;

    void setElements();
    QWidget* makePanel();
    QWidget* makeShow();

};

#endif // DIAGRAMFRAME_H
