#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "arithmetic.h"
#include "boolean.h"
using namespace std;

class Command {
public:
	//virtual ~Command() = 0;
	Command(int line);
    virtual string format() = 0;
    virtual NumericExpression* get_val(){return NULL;}
protected: // private?
	int line_; // line number
};

class Print : public Command{
public:
	Print(int line, NumericExpression* nexp);
	virtual ~Print();
	string format();
private:
	NumericExpression* nexp_;
};

class Let : public Command{
public:
	Let(int line, Variable* var, NumericExpression* nexp);
	virtual ~Let();
	NumericExpression* get_var(); // necessary?
	string format();
private:
	NumericExpression* var_;
	NumericExpression* nexp_;
};

class GoTo : public Command{
public:
	GoTo(int line, int jline);
	string format();
private:
	int jline_; // line number jumps to
};

class IfThen : public Command{
public:
	IfThen(int line, BooleanExpression* bexp, int jline);
	virtual ~IfThen();
	string format();
private:
	BooleanExpression* bexp_;
	int jline_;
};

class GoSub : public Command{
public:
	GoSub(int line, int jline);
	string format();
private:
	int jline_;
};

class Return : public Command{
public:
	Return(int line);
	string format();
};

class End : public Command{
public:
	End(int line);
	string format();
};

#endif