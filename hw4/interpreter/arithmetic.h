#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class NumericExpression {
public:
    NumericExpression(){}
    virtual ~NumericExpression(){}
    virtual std::string format() = 0;
    virtual int get_value() = 0; // get value
    virtual bool is_infinite() = 0; // get division by 0 error while parsing
    virtual bool check_divide() = 0; // pure virtual
};

class Constant : public NumericExpression{
public:
	Constant(int val);
	std::string format();
    int get_value();
    bool check_divide(){return false;}
    bool is_infinite(){return false;}
private:
	int val_;
};

class Variable : public NumericExpression{
public:
	Variable(std::string name, int val);
	virtual std::string format() = 0;
    virtual ~Variable(){}
    void set_value(int n); // set value for the variable
    int get_value();
    std::string get_name();
    virtual NumericExpression* get_index(){return 0;}
    bool check_divide(){return false;}
    virtual bool is_infinite(){return false;}
    virtual bool is_arr() = 0; // check if it is array variable
protected:
	std::string name_;
	int val_; // store value of the variable
};

class IntegerVariable : public Variable{
public:
	IntegerVariable(std::string name, int val);
	std::string format();
    bool is_infinite(){return false;}
    bool is_arr(){return false;}
};

class ArrayVariable : public Variable{
public:
	ArrayVariable(std::string name, NumericExpression *index, int val);
	virtual ~ArrayVariable();
    std::string format();
    NumericExpression* get_index();
    bool is_infinite(){return index_->is_infinite();}
    bool is_arr(){return true;}
private:
	NumericExpression *index_;
};

class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();
    int get_value();
    std::string format();
    bool check_divide(){return false;}
    bool is_infinite();
private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class SubtractionExpression : public NumericExpression{
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();
    int get_value();
    std::string format();
    bool check_divide(){return false;}
    bool is_infinite();
private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class MultiplicationExpression : public NumericExpression{
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();
    int get_value();
    std::string format();
    bool check_divide(){return false;}
    bool is_infinite();
private:
    NumericExpression* left_;
    NumericExpression* right_;
};

class DivisionExpression : public NumericExpression{
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();
    int get_value();
    std::string format();
    bool check_divide(){return true;}
    bool is_infinite();
private:
    NumericExpression* left_;
    NumericExpression* right_;
};

#endif