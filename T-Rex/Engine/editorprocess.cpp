#include "editorprocess.h"

#include <QFile>
#include <QTextStream>

EditorProcess::EditorProcess()
{

}

EditorProcess::~EditorProcess()
{

}

QString& EditorProcess::readFile(const QString &file){

    buffer = "";

    QFile data(file);
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);

        QString value;
        for(;;) {
            value = in.readLine();
            if (!value.isNull()) {
                buffer += value + "\n";
            } else
                break;
            }

    }

    data.close();

    return buffer;
}
