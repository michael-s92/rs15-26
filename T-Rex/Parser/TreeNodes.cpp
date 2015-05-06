#include "Parser/TreeNodes.hpp"
#include "Parser/thompson.h"

binary_op_reg_node::binary_op_reg_node(reg_node* left, reg_node* right)
 :_left(left),_right(right)
{
}

unary_op_reg_node::unary_op_reg_node(reg_node *reg)
 :_reg(reg)
{}

union_reg_node::union_reg_node(reg_node* left, reg_node* right)
 : binary_op_reg_node(left,right)
{

}

void union_reg_node::print(ostream & ostr) const
{
    ostr << "( ";
    _left->print(ostr);
    ostr << " | ";
    _right->print(ostr);
    ostr << " )";
}

Thompson union_reg_node::execute_T() const
{
    Thompson t1 = _left->execute_T();
    Thompson t2 = _right->execute_T();
    Thompson t(Thompson::state_count_min-1,Thompson::state_count_max+1);
    t.addEdges(t1.getEdges());
    t.addEdges(t2.getEdges());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t.getFirst(),t2.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
    t.addEdge(t2.getLast(),t.getLast(),'\0');
    return t;
}

concat_reg_node::concat_reg_node(reg_node* left, reg_node* right)
 :binary_op_reg_node(left,right)
{}

void concat_reg_node::print(ostream & ostr) const
{
    ostr << "( ";
    _left->print(ostr);
    ostr << " ";
   _right->print(ostr);
    ostr << " )";
}

Thompson concat_reg_node::execute_T() const
{
    Thompson t1 = _left->execute_T();
    Thompson t2 = _right->execute_T();
    Thompson t(t1.getFirst(),t2.getLast());
    t.addEdges(t1.getEdges());
    t.addEdges(t2.getEdges());
    t.addEdge(t1.getLast(),t2.getFirst(),'\0');
    return t;
}

star_reg_node::star_reg_node(reg_node *reg)
 :unary_op_reg_node(reg)
{}

void star_reg_node::print(ostream & ostr) const
{
    ostr << "( ";
    _reg->print(ostr);
    ostr << " *";
    ostr << " )";
}

Thompson star_reg_node::execute_T() const
{
    Thompson t1 = _reg->execute_T();
    Thompson t(Thompson::state_count_min--,Thompson::state_count_max++);
    t.addEdges(t1.getEdges());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t.getFirst(),t.getLast(),'\0');
    t.addEdge(t1.getLast(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');

    return t;
}

plus_reg_node::plus_reg_node(reg_node *reg)
 :unary_op_reg_node(reg)
{}

void plus_reg_node::print(ostream & ostr) const
{
    ostr << "( ";
    _reg->print(ostr);
    ostr << " +";
    ostr << " )";
}

Thompson plus_reg_node::execute_T() const
{
    Thompson t1 = _reg->execute_T();
    Thompson t(Thompson::state_count_min--,Thompson::state_count_max++);
    t.addEdges(t1.getEdges());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t1.getFirst(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
    return t;
}

ques_reg_node::ques_reg_node(reg_node *reg)
 :unary_op_reg_node(reg)
{}

void ques_reg_node::print(ostream & ostr) const
{
    ostr << "( ";
    _reg->print(ostr);
    ostr << " ?";
    ostr << " )";
}

Thompson ques_reg_node::execute_T() const
{
    Thompson t1 = _reg->execute_T();
    Thompson t(Thompson::state_count_min--,Thompson::state_count_max++);
    t.addEdges(t1.getEdges());
    t.addEdge(t.getFirst(),t1.getFirst(),'\0');
    t.addEdge(t1.getFirst(),t1.getLast(),'\0');
    t.addEdge(t1.getLast(),t.getLast(),'\0');
    return t;
}

symbol_reg_node::symbol_reg_node(char value)
 :_value(value)
{

}

char symbol_reg_node::getValue() const
{
    return _value;
}

normal_symbol_reg_node::normal_symbol_reg_node(char value)
 :symbol_reg_node(value)
{

}


Thompson symbol_reg_node::execute_T() const
{
    int state = Thompson::state_count_max;
    Thompson t(state,state+1);
    Thompson::state_count_max+=2;
    t.addEdge(state,state+1,_value);
    return t;
}


void normal_symbol_reg_node::print(ostream & ostr) const
{
    ostr << "" << _value;
}


backslash_symbol_reg_node::backslash_symbol_reg_node(char value)
 :symbol_reg_node(value)
{}

void backslash_symbol_reg_node::print(ostream & ostr) const
{
    ostr << "\\" << _value;

}

 backslash_symbol_reg_node * backslash_symbol_reg_node::clone() const
 {
     return new backslash_symbol_reg_node(*this);
 }

char_class_reg_node::char_class_reg_node(vector<symbol_reg_node*> elements, bool ind)
 :_ind(ind),_elements(elements)
{
}

void char_class_reg_node::print(ostream & ostr) const
{

    ostr << "( [";
    if (_ind==false)
        ostr << "^ ";
    vector<symbol_reg_node*>::const_iterator i = _elements.begin();
    for (; i!=_elements.end(); i++)
        ostr << **i << " ";
    ostr << "] )";
}

Thompson char_class_reg_node::execute_T() const
{
    Thompson t(0,0);
    return t;
}




repetition_reg_node::repetition_reg_node(reg_node * reg, int min, int max)
 :unary_op_reg_node(reg), _min(min),_max(max)
{}

void repetition_reg_node::print(ostream & ostr) const
{
    _reg->print(ostr);
    ostr << "{" << _min << "," <<_max << "}";
}

Thompson repetition_reg_node::execute_T() const
{
    Thompson t(0,0);
    return t;
}

ostream & operator << (ostream & ostr, const reg_node & reg)
{
    reg.print(ostr);
    return ostr;
}



