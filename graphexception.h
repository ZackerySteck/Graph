#pragma once
#include <exception>

class GraphException : public std::exception {
public:
	virtual const char* unique() const throw() { //Stack overflow case
		return "Error: Attempt to add non-unique value to list not allowed.";
	}
	virtual const char* fail_add_edge() const throw() { //Stack underflow case
		return "Error: Attempt to add edge to graph using unknown vertice values, or edge already exists. Please check the values are in the graph, and try again.";
	}
	virtual const char* fail_remove_edge() const throw() { //Stack underflow case
		return "Error: Attempt to remove edge to graph using unknown vertice values, or non-existent edge. Please check the vertices/edge is in the graph, and try again.";
	}
	virtual const char* full() const throw() { //Stack underflow case
		return "Error: Attempt to add node results in size greater than size set by constructor. Please check the current size, and try again.";
	}
};