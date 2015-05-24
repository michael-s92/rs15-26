#ifndef AUTOMATPROCESS_H
#define AUTOMATPROCESS_H

#include <QString>
#include <QGraphicsView>
#include <QPlainTextEdit>

#include "parserengine.h"
#include "Parser/TreeNodes.hpp"
#include "Parser/visitor_nodes.h"
#include "kretanje.h"

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

    int kreciSe(int k);

private:
    ParserEngine parser;

    QGraphicsView* panel;
    QPlainTextEdit* opis;

    Kretanje * kretanje;
    int count;

    //word -> rec koju trazis u automatu
    //procitano -> labela gde upisujes slovo koje si procitao
    //na_ulazu -> labela iz koje citas i kako procitas skines i stavis u prvu labelu
    QLineEdit *word;
    QLabel *procitano, *na_ulazu;

};


#endif // AUTOMATPROCESS_H
