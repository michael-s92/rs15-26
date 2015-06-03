#include "parserengine.h"

extern Reg_node * parse(const char * s);

ParserException::ParserException(const QString m)
 :msg(m)
{
}

ParserException::~ParserException()
{
}

QString ParserException::what()
{
    return msg;
}

ParserEngine::ParserEngine()
 :_reg_node(0)
{
}

ParserEngine::~ParserEngine()
{
}

ParserEngine::ParserEngine(QString regular)
{
   _reg_node = parse(regular.toStdString().c_str());
   if (_reg_node==0)
       throw ParserException("parser exception");
}

QString ParserEngine::getRegular() const
{
    return _regular;
}

Reg_node *ParserEngine::getRegNode() const
{
    return _reg_node;
}

