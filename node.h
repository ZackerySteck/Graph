#pragma once
#include "edge.h"

template<class Type>
class Node {

template<class Type>
friend class Graph; //Declare graph class as a friend

private:
	Edge<Type>* edges;
	Node<Type>* next;
	Type* data;
public:
	Node();

	Node(Type* in);

	~Node();

	void Node<Type>::emptyEdges(Edge<Type>* in);



	bool operator==(const Node<Type>& inNode) { return data == inNode.data }

	bool operator!=(const Node<Type>& inNode) { return data != inNode.data }

	bool operator>(const Node<Type>& inNode) { return data > inNode.data }

	bool operator<(const Node<Type>& inNode) { return data < inNode.data }
};

template<class Type>
Node<Type>::Node() {
	edges = nullptr;
	next = nullptr;
	data = nullptr;
}

template<class Type>
Node<Type>::Node(Type* in) {
	edges = nullptr;
	next = nullptr;
	data = in;
}

template<class Type>
void Node<Type>::emptyEdges(Edge<Type>* in) {
	if (in != nullptr) {
		emptyEdges(in->next);
		delete in;
	}
}

template<class Type>
Node<Type>::~Node() {
	emptyEdges(edges);
}