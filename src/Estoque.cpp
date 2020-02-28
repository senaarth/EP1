#include "Estoque.hpp"
#include "EstoqueCamisetas.hpp"
#include "EstoqueTenis.hpp"

Estoque::Estoque() {
	//Sem Necessidade de implementação
}

Estoque::~Estoque() {
	//Sem Necessidade de implementação
}

void Estoque::registraProduto(int qntd, char nome[50], float preco){

	int opcao;
	cout << "\nRegistrar em que categoria?" << endl;
	cout << "[1]Camisetas        [2]Tenis" << endl;
	cout << "Opção: ";
	cin >> opcao;

	if(opcao == 1) {
		EstoqueCamisetas estoque;
		estoque.registraProduto(qntd, nome, preco);
	}else if(opcao == 2){
		EstoqueTenis estoque;
		estoque.registraProduto(qntd, nome, preco);
	}else{
		cout << "\nOpção Inválida!\n" << endl;
	}
}

void Estoque::visualizaCategoria() {

	int opcao;
	string linha;

	system("clear");

	cout << "|                Categorias               |" << endl;
	cout << "|[1]Camisetas                             |" << endl;
	cout << "|[2]Calçados                              |" << endl;
	cout << "|[0]Encerrar                              |" << endl;
	cout << "Opcao: ";
	cin >> opcao;

	if (opcao == 1) {
		cout << "Qntd. / Nome do Produto / Preço" << endl;
		ifstream visualiza;
		visualiza.open("doc/estoqueCamisetas.txt");
		while (!visualiza.eof()) {
			getline(visualiza, linha);
			cout << linha << endl;
		}
	} else if (opcao == 2) {
		cout << "Qntd. / Nome do Produto / Preço" << endl;
		ifstream visualiza;
		visualiza.open("doc/estoqueTenis.txt");
		while (!visualiza.eof()) {
			getline(visualiza, linha);
			cout << linha << endl;
		}

	} else if (opcao == 0) {
		cout << "Ok, voltando ao menu anterior." << endl;
	} else {
		cout << "Opção Inválida!\n" << endl;
	}

	cout << "\nAperte qualquer tecla e enter para continuar." << endl;
	cin.ignore();
	getchar();

}