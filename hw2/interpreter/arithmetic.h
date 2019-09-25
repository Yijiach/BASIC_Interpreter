#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include "stdlib.h"
#include "stdio.h"
#include <string>
#include <iostream>
using namespace std;

class NumericExpression {
public:
    NumericExpression();
    virtual ~NumericExpression(){}
    virtual string format() = 0;
    virtual int get_val(){return 0;}
};

class Constant : public NumericExpression{
public:
	Constant(int val);
	string format();
	int get_val();
private:
	int val_;
};

class Variable : public NumericExpression{
public:
	Variable(string name, int val);
	virtual string format() = 0;
    virtual ~Variable(){}
protected: // private?
	string name_;
	int val_; // store value of the variable
};

class IntegerVariable : public Variable{
public:
	IntegerVariable(string name, int val);
	string format();
};

class ArrayVariable : public Variable{
public:
	ArrayVariable(string name, NumericExpression *index, int val); // (int val?)
	virtual ~ArrayVariable();
    string format();
private:
	NumericExpression *index_;
};

class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

    string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class SubtractionExpression : public NumericExpression{
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();

    string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class MultiplicationExpression : public NumericExpression{
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();

    string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class DivisionExpression : public NumericExpression{
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();

    string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

#endif