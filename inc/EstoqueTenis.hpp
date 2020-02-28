#ifndef ESTOQUETENIS_HPP_
#define ESTOQUETENIS_HPP_

#include "Estoque.hpp"

class EstoqueTenis: public Estoque{
public:
	//Construtor
	EstoqueTenis();
	//Destrutor
	virtual ~EstoqueTenis();
	//Fun�oes para manuten��o do estoque.
	void registraProduto(int qntd, char nome[50], float preco); //Exemplo Polimorfismo - Checar implemeta��o do m�todo em EstoqueTenis.cpp
};

#endif