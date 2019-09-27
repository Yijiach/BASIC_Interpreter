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

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);
    // all specific parse functions
    Constant* parse_constant(std::string n);
    Variable* parse_variable(std::string n);
    NumericExpression* parse_numeric_expression(std::string n);
    BooleanExpression* parse_boolean_expression(std::string n);

private:
    void parse(std::istream& in);
    std::vector<Command*> entire_program;
};

#endif