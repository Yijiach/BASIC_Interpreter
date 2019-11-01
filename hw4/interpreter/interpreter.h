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
#include <stack>
#include <stdexcept>

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
    int get_line_n(); // returns line number
private:
    void parse(std::istream& in);
    std::vector<Command*> entire_program;

    std::map<int, Command*> program_map; // store lines of program
    std::map<std::string, Variable*> int_variable_map; // stores int
    std::map<std::string, Variable*> arr_variable_map; // map from name+index to array variable
    std::map<std::string, int> arr_value; // store array values
    std::map<std::string, NumericExpression*> nexp_map; // stores numeric expressions
    std::map<std::string, BooleanExpression*> bexp_map; // stores boolean expressions
    std::map<int, Constant*> const_map; // map that stores constants

    std::stack<int> origin_line; // origin of gosub lines
    int line_n; // stores line number for error message
    int line_number; // line number used while parsing
    std::map<int, std::vector<NumericExpression*>> index_map; // map from line number to vector of indexes
};

#endif