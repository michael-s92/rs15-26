#ifndef AUTOMATFRAME_H
#define AUTOMATFRAME_H

#include <QFrame>

namespace Ui {
class AutomatFrame;
}

class AutomatFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AutomatFrame(QWidget *parent = 0);
    ~AutomatFrame();

private:
    Ui::AutomatFrame *ui;
};

#endif // AUTOMATFRAME_H
