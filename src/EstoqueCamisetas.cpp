#include "EstoqueCamisetas.hpp"

using namespace std;

EstoqueCamisetas::EstoqueCamisetas() {
	// sem necessidade de implementação
}

EstoqueCamisetas::~EstoqueCamisetas() {
	// sem necessidade de implementação
}

void EstoqueCamisetas::registraProduto(int qntd, char nome[50], float preco){
	ofstream registraCamiseta;
	registraCamiseta.open("doc/estoqueCamisetas.txt", ios::app);

	string categoria = "camisetas";

	Produto camiseta(nome, categoria, preco, qntd);

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