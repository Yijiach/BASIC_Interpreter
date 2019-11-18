#include "heap.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]){
	MinHeap<string> myHeap(3);

	myHeap.add("A", 11);
	myHeap.add("B", 12);
	myHeap.add("C", 13);
	myHeap.add("D", 14);
	myHeap.add("E", 15);
	myHeap.add("F", 16);
	myHeap.add("G", 17);
	myHeap.add("H", 18);
	myHeap.update(4, 9);
	cout << myHeap.peek() << endl;//E
	myHeap.update(1, 8);
	cout << myHeap.peek() << endl;//B
	myHeap.remove();
	cout << myHeap.peek() << endl;//E
	myHeap.update(1,9);




	return 0;
}