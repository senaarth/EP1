#ifndef ESTOQUETENIS_HPP_
#define ESTOQUETENIS_HPP_

#include "Estoque.hpp"

class EstoqueTenis: public Estoque{
public:
	//Construtor
	EstoqueTenis();
	//Destrutor
	virtual ~EstoqueTenis();
	//Funçoes para manutenção do estoque.
	void registraProduto(int qntd, char nome[50], float preco); //Exemplo Polimorfismo - Checar implemetação do método em EstoqueTenis.cpp
};

#endif