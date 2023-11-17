#include <iostream>
#include <fstream>
#include <vector>
#include <locale.h>

using namespace std;

struct Associado {
    int codigo;
    string tipo_socio, cpf, nome, dia_associacao, mes_associacao, ano_associacao,;
    float mensalidade;
    vector<int> dependentes;
};

struct Dependente {
    int codigo, codExterno;
    string cpf_associado, nome, data_nasc, sexo;
};

struct Visitante {
    int codigo, codigo_associado;
    string nome, cpf, data_nasc, sexo, telefone, email, endereco, data_visita_inicial, data_visita_final;
};


vector<Associado> associados;
vector<Dependente> dependentes;
vector<Visitante> visitantes;

Associado cadastroassociado;
Dependente cadastrodependente;
Visitante cadastrovisitante;

void carregarDadosDoArquivo();
void salvarDadosDependentesEmArquivo();
void salvarDadosAssociadosEmArquivo();

void cadastrarAssociado() {
	
	// 1- Cadastrar Associado. O getline é usado para aceitar espaço entre as palavras.
	cout << endl;
	cin.ignore();
	
	cout << "Digite o CPF: ";
	getline(cin, cadastroassociado.cpf);
	
	cout << endl;
	
	cout << "Insire a data de Associação: ";
	cout << endl;
	cout << "Dia: ";
	getline(cin, cadastroassociado.dia_associacao);
	cout << endl;
	cout << "Mes: ";
	getline(cin, cadastroassociado.mes_associacao);
	cout << endl;
	cout << "Ano: ";
	getline(cin, cadastroassociado.ano_associacao);
	
	cout << endl;
	
	cout << "Insira o tipo de sócio (Proprietário ou Contribuinte): ";
	getline(cin,  cadastroassociado.tipo_socio);
	
	cout << endl;
	
	cadastroassociado.codigo = cadastroassociado.codigo + 1;
	cout << "O codigo do Associado é: " << cadastroassociado.codigo;
	
	cout << endl;
	
	associados.push_back(cadastroassociado);
	salvarDadosAssociadosEmArquivo();
}

void cadastrarDependente() {
    // 2- Cadastrar dependentes
    cin.ignore();
    cout << endl;
    
    cout << "Insira o nome: ";
    getline(cin, cadastrodependente.nome);
    
    cout << endl;
    
    cout << "Insira a data de nascimento: ";
    getline(cin, cadastrodependente.data_nasc);
    
    cout << endl;
    
    cout << "Insira o sexo (M  ou F): ";
    getline(cin, cadastrodependente.sexo);
    
    cout << endl;
    
    cadastrodependente.codigo = cadastrodependente.codigo + 1;
    cout << "O codigo do Dependente é: " << cadastrodependente.codigo;
    
    dependentes.push_back(cadastrodependente);
    
    salvarDadosDependentesEmArquivo();
}

// 3- Cadastrar visitante.
void cadastrarVisitante() {
    
    cout << endl;
    cout << "Digite seu nome: ";
	cin.ignore();
    getline(cin, cadastrovisitante.nome);
    
    cout << endl;
    
    cout << "Digite seu CPF: ";
    getline(cin, cadastrovisitante.cpf);
    
    cout << endl;
    
    cout << "Digite sua data de nascimento: ";
    getline(cin, cadastrovisitante.data_nasc);
    
	cout << endl;
    
	cout << "Digite seu endereço: ";
	getline(cin, cadastrovisitante.endereco);
	
	cout << endl;
	
	cout << "Digite seu sexo (M ou F): ";
	getline(cin, cadastrovisitante.sexo);
	
	cout << endl;
	
	cout << "Digite seu telefone (com DDD): ";
	getline(cin, cadastrovisitante.telefone);
	
	cout << endl;
	
	cout << "Digite seu E-mail: ";
	getline(cin, cadastrovisitante.email);
	
	cout << endl;
	
	cout << "Insira a data de Visita Inicial: ";
	getline(cin, cadastrovisitante.data_visita_inicial);
	
	cout << endl;
	
	cout << "Insira a data de Visita Final: ";
	getline(cin, cadastrovisitante.data_visita_final);
	
	cout << endl;
	
	cadastrovisitante.codigo = cadastrovisitante.codigo + 1;
	cout << "O codigo do Visitante é: " << cadastrovisitante.codigo;
	
}

void avisoMaioridade() {
    // Implemente a lógica de aviso de maioridade
}

void registrarVisita() {
    // Implemente a lógica de registro de visita
}

void relatorioDependentesAssociados() {
    // Implemente a lógica de relatório de dependentes/associados
}

void relatorioVisitasPorAssociado() {
    // Implemente a lógica de relatório de visitas por associado
}

void salvarDadosAssociadosEmArquivo(){
	 ofstream arquivoA("dadosAssociados.txt", ios::app); // Abre o arquivo em modo de anexação
    if (arquivoA.is_open()) {
        for (size_t i = 0; i < associados.size(); ++i) {
            const Associado& associado = associados[i];
            arquivoA << associado.codigo << " " << associado.dia_associacao << " " << associado.mes_associacao << " " << associado.ano_associacao << " " << associado.tipo_socio << " " << associado.cpf << " " << associado.nome << " " << associado.mensalidade << "\n";
        }
        arquivoA.close();
    } else {
        cout << "Erro ao abrir o arquivo de associados." << endl;
    }
}

void salvarDadosDependentesEmArquivo(){
	ofstream arquivoD("dadosDependentes.txt", ios::app);
    if (arquivoD.is_open()) {
        for (size_t i = 0; i < dependentes.size(); ++i) {
            const Dependente& dependente = dependentes[i];
            arquivoD << dependente.codigo << " " << dependente.codExterno << " " << dependente.cpf_associado << " " << dependente.nome << " " << dependente.data_nasc << " " << dependente.sexo << "\n";
        }
        arquivoD.close();
    } else {
        cout << "Erro ao abrir o arquivo de dependentes." << endl;
    }
}

void salvarDadosVisitantesEmArquivo(){
	ofstream arquivoV("dadosVisitante.txt", ios::app);
    if (arquivoV.is_open()) {
        for (size_t i = 0; i < visitantes.size(); ++i) {
            const Visitante& visitante = visitantes[i];
            arquivoV << visitante.codigo << " " << visitante.codigo_associado << " " << visitante.nome << " " << visitante.cpf << " " << visitante.data_nasc << " " << visitante.sexo << " "
                     << visitante.telefone << " " << visitante.email << " " << visitante.endereco << " " << visitante.data_visita_inicial << " " << visitante.data_visita_final << "\n";
        }
        arquivoV.close();
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

int main() {
	setlocale(LC_ALL,"portuguese");
    carregarDadosDoArquivo();

    int escolha;
    do {
        cout << "\n------ Menu ------\n";
        cout << "1. Cadastrar associado\n";
        cout << "2. Cadastrar dependente\n";
        cout << "3. Cadastrar visitante\n";
        cout << "4. Aviso automático de maioridade\n";
        cout << "5. Registro de visita\n";
        cout << "6. Relatório de dependentes/associados\n";
        cout << "7. Relatório de visitas por associado\n";
        cout << "8. Encerrar programa\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                cadastrarAssociado();
                break;
            case 2:
                cadastrarDependente();
                break;
            case 3:
                cadastrarVisitante();
                break;
            case 4:
                avisoMaioridade();
                break;
            case 5:
                registrarVisita();
                break;
            case 6:
                relatorioDependentesAssociados();
                break;
            case 7:
                relatorioVisitasPorAssociado();
                break;
            case 8:
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 8);

    return 0;
}
