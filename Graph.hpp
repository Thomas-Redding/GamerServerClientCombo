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
#include <string>
#include <vector>

class Vertex; 
class Edge {
public:
	Edge(Vertex *org, Vertex *dest);
	Vertex* getOrigin();
	Vertex* getDestination;
private:
	Vertex* origin;
	Vertex* destination;

};

class Vertex {
public:
	Vertex(std::string point);
	void addEdge(Vertex *v);
	std::string getName();
	std::vector<Edge> getEdges();

private:
	std::string name;
	std::vector<Edge> edges;
};

class Graph {
public:
	Graph();
	void insert(Vertex *v);
private:
	std::vector<Vertex*> vertices;
};
	



#endif /*Graph_cpp*/

