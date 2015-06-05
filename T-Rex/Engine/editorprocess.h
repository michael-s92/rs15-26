#ifndef EDITORPROCESS_H
#define EDITORPROCESS_H

#include <QString>
#include <QPlainTextEdit>

class EditorProcess
{
public:
    EditorProcess(QPlainTextEdit *textArea);
    ~EditorProcess();

    void readFile(const QString &file);
    int doMatch(QString what, bool _ignorecaseFlag, bool _globalFlag, bool _multilineFlag);

private:
    QPlainTextEdit* tArea;

    bool _ignorecaseFlag, _globalFlag, _multilineFlag;
};

#endif // EDITORPROCESS_H
