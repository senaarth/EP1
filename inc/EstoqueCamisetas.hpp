#include "Estoque.hpp"

#ifndef ESTOQUECAMISETAS_HPP_
#define ESTOQUECAMISETAS_HPP_

class EstoqueCamisetas: public Estoque{
public:
	//Construtor
	EstoqueCamisetas();
	//Destrutor
	~EstoqueCamisetas();

	//Funções para manutenção do estoque.
	void registraProduto(int qntd, char nome[50], float preco); //Exemplo Polimorfismo - Checar implemetação do método em EstoqueCamisetas.cpp

	friend class Estoque;
	friend class Cliente;
};

#endif