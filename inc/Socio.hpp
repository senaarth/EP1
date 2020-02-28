#ifndef SOCIO_HPP_
#define SOCIO_HPP_

#include "Cliente.hpp"
#include <string>

class Socio: public Cliente{
public:
	//Construtor
	Socio(string nome, string email);
	//Destrutor
	~Socio();

	//Outros Métodos
	void  cadastraCliente(string nome, string email); //Exemplo polimorfismo, checar implementeação em Socio.cpp.

	friend class Cliente;
};

#endif
