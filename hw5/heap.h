#include <vector>
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

  int add (T item, int priority){
    /* adds the item to the heap, with the given priority. 
      multiple identical items can be in the heap simultaneously. 
      Returns the number of times add has been called prior to this
      call (for use with the update function).*/
    Node* temp = new Node;
    temp->name = item;
    temp->priority = priority;
    H.push_back(temp);
    BubbleUp(H.size()-1);
    return 0; ///////////////////////////////////////////////////////
  }

  //const T & peek () const{
  T& peek(){
    /* returns the element with smallest priority.
      If two elements have the same priority, use operator< on the 
      T data, and return the one with smaller data.*/
    return H[0]->name;
  }

  void remove (){
    /* removes the element with smallest priority, with the same tie-breaker
      as peek. */
    swap_value(H[0], H[H.size()-1]); // swap this node with the last node
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






void get_H(){
  for (int i=0; i<(int)H.size(); i++){
    std::cout << H[i]->name << std::endl;
  }
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
    T name; // used to break tie
    int index = child(i, 1);
    for (int k=1; k<=d; k++){
      if (child(i, k) < (int)H.size()){
        if (H[child(i, k)]->priority < smallest_priority){
          smallest_priority = H[child(i, k)]->priority;
          index = child(i, k);
          name = H[child(i, k)]->name;
        }
        else if (H[child(i, k)]->priority == smallest_priority){ // tie breaker
          if (H[child(i, k)]->name < name){
            smallest_priority = H[child(i, k)]->priority;
            index = child(i, k);
            name = H[child(i, k)]->name;
          }
        }
      }
    }
    return index;
  }

  void BubbleUp(int i){ // adjust the vector after add()
    if ((i > 0) && (H[i]->priority < H[parent(i)]->priority)){
      swap_value(H[i], H[parent(i)]);
      BubbleUp(parent(i));
    }
    else if ((i > 0) && (H[i]->priority == H[parent(i)]->priority)){
      if (H[i]->name < H[parent(i)]->name){
        swap_value(H[i], H[parent(i)]);
        BubbleUp(parent(i));
      }
    }
  }

  void TrickleDown(int i){ // adjust the vector after remove()
    if (child(i, 1) < (int)H.size()){ // else if leaf node, done
      if ((i < (int)H.size()) && (H[i]->priority > H[smallest_child(i)]->priority)){
        swap_value(H[i], H[smallest_child(i)]);
        TrickleDown(smallest_child(i));
      }
      else if ((i < (int)H.size()) && (H[i]->priority == H[smallest_child(i)]->priority)){
        if (H[i]->name > H[smallest_child(i)]->name){
          swap_value(H[i], H[smallest_child(i)]);
          TrickleDown(smallest_child(i));
        }
      }
    }
  }

  void swap_value(Node* node1, Node* node2){ // swap function, deep copy
    T name1 = node1->name;
    T name2 = node2->name;
    int priority1 = node1->priority;
    int priority2 = node2->priority;
    node1->name = name2;
    node2->name = name1;
    node1->priority = priority2;
    node2->priority = priority1;
  }
};