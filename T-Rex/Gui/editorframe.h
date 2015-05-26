#ifndef EDITORFRAME_H
#define EDITORFRAME_H

#include <QFrame>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QToolButton>
#include <QMenu>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QAction>

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

private Q_SLOTS:
    void LoadFile();
    void SearchText();
    void showNumMatched(bool ind);

    void ActIgnoreCase(bool chk);
    void ActMultiline(bool chk);
    void ActGlobal(bool chk);

private:
    Ui::EditorFrame *ui;

    QPlainTextEdit *textArea;
    QLineEdit *inputReg;
    QPushButton *loadFile;
    QCheckBox *chkNum;

    EditorProcess _eproc;

    void setElements();
    void makeEditCover();

    QToolButton* makeFlagsBtn();
    QAction* createAction(const QString &title, QObject* parent);

    QAction *_ignoreCase, *_multiline, *_global;
    bool _icFlag, _mFlag, _gFlag;

    class StayOpenMenu: public QMenu {
    public:
        StayOpenMenu(QWidget *parent);

    protected:
        void mousePressEvent(QMouseEvent * event);
        void closeEvent(QCloseEvent * event);

    private:
        bool m_inhibitClose;
    };

};

#endif // EDITORFRAME_H
