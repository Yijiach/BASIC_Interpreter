#include "heap.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]){
	MinHeap<string> myHeap(3);

	myHeap.add("c", 3);
	myHeap.add("a", 5);
	myHeap.add("d", 2);
	myHeap.add("e", 1);
	myHeap.add("b", 4);
	myHeap.add("x", 1);
	myHeap.add("y", 1);
	myHeap.add("z", 1);

	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;
	myHeap.remove();
	cout << myHeap.peek() << endl;

	return 0;
}