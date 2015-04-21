#ifndef TREENODES_H
#define TREENODES_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

class reg_node {
public:
    virtual string print() const = 0;
};



class binary_op_reg_node : public reg_node {

protected:
    reg_node* _left;
    reg_node* _right;

public:
    binary_op_reg_node(reg_node* left, reg_node* right);
};




class unary_op_reg_node : public reg_node {

protected:
    reg_node* _reg;

public:
    unary_op_reg_node(reg_node *reg);
};



class union_reg_node : public binary_op_reg_node {

public:
    union_reg_node();
    string print() const;
};




class concat_reg_node : public binary_op_reg_node {

public:
    concat_reg_node();
    string print() const;
};




class star_reg_node : public unary_op_reg_node {

public:
    star_reg_node();
    string print() const;

};



class plus_reg_node : public unary_op_reg_node {

public:
    plus_reg_node();
    string print() const;

};



class ques_reg_node : public unary_op_reg_node {

public:
    ques_reg_node();
    string print() const;

};




class symbol_reg_node : public reg_node {

public:
    symbol_reg_node(char value);
    string print() const;

private:
    char _value;

};




class char_class_reg_node : public reg_node {

public:
    char_class_reg_node(vector<symbol_reg_node> elements);
    string print() const;

private:
    bool ind;
    //obrati paznju ovde, char?
    vector<symbol_reg_node> _elements;

};


class repetition_reg_node : public unary_op_reg_node {

public:
    repetition_reg_node(int min, int max);
    string print() const;

private:
    unsigned int _min;
    unsigned int _max;
};



#endif // TREENODES_H
