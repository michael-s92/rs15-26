#ifndef EDITORPROCESS_H
#define EDITORPROCESS_H

#include <QString>
#include <QPlainTextEdit>

class EditorProcess
{
public:
    EditorProcess();
    ~EditorProcess();

    QString& readFile(const QString &file);
    int doMatch(QString what, QPlainTextEdit* area, bool _ignorecaseFlag, bool _globalFlag, bool _multilineFlag);

private:
    QString buffer;

    bool _ignorecaseFlag, _globalFlag, _multilineFlag;
};

#endif // EDITORPROCESS_H
