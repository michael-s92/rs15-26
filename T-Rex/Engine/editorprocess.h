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
    int doMatch(QString what, QPlainTextEdit* area);

private:
    QString buffer;
};

#endif // EDITORPROCESS_H
