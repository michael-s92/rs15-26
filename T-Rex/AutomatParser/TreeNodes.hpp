#ifndef TREENODES_H
#define TREENODES_H

#include <map>
#include <vector>
#include "automata.h"

class Visitor_nodes;

using namespace std;

class Reg_node {
public:
    virtual void accept(Visitor_nodes & v) const=0;
    virtual ~Reg_node()
    {}
};


class Binary_op_reg_node : public Reg_node {

protected:
    Reg_node* _left;
    Reg_node* _right;

public:
    Binary_op_reg_node(Reg_node* left, Reg_node* right);
    ~Binary_op_reg_node();
    Reg_node *getLeft() const;
    Reg_node *getRight() const;
};



class Unary_op_reg_node : public Reg_node {

protected:
    Reg_node* _reg;

public:
    Unary_op_reg_node(Reg_node *reg);
    ~Unary_op_reg_node();
    Reg_node * getReg() const;
};



class Union_reg_node : public Binary_op_reg_node {

public:
    Union_reg_node(Reg_node* left, Reg_node* right);
    void accept(Visitor_nodes &v) const;

};


class Concat_reg_node : public Binary_op_reg_node {

public:
    Concat_reg_node(Reg_node* left, Reg_node* right);
    void accept(Visitor_nodes & v) const;

};


class Star_reg_node : public Unary_op_reg_node {

public:
    Star_reg_node(Reg_node *reg);
    void accept(Visitor_nodes & v) const;
};



class Plus_reg_node : public Unary_op_reg_node {

public:
    Plus_reg_node(Reg_node *reg);
    void accept(Visitor_nodes & v) const;
};



class Ques_reg_node : public Unary_op_reg_node {

public:
    Ques_reg_node(Reg_node *reg);
    void accept(Visitor_nodes & v) const;
};




class Symbol_reg_node : public Reg_node {

public:
    Symbol_reg_node(char value);
    virtual Symbol_reg_node* clone() const=0;
    char getValue() const;

protected:
    char _value;
};


class Normal_symbol_reg_node : public Symbol_reg_node {

public:
    Normal_symbol_reg_node(char value);
    Normal_symbol_reg_node * clone() const;
    void accept(Visitor_nodes & v) const;

};

class Backslash_symbol_reg_node : public Symbol_reg_node {

public:
    Backslash_symbol_reg_node(char value);
    Backslash_symbol_reg_node * clone() const;
    void accept(Visitor_nodes & v) const;
};


class Char_class_reg_node : public Reg_node {

public:
    Char_class_reg_node(vector<Symbol_reg_node *> elements,bool ind);
    void accept(Visitor_nodes & v) const;
    bool getInd() const;
    vector<Symbol_reg_node*> getElements() const;


private:
    bool _ind;
    vector<Symbol_reg_node *> _elements;
};


class Repetition_reg_node : public Unary_op_reg_node {

public:
    Repetition_reg_node(Reg_node * reg, int min, int max);
    void accept(Visitor_nodes & v) const;
    int getMin() const;
    int getMax() const;


private:
    unsigned int _min;
    unsigned int _max;
};

class Empty_reg_node: public Reg_node
{
public:
    Empty_reg_node();
    void accept(Visitor_nodes &v) const;
};



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
