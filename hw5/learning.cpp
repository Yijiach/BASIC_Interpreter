#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct course{ // course object
	string name;
	double work;
	double learn;
};

// i: number of courses evaluated
// W: work capacity
// w: current total work
// l: total learned
// solutions: all valid solutions
// build solutions
void build(vector<course*>& courses, int i, double W, double w, double l, vector<double>& solutions){
	if (i == (int)courses.size()){
		solutions.push_back(l);
	}
	else{
		if (w + courses[i]->work <= W){
			solutions.push_back(l + courses[i]->learn);
			// 2 recursive calls, either add this course or not
			build(courses, i+1, W, w+courses[i]->work, l+courses[i]->learn, solutions);
			build(courses, i+1, W, w, l, solutions);
		}
		else{
			if (courses[i]->work <= W){ // a single course can be a solution
				solutions.push_back(courses[i]->learn);
			}
			build(courses, i+1, W, w, l, solutions);
		}
	}
}

// find the best solution
double findMax(vector<double>& solutions){
	double max = 0;
	for (unsigned int i=0; i<solutions.size(); i++){
		if (solutions[i] > max){
			max = solutions[i];
		}
	}
	return max;
}

int main(int argc, char* argv[]){
	ifstream File(argv[1]);
	if (File.fail()) return -1; // fail to open file
	int n; // total number of classes
	double W; // work capacity
	string line; // each line of input
	vector<course*> courses; // store all courses
	vector<double> solutions; // store all solutions

	getline(File, line);
	stringstream s(line); // first line of input
	s >> n;
	s >> W;
	for (int i=0; i<n; i++){
		getline(File, line);
		stringstream ss(line);
		course* temp_course = new course; // allocate a new course object
		ss >> temp_course->name;
		ss >> temp_course->work;
		ss >> temp_course->learn;
		courses.push_back(temp_course);
	}

	build(courses, 0, W, 0, 0, solutions); // build solutions piece by piece
	cout << findMax(solutions) << endl;

	for (int i=0; i<n; i++){
		delete courses[i];
	}
	return 0;
}