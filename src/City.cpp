#include "City.h"

City::City() : m_index(0) {}

City::City(std::size_t index, std::string name) : m_index(index), m_name(name) {}

void City::connect(City* node, int weight) {
	m_edges.push_back(Road(this, node, weight));
}

bool City::isConnected(City* node) {
	for (Road& e : m_edges)
		if (*e.getTarget() == *node)
			return true;
	return false;
}

std::string& City::getName() { return m_name; }

std::vector<Road>& City::getEdges() {
	return m_edges;
}

void City::setEdges(std::vector<Road> edges) { m_edges = edges; }

bool City::operator==(const City& other) const {
	return m_index == other.getIndex();
}

bool City::operator!=(const City& other) const {
	return m_index != other.getIndex();
}

bool City::operator<(const City& other) const {
	return this->m_index < other.getIndex();
}

std::size_t City::getIndex() const { return m_index; }