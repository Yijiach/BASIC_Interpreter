#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

class TheRani {
public:
    TheRani(char* input_path, char* output_path);
    ~TheRani();

    // Call execute and handles exceptions
    void main();

private:
    int experiment_count;       // You will need to track the number of experiments
    int subject_counts;        // For each, the number of subjects
    string** subject_history;   // And for each subject, their history

    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    int line_number; // detect the line number of error
    int** current_order;
    bool start; // check if started
    // Called in the main method
    void execute(const string& line); // keeps track of order of subjects in current experiment

    // Possible helper: deallocate all current members
};

TheRani::TheRani(char* input_path, char* output_path) : experiment_count(0), 
                input(input_path), output(output_path), start(false) {
}

TheRani::~TheRani() {
    for (int i=0; i<=experiment_count; i++){
        delete []subject_history[i];
        delete []current_order[i];
    }
    delete []subject_history;
    delete []current_order;
    subject_history = NULL;
    current_order = NULL;
}

// Possible helper: read an integer argument from a stream

void TheRani::main() {
    string line;
    line_number = 0; // initialize line number
    while (getline(input, line)) {
        try {
            this->execute(line);
        } catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output << "Error on line " << line_number <<": " << e.what() << endl;
        } 
    }
}

void TheRani::execute(const string& line) {
    line_number++; // increase line number when executing
    string command;
    stringstream stream(line);  // Initialize the stream with the line
    stream >> command;          // Read the first word, which is the command
    if (command == "START") {   // This code should be edited for error checking
        int subject_pool_count;
        double double_pool_count;
        if (!(stream >> double_pool_count)){
            throw runtime_error("expected integer argument");
        }
         if (ceil(double_pool_count) != floor(double_pool_count)){
            throw runtime_error("expected integer argument");
        }

        subject_pool_count = (int)double_pool_count;

        if (stream.fail()){
            throw runtime_error("too few arguments");
        }
        else if (subject_pool_count < 0) {
            throw runtime_error("argument out of range");
        }
        // Your code here
        else {
            if (start){
                for (int i=0; i<=experiment_count; i++){
                    delete []subject_history[i];
                    delete []current_order[i];
                }
                delete []subject_history;
                delete []current_order;
            }
            start = true;
            subject_counts = subject_pool_count;
            experiment_count = 0;
            subject_history = new string*[1];
            current_order = new int*[1];
            subject_history[0] = new string[subject_counts]; // start a new experiment pool
            current_order[0] = new int[subject_counts];
            for (int i=0; i<subject_counts; i++){
                current_order[0][i] = i;
            }
        }
    } 
    // else if (more conditions) { ...
    else if (command == "ADD"){
        if (!start){
                throw runtime_error("no subjects yet");
        }
        else{
            string temp_history[experiment_count+1][subject_counts];
            int tmep_order[experiment_count+1][subject_counts];
            for (int i=0; i<=experiment_count; i++){
                for (int j=0; j<subject_counts; j++){
                    temp_history[i][j] = subject_history[i][j];
                    tmep_order[i][j] = current_order[i][j];
                }
            }

            // delete the old arrays
            for (int i=0; i<=experiment_count; i++){
                delete []subject_history[i];
                delete []current_order[i];
            }
            delete []subject_history;
            delete []current_order;

            // allocate new arrays
            subject_history = new string*[experiment_count+2];
            current_order = new int*[experiment_count+2];
            for (int i=0; i<=experiment_count; i++){
                subject_history[i] = new string[subject_counts];
                current_order[i] = new int[subject_counts];
                for (int j=0; j<subject_counts; j++){
                    subject_history[i][j] = temp_history[i][j];
                    current_order[i][j] = tmep_order[i][j];
                }
            }
            experiment_count++;
            subject_history[experiment_count] = new string[subject_counts]; // add a new experiment to the pool
            current_order[experiment_count] = new int[subject_counts];
            for (int i=0; i<subject_counts; i++){
                current_order[experiment_count][i] = -1; // -1 means that subject i is not in this experiment
            }
        }
    }
    else if (command == "MOVE"){
        if (!start)
            {throw runtime_error("no subjects yet");}
        else {
            int max_order = -1; // use it for ordering
            int x, y, n, m;
            double double_x, double_y, double_n, double_m;
            if ((!(stream >> double_x >> double_y >> double_n >> double_m)) && (!stream.fail())){
                throw runtime_error("expected integer argument");
            }
            else if ((ceil(double_x) != floor(double_x)) || (ceil(double_y) != floor(double_y)) 
                || (ceil(double_n) != floor(double_n)) || (ceil(double_m) != floor(double_m))){
                    throw runtime_error("expected integer argument");
            }
            else if (stream.fail()){
                throw runtime_error("too few arguments");
            }
            x = (int)double_x;
            y = (int)double_y;
            n = (int)double_n;
            m = (int)double_m;

            if ((x > experiment_count) || (y > experiment_count) || (n >= subject_counts) || (m >= subject_counts)
                || (x < 0) || (y < 0) || (n < 0) || (m < 0)){
                throw runtime_error("argument out of range");
            }
            if (n > m){
                throw runtime_error("invalid range of subjects to move");
            }

            for (int i=n; i<=m; i++){
                 if (current_order[x][i] == -1){
                     throw runtime_error("argument out of range");
                }
            }

            for (int i=0; i<subject_counts; i++){
                if (current_order[y][i] > max_order)
                    {max_order = current_order[y][i];} // find the max order number in current experiment
            }

            int ordering = 1; // initialize the new ordering
            for (int i=n; i<=m; i++){
                if (x != 0){
                    subject_history[y][i] = subject_history[x][i] + " " + to_string(y);
                }
                else{
                    subject_history[y][i] = to_string(y);
                }
                current_order[y][i] =  max_order + ordering; // insert after the max order number
                ordering++;
                if (x != y){
                    current_order[x][i] = -1; // those subjects are removed, order is -1
                }
            }

            for (int i=m+1; i<subject_counts; i++){
                if (current_order[x][i] != -1){
                    current_order[x][i] -= (m-n+1); // some subjects are removed, order must be changed
                }
            }
        }
    }
    else if (command == "QUERY"){
        if (!start)
            {throw runtime_error("no subjects yet");}
        else{
            int subject_number; // use to find the number of subject
            int x, n;
            double double_x, double_n;

            if (!(stream >> double_x >> double_n)){
                throw runtime_error("expected integer argument");
            }
            else if ((ceil(double_x) != floor(double_x)) || (ceil(double_n) != floor(double_n))){
                    throw runtime_error("expected integer argument");
            }
            else if (stream.fail()){
                throw runtime_error("too few arguments");
            }
            x = (int)double_x;
            n = (int)double_n;

            if ((x > experiment_count) || (n >= subject_counts) || (x < 0) || (n < 0)){
                throw runtime_error("argument out of range");
            }

            for (int i=0; i<subject_counts; i++){
                if (current_order[x][i] == n){
                    subject_number = i; // find the subject number
                }
            }

            output << subject_history[x][subject_number] << "\n";
        }
    }
    else
        {throw runtime_error("command does not exist");}

}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }

    TheRani tr(argv[1], argv[2]);
    tr.main();
    return 0;
}