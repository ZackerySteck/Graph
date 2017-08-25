#pragma once

template<class Type>
class Edge {

template<class Type>
friend class Node; //Declare node class as a friend

template<class Type>
friend class Graph; //Declare graph class a friend

private:
	Edge<Type>* next;
	Type* data;
public:
	Edge();

	Edge(Type* data);

	Type getData();

	~Edge();
};

template<class Type>
Edge<Type>::Edge() {
	next = nullptr;
	data = nullptr;
}

template<class Type>
Edge<Type>::Edge(Type* in) {
	next = nullptr;
	data = in;
}

template<class Type>
Edge<Type>::~Edge() {
}

template<class Type>
Type Edge<Type>::getData() {
	return *data;
}