#ifndef Cliente_hpp
#define Cliente_hpp

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdio.h>

#include "Estoque.hpp"
#include "EstoqueCamisetas.hpp"
#include "EstoqueTenis.hpp"
using namespace std;

class Cliente {
private:
	string nome;
	string email;
public:
	Cliente();
	Cliente(string nome, string email); //Sobrecarga do construtor, obrigando a criação do objeto COM parametros email e nome
	Cliente(string nome); //Mais uma sobrecarga, porem aceitando apenas nome do cliente como parametro
	~Cliente(); //Destrutor

	//Getters
	string getNome();
	string getEmail();

	//Setters
	void setNome(string nome);
	void setEmail(string email);

	//outros métodos
	void realizaCompra(string nome);
	void cadastraCliente(string nome, string email);

	friend class Estoque;
};
#endif