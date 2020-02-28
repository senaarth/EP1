#ifndef ESTOQUE_HPP_
#define ESTOQUE_HPP_

#include "string"
#include "iostream"
#include "fstream"

#include "Produto.hpp"

using namespace std;

class Estoque {
public:
	//Construtor
	Estoque();
	//Destrutor
	~Estoque();

	//Getters e Setters n�o declarados pois n�o vi necessidade.

	//Fun��es para altera��es no Estoque em geral.
	void visualizaCategoria();
	void registraProduto(int qntd, char nome[50], float preco);
	void alteraEstoque(char nome[50], int qntd);

	friend class Cliente;
	friend class produto;
};

#endif