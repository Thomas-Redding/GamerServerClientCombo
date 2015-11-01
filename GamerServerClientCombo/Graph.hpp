//
// Graph.hpp
// GamerServerClientCombo
//
// Created by Jonathan Harris on Ocotber 18, 2015
//
//

#ifndef Graph_cpp
#define Graph_cpp

#include <iostream>
#include <vector>

 
template <class T> class Vertex;


template <class T> class Edge {
public:
	Edge(Vertex<T> *org, Vertex<T> *dest);
	Vertex<T>* getOrigin();
	Vertex<T>* getDestination();
private:
	Vertex<T>* origin;
	Vertex<T>* destination;

};

template <class T> class Vertex {
public:
	Vertex(T point);
	void addEdge(Vertex<T> *v);
	T getName();
	std::vector<T> getEdges();

private:
	T name;
	std::vector<Edge<T>> edges;
};


template <class T> class Graph {
public:
	Graph();
	void insert(Vertex<T> *v);
private:
	std::vector<Vertex<T>*> vertices;
};
	



#endif /*Graph_cpp*/

