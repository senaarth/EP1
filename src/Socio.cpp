#include "Socio.hpp"

Socio::Socio(string nome, string email) {
	//  Sem necessidade de implementação.

}

Socio::~Socio() {
	// Sem necessidade de implementação.
}

void Socio::cadastraCliente(string nome, string email){

	ofstream insereSocio;

	insereSocio.open("doc/cadastroSocios.txt", ios::app);

	insereSocio << nome << endl;
	insereSocio << email << endl;

	insereSocio.close();
}
