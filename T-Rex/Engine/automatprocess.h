#ifndef AUTOMATPROCESS_H
#define AUTOMATPROCESS_H

#include <QString>
#include <QGraphicsView>

class AutomatProcess
{
public:
    AutomatProcess();
    ~AutomatProcess();

    void tomson_draw(QString regular, QGraphicsView* panel);
    void glusko_draw(QString regular, QGraphicsView* panel);

};

#endif // AUTOMATPROCESS_H
