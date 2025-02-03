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
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) por for�a bruta.
	 *
	 * Este m�todo testa todas as permuta��es poss�veis de cidades para encontrar a rota
	 * de menor custo que passa por todas elas e retorna ao ponto de partida.
	 *
	 * @param graph Refer�ncia para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto � o menor custo necess�rio para visitar todas as cidades e retornar ao in�cio.
	 *         - melhorRota � a sequ�ncia de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n!) no pior caso, pois s�o consideradas todas as permuta��es poss�veis das cidades.
	 */
	static std::pair<long long, std::vector<City*>> bruteForce(Graph& graph);

	/**
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) utilizando Programa��o Din�mica (Held-Karp).
	 *
	 * Este m�todo utiliza a abordagem de Programa��o Din�mica para minimizar o custo de percorrer
	 * todas as cidades e retornar ao ponto de partida.
	 *
	 * @param graph Refer�ncia para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto � o custo m�nimo necess�rio para percorrer todas as cidades e retornar ao in�cio.
	 *         - melhorRota � a sequ�ncia de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n� * 2^n), pois utiliza uma tabela de estados para armazenar os custos parciais
	 *       das sub-rotas, reduzindo a redund�ncia das computa��es.
	 */
	static std::pair<long long, std::vector<City*>> dynamicProgramming(Graph& graph);

	/**
	 * @brief Resolve o Problema do Caixeiro Viajante (TSP) utilizando um algoritmo guloso.
	 *
	 * O m�todo emprega a estrat�gia do vizinho mais pr�ximo (Nearest Neighbor),
	 * sempre escolhendo a cidade acess�vel mais pr�xima como o pr�ximo destino.
	 *
	 * @param graph Refer�ncia para o objeto Graph contendo as cidades.
	 * @return Um par (melhorCusto, melhorRota), onde:
	 *         - melhorCusto � o custo total da rota encontrada.
	 *         - melhorRota � a sequ�ncia de City* na ordem em que devem ser visitadas.
	 *
	 * @note Complexidade: O(n�) no pior caso, pois para cada uma das n cidades poss�veis como ponto de partida,
	 *       o algoritmo constr�i uma rota em O(n�) (selecionando o vizinho mais pr�ximo a cada passo, exigindo
	 *       uma busca linear entre as cidades n�o visitadas). Assim, totaliza-se O(n � n�) = O(n�).
	 */
	static std::pair<long long, std::vector<City*>> greedy(Graph& graph);


};

#endif // ALGORITHMS_H