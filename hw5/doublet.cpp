#include "heap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

struct graph_node{
	string word; // actual word
	int h; // heuristic
	vector<int> neighbors; // words that differ only 1 char with this word
	graph_node(string w, int heuristic){ // constructor
		word = w;
		h = heuristic;
	}
};

int get_heuristic(string& n, string& target){ // find heuristic
	int h = 0;
	for (int i=0; i<(int)n.size(); i++){
		if (n[i] != target[i]){
			h++;
		}
	}
	return h;
}

void upper(string& n){ // change n to all uppercases
	for (int i=0; i<(int)n.size(); i++){
		if (n[i] >= 'a' && n[i] <= 'z'){
			n[i] = n[i] - 'a' + 'A';
		}
	}
}

// build the graph explicitly
void build_graph(map<string, int>& index_map, vector<graph_node>& graph){
	for (int i=0; i<(int)graph.size(); i++){
		string w = graph[i].word; // itrate through each word
		for (int j=0; j<(int)w.size(); j++){
			string s = w; // stores temperary word that is changed by 1 char
			for (char k='A'; k<='Z'; k++){
				s[j] = k;
				if (s == w) continue; // skips itself
				map<string, int>::iterator it = index_map.find(s); // O(logn)
				if (it != index_map.end()){
					int neighbor_index = it->second;
					// add it to the graph neighbors
					graph[index_map[w]].neighbors.push_back(neighbor_index);
				}
			}
		}
	}
}

void search(map<string, int>& index_map, vector<graph_node>& graph, int source_index, string target){
	bool found = false;
	int expansions = 0; // number of expansions
	bool visited[graph.size()]; // keep track of if visited
	int g[graph.size()]; // g values (distances from start)
	MinHeap<string> Heap(2); // binary heap
	map<string, int> n_th; // keep track of n_th added
	for (int i=0; i<(int)graph.size(); i++){
		visited[i] = false; // initialize
		g[i] = 0; // initialize
	}

	string source_stirng = graph[source_index].word;
	int priority = (g[source_index] + graph[source_index].h) * 
	(source_stirng.size() + 1) + graph[source_index].h; // properly breaks tie
	n_th[source_stirng] = Heap.add(source_stirng, priority); // first node in heap

	while (!Heap.isEmpty()){
		string curr_word = Heap.peek();
		Heap.remove(); // remove the visited node
		visited[index_map[curr_word]] = true;

		if (curr_word == target){ // if found
			found = true;
			cout << g[index_map[curr_word]] + graph[index_map[curr_word]].h << endl;
			cout << expansions << endl;
			break;
		}

		expansions++; // increment expansions

		for (int i=0; i<(int)graph[index_map[curr_word]].neighbors.size(); i++){
			int index = graph[index_map[curr_word]].neighbors[i]; // index in graph
			int h = graph[index].h;
			if (!visited[index] && (g[index_map[curr_word]]+1 < g[index] || g[index] == 0)){
				g[index] = g[index_map[curr_word]] + 1; // updates g value if finds a shorter path
				visited[index] = true;
				int priority = (g[index] + h) * (graph[index].word.size() + 1) + h;
				n_th[graph[index].word] = Heap.add(graph[index].word, priority); // add into heap
			}
			else if (visited[index] && g[index_map[curr_word]]+1 < g[index]){ // update if visited
				g[index] = g[index_map[curr_word]] + 1;
				int priority = (g[index] + h) * (graph[index].word.size() + 1) + h;
				Heap.update(n_th[graph[index].word], priority);
			}
		}
	}

	if (!found){
		cout << "No transformation" << endl;
		cout << expansions << endl;
	}
}

int main(int argc, char* argv[]){
	if (argc < 4){ // not enough argument
		return 1;
	}
	string source = argv[1];
	string target = argv[2];
	upper(source);
	upper(target);

	if (source == target || source.size() != target.size()){ // no transformation
		cout << "No transformation" << endl;
		cout << 0 << endl;
		return 0;
	}

	ifstream File(argv[3]);
	int n; // number of words in the list
	File >> n;
	string tmp; // consumes end of line
	getline(File, tmp);

	vector<graph_node> graph; // all graph nodes
	map<string, int> index_map; // map from word to index in the vector

	string line; // each line
	string w; //each word
	int index = 0; // keep track of index
	int source_index = 0; // finds where the source word is
	for (int i=0; i<n; i++){
		getline(File, line);
		if (line == "") continue; // skip if empty line
		stringstream ss(line);
		ss >> w;
		upper(w); // make it all uppercase first
		if (w.size() != target.size()) continue; // skip if different in size

		int h = get_heuristic(w, target);
		graph_node temp(w, h);
		graph.push_back(temp); // add it to graph
		index_map[w] = index; // insert a new mapping
		if (w == source) source_index = index;
		index++; // increment index
	}

	build_graph(index_map, graph); // build the graph
	search(index_map, graph, source_index, target); // perform A* search

	return 0;
}