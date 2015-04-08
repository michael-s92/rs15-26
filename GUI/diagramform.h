#ifndef DIAGRAMFORM_H
#define DIAGRAMFORM_H

#include <QWidget>
#include <QSignalMapper>

namespace Ui {
class DiagramForm;
}

class DiagramForm : public QWidget
{
    Q_OBJECT

public:
    //explicit DiagramForm(QWidget *parent = 0);
    ~DiagramForm();

    static DiagramForm* getDiagramForm();

private slots:
    void goto_main(QString msn);

private:
    explicit DiagramForm(QWidget *parent = 0);
    Ui::DiagramForm *ui;

    QSignalMapper back_to;
};

#endif // DIAGRAMFORM_H
