#include "EstoqueTenis.hpp"

EstoqueTenis::EstoqueTenis() {
	// Sem necessidade de implementação.

}

EstoqueTenis::~EstoqueTenis() {
	// Sem necessidade de implementação.
}

void EstoqueTenis::registraProduto(int qntd, char nome[50], float preco){
	ofstream registraCamiseta;
	registraCamiseta.open("doc/estoqueTenis.txt", ios::app);

	string categoria = "calçados";

	Produto calcado(nome, categoria, preco, qntd);

	for(int i = 0; i < 50; i++){
		if(nome[i] == ' '){
			nome[i] = '_';
		}
	}

	registraCamiseta << qntd;
	registraCamiseta << " ";
	registraCamiseta << nome;
	registraCamiseta << " ";
	registraCamiseta << preco;
	registraCamiseta << "\n";

}