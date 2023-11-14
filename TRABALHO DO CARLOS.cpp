#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Pessoa {
    string cpf, nome, data_nasc, endereco, sexo, telefone, email;
};

struct Associado {
    int codigo;
    string cpf, data_associacao, tipo_socio;
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

vector<Pessoa> pessoas;
vector<Associado> associados;
vector<Dependente> dependentes;
vector<Visitante> visitantes;

int proximoCodigoAssociado = 1;
int proximoCodigoDependente = 1;
int proximoCodigoVisitante = 1;

void cadastrarAssociado();
void cadastrarDependente();
void cadastrarVisitante();
void avisoMaioridade();
void registrarVisita();
void relatorioDependentesAssociados();
void relatorioVisitasPorAssociado();
void salvarDadosEmArquivo();
void carregarDadosDoArquivo();

int main() {
    carregarDadosDoArquivo();

    char escolha;
    do {
        cout << "\n------ Menu ------\n";
        cout << "1. Cadastrar associado\n";
        cout << "2. Cadastrar dependente\n";
        cout << "3. Cadastrar visitante\n";
        cout << "4. Aviso autom�tico de maioridade\n";
        cout << "5. Registro de visita\n";
        cout << "6. Relat�rio de dependentes/associados\n";
        cout << "7. Relat�rio de visitas por associado\n";
        cout << "8. Encerrar programa\n";
        cout << "Escolha uma op��o (1-8): ";
        cin >> escolha;

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
                salvarDadosEmArquivo();
                cout << "Programa encerrado.\n";
                break;
            default:
                cout << "Op��o inv�lida. Tente novamente.\n";
        }
    } while (escolha != '8');

    return 0;
}

void cadastrarAssociado() {
    // Implemente a l�gica de cadastro de associado
}

void cadastrarDependente() {
    // Implemente a l�gica de cadastro de dependente
}

void cadastrarVisitante() {
    // Implemente a l�gica de cadastro de visitante
}

void avisoMaioridade() {
    // Implemente a l�gica de aviso de maioridade
}

void registrarVisita() {
    // Implemente a l�gica de registro de visita
}

void relatorioDependentesAssociados() {
    // Implemente a l�gica de relat�rio de dependentes/associados
}

void relatorioVisitasPorAssociado() {
    // Implemente a l�gica de relat�rio de visitas por associado
}

void salvarDadosEmArquivo() {
    // Implemente a l�gica para salvar os dados em um arquivo
}

void carregarDadosDoArquivo() {
    // Implemente a l�gica para carregar os dados de um arquivo
}