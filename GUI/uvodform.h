#ifndef UVODFORM_H
#define UVODFORM_H

#include <QWidget>
#include <QSignalMapper>

namespace Ui {
class UvodForm;
}

class UvodForm : public QWidget
{
    Q_OBJECT

public:
    //explicit UvodForm(QWidget *parent = 0);
    ~UvodForm();

    static UvodForm* getUvodForm();

private slots:
    void goto_main(QString msn);

private:
    explicit UvodForm(QWidget *parent = 0);
    Ui::UvodForm *ui;

    QSignalMapper back_to;
};

#endif // UVODFORM_H
