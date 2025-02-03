#include <cassert>
#include <unordered_set>
#include <limits>
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

} // namespace

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

	long long bestCostGlobal = std::numeric_limits<long long>::max();
	std::vector<City*> bestPathGlobal;

	std::vector<std::vector<long long>> dp(1ULL << n, std::vector<long long>(n, LLONG_MAX));
	std::vector<std::vector<int>> parent(1ULL << n, std::vector<int>(n, -1));

	for (int start = 0; start < n; start++) {
		for (unsigned long long mask = 0; mask < (1ULL << n); mask++) {
			std::fill(dp[mask].begin(), dp[mask].end(), LLONG_MAX);
			std::fill(parent[mask].begin(), parent[mask].end(), -1);
		}

		dp[1ULL << start][start] = 0LL;
		for (unsigned long long mask = 0; mask < (1ULL << n); mask++) {
			for (int last = 0; last < n; last++) {
				if (dp[mask][last] == LLONG_MAX) continue;
				for (int next = 0; next < n; next++) {
					if (next == last || (mask & (1ULL << next)) != 0) continue;
					int w = dist[last][next];
					if (w == INT_MAX) continue;
					unsigned long long newMask = mask | (1ULL << next);
					long long newCost = dp[mask][last] + w;
					if (newCost < dp[newMask][next]) {
						dp[newMask][next] = newCost;
						parent[newMask][next] = last;
					}
				}
			}
		}
	}

	return { bestCostGlobal, bestPathGlobal };
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

		for (int step = 1; step < n; step++) {
			int bestNext = -1, bestDist = INT_MAX;
			for (int candidate = 0; candidate < n; candidate++) {
				if (!visited[candidate]) {
					int d = getDistance(*nodes[currentIndex], *nodes[candidate]);
					if (d < bestDist) {
						bestDist = d;
						bestNext = candidate;
					}
				}
			}
			if (bestNext == -1 || bestDist == INT_MAX) break;
			visited[bestNext] = true;
			costSoFar += bestDist;
			currentIndex = bestNext;
			path.push_back(nodes[bestNext]);
		}
	}

	return { bestCostGlobal, bestPathGlobal };
}
