#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct course{ // course object
	string name;
	double work;
	double learn;
};

// n: number of courses being evaluated
// W: work capacity
double solver(vector<course*>& courses, int n, double W){
	if ((n == 0) || (W == 0)) return 0; // base case
	if (courses[n-1]->work > W) return solver(courses, n-1, W); // skip this course
	return max(courses[n-1]->learn + solver(courses, n-1, W - courses[n-1]->work), 
		solver(courses, n-1, W)); // return the maximum of the two
}

int main(int argc, char* argv[]){
	ifstream File(argv[1]);
	if (File.fail()) return 1; // fail to open file

	int n; // total number of classes
	double W; // work capacity
	string line; // each line of input
	vector<course*> courses; // store all courses

	getline(File, line);
	stringstream s(line); // first line of input
	s >> n >> W;
	for (int i=0; i<n; i++){
		getline(File, line);
		stringstream ss(line);
		course* temp_course = new course; // allocate a new course object
		ss >> temp_course->name >> temp_course->work >> temp_course->learn;
		courses.push_back(temp_course);
	}

	cout << solver(courses, n, W) << endl; // output the best solution

	for (int i=0; i<n; i++){
		delete courses[i]; // delete memory
	}
	return 0;
}