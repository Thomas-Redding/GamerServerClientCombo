#include "Graph.hpp"

/*
 * Creates a new edge with an orgin Vertex and a destination Vertex 
 */
Edge::Edge(Vertex *org, Vertex *dest) {
	origin = org;
	destination = dest;
}

/*
 * Creates a vertex with an id as a String
 */

Vertex::Vertex(std::string id) {
	name = id;
}

/*
 * Adds an edge between this Vertex and the given vertex
 */
void Vertex::addEdge(Vertex *v) {
	Edge newEdge(this, v);
	edges.push_back(newEdge);
}

/*
 * Returns the name of the Vertex
 */
std::string Vertex::getName() {
	return name;
}

/*
 * Returns a list off all the edges in the Graph
 */
std::vector<Edge> Vertex::getEdges() {
	return edges;
}

Graph::Graph() {} // creates a new empty Graph

/*
 * Adds vertex to the list of vertices in the Graph
 */
void Graph::insert(Vertex *v) {
	vertices.push_back(v);
}