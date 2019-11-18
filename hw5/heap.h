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
    n = 0;
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
    temp->index = n;
    H.push_back(temp);
    I.push_back((int)H.size()-1);
    BubbleUp(H.size()-1);
    n++; // increase n
    return n-1; // num of adds prior to this call
  }

  //const T & peek () const{
  T& peek(){
    /* returns the element with smallest priority.
      If two elements have the same priority, use operator< on the 
      T data, and return the one with smaller data.*/
    if (isEmpty()) {} // do nothing if empty
    return H[0]->name;
  }

  void remove (){
    /* removes the element with smallest priority, with the same tie-breaker
      as peek. */
    if (!isEmpty()){
      swap_value(H[0], H[H.size()-1]); // swap this node with the last node
      swap_index(I, H[0]->index, H[H.size()-1]->index); // swap index
      delete H[H.size()-1]; // delete the node
      H.pop_back(); // remove the last spot
      TrickleDown(0);
    }
  }

  void update (int nth, int priority){
    /* finds the nth item (where nth is 0-based) that has ever been added 
        to the heap (the node that was created on the nth call to add), 
        and updates its priority accordingly. */
    if (I[nth] < (int)H.size()){
      H[I[nth]]->priority = priority;
      if ((I[nth] > 0) && (H[I[nth]]->priority <= H[parent(I[nth])]->priority)){
        BubbleUp(I[nth]);
      }
      else if ((smallest_child(I[nth]) < (int)H.size()) && 
        (H[I[nth]]->priority >= H[smallest_child(I[nth])]->priority)){
        TrickleDown(I[nth]);
      }
    }
  }

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
    int index; // nth add
  };
  std::vector<Node*> H; // vector that stores heap 
  std::vector<int> I; // stores index
  int d; // d-ary heap
  int n; // number of adds

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
      swap_value(H[i], H[parent(i)]); // swap node
      swap_index(I, H[i]->index, H[parent(i)]->index); // swap index
      BubbleUp(parent(i));
    }
    else if ((i > 0) && (H[i]->priority == H[parent(i)]->priority)){
      if (H[i]->name < H[parent(i)]->name){
        swap_value(H[i], H[parent(i)]); // swap node
        swap_index(I, H[i]->index, H[parent(i)]->index); // swap index
        BubbleUp(parent(i));
      }
    }
  }

  void TrickleDown(int i){ // adjust the vector after remove()
    if (child(i, 1) < (int)H.size()){ // else if leaf node, done
      if ((i < (int)H.size()) && (H[i]->priority > H[smallest_child(i)]->priority)){
        swap_value(H[i], H[smallest_child(i)]); // swap node
        swap_index(I, H[i]->index, H[smallest_child(i)]->index); // swap index
        TrickleDown(smallest_child(i));
      }
      else if ((i < (int)H.size()) && (H[i]->priority == H[smallest_child(i)]->priority)){
        if (H[i]->name > H[smallest_child(i)]->name){
          swap_value(H[i], H[smallest_child(i)]); // swap node
          swap_index(I, H[i]->index, H[smallest_child(i)]->index); // swap index
          TrickleDown(smallest_child(i));
        }
      }
    }
  }

  void swap_value(Node* node1, Node* node2){ // swap node data members
    T name1 = node1->name;
    T name2 = node2->name;
    int priority1 = node1->priority;
    int priority2 = node2->priority;
    int index1 = node1->index;
    int index2 = node2->index;
    node1->name = name2;
    node2->name = name1;
    node1->priority = priority2;
    node2->priority = priority1;
    node1->index = index2;
    node2->index = index1;
  }

  void swap_index(std::vector<int>& I, int a, int b){ // swap the index of two nodes
    int temp1 = I[a];
    int temp2 = I[b];
    I[a] = temp2;
    I[b] = temp1;
  }
};