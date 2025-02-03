#ifndef Archadian_H
#define Archadian_H

#include <vector>

#include "City.h"

/**
 * \class Archadian
 * \brief Representa um grafo contendo múltiplos nós (Citys).
 *
 * Esta classe encapsula um grafo, onde os nós representam cidades (Citys)
 * e as arestas representam conexões entre elas. Também fornece métodos para
 * realizar cálculos relacionados a capital, batalhões e patrulhamento no grafo.
 */
class Graph {
public:
	/**
	 * \brief Construtor padrão da classe Archadian.
	 *
	 * Inicializa um grafo vazio sem nenhum nó. Este construtor cria uma instância
	 * de 'Archadian' sem nós ou arestas, ideal para ser preenchido posteriormente.
	 */
	Graph();

	/**
	 * \brief Construtor da classe Archadian com um conjunto de nós.
	 *
	 * \param nodes Vetor contendo os nós (Citys) que farão parte do grafo.
	 *
	 * Este construtor inicializa o grafo com um vetor de nós fornecido. Ele permite
	 * a criação de um grafo já populado com nós.
	 */
	Graph(const std::vector<City>& nodes);

	/**
	 * \brief Obtém os nós do grafo.
	 * \return Referência ao vetor de Citys presentes no grafo.
	 *
	 * Este método retorna todos os nós armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os nós do grafo.
	 */
	std::vector<City>& getNodes();

private:
	/**
	 * \brief Armazena os nós (Citys) do grafo.
	 *
	 * Um vetor que contém todos os nós (Citys) presentes no grafo. Cada nó
	 * pode estar conectado a outros nós através de arestas (Roads).
	 */
	std::vector<City> m_nodes;
};

#endif // Archadian_H