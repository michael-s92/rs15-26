#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QFrame>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class EditorForm;
}

//moze da se nasledjuje i iz QWidget
//stavio namerno QFrame da vidim kakve mogucnosti mi pruza
class EditorForm : public QFrame
{
    Q_OBJECT

public:
    //explicit EditorForm(QWidget *parent = 0);
    ~EditorForm();

    static EditorForm* getEditorForm();

private Q_SLOTS:
    void LoadFile();
    void SearchText();

private:
    explicit EditorForm(QWidget *parent = 0);
    Ui::EditorForm *ui;

    QPlainTextEdit *textArea;
    QLineEdit *inputReg;
    QPushButton *loadFile;

    void setElements();
    QFrame* makeEditCover();

};

#endif // EDITORFORM_H
