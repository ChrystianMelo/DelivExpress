#include <iostream>

#include <cassert>
#include <unordered_set>
#include <string>
#include <limits>

#include "Algorithms.h"

int main() {
	std::string mode;
	std::cin >> mode;

	std::size_t v, e;
	std::cin >> v >> e;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::size_t index = 1;
	std::unordered_map<std::string, City> map;
	std::vector<std::string> insertion_order;

	for (std::size_t i = 0; i < e; i++) {
		std::string s1, s2;
		int weight;

		std::cin >> s1 >> s2 >> weight;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		City* c1 = nullptr;
		if (auto it = map.find(s1); it == map.end()) {
			map.insert({ s1, City(index++, s1) });
			c1 = &map[s1];
			insertion_order.push_back(s1);
		}
		else {
			c1 = &it->second;
		}

		City* c2 = nullptr;
		if (auto it2 = map.find(s2); it2 == map.end()) {
			map.insert({ s2, City(index++, s2) });
			c2 = &map[s2];
			insertion_order.push_back(s2);
		}
		else {
			c2 = &it2->second;
		}

		c1->connect(c2, weight);
		c2->connect(c1, weight);
	}

	assert(map.size() == v);

	std::vector<City> cities;
	for (const auto& name : insertion_order) {
		cities.push_back(map[name]);
	}

	Graph graph = Graph(cities);

	long long bestCost = 0;
	std::vector<City*> bestPath;
	if (mode == "b")
		std::tie(bestCost, bestPath) = Algorithms::bruteForce(graph);
	else if (mode == "d")
		std::tie(bestCost, bestPath) = Algorithms::dynamicProgramming(graph);
	else if (mode == "g")
		std::tie(bestCost, bestPath) = Algorithms::greedy(graph);
	else
		assert(false);

	std::cout << bestCost << std::endl;
	for (City* city : bestPath) {
		std::cout << city->getName() << " ";
	}
	std::cout << std::endl;
}
