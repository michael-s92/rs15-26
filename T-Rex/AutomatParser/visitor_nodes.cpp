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

void PrintNodes::visit_empty(const Empty_reg_node &)
{
    _ostr<< "( eps )";
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
    t.addAlphabet(t1.getAlphabet());
    t.addAlphabet(t2.getAlphabet());
    t.addEdge(t.getStart(),t1.getStart(),'\0');
    t.addEdge(t.getStart(),t2.getStart(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
    t.addEdge(t2.getLast(),t.getLast(),'\0');

}

void ThompsonNodes::visit_concat(const Concat_reg_node &reg)
{
    ThompsonNodes t1;
    ThompsonNodes t2;
    reg.getLeft()->accept(t1);
    reg.getRight()->accept(t2);
    t = Thompson(t1.getStart(),t2.getLast());
    t.addEdges(t1.getEdges());
    t.addEdges(t2.getEdges());
    t.addAlphabet(t1.getAlphabet());
    t.addAlphabet(t2.getAlphabet());
    t.addEdge(t1.getLast(),t2.getStart(),'\0');
}

void ThompsonNodes::visit_star(const Star_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson(state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addAlphabet(t1.getAlphabet());
    t.addEdge(t.getStart(),t1.getStart(),'\0');
    t.addEdge(t.getStart(),t.getLast(),'\0');
    t.addEdge(t1.getLast(),t1.getStart(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
}

void ThompsonNodes::visit_plus(const Plus_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson(state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addAlphabet(t1.getAlphabet());
    t.addEdge(t.getStart(),t1.getStart(),'\0');
    t.addEdge(t1.getLast(),t1.getStart(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');

}

void ThompsonNodes::visit_ques(const Ques_reg_node &reg)
{
    int state = Thompson::state_count++;
    ThompsonNodes t1;
    reg.getReg()->accept(t1);
    t = Thompson (state,Thompson::state_count++);
    t.addEdges(t1.getEdges());
    t.addAlphabet(t1.getAlphabet());
    t.addEdge(t.getStart(),t1.getStart(),'\0');
    t.addEdge(t1.getStart(),t1.getLast(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
}

void ThompsonNodes::visit_symbol(const Symbol_reg_node &reg)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,reg.getValue());
    t.addChar(reg.getValue());
}

void ThompsonNodes::visit_normal_symbol(const Normal_symbol_reg_node &reg)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,reg.getValue());
    t.addChar(reg.getValue());
}

void ThompsonNodes::visit_backslash_symbol(const Backslash_symbol_reg_node &reg)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,reg.getValue());
    t.addChar(reg.getValue());
}

void ThompsonNodes::visit_char_class(const Char_class_reg_node &reg)
{
    vector<Symbol_reg_node *> elements = reg.getElements();
    if (elements.size()==1)
    {
       visit_symbol(*elements[0]);
       return;
    }
    Union_reg_node * reg_new=makeCharRegUnion(elements);
    visit_union(*reg_new);
}



void ThompsonNodes::visit_repetition(const Repetition_reg_node &reg)
{

    int m = reg.getMin();
    int n = reg.getMax();
    if (m==n)
    {
        Concat_reg_node *reg_new = makeCharRegConcat(*reg.getReg(),m);
        visit_concat(*reg_new);
    }
    else if (n==-1)
    {
        if (m>1)
        {
            Concat_reg_node *reg_new = makeCharRegConcat(*reg.getReg(),m);
            Reg_node *reg1 = reg.getReg();
            Star_reg_node * reg_star = new Star_reg_node(reg1);
            Concat_reg_node *reg2 = new Concat_reg_node(reg_new,reg_star);
            visit_concat(*reg2);
        }
        else if (m==1)
        {
            Reg_node *reg1 = reg.getReg();
            Plus_reg_node * reg_plus = new Plus_reg_node(reg1);
            visit_plus(*reg_plus);
        }
        else
        {
            Reg_node *reg1 = reg.getReg();
            Star_reg_node * reg_star = new Star_reg_node(reg1);
            visit_star(*reg_star);
        }
    }
    else
    {
        if (m==0)
          m++;
        vector<Reg_node *> konkatenacije;
        for (int i=m; i<=n; i++)
        {
            if (i==1)
            {
              konkatenacije.push_back(reg.getReg());
              continue;
            }
            Concat_reg_node * reg_conc = makeCharRegConcat(*reg.getReg(),i);
            konkatenacije.push_back(reg_conc);
        }

      Union_reg_node *reg_union = makeCharRegUnion(konkatenacije);
        visit_union(*reg_union);
    }
}

void ThompsonNodes::visit_empty(const Empty_reg_node &)
{
    int state = Thompson::state_count;
    t= Thompson(state,state+1);
    Thompson::state_count+=2;
    t.addEdge(state,state+1,'\0');
}

Concat_reg_node * makeCharRegConcat(Reg_node & reg, int k)
{
   if (k==2)
     return new Concat_reg_node(&reg,&reg);
   return new Concat_reg_node(makeCharRegConcat(reg,k-1),&reg);
}

Thompson ThompsonNodes::getTh() const
{
    return t;
}

int ThompsonNodes::getLast() const
{
    return t.getLast();
}


int ThompsonNodes::getStart() const
{
    return t.getStart();
}

QVector<char> ThompsonNodes::getAlphabet() const
{
    return t.getAlphabet();
}

QVector<Edge> ThompsonNodes::getEdges() const
{
    return t.getEdges();
}
