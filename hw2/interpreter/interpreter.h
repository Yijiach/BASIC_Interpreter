#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "arithmetic.h"
#include "boolean.h"
#include "command.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Interpreter {
public:
    Interpreter(istream& in);
    ~Interpreter();

    void write(ostream& out);
    Constant* parse_constant(string n);
    Variable* parse_variable(string n);
    NumericExpression* parse_numeric_expression(string n);
    BooleanExpression* parse_boolean_expression(string n);

private:
    void parse(istream& in);
    vector<Command*> entire_program;
};

#endif