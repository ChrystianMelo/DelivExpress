#include "Road.h"

Road::Road(City* source, City* target, int weight) : m_source(source), m_target(target), m_weight(weight) {}

City* Road::getSource() const {
	return m_source;
}

City* Road::getTarget() const {
	return m_target;
}

int Road::getWeight() const {
	return m_weight;
}

bool Road::operator==(const Road& other) const {
	return m_source == other.getSource() && m_target == other.getTarget();
}
