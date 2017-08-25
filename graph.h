#pragma once

#include "node.h"
#include "edge.h"
#include "graphexception.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<class Type>
class Graph {
private:
	GraphException exception;
	int num_nodes;
	int init_num_nodes;
	int num_edges;
	Type max_val;
	static Node<Type>* root;
public:

	Graph();

	Graph(int numNodes);

	void addNode(Type* i);

	Node<Type>* findNode(Type* i);

	void addEdge(Type* i, Type* j, bool make_bidirectional = false);

	void removeEdge(Type* i, Type* j, bool check_bidirectional = false);

	bool hasEdge(Type* i, Type* j);

	vector<Type> outEdges(Type* i);

	vector<Type> inEdges(Type* i);

	void breadth_first(Type* s);

	void depth_first(Type* s, bool* visited = nullptr);

	void displayGraph();
	
	void emptyGraph(Type* s = root->data, bool* visited = nullptr);

	~Graph();
};

template<class Type>
Node<Type>* Graph<Type>::root = nullptr;

template<class Type>
Graph<Type>::Graph() {
	init_num_nodes = 0;
	num_nodes = 0;
	num_edges = 0;
	root = nullptr;
}

template<class Type>
Graph<Type>::Graph(int numNodes) {
	init_num_nodes = numNodes;
	num_nodes = 0;
	num_edges = 0;
	root = nullptr;
}

template<class Type>
void Graph<Type>::addNode(Type* i) {
	if (root == nullptr) {
		root = new Node<Type>(i);
		num_nodes++;
		max_val = *i;
		return;
	}
	if (findNode(i) != nullptr) { //Make sure value is unique
		throw exception.unique();
	}
	if (num_nodes == init_num_nodes && init_num_nodes != 0) {
		throw exception.full();
	}
	Node<Type>* searched = new Node<Type>(i);
	searched->next = root;
	root = searched;
	if (*i > max_val) {
		max_val = *i;
	}
	num_nodes++;
}

template<class Type>
Node<Type>* Graph<Type>::findNode(Type* i) { //Traverses through graph to find value
	Node<Type>* searched = root;
	while (searched != nullptr) {
		if (*searched->data == *i) {
			return searched;
		}
		searched = searched->next;
	}
	return searched;
}

template<class Type>
void Graph<Type>::addEdge(Type* i, Type* j, bool make_bidirectional) { //Finds prospective vertices and adds the directional edge
	if (!hasEdge(i, j)) {
		Node<Type>* node1 = findNode(i);
		Node<Type>* node2 = findNode(j);
		if (node1 != nullptr && node2 != nullptr) {
			Edge<Type>* insert = new Edge<Type>(j);
			insert->next = node1->edges;
			node1->edges = insert;
			if (make_bidirectional) {
				insert = new Edge<Type>(i);
				insert->next = node2->edges;
				node2->edges = insert;
			}
			return;
		}
	}
	throw exception.fail_add_edge(); //Throws if either vertice doesn't exist
}

//Attempts to remove the edge from both vertices
template<class Type>
void Graph<Type>::removeEdge(Type* i, Type* j, bool check_bidirectional) {
	//Find both vertices
	Node<Type>* node1 = findNode(i);
	Node<Type>* node2 = findNode(j);
	//Make sure both vertices exist
	if (node1 != nullptr && node2 != nullptr) {
		Edge<Type>* tmp = node1->edges;
		Edge<Type>* prev = node1->edges;
		bool found = false;
		while (tmp != nullptr) {
			if (*tmp->data == *j) {
				found = true;
				if (node1->edges = tmp) {
					node1->edges = tmp->next;
				}
				else {
					prev->next = tmp->next;
				}
				delete tmp;
				break;
			}
			tmp = tmp->next;
		}
		if (!found) { //If the edge doesn't exist - throw
			throw exception.fail_remove_edge();
		}
		if (check_bidirectional) {
			tmp = node2->edges;
			prev = node2->edges;
			while (tmp != nullptr) {
				if (*tmp->data == *i) {
					found = true;
					if (node2->edges = tmp) {
						node2->edges = tmp->next;
					}
					else {
						prev->next = tmp->next;
					}
					delete tmp;
					break;
				}
				tmp = tmp->next;
			}
		}
		return;
	}
	throw exception.fail_remove_edge(); //If a vertice doesn't exist, throw
}

template<class Type>
bool Graph<Type>::hasEdge(Type* i, Type* j) { //Make sure edge exists and is directional
	Node<Type>* node1 = findNode(i);
	Node<Type>* node2 = findNode(j);
	bool found = false;
	if (node1 != nullptr && node2 != nullptr) {
		Edge<Type>* tmp = node1->edges;
		while (tmp != nullptr) {
			if (*tmp->data == *j) {
				found = true;
			}
			tmp = tmp->next;
		}
	}
	return found;
}

template<class Type>
vector<Type> Graph<Type>::outEdges(Type* i) {
	//Return list of integers
	Node<Type>* node = findNode(i);
	vector<Type> output;
	if (node != nullptr) {
		Edge<Type>* e = node->edges;
		while (e != nullptr) {
			output.push_back(*e->data);
			e = e->next;
		}
		return output;
	}
}

template<class Type>
vector<Type> Graph<Type>::inEdges(Type* i) {
	//Return list of integers
	Node<Type>* node = root;
	vector<Type> output;
	while (node != nullptr) {
		if (hasEdge(node->data, i)){
			output.push_back(*node->data);
		}
		node = node->next;
	}
	return output;
}

template<class Type>
void Graph<Type>::breadth_first(Type* s) {
	if (root == nullptr) {
		cout << "NULL" << endl;
		return;
	}
	bool* visited = new bool[max_val+1];
	for (int i = 0; i < max_val+1; i++) {
		visited[i] = false;
	}
	list<Type*> queue;
	Node<Type>* start = findNode(s);
	if (start != nullptr) {
		visited[*s] = true;
		queue.push_back(s);

		while (!queue.empty()) {
			s = queue.front();
			cout << *s << " ";
			queue.pop_front();
			
			start = findNode(s);
			Edge<Type>* edges = start->edges;
			while (edges != nullptr) {
				if (!visited[*edges->data]) {
					visited[*edges->data] = true;
					queue.push_back(edges->data);
				}
				edges = edges->next;
			}
		}
	}
};

template<class Type>
void Graph<Type>::depth_first(Type* s, bool* visited) {
	if (root == nullptr) {
		cout << "NULL" << endl;
		return;
	}
	if (visited == nullptr) {
		visited = new bool[max_val + 1];
		for (int i = 0; i < max_val + 1; i++) {
			visited[i] = false;
		}
	}
	visited[*s] = true;
	cout << *s << " ";
	Node<Type>* start = findNode(s);
	if (start != nullptr) {
		Edge<Type>* edges = start->edges;
		while (edges != nullptr) {
			if (!visited[*edges->data]) {
				depth_first(edges->data, visited);
			}
			edges = edges->next;
		}
	}
};

template<class Type>
void Graph<Type>::displayGraph() { //Displays graph as adjacency table
	if (root != nullptr) {
		cout << "-------Vertices------" << endl;
		Node<Type>* tmp = root;
		while (tmp != nullptr) {
			cout << *tmp->data << " | ";
			tmp = tmp->next;
		}
		cout << endl;
		tmp = root;
		while (tmp != nullptr) {
			cout << "--- ";
			tmp = tmp->next;
		}
		cout << endl;
		tmp = root;
		int edge = 0;
		bool notNull; //flag for first iteration where all edges are null
		do{
			notNull = false;
			while (tmp != nullptr) {
				Edge<Type>* e = tmp->edges;
				for (int i = 0; i < edge; i++) {
					if (e != nullptr) {
						e = e->next;
					}
					else {
						break;
					}
				}
				if (e != nullptr) {
					notNull = true;
					cout << *e->data << " | ";
				}
				else {
					cout << "  | ";
				}
				tmp = tmp->next;
			}
			cout << endl;
			tmp = root;
			edge++;
		} while (notNull);
	}
	else {
		cout << "NULL" << endl;
	}
}

template<class Type>
void Graph<Type>::emptyGraph(Type* s, bool* visited) { //Perform depth first deletion of Graph (Breadth first results in recursive callback to deleted nodes, crashing)
	if (visited == nullptr) {
		visited = new bool[max_val + 1];
		for (int i = 0; i < max_val + 1; i++) {
			visited[i] = false;
		}
	}
	visited[*s] = true;
	Node<Type>* start = findNode(s); //Find node with value
	if (start != nullptr) {
		Edge<Type>* edges = start->edges;
		while (edges != nullptr) {
			if (!visited[*edges->data]) {
				emptyGraph(edges->data, visited); //Traverse as far as you can
			}
			edges = edges->next;
		}
	}
	delete start; //On the way back up, delete the nodes
	num_nodes--;
}

template<class Type>
Graph<Type>::~Graph() {
	if (root != nullptr) {
		emptyGraph(root->data);
	}
}