#include "interpreter.h"
using namespace std;

Interpreter::Interpreter(istream& in) {
    this->parse(in);
}

Interpreter::~Interpreter() {
	for (int i=0; i<entire_program.size(); i++){
        delete entire_program[i];
	}
    entire_program.clear();
}

Constant* Interpreter :: parse_constant(string n){
    stringstream s(n);
    int val = 0;
    s >> val;
    return new Constant(val);
}

Variable* Interpreter :: parse_variable(string n){
    if (n[n.size()-1] == ']'){
        int start = 0;
        int end = 0;
        for (int i=0; i<n.size(); i++){
            if (n[i] == '['){start = i;}
            if (n[i] == ']'){end = i;}
        }
        string name = n.substr(0, start);
        NumericExpression* index = 
        parse_numeric_expression(n.substr(start+1, end-start-1));
        return new ArrayVariable(name, index, 0); // value is not given, so make it 0
    }
    else{
        return new IntegerVariable(n, 0); // value is not given, so make it 0
    }
}

NumericExpression* Interpreter :: parse_numeric_expression(string n){
    if ((n[0] == '-') || (n[0] == '0') || (n[0] == '1') || (n[0] == '1')
        || (n[0] == '2') || (n[0] == '3') || (n[0] == '4') || (n[0] == '5')
        || (n[0] == '6') || (n[0] == '7') || (n[0] == '8') || (n[0] == '9')){
        return parse_constant(n);
    }
    else if (n[0] != '('){
        return parse_variable(n);
    }
    else{
        bool most_inside = true;
        for (int i=1; i<n.size(); i++){
            if (n[i] == '('){
                most_inside = false;
            }
        }
        if (most_inside){
            bool is_add = false;
            bool is_multiply = false;
            bool is_subtract = false;
            bool is_divide = false;
            // find the position of the operator
            int operator_index = 0; 
            for (int i=1; i<n.size()-1; i++){
                if (n[i] == '+'){
                    is_add = true;
                    operator_index = i;
                }
                if (n[i] == '*'){
                    is_multiply = true;
                    operator_index = i;
                }
                if (n[i] == '-'){
                    is_subtract = true;
                    operator_index = i;
                }
                if (
                    n[i] == '/'){
                    is_divide = true;
                    operator_index = i;
                }
            }
            NumericExpression* left = 
            parse_numeric_expression(n.substr(1,operator_index-1));
            NumericExpression* right = 
            parse_numeric_expression(n.substr(operator_index+1,n.size()-2-operator_index));
            if (is_add){return new AdditionExpression(left, right);}
            if (is_multiply){return new MultiplicationExpression(left, right);}
            if (is_subtract){return new SubtractionExpression(left, right);}
            if (is_divide){return new DivisionExpression(left, right);}
        }
        else{
            //n = n.substr(1,n.size()-2);
            int left_count = 0;
            int right_count = 0;
            bool is_add = false;
            bool is_multiply = false;
            bool is_subtract = false;
            bool is_divide = false;
            int operator_index = 0;
            for (int i=1; i<n.size()-1; i++){
                // count the number of ()
                if (n[i] == '('){left_count++;}
                if (n[i] == ')'){right_count++;}
                // find the outmost operator
                if ((n[i] == '+') && (left_count == right_count)){
                    operator_index = i;
                    is_add = true;
                    break;
                }
                else if ((n[i] == '*') && (left_count == right_count)){
                    operator_index = i;
                    is_multiply = true;
                    break;
                }
                else if ((n[i] == '-') && (left_count == right_count)){
                    operator_index = i;
                    is_subtract = true;
                    break;
                }
                else if ((n[i] == '/') && (left_count == right_count)){
                    operator_index = i;
                    is_divide = true;
                    break;
                }
            }
            NumericExpression* left = 
            parse_numeric_expression(n.substr(1,operator_index-1));
            NumericExpression* right = 
            parse_numeric_expression(n.substr(operator_index+1,n.size()-2-operator_index));
            if (is_add){return new AdditionExpression(left, right);}
            if (is_multiply){return new MultiplicationExpression(left, right);}
            if (is_subtract){return new SubtractionExpression(left, right);}
            if (is_divide){return new DivisionExpression(left, right);}
        }
    }
}

BooleanExpression* Interpreter :: parse_boolean_expression(string n){
    bool is_equal = false;
    bool is_larger = false;
    bool is_less = false;
    int operator_index = 0;
    for (int i=0; i<n.size(); i++){
        if (n[i] == '='){
            is_equal = true;
            operator_index = i;
        }
        if (n[i] == '>'){
            is_larger = true;
            operator_index = i;
        }
        if (n[i] == '<'){
            is_less = true;
            operator_index = i;
        }
    }
    NumericExpression* left = 
    parse_numeric_expression(n.substr(0,operator_index));
    NumericExpression* right = 
    parse_numeric_expression(n.substr(operator_index+1,n.size()-1-operator_index));
    if (is_equal){return new EqualTo(left, right);}
    if (is_larger){return new LargerThan(left, right);}
    if (is_less){return new LessThan(left, right);}
}

void Interpreter::parse(istream& in) {
    string line;
    while (getline(in, line)) {
        int line_number;
        stringstream stream(line);
        stream >> line_number;

        // Your code here
        string command_name;
        stream >> command_name;
        if (command_name == "PRINT"){
            string numeric_expression = "";
            string temp_string = "";
            while (stream >> temp_string){numeric_expression += temp_string;}
            NumericExpression* nexp = parse_numeric_expression(numeric_expression);
            Print* newCommand = new Print(line_number, nexp);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "LET"){
            string variable = ""; // the integer variable or array variable
            string numeric_expression = ""; // the actual numeric expression
            string variable_name = "";
            stream >> variable_name;
            string remaining = "";
            int end_variable_index = 0; // if the close bracket is in the remaining
            string temp_string;
            while (stream >> temp_string){remaining += temp_string;}
            if (variable_name[variable_name.size()-1] == ']'){ // Y[5]
                variable = variable_name;
                numeric_expression = remaining;
            }
            else if (remaining[0] == '['){ // Y  [5]
                for (int i=0; i<remaining.size(); i++){
                    if (remaining[i] == ']'){
                        end_variable_index = i;
                        break;
                    }
                }
                variable = variable_name + remaining.substr(0, end_variable_index+1);
                numeric_expression = remaining.substr(end_variable_index+1, 
                    remaining.size()-end_variable_index-1);
            }
            else{ // Y[5   ] or Y
                bool break_in_half = false;
                for (int i=0; i<variable_name.size(); i++){
                    if (variable_name[i] == '['){
                        break_in_half = true;
                        break;
                    }
                }
                if (break_in_half){ // Y[5   ]
                    for (int i=0; i<remaining.size(); i++){
                        if (remaining[i] == ']'){
                            end_variable_index = i;
                            break;
                        }
                    }
                    variable = variable_name + remaining.substr(0, end_variable_index+1);
                    numeric_expression = remaining.substr(end_variable_index+1, 
                        remaining.size()-end_variable_index-1);
                }
                else{ // Y
                    variable = variable_name;
                    numeric_expression = remaining;
                }
            }
            // parse the correct variable and numeric expression
            Variable* var = parse_variable(variable);
            NumericExpression* nexp = parse_numeric_expression(numeric_expression);
            Let* newCommand = new Let(line_number, var, nexp);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "GOTO"){
            int jline;
            stream >> jline;
            GoTo* newCommand = new GoTo(line_number, jline);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "IF"){
            string boolean_expression = "";
            string temp_string;
            int jline = 0;
            while(stream >> temp_string){
                if (temp_string == "THEN"){break;}
                else{boolean_expression += temp_string;}
            }
            stream >> jline;
            BooleanExpression* bexp = parse_boolean_expression(boolean_expression);
            IfThen* newCommand= new IfThen(line_number, bexp, jline);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "GOSUB"){
            int jline;
            stream >> jline;
            GoSub* newCommand = new GoSub(line_number, jline);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "RETURN"){
            Return* newCommand = new Return(line_number);
            entire_program.push_back(newCommand);
        }
        else if (command_name == "END"){
            End* newCommand = new End(line_number);
            entire_program.push_back(newCommand);
        }
    }
}

void Interpreter::write(ostream& out) {
    for (unsigned int i=0; i<entire_program.size(); i++){
        out << entire_program[i]->format() << endl;
    }
}
