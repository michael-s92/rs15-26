#include "TreeNodes.hpp"
#include "automata.h"
#include "visitor_nodes.h"
#include <iostream>

Binary_op_reg_node::Binary_op_reg_node(Reg_node* left, Reg_node* right)
 :_left(left),_right(right)
{
}

Binary_op_reg_node::~Binary_op_reg_node()
{
    delete _left;
    delete _right;
}

Reg_node *Binary_op_reg_node::getLeft() const
{
    return _left;
}

Reg_node *Binary_op_reg_node::getRight() const
{
    return _right;
}



Unary_op_reg_node::Unary_op_reg_node(Reg_node *reg)
    :_reg(reg)
{}

Unary_op_reg_node::~Unary_op_reg_node()
{
    delete _reg;
}

Reg_node *Unary_op_reg_node::getReg() const
{
   return _reg;
}




Union_reg_node::Union_reg_node(Reg_node* left, Reg_node* right)
 : Binary_op_reg_node(left,right)
{

}

void Union_reg_node::accept(Visitor_nodes &v) const
{
  v.visit_union(*this);
}




Concat_reg_node::Concat_reg_node(Reg_node* left, Reg_node* right)
 :Binary_op_reg_node(left,right)
{}


void Concat_reg_node::accept(Visitor_nodes &v) const
{
   v.visit_concat(*this);
}

Star_reg_node::Star_reg_node(Reg_node *reg)
 :Unary_op_reg_node(reg)
{}



void Star_reg_node::accept(Visitor_nodes &v) const
{
   v.visit_star(*this);
}




Plus_reg_node::Plus_reg_node(Reg_node *reg)
 :Unary_op_reg_node(reg)
{}


void Plus_reg_node::accept(Visitor_nodes &v) const
{
    v.visit_plus(*this);
}




Ques_reg_node::Ques_reg_node(Reg_node *reg)
 :Unary_op_reg_node(reg)
{

}


void Ques_reg_node::accept(Visitor_nodes &v) const
{
    v.visit_ques(*this);
}


Symbol_reg_node::Symbol_reg_node(char value)
 :_value(value)
{

}

char Symbol_reg_node::getValue() const
{
    return _value;
}




Normal_symbol_reg_node::Normal_symbol_reg_node(char value)
 :Symbol_reg_node(value)
{

}

Normal_symbol_reg_node *Normal_symbol_reg_node::clone() const
{
         return new Normal_symbol_reg_node(*this);
}


void Normal_symbol_reg_node::accept(Visitor_nodes &v) const
{
   v.visit_normal_symbol(*this);
}




Backslash_symbol_reg_node::Backslash_symbol_reg_node(char value)
 :Symbol_reg_node(value)
{}


 Backslash_symbol_reg_node * Backslash_symbol_reg_node::clone() const
 {
     return new Backslash_symbol_reg_node(*this);
 }

 void Backslash_symbol_reg_node::accept(Visitor_nodes &v) const
 {
    v.visit_backslash_symbol(*this);
 }




Char_class_reg_node::Char_class_reg_node(vector<Symbol_reg_node*> elements, bool ind)
 :_ind(ind),_elements(elements)
{
}

void Char_class_reg_node::accept(Visitor_nodes &v) const
{
    v.visit_char_class(*this);
}

bool Char_class_reg_node::getInd() const
{
    return _ind;
}

vector<Symbol_reg_node*> Char_class_reg_node::getElements() const
{
    return _elements;
}



Repetition_reg_node::Repetition_reg_node(Reg_node * reg, int min, int max)
 :Unary_op_reg_node(reg), _min(min),_max(max)
{}



void Repetition_reg_node::accept(Visitor_nodes &v) const
{
    v.visit_repetition(*this);
}

int Repetition_reg_node::getMin() const
{
    return _min;
}


int Repetition_reg_node::getMax() const
{
    return _max;
}





Empty_reg_node::Empty_reg_node()
{

}

void Empty_reg_node::accept(Visitor_nodes &v) const
{
   v.visit_empty(*this);
}
