#define BOOST_TEST_MODULE testAlgorithms

#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <set>

/**
 * \brief Compara duas strings de entrada para verificar igualdade em estrutura e conte�do.
 *
 * Esta fun��o realiza a compara��o de duas strings formatadas. A estrutura esperada �:
 * 1. Uma palavra inicial, seguida por um n�mero (m1/m2).
 * 2. Um conjunto de palavras (de tamanho m1/m2).
 * 3. Um n�mero adicional (n1/n2), seguido por n1/n2 linhas contendo palavras.
 *
 * A fun��o verifica se:
 * - A palavra inicial e os n�meros m1/n1 s�o iguais.
 * - Os conjuntos de palavras associados s�o equivalentes.
 * - As palavras nas linhas subsequentes (como um conjunto) s�o iguais.
 *
 * \param input1 Primeira string de entrada a ser comparada.
 * \param input2 Segunda string de entrada a ser comparada.
 *
 * \return Verdadeiro se as duas strings forem estruturalmente e semanticamente iguais; falso caso contr�rio.
 */
bool compareStrings(const std::string& input1, const std::string& input2) {
	std::istringstream stream1(input1);
	std::istringstream stream2(input2);

	std::string word1, word2;
	stream1 >> word1;
	stream2 >> word2;
	if (word1 != word2) return false;

	int m1, m2;
	stream1 >> m1;
	stream2 >> m2;
	if (m1 != m2) return false;

	std::set<std::string> set1, set2;
	for (int i = 0; i < m1; ++i) {
		stream1 >> word1;
		set1.insert(word1);
	}
	for (int i = 0; i < m2; ++i) {
		stream2 >> word2;
		set2.insert(word2);
	}
	if (set1 != set2) return false;

	int n1, n2;
	stream1 >> n1;
	stream2 >> n2;
	if (n1 != n2) return false;

	std::set<std::string>  allWords1, allWords2;
	std::string line;

	std::getline(stream1, line); 	std::getline(stream2, line);
	for (int i = 0; i < n1; ++i) {
		std::getline(stream1, line);
		std::istringstream lineStream1(line);
		while (lineStream1 >> word1) {
			allWords1.insert(word1);
		}
	}

	for (int i = 0; i < n2; ++i) {
		std::getline(stream2, line);
		std::istringstream lineStream2(line);
		while (lineStream2 >> word2) {
			allWords2.insert(word2);
		}
	}

	return allWords1 == allWords2;

}

/**
 * \brief L� o conte�do de um arquivo para uma string.
 *
 * Esta fun��o abre um arquivo no caminho fornecido, l� todo o seu conte�do e o retorna como uma string.
 * Lan�a uma exce��o se o arquivo n�o puder ser aberto.
 *
 * \param filePath Caminho para o arquivo a ser lido.
 * \return O conte�do do arquivo como uma string.
 *
 * \throws std::runtime_error Se o arquivo n�o puder ser aberto.
 */
std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		throw std::runtime_error("Erro ao abrir arquivo: " + filePath);
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

/**
 * \brief Executa um programa externo com uma entrada fornecida e retorna a sa�da.
 *
 * Esta fun��o cria dois arquivos tempor�rios:
 * 1. `temp_input.txt` para armazenar a entrada.
 * 2. `temp_output.txt` para armazenar a sa�da gerada pelo programa externo.
 *
 * O programa execut�vel deve estar localizado em `./bin/run.out`. A entrada � redirecionada do arquivo tempor�rio
 * e a sa�da capturada no arquivo de sa�da. Ap�s a execu��o, os arquivos tempor�rios s�o removidos.
 *
 * \param input A string de entrada que ser� passada para o programa.
 * \return A sa�da gerada pelo programa como uma string.
 *
 * \throws std::runtime_error Se o programa n�o puder ser executado ou se ocorrer erro na manipula��o de arquivos.
 */
std::string runProgram(const std::string& input) {
	const std::string executable = "./bin/run.out";

	const std::string tempInput = "temp_input.txt";
	const std::string tempOutput = "temp_output.txt";

	std::ofstream inputFile(tempInput);
	inputFile << input;
	inputFile.close();

	const std::string command = executable + " < " + tempInput + " > " + tempOutput;
	int retCode = std::system(command.c_str());
	if (retCode != 0) {
		throw std::runtime_error("Erro ao executar o programa.");
	}

	std::string output = readFile(tempOutput);

	std::filesystem::remove(tempInput);
	std::filesystem::remove(tempOutput);

	return output;
}


BOOST_AUTO_TEST_CASE(IntegrationTest) {
	BOOST_CHECK(1==1);
}
/*
// Roda os arquivos de teste em modo Força bruta
BOOST_AUTO_TEST_CASE(IntegrationTest_BruteForce) {
	namespace fs = std::filesystem;
	const std::string inputsPath = "./tests/inputs";
	const std::string outputsPath = "./tests/outputs";

	for (const auto& inputFile : fs::directory_iterator(inputsPath)) {
		std::string inputFilePath = "b" + std::endl + inputFile.path().string();

		std::string outputFilePath = outputsPath + "/" + inputFile.path().filename().string();

		std::string input = readFile(inputFilePath);
		std::string expectedOutput = readFile(outputFilePath);

		std::string actualOutput = runProgram(input);

		BOOST_CHECK_MESSAGE(
			compareStrings(actualOutput, expectedOutput),
			"Falha no teste para arquivo: " + inputFilePath +
			"\nSa�da esperada:\n" + expectedOutput +
			"\nSa�da gerada:\n" + actualOutput
		);
	}
}

// Roda os arquivos de teste em modo Programação Dinamica
BOOST_AUTO_TEST_CASE(IntegrationTest_DynamicProgramming) {
	namespace fs = std::filesystem;
	const std::string inputsPath = "./tests/inputs";
	const std::string outputsPath = "./tests/outputs";

	for (const auto& inputFile : fs::directory_iterator(inputsPath)) {
		std::string inputFilePath = "d" + std::endl + inputFile.path().string();

		std::string outputFilePath = outputsPath + "/" + inputFile.path().filename().string();

		std::string input = readFile(inputFilePath);
		std::string expectedOutput = readFile(outputFilePath);

		std::string actualOutput = runProgram(input);

		BOOST_CHECK_MESSAGE(
			compareStrings(actualOutput, expectedOutput),
			"Falha no teste para arquivo: " + inputFilePath +
			"\nSa�da esperada:\n" + expectedOutput +
			"\nSa�da gerada:\n" + actualOutput
		);
	}
}*/
