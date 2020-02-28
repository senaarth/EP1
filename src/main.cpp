#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "Cliente.hpp"
#include "Produto.hpp"
#include "Estoque.hpp"
#include "EstoqueCamisetas.hpp"
#include "EstoqueTenis.hpp"

using namespace std;

int procura();
void cadastro(string nome, string email);
void modoVenda();
void modoEstoque();
void modoRecomenda();
void menu();

int main() {
	menu(); //chamada do menu
	remove("doc/carrinho.txt");
	return 0;
}

int procura() {

	//Fun��o respons�vel por verificar se o cliente consta no arquivo txt.
	//Retorna 0 se n�o encontrar e 1 se encontrar.
	int retorno = 0;

	string busca, linha;

	cout << "Nome do cliente: ";
	getchar();
	getline(cin, busca);

	ifstream procura;

	procura.open("doc/cadastroClientes.txt", ios::app);

	while (!procura.eof()) {
		getline(procura, linha);
		if (busca == linha) {
			retorno = 1;
		}
	}

	return retorno;
}

void cadastro(string nome, string email) {

	//Fun��o Respons�vel por armazenar dados dos clientes no arquivo txt.
	Cliente cliente(nome);
	cliente.cadastraCliente(nome, email);
}

void modoVenda() {
	//Iniciando modo venda.
	string nome;
	cout << "\nIniciar venda no nome de: ";
	getline(cin, nome);
	Cliente cliente(nome);
	cliente.realizaCompra(nome); //Chamando m�todo da classe cliente respons�vel pela realiza��o da compra.
}

void modoEstoque() {

	Estoque estoque;

	int opcao;

	//Menu modo estoque
	cout << "\nIniciando Modo Estoque . . . . . . . .  " << endl;
	cout << "\n|Acessando estoque, o que deseja realizar?|" << endl;
	cout << "|[1]Inserir Produto                       |" << endl;
	cout << "|[2]Visualizar Estoque                    |" << endl;
	cout << "|[0]Encerrar                              |" << endl;
	cout << "Opcao: ";
	cin >> opcao;

	if (opcao == 1) {

		char nome[50];
		int qntd;
		float preco;

		cout << "Nome: ";
		getchar();
		cin.get(nome, 50);
		cout << "Qntd. Estoque: ";
		cin >> qntd;
		cout << "Pre�o: ";
		cin >> preco;

		estoque.registraProduto(qntd, nome, preco); //Chamando m�todo da classe estoque para inserir produtos no arquivo txt.

	} else if (opcao == 2) {
		estoque.visualizaCategoria(); //Chamando m�todo da classe estoque para visualizar produtos disponiveis.
	} else if (opcao == 0) {
		cout << "Ok Voltando ao Menu Principal" << endl;
	}

}

void modoRecomenda() {
	cout << "\nIniciando Modo Recomenda��o . . . . .\n" << endl;
}

void menu() {

	//In�cio do Programa
	int mantem = 1; //Vari�vel respons�vel por manter o menu rodando.

	vector<Cliente> clientes_lista;
	vector<Produto> produtos_lista;

	do {

		int opcao; //Vari�vel que navega pelo switch menu.
		cout << "\nGerenciamento Com�rcio da Victoria" << endl;
		cout << "[1] Modo Venda" << endl;
		cout << "[2] Modo Estoque" << endl;
		cout << "[3] Modo Recomenda��o" << endl;
		cout << "[0] Encerrar" << endl;
		cout << "Op��o: ";
		cin >> opcao;
		system("clear");

		switch (opcao) {

		//Modo Venda ----------------------------------------------------------------------------------------------------
		case 1:

			char resposta;
			cout << "\nCliente j� cadastrado? [S/N]" << endl;
			cin >> resposta;

			//Verificando se o cadastro do cliente consta no arquivo.
			if (resposta == 's' or resposta == 'S') {

				int busca = procura();
				if (busca == 1) {
					cout << "Cliente Encontrado! Iniciando Modo Venda!" << endl;
					modoVenda(); //In�cio do modo venda, j� queo cliente j� est� cadastrado.
					system("clear");
				} else {
					//Cliente n�o encontrado, voltando ao menu.
					cout << "Cliente n�o encontrado, favor tentar novamente!" << endl;
					cout << "Lembre-se que as maisculas diferenciam de minusculas" << endl;
				}

			} else if (resposta == 'n' or 'N') {

				//Clientes n�o cadastrados n�o podem comprar, por isso iniciando cadastro de um novo cliente.
				cout << "OK! Iniciando Cadastro de Novo Cliente" << endl;

				string nome, email;

				cout << "Nome: ";
				getchar();
				getline(cin, nome);
				cout << "Email: ";
				getline(cin, email);

				Cliente cliente(nome, email);
				clientes_lista.push_back(cliente);

				cadastro(nome, email); //Chama fun��o de cadastro.

				cliente.realizaCompra(cliente.getNome()); //Chama modo venda dentro do m�todo da classe cliente.

			}

			break;

			//Modo Estoque ----------------------------------------------------------------------------------------------------
		case 2:
			modoEstoque(); //Chamando fun��o de modo estoque
			system("clear");
			break;

			//Modo Recomenda��o -----------------------------------------------------------------------------------------------
		case 3:

			cout << "\nCliente j� cadastrado? [S/N]" << endl;
			cin >> resposta;
			if (resposta == 's' or resposta == 'S') {

				//Verificando se o cliente est� no arquivo.
				int verifica = procura();

				if (verifica == 1) {
					//Inicia recomenda��o, cliente j� cadastrado.
					cout << "Cliente Encontrado!" << endl;
					modoRecomenda();
				} else {
					//Mensagem de Erro, clientes n�o cadastrados n�o tem como receber recomenda��o.
					cout << "Cliente n�o Encontrado!" << endl;
					cout << "Favor cadastrar o cliente no modo venda antes de entrar no modo recomenda��o.\n" << endl;
				}

			} else if (resposta == 'n' or 'N') {
				//Mensagem de Erro, clientes n�o cadastrados n�o tem como receber recomenda��o.
				cout << "\nFavor cadastrar o cliente no modo venda antes de entrar no modo recomenda��o.\n" << endl;
			}

			system("clear");
			break;

			//Encerramento ----------------------------------------------------------------------------------------------------
		case 0:
			cout << "Ok, encerrando . . . . . . . . . . . ." << endl;
			mantem = 0;
			break;
		}

	} while (mantem);
}
