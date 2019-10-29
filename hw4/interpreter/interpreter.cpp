#include "interpreter.h"
using namespace std;
Interpreter::Interpreter(istream& in) { // constructor
    this->parse(in);
}
Interpreter::~Interpreter() { // destructor
    map<string, Variable*> :: iterator it;
    for (it = int_variable_map.begin(); it != int_variable_map.end(); ++it){
        delete it->second; // delete int variables
    }
    for (it = arr_variable_map.begin(); it != arr_variable_map.end(); ++it){
        delete it->second; // delete array variables
    }
    map<string, NumericExpression*> :: iterator it2;
    for (it2 = nexp_map.begin(); it2 != nexp_map.end(); ++it2){
        delete it2->second; // delete numeric expressions
    }
    map<int, Command*> :: iterator it3;
    for (it3 = program_map.begin(); it3 != program_map.end(); ++it3){
        delete it3->second; // delete commands
    }
    map<int, Constant*> :: iterator it4;
    for (it4 = const_map.begin(); it4 != const_map.end(); ++it4){
        delete it4->second; // delete constants
    }
    map<string, BooleanExpression*> :: iterator it5;
    for (it5 = bexp_map.begin(); it5 != bexp_map.end(); ++it5){
        delete it5->second; // delete bools
    }
}
Constant* Interpreter :: parse_constant(string n){ // parse constant
    stringstream s(n);
    int val = 0;
    s >> val;
    if (const_map.find(val) != const_map.end()){
        return const_map[val];
    }
    Constant* temp = new Constant(val);
    const_map[val] = temp;
    return temp;
}
Variable* Interpreter :: parse_variable(string n){ // parse variable
    if (n[n.size()-1] == ']'){
        int start = 0;
        int end = 0;
        for (unsigned int i=0; i<n.size(); i++){
            if (n[i] == '['){
                start = i;
                break;
            }
        }
        end = n.size()-1;
        string name = n.substr(0, start);
        NumericExpression* index = parse_numeric_expression(n.substr(start+1, end-start-1));
        string string_index = index->format();
        if (arr_variable_map.find(name+string_index+to_string(line_number)) != arr_variable_map.end()){
            index_map[line_number].push_back(index);
            return arr_variable_map[name+string_index+to_string(line_number)];
        }
        ArrayVariable* temp =  new ArrayVariable(name, index, 0);
        arr_variable_map[name+string_index+to_string(line_number)] = temp; // store it in map
        index_map[line_number].push_back(index);
        return temp;
    }
    else{
        if (int_variable_map.find(n) != int_variable_map.end()){
            return int_variable_map[n]; // if variable already exist
        }
        IntegerVariable* temp = new IntegerVariable(n, 0);
        int_variable_map[n] = temp;
        return temp;
    }
    return 0;
}
// parse numeric expression, use recursion. Base case: (X+Y)
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
        for (unsigned int i=1; i<n.size(); i++){
            if (n[i] == '('){
                most_inside = false;
            }
        }
        if (most_inside){
            bool is_add = false, is_multiply = false, is_subtract = false, is_divide = false;
            int operator_index = 0; // find the position of the operator
            for (unsigned int i=1; i<n.size()-1; i++){
                if (n[i] == '+'){
                    is_add = true;
                    operator_index = i;
                    break;
                }
                if (n[i] == '*'){
                    is_multiply = true;
                    operator_index = i;
                    break;
                }
                if ((n[i] == '-') && (i != 1)){ // case -1 - -1
                    is_subtract = true;
                    operator_index = i;
                    break;
                }
                if (
                    n[i] == '/'){
                    is_divide = true;
                    operator_index = i;
                    break;
                }
            }
            string l = n.substr(1,operator_index-1); // left
            string r = n.substr(operator_index+1,n.size()-2-operator_index); // right
            NumericExpression* left = NULL;
            NumericExpression* right = NULL;
            if ((l[0] == '-') || (l[0] == '0') || (l[0] == '1') || (l[0] == '1')
                || (l[0] == '2') || (l[0] == '3') || (l[0] == '4') || (l[0] == '5')
                || (l[0] == '6') || (l[0] == '7') || (l[0] == '8') || (l[0] == '9')){
                left = parse_constant(l); // parse constant after chacking the first digit
            }
            else{
                left = parse_variable(l);
            }
            if ((r[0] == '-') || (r[0] == '0') || (r[0] == '1') || (r[0] == '1')
                || (r[0] == '2') || (r[0] == '3') || (r[0] == '4') || (r[0] == '5')
                || (r[0] == '6') || (r[0] == '7') || (r[0] == '8') || (r[0] == '9')){
                right = parse_constant(r); // parse constant after chacking the first digit
            }
            else{
                right = parse_variable(r);
            }
            if (is_add){
                AdditionExpression* temp = new AdditionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                AdditionExpression* new_nexp = new AdditionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_multiply){
                MultiplicationExpression* temp = new MultiplicationExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                MultiplicationExpression* new_nexp = new MultiplicationExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_subtract){
                SubtractionExpression* temp = new SubtractionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                SubtractionExpression* new_nexp = new SubtractionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_divide){
                DivisionExpression* temp = new DivisionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                DivisionExpression* new_nexp = new DivisionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
        }
        else{
            int left_count = 0, right_count = 0, operator_index = 0;
            bool is_add = false, is_multiply = false, is_subtract = false, is_divide = false;
            for (unsigned int i=0; i<n.size()-1; i++){
                // count the number of ()
                if (n[i] == '('){left_count++;}
                if (n[i] == ')'){right_count++;}
                // find the outmost operator
                if ((n[i] == '+') && (left_count == right_count+1)){
                    operator_index = i;
                    is_add = true;
                    break;
                }
                else if ((n[i] == '*') && (left_count == right_count+1)){
                    operator_index = i;
                    is_multiply = true;
                    break;
                }
                else if ((n[i] == '-') && (left_count == right_count+1) && (i != 1)){
                    operator_index = i;
                    is_subtract = true;
                    break; // edge case (-1 - -1)
                }
                else if ((n[i] == '/') && (left_count == right_count+1)){
                    operator_index = i;
                    is_divide = true;
                    break;
                }
            }
            NumericExpression* left = 
            parse_numeric_expression(n.substr(1,operator_index-1));
            NumericExpression* right = 
            parse_numeric_expression(n.substr(operator_index+1,n.size()-2-operator_index));
            if (is_add){
                AdditionExpression* temp = new AdditionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                AdditionExpression* new_nexp = new AdditionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_multiply){
                MultiplicationExpression* temp = new MultiplicationExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                MultiplicationExpression* new_nexp = new MultiplicationExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_subtract){
                SubtractionExpression* temp = new SubtractionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                SubtractionExpression* new_nexp = new SubtractionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
            if (is_divide){
                DivisionExpression* temp = new DivisionExpression(left, right);
                if (nexp_map.find(temp->format()) != nexp_map.end()){
                    string numeric_string = temp->format();
                    delete temp; // temp only used to check format
                    return nexp_map[numeric_string];
                }
                delete temp;
                DivisionExpression* new_nexp = new DivisionExpression(left, right);
                nexp_map[new_nexp->format()] = new_nexp;
                return new_nexp; // if not already exist
            }
        }
    }
    return 0;
}
BooleanExpression* Interpreter :: parse_boolean_expression(string n){ // parse boolean expression
    bool is_equal = false, is_larger = false, is_less = false;
    int operator_index = 0;
    for (unsigned int i=0; i<n.size(); i++){
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
    if (is_equal){
        EqualTo* temp = new EqualTo(left, right);
        if (bexp_map.find(temp->format()) != bexp_map.end()){
            string bool_string = temp->format();
            delete temp; // temp only used to check format
            return bexp_map[bool_string];
        }
        delete temp;
        EqualTo* new_bexp = new EqualTo(left, right);
        bexp_map[new_bexp->format()] = new_bexp;
        return new_bexp; // if not already exist
    }
    if (is_larger){
        LessThan* temp = new LessThan(right, left);
        if (bexp_map.find(temp->format()) != bexp_map.end()){
            string bool_string = temp->format();
            delete temp; // temp only used to check format
            return bexp_map[bool_string];
        }
        delete temp;
        LessThan* new_bexp = new LessThan(right, left);
        bexp_map[new_bexp->format()] = new_bexp;
        return new_bexp; // if not already exist
    } // change X>Y to Y<X
    if (is_less){
        LessThan* temp = new LessThan(left, right);
        if (bexp_map.find(temp->format()) != bexp_map.end()){
            string bool_string = temp->format();
            delete temp; // temp only used to check format
            return bexp_map[bool_string];
        }
        delete temp;
        LessThan* new_bexp = new LessThan(left, right);
        bexp_map[new_bexp->format()] = new_bexp;
        return new_bexp; // if not already exist
    }
    return 0;
}
void Interpreter::parse(istream& in) { // parse command and store them in vector
    string line;
    while (getline(in, line)) {
        //int line_number;
        stringstream stream(line);
        stream >> line_number;
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
            int left_bracket_count = 0, right_bracket_count = 0;
            while (stream >> temp_string){remaining += temp_string;}
            for (unsigned int i=0; i<variable_name.size(); i++){
                if (variable_name[i]=='['){left_bracket_count++;}
                else if (variable_name[i]==']'){right_bracket_count++;}
            }
            if (left_bracket_count == right_bracket_count){ // Y[5]
                variable = variable_name;
                numeric_expression = remaining;
            }
            else if (remaining[0] == '['){ // Y  [5]
                int left_count = 0;
                int right_count = 0;
                for (unsigned int i=0; i<remaining.size(); i++){
                    if (remaining[i] == '['){left_count++;}
                    if (remaining[i] == ']'){right_count++;}
                    if ((remaining[i] == ']') && (left_count == right_count)){
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
                for (unsigned int i=0; i<variable_name.size(); i++){
                    if (variable_name[i] == '['){
                        break_in_half = true;
                        break;
                    }
                }
                if (break_in_half){ // Y[5   ]
                    int left_count = 0;
                    int right_count = 0;
                    for (unsigned int i=0; i<variable_name.size(); ++i){
                        if (variable_name[i] == '['){left_count++;}
                        if (variable_name[i] == ']'){right_count++;}
                    }
                    for (unsigned int i=0; i<remaining.size(); i++){
                        if (remaining[i] == '['){left_count++;}
                        if (remaining[i] == ']'){right_count++;}
                        if ((remaining[i] == ']') && (left_count == right_count)){
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
void Interpreter::write(ostream& out) { // pretty print
    for (unsigned int i=0; i<entire_program.size(); i++){
        out << entire_program[i]->format() << endl;
    }
}
int Interpreter :: get_line_n(){return line_n;} // returns line number for error message