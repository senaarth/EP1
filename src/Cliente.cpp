#include "Cliente.hpp"
#include "Socio.hpp"

//Construtores
Cliente::Cliente() {
	setNome("NOME N�O PREENCHIDO");
	setNome("EMAIL N�O PREENCHIDO");
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

//Outros M�todos
void Cliente::cadastraCliente(string nome, string email) {

	ofstream insereCliente;

	insereCliente.open("doc/cadastroClientes.txt", ios::app);

	insereCliente << nome << endl;
	insereCliente << email << endl;

	insereCliente.close();

	char resposta;
	Pergunta: cout << "\nCadastrar cliente como S�cio?[S/N]\n";
	cout << "S�cios recebem 15% de desconto.\n";
	cin >> resposta;

	if (resposta == 's' or resposta == 'S') {
		Socio socio(nome, email);
		socio.cadastraCliente(nome, email);
	} else if (resposta == 'n' or resposta == 'N') {
		cout << "Ok, seguindo para o modo venda." << endl;
	} else {
		cout << "\nResposta inv�lida, Tente novamente.\n" << endl;
		goto Pergunta;
	}
}

void Cliente::realizaCompra(string nome) {

	cout << "\nIniciando Modo Venda . . . . . . . . . \n" << endl;
	//Armazenamento do nome do cliente para mais tarde inserir no txt
	//de compras j� feitas para leva-lo ao modo recomenda��o.
	cout << "Compra no nome de " << nome << endl << endl;

	MenuCompra: cout << "-------Abrindo Estoque-------" << endl << endl;
	cout << "CATEGORIA CAMISETAS: " << endl;

	cout << "Qntd. / Nome do Produto / Pre�o" << endl;

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

	cout << "CATEGORIA CAL�ADOS: " << endl;

	cout << "Qntd. / Nome do Produto / Pre�o" << endl;

	visualiza.open("doc/estoqueTenis.txt"); //Aqui abre a leitura do estoque de cal�ados.

	while (!visualiza.eof()) {
		getline(visualiza, linha);
		cout << linha << endl;
	}

	visualiza.close();

	int opcao;
	//Menu de Compra
	cout << "Comprar em que categoria?" << endl;
	cout << "[1] Camisetas" << endl;
	cout << "[2] Cal�ados" << endl;
	cout << "[0] Voltar ao Menu Principal" << endl;
	cout << "Opcao: ";
	cin >> opcao;

	if (opcao == 1) {

		cout << "Inserir qual produto no carrinho?" << endl;
		getchar();
		cin.get(produto, 50);

		//Repeti��o que troca espa�os por underlines para facilitar na leitura do txt.
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
				buscaProduto = 1; //Vari�vel de retorno, retorna 1 se o produto for encontrado.
				linhaProduto = i; //Vari�vel que armazena em qual linha o produto est� para atualiza��o do estoque.
				break;
			}
		}

		int preco = quantia * precoLido;

		fclose(checagem);

		if (qntdLida < quantia) {
			//Verificando se o cliente n�o inseriu uma quantia maior do que a disponivel no estoque.
			cout << "N�mero de pe�as insuficientes no estoque! Favor reinserir."
					<< endl;
			goto Quantia;
		} else {
			if (buscaProduto == 1) {
				cout << "\nProduto Encontrado! Inserindo " << quantia << " "
						<< produto << "(s)" << " no carrinho." << endl << endl;

				ofstream carrinho;
				carrinho.open("doc/carrinho.txt", ios::app); //Var�avel de inser��o para colocar os produtos no txt do carrinho

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
						<< "\nProduto N�o Encontrado!\nLembre-se, mai�sculas diferenciam de min�sculas.";
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

		//Repeti��o que troca espa�os por underlines para facilitar na leitura do txt
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
				buscaProduto = 1; //V�riavel de retorno, retorna 1 se o produto for encontrado.
				linhaProduto = i; //Vari�vel que armazena em qual linha o produto est� para atualiza��o do estoque.
				break;
			}
		}

		if (qntdLida < quantia) {
			//Verificando se o cliente n�o inseriu uma quantia maior do que a disponivel no estoque.
			cout << "N�mero de pe�as insuficientes no estoque! Favor reinserir."
					<< endl;
			goto QuantiaTenis;
		} else {
			if (buscaProduto == 1) {
				cout << "\nProduto Encontrado! Inserindo " << quantia << " "
						<< produto << "(s)" << " no carrinho." << endl << endl;

				ofstream carrinho; //Var�avel de inser��o para colocar os produtos no txt do carrinho
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
						<< "\nProduto N�o Encontrado!\nLembre-se, mai�sculas diferenciam de min�sculas.";
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

		ifstream leCarrinho; // Vari�vel de leitura para print do carrinho na tela.
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
			cout << "\nOk seguindo para finaliza��o.\n" << endl;
		} else if (resposta == 'n' or resposta == 'N') {
			cout << "\nOk, voltando para menu de compra.\n" << endl;
			goto MenuCompra;
		} else {
			cout << "\nResposta Inv�lida, tente novamente.\n" << endl;
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
		//Mostr Pre�o total da compra e oferece desconto de 15% para s�cios.
		cout << "PRE�O TOTAL: " << total << endl;
		cout << "PRE�O PARA S�CIOS: " << (total - (total * 0.15)) << endl;
		Pergunta2: cout << "Cliente atual j� � s�cio?[S/N]" << endl;
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
				cout << "S�cio encontrado, finalizando. " << endl;
				cout << "Compra no nome de " << nome << ", total: R$"
						<< (total - (total * 0.15)) << " finalizada." << endl;
			} else {
				cout << "S�cio n�o encontrado, finalizando compra sem desconto."
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
				cout << "Ok, iniciando associa��o. " << endl;
				cout << "Email: ";
				getchar();
				getline(cin, email);
				Socio novo_socio(nome, email);
				novo_socio.cadastraCliente(nome, email);

				cout << "Associado, finalizando compra com desconto." << endl;
				cout << "Compra no nome de " << nome << ", total: R$"
						<< (total - (total * 0.15)) << " finalizada." << endl;

			} else {
				cout << "\nResposta Inv�lida, tente novamente." << endl;
				goto Pergunta3;
			}

		} else {
			cout << "\nResposta Inv�lida, tente novamente." << endl;
			goto Pergunta2;
		}
	}

	cout << "\nAperte qualquer tecla e enter para continuar." << endl;
	cin.ignore();
	getchar();

}