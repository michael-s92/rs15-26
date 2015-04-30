#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>
#include <QSignalMapper>

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    //explicit EditorForm(QWidget *parent = 0);
    ~EditorForm();

    static EditorForm* getEditorForm();

private Q_SLOTS:
    void goto_main(QString msn);

private:
    explicit EditorForm(QWidget *parent = 0);
    Ui::EditorForm *ui;

    QSignalMapper back_to;
};

#endif // EDITORFORM_H
