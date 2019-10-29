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
    virtual std::string get_name() = 0; // pure virtual
    virtual Variable* get_var(){return NULL;}
    virtual NumericExpression* get_nexp(){return NULL;}
    virtual BooleanExpression* get_bexp(){return NULL;}
    virtual int get_jline(){return 0;} // not pure virtual
protected:
	int line_; // line number
};

class Print : public Command{
public:
	Print(int line, NumericExpression* nexp);
	virtual ~Print();
	std::string format();
	std::string get_name();
	NumericExpression* get_nexp();
private:
	NumericExpression* nexp_;
};

class Let : public Command{
public:
	Let(int line, Variable* var, NumericExpression* nexp);
	virtual ~Let();
	std::string format();
	std::string get_name();
	Variable* get_var();
	NumericExpression* get_nexp();
private:
	Variable* var_;
	NumericExpression* nexp_;
};

class GoTo : public Command{
public:
	GoTo(int line, int jline);
	std::string format();
	std::string get_name();
	int get_jline();
private:
	int jline_; // line number jumps to
};

class IfThen : public Command{
public:
	IfThen(int line, BooleanExpression* bexp, int jline);
	virtual ~IfThen();
	std::string format();
	std::string get_name();
	BooleanExpression* get_bexp();
	int get_jline();
private:
	BooleanExpression* bexp_;
	int jline_;
};

class GoSub : public Command{
public:
	GoSub(int line, int jline);
	std::string format();
	std::string get_name();
	int get_jline();
private:
	int jline_;
};

class Return : public Command{
public:
	Return(int line);
	std::string format();
	std::string get_name();
};

class End : public Command{
public:
	End(int line);
	std::string format();
	std::string get_name();
};

#endif
