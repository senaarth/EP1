#include "Socio.hpp"

Socio::Socio(string nome, string email) {
	//  Sem necessidade de implementa��o.

}

Socio::~Socio() {
	// Sem necessidade de implementa��o.
}

void Socio::cadastraCliente(string nome, string email){

	ofstream insereSocio;

	insereSocio.open("doc/cadastroSocios.txt", ios::app);

	insereSocio << nome << endl;
	insereSocio << email << endl;

	insereSocio.close();
}
