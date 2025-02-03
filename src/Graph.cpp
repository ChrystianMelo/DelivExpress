#include "Graph.h"

#include <cassert>
#include <limits>

#include "Algorithms.h"

Graph::Graph() : m_nodes() {}

Graph::Graph(const std::vector<City>& nodes) : m_nodes(nodes) {}

std::vector<City>& Graph::getNodes() {
	return m_nodes;
}