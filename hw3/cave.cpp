#include <stack>
#include <fstream>
#include <iostream>
using namespace std;

// check if it is able to roll up
bool roll_up(stack<char> s, char dir){
	if (s.empty()) return false;
	if ((s.top() == 'N') && (dir == 'S')) return true;
	else if ((s.top() == 'S') && (dir == 'N')) return true;
	else if ((s.top() == 'W') && (dir == 'E')) return true;
	else if ((s.top() == 'E') && (dir == 'W')) return true;
	return false;
}

int main(int argc, char* argv[]){
	ifstream myFile(argv[1]);
	stack<char> s;
	char dir; // stores current direction
	while (myFile >> dir){
		if (roll_up(s, dir)) s.pop();
		else s.push(dir);
	}
	cout << s.size() << endl;
	return 0;
}