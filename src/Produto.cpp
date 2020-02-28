#include "Produto.hpp"
using namespace std;

Produto::Produto(char nome[50], string categoria, float preco, int qntdEstoque){
	setNome(nome);
	setPreco(preco);
	setCategoria(categoria);
	setPreco(preco);
	setQntdEstoque(qntdEstoque);
	cout << "\n" << getQntdEstoque() << " " << getNome() << " registrado(s) no estoque de " << getCategoria() << ".\n" << endl;
}

Produto::~Produto() {
	//Sem necessidade de implementação
}

//Getters

string Produto::getNome(){
	return this->nome;
}
string Produto::getCategoria(){
	return this->categoria;
}
float Produto::getPreco(){
	return this->preco;
}
int Produto::getQntdEstoque(){
	return this->qntdEstoque;
}

//Setters

void Produto::setNome(char nome[50]){
	this->nome = nome;
}
void Produto::setPreco(float preco){
	this->preco = preco;
}
void Produto::setCategoria(string categoria){
	this->categoria = categoria;
}
void Produto::setQntdEstoque(int qntdEstoque){
	this->qntdEstoque = qntdEstoque;
}