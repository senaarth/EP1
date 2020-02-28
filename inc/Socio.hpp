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

	//Outros M�todos
	void  cadastraCliente(string nome, string email); //Exemplo polimorfismo, checar implementea��o em Socio.cpp.

	friend class Cliente;
};

#endif
