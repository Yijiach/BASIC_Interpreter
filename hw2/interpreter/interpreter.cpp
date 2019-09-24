#include "interpreter.h"
using namespace std;

Interpreter::Interpreter(istream& in) {
    this->parse(in);
}

Interpreter::~Interpreter() {
	for (int i=0; i<entire_program.size(); i++){
		entire_program.pop_back();
	}
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
        return new ArrayVariable(name, index, 0);
    }
    else{
        return new IntegerVariable(n, 0);
    }
}

NumericExpression* Interpreter :: parse_numeric_expression(string n){
    if ((n[0] == '-') || (n[0] == '0') || (n[0] == '1') || (n[0] == '1')
        || (n[0] == '2') || (n[0] == '3') || (n[0] == '4') || (n[0] == '5')
        || (n[0] == '6') || (n[0] == '7') || (n[0] == '8') || (n[0] == '9')){
        return parse_constant(n);
    }
    if (n[0] != '('){
        return parse_variable(n);
    }
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
            while (stream >> temp_string){
                numeric_expression += temp_string;
            }
            NumericExpression* nexp = parse_numeric_expression(numeric_expression);
            Print* newCommand = new Print(line_number, nexp);
            entire_program.push_back(newCommand->format());
            delete newCommand;
        }
        else if (command_name == "LET"){

        }
        else if (command_name == "GOTO"){
            int jline;
            stream >> jline;
            GoTo* newCommand = new GoTo(line_number, jline);
            entire_program.push_back(newCommand->format());
            delete newCommand;
        }
        else if (command_name == "IF"){

        }
        else if (command_name == "GOSUB"){
            int jline;
            stream >> jline;
            GoSub* newCommand = new GoSub(line_number, jline);
            entire_program.push_back(newCommand->format());
            delete newCommand;
        }
        else if (command_name == "RETURN"){
            Return* newCommand = new Return(line_number);
            entire_program.push_back(newCommand->format());
            delete newCommand;
        }
        else if (command_name == "END"){
            End* newCommand = new End(line_number);
            entire_program.push_back(newCommand->format());
            delete newCommand;
        }
    }
}

void Interpreter::write(ostream& out) {
    for (unsigned int i=0; i<entire_program.size(); i++){
        out << i+1 << " " << entire_program[i] << endl;
    }
}
