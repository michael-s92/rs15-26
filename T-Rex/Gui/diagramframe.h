#ifndef DIAGRAMFRAME_H
#define DIAGRAMFRAME_H

#include <QFrame>

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
};

#endif // DIAGRAMFRAME_H
