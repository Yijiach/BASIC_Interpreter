# include <iostream>
# include <fstream>
# include <string>
using namespace std;

int main(int argc, char* argv[])
{
	int *size = new int; // length of the sentence	
	ifstream myFile(argv[1]); // read file

	if (!myFile.fail())
	{
		myFile >> *size;
		char *reverse = new char[*size]; // will store the sentence
		string line;
		getline(myFile, line); // consumes "\n"
		getline(myFile, line); // get the sentence

		for (int i=0; i<*size; i++)
		{reverse[i] = line[*size-i-1];} // stores the sentence in reverse order

		for (int i=0; i<*size; i++)
		{cout << reverse[i];}
		cout << endl;

		delete []reverse;
	}
	delete size;
	return 0;
}