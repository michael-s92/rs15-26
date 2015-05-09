#ifndef EDITORFRAME_H
#define EDITORFRAME_H

#include <QFrame>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class EditorFrame;
}

//moze da se nasledjuje i iz QWidget
//stavio namerno QFrame da vidim kakve mogucnosti mi pruza
class EditorFrame : public QFrame
{
    Q_OBJECT

public:
    explicit EditorFrame(QWidget *parent = 0);
    ~EditorFrame();

private Q_SLOTS:
    void LoadFile();
    void SearchText();

private:
    Ui::EditorFrame *ui;

    QPlainTextEdit *textArea;
    QLineEdit *inputReg;
    QPushButton *loadFile;

    void setElements();
    QFrame* makeEditCover();
};

#endif // EDITORFRAME_H
