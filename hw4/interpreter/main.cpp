#include <iostream>
#include <fstream>
#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        return 1;
    }
    ifstream input(argv[1]); // check if the file exist or can be opened
    if (input.fail()){
    	cout << "File " << argv[1] << " cannot be opened." << endl;
    	return 1;
    }
    Interpreter interpreter(input);
    //interpreter.write(cout);
    try{
        interpreter.execute(); // code executions
    } catch(exception& e) {
        cout << "Error in Line " << interpreter.get_line_n() << ": ";
        cout << e.what() << endl;
    } 
    return 0;
}
