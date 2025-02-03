#ifndef City_H
#define City_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Road.h"

class Road;
class City;

/**
 * \class NodeVisitor
 * \brief Classe base abstrata para visitar n�s (Citys) em um grafo.
 *
 * Esta classe define a interface para visitantes de n�s em um grafo, permitindo
 * realizar opera��es espec�ficas durante a travessia (DFS ou outros algoritmos).
 */
class NodeVisitor {
public:
	/**
	 * \brief Destrutor virtual padr�o.
	 *
	 * Permite a correta destrui��o de classes derivadas.
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief Visita um n� (City) durante a travessia do grafo.
	 *
	 * Este m�todo deve ser implementado pelas subclasses para definir o comportamento
	 * durante a visita a um n� espec�fico.
	 *
	 * \param node Ponteiro para o n� a ser visitado.
	 */
	virtual void visit(City* node) = 0;

	/**
	 * \brief Ponteiro para o n� principal visitado durante a execu��o do DFS.
	 *
	 * Armazena o n� principal sendo processado durante a travessia.
	 */
	City* dfs_main_visit = nullptr;

	/**
	 * \brief Ponteiro para o n� mais recente visitado no DFS.
	 *
	 * Armazena o n� que foi processado mais recentemente.
	 */
	City* dfs_recent_visit = nullptr;
};

/**
 * \class City
 * \brief Representa um n� (v�rtice) em um grafo.
 *
 * A classe `City` modela um n� em um grafo, que pode estar conectado a outros n�s
 * atrav�s de arestas (representadas pela classe `Road`). Ela oferece m�todos para
 * gerenciar conex�es, acessar informa��es e operar sobre n�s.
 */
class City {
public:
	/**
	 * \brief Construtor padr�o de City.
	 *
	 * Cria uma inst�ncia de City sem arestas conectadas inicialmente.
	 */
	City();

	/**
	 * \brief Construtor de City com �ndice e nome.
	 *
	 * \param index �ndice �nico para identificar a cidade.
	 * \param name Nome opcional para a cidade.
	 *
	 * Este construtor inicializa um n� com um �ndice espec�fico e, opcionalmente, um nome.
	 */
	City(std::size_t index, std::string name = "");

	/**
	 * \brief Obt�m o �ndice da cidade.
	 * \return O �ndice �nico associado � cidade.
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta dois n�s (Citys).
	 *
	 * \param node Ponteiro para o n� a ser conectado a este.
	 * \param weight 
	 *
	 * Adiciona uma conex�o (Road) entre este n� e o n� fornecido.
	 */
	void connect(City* node, int weight);

	/**
	 * \brief Verifica se este n� est� conectado a outro n�.
	 *
	 * \param node Ponteiro para o n� a ser verificado.
	 * \return Verdadeiro se os dois n�s est�o conectados; caso contr�rio, falso.
	 */
	bool isConnected(City* node);

	/**
	 * \brief Obt�m o nome da cidade.
	 * \return Refer�ncia para o nome da cidade.
	 */
	std::string& getName();

	/**
	 * \brief Obt�m as arestas conectadas ao n�.
	 * \return Um vetor de ponteiros para Roads conectadas a este n�.
	 *
	 * Retorna todas as arestas que est�o conectadas ao n� atual, permitindo que
	 * o chamador interaja com as conex�es do n�.
	 */
	std::vector<Road>& getEdges();

	/**
	 * \brief Define as arestas conectadas ao n�.
	 *
	 * \param edges Um vetor de arestas (Roads) a serem atribu�das ao n�.
	 */
	void setEdges(std::vector<Road> edges);

	/**
	 * \brief Operador de igualdade para compara��o de n�s.
	 *
	 * \param other Outro n� a ser comparado.
	 * \return Verdadeiro se os dois n�s possuem o mesmo �ndice.
	 */
	bool operator==(const City& other) const;

	/**
	 * \brief Operador de desigualdade para compara��o de n�s.
	 *
	 * \param other Outro n� a ser comparado.
	 * \return Verdadeiro se os dois n�s possuem �ndices diferentes.
	 */
	bool operator!=(const City& other) const;

	/**
	 * \brief Operador menor que para compara��o de n�s.
	 *
	 * \param other Outro n� a ser comparado.
	 * \return Verdadeiro se o �ndice deste n� for menor que o do outro n�.
	 */
	bool operator<(const City& other) const;

	/**
	 * \struct CityHash
	 * \brief Functor para calcular o hash de um ponteiro para `City`.
	 *
	 * Este functor utiliza o �ndice da cidade para calcular o hash.
	 */
	struct CityHash {
		std::size_t operator()(const City* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 * \struct CityEqual
	 * \brief Functor para verificar a igualdade de dois ponteiros para `City`.
	 *
	 * Este functor utiliza o operador `==` definido na classe `City` para verificar igualdade.
	 */
	struct CityEqual {
		bool operator()(const City* lhs, const City* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 * \brief Cria um mapa personalizado para armazenar dados associados a cidades.
	 *
	 * \tparam T Tipo dos valores armazenados no mapa.
	 * \return Um mapa com chaves do tipo `City*` e valores do tipo `T`.
	 */
	template<typename T>
	static std::unordered_map<City*, T, CityHash, CityEqual> map() {
		return std::unordered_map<City*, T, CityHash, CityEqual>();
	}

private:
	/**
	 * \brief Armazena as arestas conectadas ao n�.
	 *
	 * Um vetor que cont�m todas as conex�es (Roads) que partem deste n� para outros.
	 */
	std::vector<Road> m_edges;

	/**
	 * \brief �ndice �nico da cidade.
	 *
	 * Identifica exclusivamente o n� em um grafo.
	 */
	std::size_t m_index;

	/**
	 * \brief Nome da cidade.
	 *
	 * Nome opcional que pode ser usado para identificar o n� de forma descritiva.
	 */
	std::string m_name;
};

namespace std {
	template <>
	/**
	 * \struct hash<City>
	 * \brief Especializa��o de `std::hash` para a classe `City`.
	 *
	 * Utiliza o �ndice da cidade para calcular o hash.
	 */
	struct hash<City> {
		std::size_t operator()(const City node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // City_H
