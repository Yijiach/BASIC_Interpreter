# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
using namespace std;

int main(int argc, char* argv[])
{
	int size; // length of the sentence
	string line; // stores size and the sentence
	ifstream myFile(argv[1]); // read in file
	if (!myFile.fail())
	{
		getline(myFile, line); // get the size
		stringstream ss(line);
		ss >> size;
		getline(myFile, line); // get the sentence

		for (int i=0; i<size; i++)
		{
			cout << line[size-i-1]; // output the sentence in reverse order
		}
		cout << endl;
	}
	return 0;
}