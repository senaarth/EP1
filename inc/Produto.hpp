#ifndef PRODUTO_HPP_
#define PRODUTO_HPP_

#include <iostream>
#include <string>
using namespace std;

class Produto {
private:
	int qntdEstoque;
	float preco;
	string categoria, nome;
public:
	Produto(char nome[50], string categoria, float preco, int qntdEstoque);
	Produto(char nome[50], float preco); //sobrecarga do construtor onde um produto pode ser criado apenas com preço e nome
	~Produto();

	//getters
	string getNome();
	string getCategoria();
	float getPreco();
	int getQntdEstoque();

	//setters
	void setNome(char nome[50]);
	void setCategoria(string categoria);
	void setPreco(float preco);
	void setQntdEstoque(int qntdEstoque);

	friend class cliente;
	friend class estoque;
};

#endif