#include "Cliente.hpp"
#include "Socio.hpp"

//Construtores
Cliente::Cliente() {
	setNome("NOME NÃO PREENCHIDO");
	setNome("EMAIL NÃO PREENCHIDO");
}

Cliente::Cliente(string nome, string email) {
	setNome(nome);
	setEmail(email);
}

Cliente::Cliente(string nome) {
	setNome(nome);
	setEmail("");
}

//Destrutor
Cliente::~Cliente() {
	cout << "";
}

//Getters
string Cliente::getNome() {
	return this->nome;
}
string Cliente::getEmail() {
	return this->email;
}

//Setters
void Cliente::setNome(string nome) {
	this->nome = nome;
}
void Cliente::setEmail(string email) {
	this->email = email;
}

//Outros Métodos
void Cliente::cadastraCliente(string nome, string email) {

	ofstream insereCliente;

	insereCliente.open("doc/cadastroClientes.txt", ios::app);

	insereCliente << nome << endl;
	insereCliente << email << endl;

	insereCliente.close();

	char resposta;
	Pergunta: cout << "\nCadastrar cliente como Sócio?[S/N]\n";
	cout << "Sócios recebem 15% de desconto.\n";
	cin >> resposta;

	if (resposta == 's' or resposta == 'S') {
		Socio socio(nome, email);
		socio.cadastraCliente(nome, email);
	} else if (resposta == 'n' or resposta == 'N') {
		cout << "Ok, seguindo para o modo venda." << endl;
	} else {
		cout << "\nResposta inválida, Tente novamente.\n" << endl;
		goto Pergunta;
	}
}

void Cliente::realizaCompra(string nome) {

	cout << "\nIniciando Modo Venda . . . . . . . . . \n" << endl;
	//Armazenamento do nome do cliente para mais tarde inserir no txt
	//de compras já feitas para leva-lo ao modo recomendação.
	cout << "Compra no nome de " << nome << endl << endl;

	MenuCompra: cout << "-------Abrindo Estoque-------" << endl << endl;
	cout << "CATEGORIA CAMISETAS: " << endl;

	cout << "Qntd. / Nome do Produto / Preço" << endl;

	char produto[50];
	int quantia;
	int carrinho;

	ifstream visualiza; //Variavel para leitura de arquivo, no momento lendo o estoque de camisetas.
	string linha;

	visualiza.open("doc/estoqueCamisetas.txt");

	while (!visualiza.eof()) {
		getline(visualiza, linha);
		cout << linha << endl;
	}

	visualiza.close();

	cout << "CATEGORIA CALÇADOS: " << endl;

	cout << "Qntd. / Nome do Produto / Preço" << endl;

	visualiza.open("doc/estoqueTenis.txt"); //Aqui abre a leitura do estoque de calçados.

	while (!visualiza.eof()) {
		getline(visualiza, linha);
		cout << linha << endl;
	}

	visualiza.close();

	int opcao;
	//Menu de Compra
	cout << "Comprar em que categoria?" << endl;
	cout << "[1] Camisetas" << endl;
	cout << "[2] Calçados" << endl;
	cout << "[0] Voltar ao Menu Principal" << endl;
	cout << "Opcao: ";
	cin >> opcao;

	if (opcao == 1) {

		cout << "Inserir qual produto no carrinho?" << endl;
		getchar();
		cin.get(produto, 50);

		//Repetição que troca espaços por underlines para facilitar na leitura do txt.
		for (int i = 0; i < 50; i++) {
			if (produto[i] == ' ') {
				produto[i] = '_';
			}
		}

		Quantia: cout << "Quantas unidades?" << endl;
		cin >> quantia;

		//Checando se o produto consta no estoque.
		FILE *checagem;
		int i = 0, buscaProduto, linhaProduto;
		char nomeLido[50];
		int qntdLida;
		float precoLido;
		checagem = fopen("doc/estoqueCamisetas.txt", "r");

		while (!feof(checagem)) {
			fscanf(checagem, "%d %s %f\n", &qntdLida, nomeLido, &precoLido);
			i++;
			if (strcmp(nomeLido, produto) == 0) { //Comparando o nome do produto de cada linha com o solicitado pelo cliente.
				buscaProduto = 1; //Variável de retorno, retorna 1 se o produto for encontrado.
				linhaProduto = i; //Variável que armazena em qual linha o produto está para atualização do estoque.
				break;
			}
		}

		int preco = quantia * precoLido;

		fclose(checagem);

		if (qntdLida < quantia) {
			//Verificando se o cliente não inseriu uma quantia maior do que a disponivel no estoque.
			cout << "Número de peças insuficientes no estoque! Favor reinserir."
					<< endl;
			goto Quantia;
		} else {
			if (buscaProduto == 1) {
				cout << "\nProduto Encontrado! Inserindo " << quantia << " "
						<< produto << "(s)" << " no carrinho." << endl << endl;

				ofstream carrinho;
				carrinho.open("doc/carrinho.txt", ios::app); //Varíavel de inserção para colocar os produtos no txt do carrinho

				carrinho << quantia;
				carrinho << " ";
				carrinho << produto;
				carrinho << " ";
				carrinho << preco;
				carrinho << endl;

				carrinho.close();

				cout << "\nAperte qualquer tecla e enter para continuar." << endl;
				cin.ignore();
				getchar();

			} else {
				cout
						<< "\nProduto Não Encontrado!\nLembre-se, maiúsculas diferenciam de minúsculas.";
			}
		}

		string linha, linhaLixo;
		ifstream leEstoque;
		leEstoque.open("doc/estoqueCamisetas.txt");

		ofstream estoqueTemp;
		estoqueTemp.open("doc/estoqueTemp.txt");

		int j = 0;

		while (!leEstoque.eof()) {
			j++;
			if (j != linhaProduto) {
				getline(leEstoque, linha);
				estoqueTemp << linha << endl;
			} else {
				getline(leEstoque, linhaLixo);
			}
		}

		estoqueTemp << (qntdLida - quantia);
		estoqueTemp << " ";
		estoqueTemp << nomeLido;
		estoqueTemp << " ";
		estoqueTemp << precoLido << endl;

		fclose(checagem);

		string linhaNova;

		fstream atualiza;
		atualiza.open("doc/estoqueTemp.txt");

		fstream atualiza2;
		atualiza2.open("doc/estoqueCamisetas.txt");

		while (!atualiza.eof()) {
			getline(atualiza, linhaNova);
			if (linhaNova != "") {
				atualiza2 << linhaNova << endl;
			}
		}

		atualiza << " ";

		carrinho = 1;
	} else if (opcao == 2) {

		cout << "Inserir qual produto no carrinho?" << endl;
		getchar();
		cin.get(produto, 50);

		//Repetição que troca espaços por underlines para facilitar na leitura do txt
		for (int i = 0; i < 50; i++) {
			if (produto[i] == ' ') {
				produto[i] = '_';
			}
		}

		QuantiaTenis: cout << "Quantas unidades?" << endl;
		cin >> quantia;

		//Checando se o produto consta no estoque.
		FILE *checagem;
		int i = 0, buscaProduto, linhaProduto;
		char nomeLido[50];
		int qntdLida;
		float precoLido;
		checagem = fopen("doc/estoqueTenis.txt", "r");

		while (!feof(checagem)) {
			fscanf(checagem, "%d %s %f\n", &qntdLida, nomeLido, &precoLido);
			i++;
			if (strcmp(nomeLido, produto) == 0) { //Comparando o nome do produto de cada linha com o solicitado pelo cliente.
				buscaProduto = 1; //Váriavel de retorno, retorna 1 se o produto for encontrado.
				linhaProduto = i; //Variável que armazena em qual linha o produto está para atualização do estoque.
				break;
			}
		}

		if (qntdLida < quantia) {
			//Verificando se o cliente não inseriu uma quantia maior do que a disponivel no estoque.
			cout << "Número de peças insuficientes no estoque! Favor reinserir."
					<< endl;
			goto QuantiaTenis;
		} else {
			if (buscaProduto == 1) {
				cout << "\nProduto Encontrado! Inserindo " << quantia << " "
						<< produto << "(s)" << " no carrinho." << endl << endl;

				ofstream carrinho; //Varíavel de inserção para colocar os produtos no txt do carrinho
				carrinho.open("doc/carrinho.txt", ios::app);

				carrinho << quantia;
				carrinho << " ";
				carrinho << produto;
				carrinho << " ";
				carrinho << (quantia * precoLido);
				carrinho << endl;

				carrinho.close();

				cout << "\nAperte qualquer tecla e enter para continuar." << endl;
				cin.ignore();
				getchar();

			} else {
				cout
						<< "\nProduto Não Encontrado!\nLembre-se, maiúsculas diferenciam de minúsculas.";
			}
		}


		string linha, linhaLixo;
		ifstream leEstoque;
		leEstoque.open("doc/estoqueTenis.txt");

		ofstream estoqueTemp;
		estoqueTemp.open("doc/estoqueTemp.txt");

		int j = 0;

		while (!leEstoque.eof()) {
			j++;
			if (j != linhaProduto) {
				getline(leEstoque, linha);
				estoqueTemp << linha << endl;
			} else {
				getline(leEstoque, linhaLixo);
			}
		}

		estoqueTemp << (qntdLida - quantia);
		estoqueTemp << " ";
		estoqueTemp << nomeLido;
		estoqueTemp << " ";
		estoqueTemp << precoLido << endl;

		fclose(checagem);

		string linhaNova;

		fstream atualiza;
		atualiza.open("doc/estoqueTemp.txt");

		fstream atualiza2;
		atualiza2.open("doc/estoqueTenis.txt");

		while (!atualiza.eof()) {
			getline(atualiza, linhaNova);
			if (linhaNova != "") {
				atualiza2 << linhaNova << endl;
			}
		}

		atualiza << " ";

		carrinho = 1;

	} else if (opcao == 0) {
		carrinho = 0;
		cout << "Ok Voltando ao Menu Principal" << endl;
	}

	if (carrinho == 1) {

		ifstream leCarrinho; // Variável de leitura para print do carrinho na tela.
		leCarrinho.open("doc/carrinho.txt");

		string linhaCarrinho;

		system("clear");
		cout << "\n\n-----CARRINHO DE COMPRAS-----" << endl;

		while (!leCarrinho.eof()) {
			getline(leCarrinho, linha);
			cout << linha << endl; //Mostrando cada linha do carrinho na tela.
		}

		leCarrinho.close();

		char resposta;
		Pergunta: cout << "Finalizar compra?[S/N]" << endl;
		cin >> resposta;

		//Verificando se cliente deseja continuar a compra.
		if (resposta == 's' or resposta == 'S') {
			cout << "\nOk seguindo para finalização.\n" << endl;
		} else if (resposta == 'n' or resposta == 'N') {
			cout << "\nOk, voltando para menu de compra.\n" << endl;
			goto MenuCompra;
		} else {
			cout << "\nResposta Inválida, tente novamente.\n" << endl;
			goto Pergunta;
		}

		//Calculando o prelo total da compra
		FILE *precoFinal;

		precoFinal = fopen("doc/carrinho.txt", "r");

		int qntd;
		char produtos[50];
		float preco = 0, total = 0;

		while (!feof(precoFinal)) {
			total += preco;
			fscanf(precoFinal, "%d %s %f", &qntd, produtos, &preco);
		}

		char confirmaSocio;
		//Mostr Preço total da compra e oferece desconto de 15% para sócios.
		cout << "PREÇO TOTAL: " << total << endl;
		cout << "PREÇO PARA SÓCIOS: " << (total - (total * 0.15)) << endl;
		Pergunta2: cout << "Cliente atual já é sócio?[S/N]" << endl;
		cin >> confirmaSocio;

		if (confirmaSocio == 's' or confirmaSocio == 'S') {

			fstream associado;
			int busca = 0;
			string checaLinha;
			associado.open("doc/cadastroSocios.txt");

			while (!associado.eof()) {
				getline(associado, checaLinha);
				if (checaLinha == nome) {
					busca = 1;
					break;
				}
			}

			if (busca == 1) {
				cout << "Sócio encontrado, finalizando. " << endl;
				cout << "Compra no nome de " << nome << ", total: R$"
						<< (total - (total * 0.15)) << " finalizada." << endl;
			} else {
				cout << "Sócio não encontrado, finalizando compra sem desconto."
						<< endl;
				cout << "Compra no nome de " << nome << ", total: R$" << total
						<< " finalizada." << endl;
			}

		} else if (confirmaSocio == 'n' or confirmaSocio == 'N') {

			Pergunta3: cout << "Seguir sem desconto?[S/N]" << endl;
			cin >> resposta;

			if (resposta == 's' or resposta == 'S') {

				cout << "Finalizando compra sem desconto." << endl;
				cout << "Compra no nome de " << nome << ", total: R$" << total
						<< " finalizada." << endl;

			} else if (resposta == 'n' or resposta == 'N') {

				string email;
				cout << "Ok, iniciando associação. " << endl;
				cout << "Email: ";
				getchar();
				getline(cin, email);
				Socio novo_socio(nome, email);
				novo_socio.cadastraCliente(nome, email);

				cout << "Associado, finalizando compra com desconto." << endl;
				cout << "Compra no nome de " << nome << ", total: R$"
						<< (total - (total * 0.15)) << " finalizada." << endl;

			} else {
				cout << "\nResposta Inválida, tente novamente." << endl;
				goto Pergunta3;
			}

		} else {
			cout << "\nResposta Inválida, tente novamente." << endl;
			goto Pergunta2;
		}
	}

	cout << "\nAperte qualquer tecla e enter para continuar." << endl;
	cin.ignore();
	getchar();

}