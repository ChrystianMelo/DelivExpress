#include <cassert>
#include <unordered_set>
#include <limits>
#include <climits>
#include <utility>

#include "Algorithms.h"

namespace {

	/**
	 * \brief Retorna a distância (peso) de `a` para `b`, ou INT_MAX se não houver conexão direta.
	 */
	int getDistance(City& a, City& b) {
		for (const Road& road : a.getEdges()) {
			if (*road.getTarget() == b) {
				return road.getWeight();
			}
		}
		return INT_MAX;
	}

	/**
	 * @brief Função recursiva de Backtracking que testa todas as ordens de visita.
	 */
	void backtrack(
		const std::vector<City*>& nodes,
		City* start,
		City* current,
		long long costSoFar,
		int visitedCount,
		std::vector<bool>& visited,
		std::vector<City*>& path,
		long long& bestCost,
		std::vector<City*>& bestPath
	) {
		int V = static_cast<int>(nodes.size());

		if (visitedCount == V) {
			int w = getDistance(*current, *start);
			if (w != INT_MAX) {
				long long totalCost = costSoFar + w;
				if (totalCost < bestCost) {
					bestCost = totalCost;
					bestPath = path;
				}
			}
			return;
		}

		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				int w = getDistance(*current, *nodes[i]);
				if (w != INT_MAX) {
					visited[i] = true;
					path.push_back(nodes[i]);

					backtrack(nodes, start, nodes[i], costSoFar + w,
						visitedCount + 1, visited, path,
						bestCost, bestPath);

					path.pop_back();
					visited[i] = false;
				}
			}
		}
	}

	std::vector<City*> buildPath(const std::vector<std::vector<int>>& parent,
		unsigned long long mask,
		int current,
		const std::vector<City*>& nodes)
	{
		std::vector<int> order;
		while (current != -1) {
			order.push_back(current);
			int prev = parent[mask][current];

			mask &= ~(1ULL << current);
			current = prev;
		}

		std::reverse(order.begin(), order.end());


		std::vector<City*> path;
		path.reserve(order.size());
		for (int idx : order) {
			path.push_back(nodes[idx]);
		}
		return path;
	}

}

std::pair<long long, std::vector<City*>> Algorithms::bruteForce(Graph& graph) {
	auto& cityList = graph.getNodes();
	std::vector<City*> nodes;
	nodes.reserve(cityList.size());
	for (auto& c : cityList) {
		nodes.push_back(&c);
	}

	long long bestCost = std::numeric_limits<long long>::max();
	std::vector<City*> bestPath;

	int V = static_cast<int>(nodes.size());
	for (int startIndex = 0; startIndex < V; startIndex++) {
		std::vector<bool> visited(V, false);
		visited[startIndex] = true;

		std::vector<City*> path;
		path.push_back(nodes[startIndex]);

		backtrack(nodes, nodes[startIndex], nodes[startIndex], 0LL,
			1, visited, path, bestCost, bestPath);
	}

	return std::make_pair(bestCost, bestPath);
}

std::pair<long long, std::vector<City*>> Algorithms::dynamicProgramming(Graph& graph) {
	auto& cityList = graph.getNodes();
	const int n = static_cast<int>(cityList.size());
	if (n == 0) {
		return { 0LL, {} };
	}

	std::vector<City*> nodes(n);
	for (int i = 0; i < n; i++) {
		nodes[i] = &cityList[i];
	}

	std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = (i == j) ? 0 : getDistance(*nodes[i], *nodes[j]);
		}
	}

	int start = 0;
	std::vector<std::vector<long long>> dp(1ULL << n, std::vector<long long>(n, LLONG_MAX));
	std::vector<std::vector<int>> parent(1ULL << n, std::vector<int>(n, -1));
	dp[1ULL << start][start] = 0LL;

	for (unsigned long long mask = 0; mask < (1ULL << n); mask++) {
		for (int last = 0; last < n; last++) {
			long long costSoFar = dp[mask][last];
			if (costSoFar == LLONG_MAX) continue;

			for (int next = 0; next < n; next++) {

				if ((mask & (1ULL << next)) != 0 || next == last) {
					continue;
				}

				int w = dist[last][next];
				if (w == INT_MAX) {
					continue;
				}
				unsigned long long newMask = mask | (1ULL << next);
				long long newCost = costSoFar + w;
				if (newCost < dp[newMask][next]) {
					dp[newMask][next] = newCost;
					parent[newMask][next] = last;
				}
			}
		}
	}

	long long bestCost = LLONG_MAX;
	int bestEnd = -1;
	unsigned long long fullMask = (1ULL << n) - 1;

	for (int end = 0; end < n; end++) {

		if (dp[fullMask][end] == LLONG_MAX) {
			continue;
		}

		if (dist[end][start] == INT_MAX) {
			continue;
		}

		long long totalCost = dp[fullMask][end] + dist[end][start];
		if (totalCost < bestCost) {
			bestCost = totalCost;
			bestEnd = end;
		}
	}

	std::vector<City*> bestPath;
	if (bestEnd != -1) {
		bestPath = buildPath(parent, fullMask, bestEnd, nodes);
	}

	return { bestCost, bestPath };
}

std::pair<long long, std::vector<City*>> Algorithms::greedy(Graph& graph) {
	auto& cityList = graph.getNodes();
	int n = static_cast<int>(cityList.size());
	if (n == 0) {
		return { 0LL, {} };
	}

	std::vector<City*> nodes(n);
	for (int i = 0; i < n; i++) {
		nodes[i] = &cityList[i];
	}

	long long bestCostGlobal = std::numeric_limits<long long>::max();
	std::vector<City*> bestPathGlobal;


	for (int startIndex = 0; startIndex < n; startIndex++) {
		std::vector<bool> visited(n, false);
		visited[startIndex] = true;

		std::vector<City*> path;
		path.push_back(nodes[startIndex]);

		long long costSoFar = 0LL;
		int currentIndex = startIndex;
		int visitedCount = 1;


		while (visitedCount < n) {
			int bestNext = -1;
			int bestDist = INT_MAX;

			for (int candidate = 0; candidate < n; candidate++) {
				if (!visited[candidate]) {
					int d = getDistance(*nodes[currentIndex], *nodes[candidate]);
					if (d < bestDist) {
						bestDist = d;
						bestNext = candidate;
					}
				}
			}

			if (bestNext == -1 || bestDist == INT_MAX) {

				costSoFar = std::numeric_limits<long long>::max();
				break;
			}

			visited[bestNext] = true;
			path.push_back(nodes[bestNext]);
			costSoFar += bestDist;
			currentIndex = bestNext;
			visitedCount++;
		}

		if (costSoFar != std::numeric_limits<long long>::max()) {

			int distBack = getDistance(*nodes[currentIndex], *nodes[startIndex]);
			if (distBack == INT_MAX) {
				costSoFar = std::numeric_limits<long long>::max();
			}
			else {
				costSoFar += distBack;
			}
		}

		if (costSoFar < bestCostGlobal) {
			bestCostGlobal = costSoFar;
			bestPathGlobal = path;
		}
	}

	return { bestCostGlobal, bestPathGlobal };
}
