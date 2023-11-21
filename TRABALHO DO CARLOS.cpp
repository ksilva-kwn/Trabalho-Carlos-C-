#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <locale.h>

using namespace std;

struct Associado {
    int codigo, qntdDependentes;
    string nome, cpf, dia_associacao,mes_associacao,ano_associacao, tipo_socio, data_nasc;
    float mensalidade;
    vector<int> dependentes;
};

struct Dependente {
    int codigo, codExterno;
    string cpf_associado, nome, data_nasc, sexo;
};

struct Visitante {
    int codigo, cpf, codigo_associado;
    string nome, data_nasc, sexo, data_visita_inicial, data_visita_final;
};

Associado cadastrarAssociadoStruct;
Dependente cadastrarDependenteStruct;
Visitante cadastrarVisitanteStruct;

int contadorDeLinhas(const string& nomeArquivo);
void cadastrarAssociado();
void cadastrarDependente();
void cadastrarVisitante();
void avisoMaioridade();
void registrarVisita();
void relatorioDependentesAssociados();
void relatorioVisitasPorAssociado();
void salvarDadosAssociadosEmArquivo();
void salvarDadosDependentesEmArquivo();
void salvarDadosVisitantesEmArquivo();
void carregarDadosDoArquivo();


vector<Associado>associados;
vector<Dependente>dependentes;
vector<Visitante>visitantes;

int main() {
	setlocale(LC_ALL,"portuguese");
	
    carregarDadosDoArquivo();

    char escolha;
    do {
        cout << "\n------ Menu ------\n";
        cout << "1. Cadastrar associado\n";
        cout << "2. Cadastrar dependente\n";
        cout << "3. Cadastrar visitante\n";
        cout << "4. Aviso automático de maioridade\n";
        cout << "5. Registro de visita\n";
        cout << "6. Relatório de dependentes/associados\n";
        cout << "7. Relatório de visitas por associado\n";
        cout << "8. Alterar Dados\n";
        cout << "9. Encerrar o Programa\n";
        cout << "Escolha uma opção (1-9): ";
        cin >> escolha;
        cout << endl;

        switch (escolha) {
            case '1':
                cadastrarAssociado();
                break;
            case '2':
                cadastrarDependente();
                break;
            case '3':
                cadastrarVisitante();
                break;
            case '4':
                avisoMaioridade();
                break;
            case '5':
                registrarVisita();
                break;
            case '6':
                relatorioDependentesAssociados();
                break;
            case '7':
                relatorioVisitasPorAssociado();
                break;
            case '8':
                
                break;
            case '9':
            	cout << "Programa encerrado.\n";
            	break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != '9');

    return 0;
}

int contadorDeLinhas(const char* nomeArquivo) {
    FILE *arquivo;
    int contador = 0;
    char linha[100000];

    // Abre o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return -1; // Retorna -1 para indicar um erro
    }

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contador++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    return contador;
}

void cadastrarAssociado() {
  	
	const char* nomeArquivo = "dadosAssociados.txt";
  	int linhas = contadorDeLinhas(nomeArquivo);
  	
  	cout << "Digite o nome do associado (Utilize ' _ 'como espaço): ";
  	cin >> cadastrarAssociadoStruct.nome;
  	
  	cout << "Digite o CPF: ";
	cin >> cadastrarAssociadoStruct.cpf;
	
	cout << endl;
	
	cout << "Insire a data de Associação: ";
	cout << endl;
	
	cout << "Dia: ";
	cin >> cadastrarAssociadoStruct.dia_associacao;
	
	cout << "Mes: ";
	cin >> cadastrarAssociadoStruct.mes_associacao;
	
	cout << "Ano: ";
	cin >> cadastrarAssociadoStruct.ano_associacao;
	
	cout << endl;
	
	cout << "Insira o tipo de sócio (Proprietário ou Contribuinte): ";
	cin >> cadastrarAssociadoStruct.tipo_socio;
	
	cout << endl;

  	cadastrarAssociadoStruct.codigo = linhas + 1;
  	cout << "O codigo do Associado é: " << cadastrarAssociadoStruct.codigo;
  	
  	associados.push_back(cadastrarAssociadoStruct);
	salvarDadosAssociadosEmArquivo();
	
	cout << endl;
	cout << endl;
	
	cout << "Digite quantos dependentes você quer cadastrar: ";
	cin >> cadastrarAssociadoStruct.qntdDependentes;
	cout << endl;
	
	for(int i=0; i < cadastrarAssociadoStruct.qntdDependentes; i++){
		cadastrarDependente();
	}
}

void cadastrarDependente() {
	
	const char* nomeArquivo = "dadosDependentes.txt";
  	int linhas = contadorDeLinhas(nomeArquivo);
    
    cout << "Insira o nome(Utilize ' _ ' como espaço): ";
    cin >> cadastrarDependenteStruct.nome;
    
    cout << endl;
    
    cout << "Insira a data de nascimento (Utilize / ou - e 0): ";
    cin >> cadastrarDependenteStruct.data_nasc;
    
    cout << endl;
    
    cout << "Insira o sexo (Masculino  ou Feminino): ";
    cin >> cadastrarDependenteStruct.sexo;
    
    cout << endl;
    
    cadastrarDependenteStruct.codigo = linhas + 1;
    cout << "O codigo do Dependente é: " << cadastrarDependenteStruct.codigo;
    
    dependentes.push_back(cadastrarDependenteStruct);
	salvarDadosDependentesEmArquivo();
}

void cadastrarVisitante() {
	
	const char* nomeArquivo = "dadosVisitantes.txt";
  	int linhas = contadorDeLinhas(nomeArquivo);
  	
	cout << "Insira o nome do Visitante(Utilize ' _ ' como espaço): ";
	cin >> cadastrarVisitanteStruct.nome;
	
	cout << endl;
	
	cout << "Insira a data de nascimento (Utilize / ou - e 0): ";
	cin >> cadastrarVisitanteStruct.data_nasc;
	
	cout << endl;
	
	cout << "Insira o sexo (Masculino  ou Feminino): ";
	cin >> cadastrarVisitanteStruct.sexo;
	
	cout << endl;
	
	cout << "Insira a data de visita inicial ( Utilize - ou / ): ";
	cin >> cadastrarVisitanteStruct.data_visita_inicial;
	
	cout << endl;
	
	cout << "Insira a data de visita final ( Utilize - ou / ): ";
	cin >> cadastrarVisitanteStruct.data_visita_final;
	
	cout << endl;
	
	cadastrarVisitanteStruct.codigo = linhas+1;
	cout << "O código do visitante é: " << cadastrarVisitanteStruct.codigo;
	
	
	visitantes.push_back(cadastrarVisitanteStruct);
	salvarDadosVisitantesEmArquivo();
}

void avisoMaioridade() {
    
}

void registrarVisita() {
    
}

void relatorioDependentesAssociados() {
    
}

void relatorioVisitasPorAssociado() {
    
}


void salvarDadosAssociadosEmArquivo(){
	ofstream arquivo("dadosAssociados.txt");
    if (arquivo.is_open()) {
        for (size_t i = 0; i < associados.size(); ++i) {
            const Associado& associado = associados[i];
            arquivo <<"codigo:"<< associado.codigo << " " <<"tipo:"<< associado.tipo_socio << " " <<"cpf:" << associado.cpf << " " <<"diaA:"<< associado.dia_associacao << " " <<"mesA:" <<associado.mes_associacao << " " <<"anoA:"<< associado.ano_associacao << " "<<"mensalidade:"<< associado.mensalidade << " " << "nome:"<<associado.nome << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo de associados." << endl;
    }
}

void salvarDadosDependentesEmArquivo(){
	ofstream arquivo("dadosDependentes.txt");
    if (arquivo.is_open()) {
        for (size_t i = 0; i < dependentes.size(); ++i) {
            const Dependente& dependente = dependentes[i];
            arquivo <<"codigo:"<< dependente.codigo << " " << dependente.codExterno << " " << dependente.cpf_associado << " " << dependente.nome << " " << dependente.data_nasc << " " << dependente.sexo << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo de dependentes." << endl;
    }
}

void salvarDadosVisitantesEmArquivo(){
	ofstream arquivo("dadosVisitantes.txt");
    if (arquivo.is_open()) {
        for (size_t i = 0; i < visitantes.size(); ++i) {
            const Visitante& visitante = visitantes[i];
            arquivo << visitante.codigo << " " << visitante.cpf << " " << visitante.codigo_associado << " " << visitante.nome << " " << visitante.data_nasc << " " << visitante.sexo << " "
                    << visitante.data_visita_inicial << " " << visitante.data_visita_final << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo de visitantes." << endl;
    }
}

void carregarDadosDoArquivo() {
    fstream arquivoA,arquivoD,arquivoV;
    arquivoA.open("dadosAssociados.txt", fstream::in|fstream::out|fstream::app);
    arquivoD.open("dadosDependentes.txt", fstream::in|fstream::out|fstream::app);
    arquivoV.open("dadosVisitante.txt", fstream::in|fstream::out|fstream::app);
}
