#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "arithmetic.h"
#include "boolean.h"

class Command {
public:
	Command(int line);
    virtual std::string format() = 0;
    virtual ~Command(){}
    int get_line();
protected:
	int line_; // line number
};

class Print : public Command{
public:
	Print(int line, NumericExpression* nexp);
	virtual ~Print();
	std::string format();
private:
	NumericExpression* nexp_;
};

class Let : public Command{
public:
	Let(int line, Variable* var, NumericExpression* nexp);
	virtual ~Let();
	std::string format();
private:
	NumericExpression* var_;
	NumericExpression* nexp_;
};

class GoTo : public Command{
public:
	GoTo(int line, int jline);
	std::string format();
private:
	int jline_; // line number jumps to
};

class IfThen : public Command{
public:
	IfThen(int line, BooleanExpression* bexp, int jline);
	virtual ~IfThen();
	std::string format();
private:
	BooleanExpression* bexp_;
	int jline_;
};

class GoSub : public Command{
public:
	GoSub(int line, int jline);
	std::string format();
private:
	int jline_;
};

class Return : public Command{
public:
	Return(int line);
	std::string format();
};

class End : public Command{
public:
	End(int line);
	std::string format();
};

#endif
