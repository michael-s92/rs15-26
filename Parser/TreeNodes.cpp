#include "TreeNodes.hpp"

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

symbol_reg_node::symbol_reg_node(char value)
 :_value(value)
{

}

normal_symbol_reg_node::normal_symbol_reg_node(char value)
 :symbol_reg_node(value)
{

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
    cout << "\\" << _value;

}

char_class_reg_node::char_class_reg_node(vector<symbol_reg_node*> elements)
 :_elements(elements)
{}

void char_class_reg_node::print(ostream & ostr) const
{
  //  string s;
  //  vector<symbol_reg_node*>::const_iterator i = _elements.begin();
    ostr << "";
}

repetition_reg_node::repetition_reg_node(reg_node * reg, int min, int max)
 :unary_op_reg_node(reg), _min(min),_max(max)
{}

void repetition_reg_node::print(ostream & ostr) const
{
    ostr << "";
}

ostream & operator << (ostream & ostr, const reg_node & reg)
{
    reg.print(ostr);
    return ostr;
}
