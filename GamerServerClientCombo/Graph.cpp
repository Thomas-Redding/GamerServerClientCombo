#include "Graph.hpp"

template <class T>

Edge<T>::Edge(Vertex<T> *org, Vertex<T> *dest) {
	 origin = *org;
	 destination = *dest;
}

template <class T>
Vertex<T>* Edge<T>::getOrigin() {
	return origin;
}

template <class T>
Vertex<T>* Edge<T>::getDestination() {
	return destination;
}

template <class T>
Vertex<T>::Vertex(T id) {
	name = id;
}

template <class T>
void Vertex<T>::addEdge(Vertex *v) {
	Edge<T> newEdge(this, v);
	edges.push_back(newEdge);
}

template <class T>
T Vertex<T>::getName() {
	return name;
}

template <class T>
std::vector<T> Vertex<T>::getEdges() {
	return edges;
}

template <class T>
Graph<T>::Graph() {

}

template <class T>
void Graph<T>::insert(Vertex<T> *v) {
	vertices.push_back(v);
}
