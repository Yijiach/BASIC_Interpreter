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
            if (inf_index_arrays.find(line_n) != inf_index_arrays.end()){ // invalid array check
                cout << inf_index_arrays[line_n]->get_index()->get_value() << endl;
            }
            cout << it->second->get_nexp()->get_value() << endl; // prints out value
        }
        else if (it->second->get_name() == "LET"){
            if (inf_index_arrays.find(line_n) != inf_index_arrays.end()){ // invalid array check
                cout << inf_index_arrays[line_n]->get_index()->get_value() << endl;
            }
            it->second->get_var()->set_value(it->second->get_nexp()); //set value
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
            if (inf_index_arrays.find(line_n) != inf_index_arrays.end()){ // invalid array check
                cout << inf_index_arrays[line_n]->get_index()->get_value() << endl;
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