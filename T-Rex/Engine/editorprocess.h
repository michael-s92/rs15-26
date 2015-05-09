#ifndef EDITORPROCESS_H
#define EDITORPROCESS_H

#include <QString>

class EditorProcess
{
public:
    EditorProcess();
    ~EditorProcess();

    QString& readFile(const QString &file);

private:
    QString buffer;
};

#endif // EDITORPROCESS_H
