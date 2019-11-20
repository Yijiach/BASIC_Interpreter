# include <iostream>
# include <string>
using namespace std;

// function prototypes
void permutations(string in);
void helper(string n, int index);
void swap_char(string& n, int i, int j);

void swap_char(string& n, int i, int j){
	char temp = n[i];
	n[i] = n[j];
	n[j] = temp;
}

void permutations(string in){
	if (!in.empty()){ // check if the input is empty
		int index = 0;
		helper(in, index); // call helper function
	}
}

void helper(string n, int index){
	// when every element is swapped, cout the string
	if (index == (int)n.size()-1){
		cout << n << endl;
	}
	else{
		for (int i=index; i<(int)n.size(); ++i){
			swap_char(n, i, index); // swap 2 elements each step
			helper(n, index+1); // recursive call
			swap_char(n, i, index); // swap back
		}
	}
}