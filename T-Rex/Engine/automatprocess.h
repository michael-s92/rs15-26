#ifndef AUTOMATPROCESS_H
#define AUTOMATPROCESS_H

#include <QString>
#include <QGraphicsView>
#include <QPlainTextEdit>

#include "AutomatParser/parserengine.h"
#include "AutomatParser/TreeNodes.hpp"
#include "AutomatParser/visitor_nodes.h"
#include "AutomatParser/kretanje.h"

//nesto

class AutomatProcess
{
public:
    AutomatProcess(QGraphicsView* p, QPlainTextEdit* o, QLineEdit *rec, QLabel *pr, QLabel *nu);
    ~AutomatProcess();

    bool tomson_draw(const QString& regular);
    bool glusko_draw(const QString &regular);
    bool determi_draw(const QString &regular);
    bool minimal_draw(const QString &regular);

    void ispisi_podatke(Automata & a);
    void save_picture(QGraphicsView * panel, QString filename);

    void setSendColor(const QString &cl);

    int kreciSe(int k);

private:
    ParserEngine parser;

    QGraphicsView* panel;
    QPlainTextEdit* opis;

    GraphView *scene;
    Kretanje kretanje;
    bool ind_kretanje;
    int count;

    QLineEdit *word;
    QLabel *procitano, *na_ulazu;

};


#endif // AUTOMATPROCESS_H
