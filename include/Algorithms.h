#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Graph.h"

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) por força bruta.
	 *
	 * Este método testa todas as permutações possíveis de cidades para encontrar a rota
	 * de menor custo que passa por todas elas e retorna ao ponto de partida.
	 *
	 * @param graph Referência para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto é o menor custo necessário para visitar todas as cidades e retornar ao início.
	 *         - melhorRota é a sequência de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n!) no pior caso, pois são consideradas todas as permutações possíveis das cidades.
	 */
	static std::pair<long long, std::vector<City*>> bruteForce(Graph& graph);

	/**
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) utilizando Programação Dinâmica (Held-Karp).
	 *
	 * Este método utiliza a abordagem de Programação Dinâmica para minimizar o custo de percorrer
	 * todas as cidades e retornar ao ponto de partida.
	 *
	 * @param graph Referência para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto é o custo mínimo necessário para percorrer todas as cidades e retornar ao início.
	 *         - melhorRota é a sequência de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n² * 2^n), pois utiliza uma tabela de estados para armazenar os custos parciais
	 *       das sub-rotas, reduzindo a redundância das computações.
	 */
	static std::pair<long long, std::vector<City*>> dynamicProgramming(Graph& graph);

	/**
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) utilizando um algoritmo guloso.
	 *
	 * O método emprega a estratégia do vizinho mais próximo (Nearest Neighbor),
	 * sempre escolhendo a cidade acessível mais próxima como o próximo destino.
	 *
	 * @param graph Referência para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto é o custo total da rota encontrada.
	 *         - melhorRota é a sequência de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n³) no pior caso, pois para cada uma das n cidades possíveis como ponto de partida,
	 *       o algoritmo constrói uma rota em O(n²) (selecionando o vizinho mais próximo a cada passo, exigindo
	 *       uma busca linear entre as cidades não visitadas). Assim, totaliza-se O(n × n²) = O(n³).
	 */
	static std::pair<long long, std::vector<City*>> greedy(Graph& graph);


};

#endif // ALGORITHMS_H