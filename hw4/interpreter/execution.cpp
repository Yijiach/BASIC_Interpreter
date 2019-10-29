#include "interpreter.h"
using namespace std;
void Interpreter :: execute(){ // things those commands actually do
    for (unsigned int i=0; i<entire_program.size(); i++){ // store the program in a map
        program_map[entire_program[i]->get_line()] = entire_program[i];
    }
    map<int, Command*> :: iterator it; // iterate through the entire program
    for (it = program_map.begin(); it != program_map.end(); ++it){
        line_n = it->first;
        // different commands
        if (it->second->get_name() == "END"){
            break;
        }
        else if (it->second->get_name() == "RETURN"){
            if (origin_line.empty()){
                throw runtime_error("No matching GOSUB for RETURN."); // use exception
            }
            it = program_map.find(origin_line.top());
            origin_line.pop();
        }
        else if (it->second->get_name() == "PRINT"){
            vector<NumericExpression*> index_check = index_map[line_n];
            for (unsigned int i=0; i<index_check.size(); i++){
                if (index_check[i]->is_infinite()){
                    cout << index_check[i]->get_value() << endl; // output the division by 0 error message
                }
            }
            cout << it->second->get_nexp()->get_value() << endl; // prints out value
        }
        else if (it->second->get_name() == "LET"){
            vector<NumericExpression*> index_check = index_map[line_n];
            for (unsigned int i=0; i<index_check.size(); i++){
                if (index_check[i]->is_infinite()){
                    cout << index_check[i]->get_value() << endl; // output the division by 0 error message
                }
            }
            if (!it->second->get_var()->is_arr()){
                it->second->get_var()->set_value(it->second->get_nexp()->get_value()); // set value
            }
            else{
                it->second->get_var()->set_value(it->second->get_nexp()->get_value()); // set value
                arr_value[it->second->get_var()->get_name()+
                    to_string(it->second->get_var()->get_index()->get_value())] = 
                it->second->get_nexp()->get_value(); // update the array value map
            }
            // because some variable has changed, so must update other variables as well
            map<string, Variable*> :: iterator it_array;
            for (it_array = arr_variable_map.begin(); it_array != arr_variable_map.end(); ++it_array){
                Variable* temp = it_array->second;
                // update only when the array index has no division by 0 error
                if (!temp->get_index()->is_infinite()){
                    temp->set_value(arr_value[temp->get_name()+to_string(temp->get_index()->get_value())]);
                }
            }
        } // if LET
        else if (it->second->get_name() == "GOTO"){
            if (program_map.find(it->second->get_jline()) == program_map.end()){
                throw runtime_error("GOTO to non-existent line " + 
                    to_string(it->second->get_jline()) + ".");
            }
            it = program_map.find(it->second->get_jline());
            --it; // cancel out the ++i
        }
        else if (it->second->get_name() == "GOSUB"){
            if (program_map.find(it->second->get_jline()) == program_map.end()){
                throw runtime_error("GOSUB to non-existent line " + 
                    to_string(it->second->get_jline()) + ".");
            }
            origin_line.push(it->second->get_line());
            it = program_map.find(it->second->get_jline());
            --it;
        }
        else if (it->second->get_name() == "IF"){
            vector<NumericExpression*> index_check = index_map[line_n];
            for (unsigned int i=0; i<index_check.size(); i++){
                if (index_check[i]->is_infinite()){
                    cout << index_check[i]->get_value() << endl; // output the division by 0 error message
                }
            }
            if (it->second->get_bexp()->get_value()){
                if (program_map.find(it->second->get_jline()) == program_map.end()){
                    throw runtime_error("IF jump to non-existent line " + 
                        to_string(it->second->get_jline()) + ".");
                }
                it = program_map.find(it->second->get_jline());
                --it;
            }
        }
    } // for iterator
} // void execute