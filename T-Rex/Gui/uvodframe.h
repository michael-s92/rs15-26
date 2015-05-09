#ifndef UVODFRAME_H
#define UVODFRAME_H

#include <QFrame>

namespace Ui {
class UvodFrame;
}

class UvodFrame : public QFrame
{
    Q_OBJECT

public:
    explicit UvodFrame(QWidget *parent = 0);
    ~UvodFrame();

private:
    Ui::UvodFrame *ui;
};

#endif // UVODFRAME_H
