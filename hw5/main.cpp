#include "heap.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]){
	MinHeap<string> myHeap(3);

	myHeap.add("a", 10);
	myHeap.add("b", 9);
	myHeap.add("c", 8);
	myHeap.add("d", 7);
	myHeap.remove();
	cout << myHeap.peek() << endl;

	return 0;
}