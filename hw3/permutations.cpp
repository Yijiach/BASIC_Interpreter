# include <iostream>
# include <string>
using namespace std;

void permutations(string in);
void helper(string n, int index);

void permutations(string in){
	int index = 0;
	helper(in, index);
}

void helper(string n, int index){
	if (index == (int)n.size()-1){
		cout << n << endl;
	}
	else{
		for (int i=index; i<(int)n.size(); ++i){
			swap(n[i], n[index]);
			helper(n, index+1);
			swap(n[i], n[index]);
		}
	}
}

// int main(int argc, char* argv[]){
// 	permutations(argv[1]);
// 	return 0;
// }