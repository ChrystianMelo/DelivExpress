#ifndef Road_H
#define Road_H

#include "City.h"

class City;

/**
 * \class Road
 * \brief Representa uma aresta (conex�o) entre dois n�s (Citys) em um grafo.
 *
 * A classe `Road` modela uma conex�o entre dois n�s (Citys) em um grafo,
 * estabelecendo uma rela��o de vizinhan�a entre eles. Ela tamb�m pode incluir
 * um peso associado � conex�o, �til para algoritmos de grafos ponderados.
 */
class Road {
public:
	/**
	 * \brief Construtor de Road.
	 * \param source N� de origem da aresta.
	 * \param target N� de destino da aresta.
	 * \param weight 
	 *
	 * Cria uma inst�ncia de `Road` que conecta o n� de origem ao n� de destino.
	 * Inicializa o peso padr�o como 1, caso n�o seja especificado.
	 */
	Road(City* source, City* target, int weight);

	/**
	 * \brief Obt�m o n� de origem da aresta.
	 * \return Ponteiro para o n� de origem.
	 *
	 * Retorna o n� de onde a aresta se origina. Este n� � armazenado em `m_source`.
	 */
	City* getSource() const;

	/**
	 * \brief Obt�m o n� de destino da aresta.
	 * \return Ponteiro para o n� de destino.
	 *
	 * Retorna o n� para onde a aresta aponta. Este n� � armazenado em `m_target`.
	 */
	City* getTarget() const;

	/**
	 * \brief Obt�m o peso da aresta.
	 * \return O peso associado � aresta.
	 *
	 * Retorna o valor do peso (por padr�o, inicializado como 1), que pode ser
	 * utilizado em algoritmos de caminhos m�nimos, como Dijkstra.
	 */
	int getWeight() const;

	/**
	 * \brief Operador de igualdade para compara��o de arestas.
	 * \param other Outra inst�ncia de `Road` para comparar.
	 * \return Verdadeiro se ambas as arestas possuem o mesmo n� de origem,
	 *         n� de destino e peso; caso contr�rio, retorna falso.
	 */
	bool operator==(const Road& other) const;

private:
	/**
	 * \brief N� de origem da aresta.
	 *
	 * Este atributo armazena o ponteiro para o n� (City) de onde a aresta se origina.
	 */
	City* m_source;

	/**
	 * \brief N� de destino da aresta.
	 *
	 * Este atributo armazena o ponteiro para o n� (City) para onde a aresta aponta.
	 */
	City* m_target;

	/**
	 * \brief Peso da aresta.
	 *
	 * Um valor inteiro que representa o custo ou peso associado � aresta.
	 * O peso � inicializado como 1 por padr�o.
	 */
	int m_weight;
};

#endif // Road_H
