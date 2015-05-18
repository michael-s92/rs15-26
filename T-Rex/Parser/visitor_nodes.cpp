#include "visitor_nodes.h"
#include "TreeNodes.hpp"
#include <iostream>

using namespace std;


void PrintNodes::visit_reg_node(const Reg_node &)
{
}

void PrintNodes::visit_binary_op(const Binary_op_reg_node &)
{
}

void PrintNodes::visit_unary_op(const Unary_op_reg_node &)
{
}

void PrintNodes::visit_union(const Union_reg_node &reg)
{
    _ostr << "( ";
    reg.getLeft()->accept(*this);
    _ostr << " | ";
    reg.getRight()->accept(*this);
    _ostr << " )";
}

void PrintNodes::visit_concat(const Concat_reg_node &reg)
{
    _ostr << "( ";
    reg.getLeft()->accept(*this);
    _ostr << " ";
     reg.getRight()->accept(*this);
    _ostr << " )";
}

void PrintNodes::visit_star(const Star_reg_node &reg)
{
    _ostr << "( ";
    reg.getReg()->accept(*this);
    _ostr << " *";
    _ostr << " )";
}

void PrintNodes::visit_plus(const Plus_reg_node &reg)
{
    _ostr << "( ";
    reg.getReg()->accept(*this);
    _ostr << " +";
    _ostr << " )";
}

void PrintNodes::visit_ques(const Ques_reg_node &reg)
{
    _ostr << "( ";
    reg.getReg()->accept(*this);
    _ostr << " ?";
    _ostr << " )";
}

void PrintNodes::visit_symbol(const Symbol_reg_node &)
{
}

void PrintNodes::visit_normal_symbol(const Normal_symbol_reg_node & reg)
{
    _ostr << "" << reg.getValue();
}

void PrintNodes::visit_backslash_symbol(const Backslash_symbol_reg_node &reg)
{
    _ostr << "\\" << reg.getValue();
}

void PrintNodes::visit_char_class(const Char_class_reg_node &reg)
{
    _ostr << "( [";
    if (reg.getInd()==false)
        _ostr << "^ ";
    vector<Symbol_reg_node*> elements = reg.getElements();
    vector<Symbol_reg_node*>::iterator i = elements.begin();
    for (; i!=elements.end(); i++)
        _ostr << (*i)->getValue() << " ";
    _ostr << "] )";
}

void PrintNodes::visit_repetition(const Repetition_reg_node &reg)
{
    reg.getReg()->accept(*this);
    _ostr << "{" << reg.getMin() << "," << reg.getMax() << "}";
}


void ThompsonNodes::visit_reg_node(const Reg_node &)
{

}

void ThompsonNodes::visit_binary_op(const Binary_op_reg_node &)
{

}

void ThompsonNodes::visit_unary_op(const Unary_op_reg_node &)
{
}

void ThompsonNodes::visit_union(const Union_reg_node & reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    ThompsonNodes t2;
    reg.getLeft()->accept(t1);
    reg.getRight()->accept(t2);
    t = Thompson (state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addEdges(t2.getEdges());
    t.addSlova(t1.getSlova());
    t.addSlova(t2.getSlova());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t.getFirst(),t2.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
    t.addEdge(t2.getLast(),t.getLast(),'\0');

}

void ThompsonNodes::visit_concat(const Concat_reg_node &reg)
{
    ThompsonNodes t1;
    ThompsonNodes t2;
    reg.getLeft()->accept(t1);
    reg.getRight()->accept(t2);
    t = Thompson(t1.getFirst(),t2.getLast());
    t.addEdges(t1.getEdges());
    t.addEdges(t2.getEdges());
    t.addSlova(t1.getSlova());
    t.addSlova(t2.getSlova());
    t.addEdge(t1.getLast(),t2.getFirst(),'\0');
}

void ThompsonNodes::visit_star(const Star_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson(state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addSlova(t1.getSlova());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t.getFirst(),t.getLast(),'\0');
    t.addEdge(t1.getLast(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
}

void ThompsonNodes::visit_plus(const Plus_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson(state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addSlova(t1.getSlova());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');

}

void ThompsonNodes::visit_ques(const Ques_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson (state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addSlova(t1.getSlova());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t1.getFirst(),t1.getLast(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
}

void ThompsonNodes::visit_symbol(const Symbol_reg_node &)
{
}

void ThompsonNodes::visit_normal_symbol(const Normal_symbol_reg_node &reg)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,reg.getValue());
    t.addSlovo(reg.getValue());
}

void ThompsonNodes::visit_backslash_symbol(const Backslash_symbol_reg_node &reg)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,reg.getValue());
    t.addSlovo(reg.getValue());
}

void ThompsonNodes::visit_char_class(const Char_class_reg_node &reg)
{

}

void ThompsonNodes::visit_repetition(const Repetition_reg_node &reg)
{

}

Thompson ThompsonNodes::getTh() const
{
    return t;
}

int ThompsonNodes::getLast() const
{
    return t.getLast();
}


int ThompsonNodes::getFirst() const
{
    return t.getFirst();
}

QVector<char> ThompsonNodes::getSlova() const
{
    return t.getSlova();
}

QVector<Edge> ThompsonNodes::getEdges() const
{
    return t.getEdges();
}
