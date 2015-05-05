#ifndef TREENODES_H
#define TREENODES_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "thompson.h"

using namespace std;

class reg_node {
public:
    virtual void print(ostream & ostr) const=0;
    virtual Thompson execute_T() const=0;
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
    union_reg_node(reg_node* left, reg_node* right);
    void print(ostream & ostr) const;
    Thompson execute_T() const;

};




class concat_reg_node : public binary_op_reg_node {

public:
    concat_reg_node(reg_node* left, reg_node* right);
    void print(ostream & ostr) const;
    Thompson execute_T() const;

};




class star_reg_node : public unary_op_reg_node {

public:
    star_reg_node(reg_node *reg);
    void print(ostream & ostr) const;
    Thompson execute_T() const;


};



class plus_reg_node : public unary_op_reg_node {

public:
    plus_reg_node(reg_node *reg);
    void print(ostream & ostr) const;
    Thompson execute_T() const;




};



class ques_reg_node : public unary_op_reg_node {

public:
    ques_reg_node(reg_node *reg);
    void print(ostream & ostr) const;
    Thompson execute_T() const;



};




class symbol_reg_node : public reg_node {

public:
    symbol_reg_node(char value);
    virtual symbol_reg_node* clone() const=0;
    char getValue() const;
    Thompson execute_T() const;

protected:
    char _value;
};


class normal_symbol_reg_node : public symbol_reg_node {

public:
    normal_symbol_reg_node(char value);
    void print(ostream & ostr) const;
    normal_symbol_reg_node * clone() const
        {
             return new normal_symbol_reg_node(*this);
    }


};

class backslash_symbol_reg_node : public symbol_reg_node {

public:
    backslash_symbol_reg_node(char value);
    void print(ostream & ostr) const;
    backslash_symbol_reg_node * clone() const;

};



// nije uredjen konstruktor za karaktersku klasu
// ni print funkcija

class char_class_reg_node : public reg_node {

public:
    char_class_reg_node(vector<symbol_reg_node *> elements,bool ind);
    void print(ostream & ostr) const;
    Thompson execute_T() const;


private:
    bool _ind;
    vector<symbol_reg_node *> _elements;
};

// nije uradjen konstruktor za repetition
// ni funkcija print

class repetition_reg_node : public unary_op_reg_node {

public:
    repetition_reg_node(reg_node * reg, int min, int max);
    void print(ostream & ostr) const;
    Thompson execute_T() const;



private:
    unsigned int _min;
    unsigned int _max;
};

ostream & operator <<(ostream & ostr, const reg_node & reg);

struct numbers
{
  int a;
  int b;
  numbers(int x, int y)
      :a(x),b(y)
  {
  }
};

#endif // TREENODES_H
