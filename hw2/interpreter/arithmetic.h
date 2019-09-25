#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <iostream>

class NumericExpression {
public:
    NumericExpression(){}
    virtual ~NumericExpression(){}
    virtual std::string format() = 0;
};

class Constant : public NumericExpression{
public:
	Constant(int val);
	std::string format();
private:
	int val_;
};

class Variable : public NumericExpression{
public:
	Variable(std::string name, int val);
	virtual std::string format() = 0;
    virtual ~Variable(){}
protected: // private?
	std::string name_;
	int val_; // store value of the variable
};

class IntegerVariable : public Variable{
public:
	IntegerVariable(std::string name, int val);
	std::string format();
};

class ArrayVariable : public Variable{
public:
	ArrayVariable(std::string name, NumericExpression *index, int val); // (int val?)
	virtual ~ArrayVariable();
    std::string format();
private:
	NumericExpression *index_;
};

class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

    std::string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class SubtractionExpression : public NumericExpression{
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();

    std::string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class MultiplicationExpression : public NumericExpression{
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();

    std::string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class DivisionExpression : public NumericExpression{
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();

    std::string format();

private:
    NumericExpression* left_;
    NumericExpression* right_;
};

#endif