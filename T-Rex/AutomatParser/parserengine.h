#ifndef PARSERENGINE_H
#define PARSERENGINE_H
#include "AutomatParser/TreeNodes.hpp"
#include <QString>

class ParserException:public exception{
public:
          ParserException(const QString m="parser exception");
          ~ParserException();
          QString what();
private:
           QString msg;
};


class ParserEngine
{
public:
    ParserEngine();
    ~ParserEngine();
    ParserEngine(QString regular);
    QString getRegular() const;
    Reg_node * getRegNode() const;

private:
    QString _regular;
    Reg_node * _reg_node;
};

#endif // PARSERENGINE_H
