#ifndef EDITORFRAME_H
#define EDITORFRAME_H

#include <QFrame>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "Engine/editorprocess.h"

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

public Q_SLOTS:
    void showNumMatched(bool ind);

private Q_SLOTS:
    void LoadFile();
    void SearchText();

private:
    Ui::EditorFrame *ui;

    QPlainTextEdit *textArea;
    QLineEdit *inputReg;
    QPushButton *loadFile;
    QLabel *matched_num;

    EditorProcess _eproc;

    void setElements();
    QWidget* makeEditCover();
    QWidget* makeInputCover();
};

#endif // EDITORFRAME_H
