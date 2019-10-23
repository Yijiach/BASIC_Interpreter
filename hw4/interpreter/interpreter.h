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
#include <map>

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
    // actual execution of codes
    void execute();
private:
    void parse(std::istream& in);
    std::vector<Command*> entire_program;
    // memory used to store pieces of program
    std::map<int, Command*> program_map;
    std::map<std::string, int> int_variable_map;
    std::map<std::string, std::vector<int>> arr_variable_map;
};

#endif