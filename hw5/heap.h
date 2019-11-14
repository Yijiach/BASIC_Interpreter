#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class MinHeap {
public:
  MinHeap (int d){
    /* Constructor that builds a d-ary Min Heap
      This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/
    this->d = d;
  }

  ~MinHeap (){
    for (unsigned int i=0; i<H.size(); i++){
      delete H[i];
    }
    H.clear();
  }

  int add (T item, int priority);
    /* adds the item to the heap, with the given priority. 
      multiple identical items can be in the heap simultaneously. 
      Returns the number of times add has been called prior to this
      call (for use with the update function).*/

  const T & peek () const{
    /* returns the element with smallest priority.
      If two elements have the same priority, use operator< on the 
      T data, and return the one with smaller data.*/
    return H[tie_breaker(H.front()->priority)]->name;
  }

  void remove (){
    /* removes the element with smallest priority, with the same tie-breaker
      as peek. */
    int index = tie_breaker(H.front()->priority);
    swap(H[index], H[0]); // swap this node with root node first
    swap(H[0], H[H.size()-1]); // swap this node with the last node
    delete H[H.size()-1]; // delete the node
    H.pop_back(); // remove the last spot
    TrickleDown(0);
  }

  void update (int nth, int priority);
    /* finds the nth item (where nth is 0-based) that has ever been added 
        to the heap (the node that was created on the nth call to add), 
        and updates its priority accordingly. */

  bool isEmpty (){
    /* returns true if there are no elements on the heap. */
    if (H.empty()) return true;
    return false;
  }

private:
  // whatever you need to naturally store things.
  struct Node{ // stores each node
    T name;
    int priority;
  };
  std::vector<Node*> H; // vector that stores heap 
  int d; // d-ary heap

  // You may also add helper functions here.
  int parent(int i){ // returns parent index
    return (i - 1) / d;
  }

  int child(int i, int k){ // returns kth child index
    return d * i + k;
  }

  int smallest_child(int i){ // returns index of the child with smallest priority
    int smallest_priority = H[child(i, 1)]->priority; // first child's priority
    int index = 0;
    for (int k=1; k<=d; k++){
      if (H[child(i, k)]->priority < smallest_priority){
        smallest_priority = H[child(i, k)]->priority;
        index = child(i, k);
      }
    }
    return index;
  }

  int tie_breaker(int priority){ // returns smallest data's index
    std::vector<Node*> ties;
    T smallest;
    int index;
    for (int i=0; i<(int)H.size(); i++){
      if (H[i]->priority == priority){
        ties.push_back(H[i]);
      }
    }
    // return the root node if it's the only one with smallest priority
    if (ties.size() == 1) return 0;
    smallest = ties[0]->name;
    for (int i=0; i<(int)ties.size(); i++){ // finds smallest data 
      if (ties[i]->name < smallest){
        smallest = ties[i]->name;
        for (int j=0; j<H.size(); j++){ // finds index
          if (H[j]->name = smallest){
            index = j;
          }
        }
      }
    }
    return index;
  }

  void BubbleUp(int i){ // adjust the vector after add()
    if ((i > 0) && (H[i]->priority < H[parent(i)]->priority)){
      swap(H[i], H[parent(i)]);
      BubbleUp(parent(i));
    }
  }

  void TrickleDown(int i){ // adjust the vector after remove()
    if ((i < (int)H.size()) && (H[i]->priority > H[smallest_child(i)]->priority)){
      swap(H[i], H[smallest_child(i)]);
      TrickleDown(smallest_child(i));
    }
  }
};