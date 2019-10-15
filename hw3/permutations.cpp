# include <iostream>
# include <string>
using namespace std;

void permutations(string in);
void helper(string n, int index);

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
			swap(n[i], n[index]); // swap 2 elements each step
			helper(n, index+1); // recursive call
			swap(n[i], n[index]); // swap back
		}
	}
}