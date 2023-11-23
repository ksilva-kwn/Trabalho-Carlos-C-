#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <locale.h>

using namespace std;

struct Associado{
	
    int codigo, qntdDependentes;
    string nome, cpf, dia_associacao, mes_associacao, ano_associacao, tipo_socio, data_nasc;
    float mensalidade;
    vector<int> dependentes;
};

struct Dependente{
	
    int codigo, codExterno;
    string cpf_associado, nome, data_nasc, sexo;
};

struct Visitante{
	
    int codigo, cpf, codigo_associado;
    string nome, data_nasc, sexo, data_visita_inicial, data_visita_final;
};

int contadorDeLinhas(const string &nomeArquivo);
void cadastrarAssociado();
void cadastrarDependente();
void cadastrarVisitante();
void avisoMaioridade();
void relatorioDependentesAssociados();
void relatorioVisitasPorAssociado();
void salvarDadosAssociadosEmArquivo();
void salvarDadosDependentesEmArquivo();
void salvarDadosVisitantesEmArquivo();
void carregarDadosDoArquivo();
void alterarDados();
int alterarDadosAssociados(const char *nomeArquivo);
int alterarDadosDependentes(const char *nomeArquivo);
int alterarDadosVisitantes(const char *nomeArquivo);

vector<Associado> associados;
vector<Dependente> dependentes;
vector<Visitante> visitantes;

Associado cadastrarAssociadoStruct;
Dependente cadastrarDependenteStruct;
Visitante cadastrarVisitanteStruct;

int main(){
	
    setlocale(LC_ALL, "portuguese");

    carregarDadosDoArquivo();

    char escolha;
    do
    {
        cout << "\n------ Menu ------\n";
        cout << "1. Cadastrar associado\n";
        cout << "2. Cadastrar dependente\n";
        cout << "3. Cadastrar visitante\n";
        cout << "4. Aviso automÃ¡tico de maioridade\n";
        cout << "5. RelatÃ³rio de dependentes/associados\n";
        cout << "6. RelatÃ³rio de visitas por associado\n";
        cout << "7. Alterar Dados\n";
        cout << "8. Encerrar o Programa\n";
        cout << "Escolha uma opÃ§Ã£o (1-8): ";
        cin >> escolha;
        cout << endl;

        switch (escolha)
        {
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
            relatorioDependentesAssociados();
            break;
        case '6':
            relatorioVisitasPorAssociado();
            break;
        case '7':
            alterarDados();
            break;
        case '8':
            cout << "Programa encerrado.\n";
            break;
        default:
            cout << "OpÃ§Ã£o invÃ¡lida. Tente novamente.\n";
            break;
        }
    } while (escolha != '8');

    return 0;
}

int contadorDeLinhas(const char *nomeArquivo){
	
    FILE *arquivo;
    int contador = 0;
    char linha[100000];

    // Abre o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return -1; // Retorna -1 para indicar um erro
    }

    // Lï¿½ cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        contador++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    return contador;
}

void cadastrarAssociado(){

	associados.clear();
	
    const char *nomeArquivo = "dadosAssociados.txt";
    int linhas = contadorDeLinhas(nomeArquivo);

    cout << "Digite o nome do associado (Utilize ' _ 'como espaï¿½o): ";
    cin >> cadastrarAssociadoStruct.nome;

    cout << "Digite o CPF: ";
    cin >> cadastrarAssociadoStruct.cpf;

    cout << endl;

    cout << "Insire a data de AssociaÃ§Ã£o: ";
    cout << endl;

    cout << "Dia: ";
    cin >> cadastrarAssociadoStruct.dia_associacao;

    cout << "Mes: ";
    cin >> cadastrarAssociadoStruct.mes_associacao;

    cout << "Ano: ";
    cin >> cadastrarAssociadoStruct.ano_associacao;

    cout << endl;

    cout << "Insira o tipo de sÃ³cio (ProprietÃ¡rio ou Contribuinte): ";
    cin >> cadastrarAssociadoStruct.tipo_socio;

    cout << endl;

    cadastrarAssociadoStruct.codigo = linhas + 1;
    cout << "O codigo do Associado Ã©: " << cadastrarAssociadoStruct.codigo;

    cout << endl;
    cout << endl;

    cout << "Digite quantos dependentes vocÃª quer cadastrar: ";
    cin >> cadastrarAssociadoStruct.qntdDependentes;
    cout << endl;

    cadastrarAssociadoStruct.mensalidade = 200 + (30 * cadastrarAssociadoStruct.qntdDependentes);

    associados.push_back(cadastrarAssociadoStruct);
    cout << "\nDados do novo associado:\n";
	cout << "Nome: " << cadastrarAssociadoStruct.nome << "\n";
	cout << "CPF: " << cadastrarAssociadoStruct.cpf << "\n";
	cout << "Código: " << cadastrarAssociadoStruct.codigo << "\n";
	cout << "Tipo de sócio: " << cadastrarAssociadoStruct.tipo_socio << "\n";
	cout << "Quantidade de Dependentes: " << cadastrarAssociadoStruct.qntdDependentes << "\n";
	cout << "Mensalidade: " << cadastrarAssociadoStruct.mensalidade << "\n";
	cout<<endl;
    salvarDadosAssociadosEmArquivo();
    
    for (int i = 0; i < cadastrarAssociadoStruct.qntdDependentes; i++)
    {
        cadastrarDependente();
    }
    
}

void cadastrarDependente(){
	
	dependentes.clear();
	
    const char *nomeArquivo = "dadosDependentes.txt";
    int linhas = contadorDeLinhas(nomeArquivo);

    cout << "Insira o nome do dependente(Utilize ' _ ' como espaÃ§o): ";
    cin >> cadastrarDependenteStruct.nome;
    
    cout<<endl;
    
    cout << "Digite o CPF do Associado: ";
	cin >> cadastrarDependenteStruct.cpf_associado;

    cout << endl;

    cout << "Insira a data de nascimento (Utilize / ou - e 0): ";
    cin >> cadastrarDependenteStruct.data_nasc;

    cout << endl;

    cout << "Insira o sexo (Masculino  ou Feminino): ";
    cin >> cadastrarDependenteStruct.sexo;

    cout << endl;

    cadastrarDependenteStruct.codigo = linhas + 1;
    cout << "O codigo do Dependente é: " << cadastrarDependenteStruct.codigo << endl;

    dependentes.push_back(cadastrarDependenteStruct);
    salvarDadosDependentesEmArquivo();
}

void cadastrarVisitante(){
	
	visitantes.clear();
	
	const char *nomeArquivo = "dadosVisitante.txt";
    int linhas = contadorDeLinhas(nomeArquivo);

	int codAssociadoVisitante;
	
	cout << "Digite o cod do Associado: ";
	cin >> codAssociadoVisitante;
		
    cout << "Insira o nome do Visitante(Utilize ' _ ' como espaÃ§o): ";
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

    cadastrarVisitanteStruct.codigo = linhas + 1;
    cout << "O codigo do visitante é: " << cadastrarVisitanteStruct.codigo;

    visitantes.push_back(cadastrarVisitanteStruct);
    salvarDadosVisitantesEmArquivo();
}

void avisoMaioridade(){
	
	
}

void relatorioDependentesAssociados(){
	
}

void relatorioVisitasPorAssociado(){
	
}

void alterarDados(){
	

    char op;

    cout << "Alterar dados de Associados,Dependentes ou dos Visitantes? (A/D/V): ";
    cin >> op;

    switch (op)
    {
    case 'A':
        alterarDadosAssociados("dadosAssociados.txt");
        break;
    case 'D':
        alterarDadosDependentes("dadosDependentes.txt");
        break;
    case 'V':
        alterarDadosVisitantes("dadosVisitantes.txt");
        break;
    case 'a':
        alterarDadosAssociados("dadosAssociados.txt");
        break;
    case 'd':
        alterarDadosDependentes("dadosDependentes.txt");
        break;
    case 'v':
        alterarDadosVisitantes("dadosVisitantes.txt");
        ;
        break;
    default:
        cout << "Opcao Invalida";
    }
}

int alterarDadosAssociados(const char *nomeArquivo){
	
    int codigoAssociado;

    cout << "Digite o codigo do associado que deseja alterar: ";
    cin >> codigoAssociado;
    cin.ignore();

    // Procura o associado pelo cï¿½digo
    for (size_t i = 0; i < associados.size(); ++i)
    {
        if (associados[i].codigo == codigoAssociado)
        {
            // Mostra os dados atuais do associado
            cout << "\nDados atuais do associado:\n";
            cout << "Cï¿½digo: " << associados[i].codigo << "\n";
            cout << "Nome: " << associados[i].nome << "\n";
            cout << "CPF: " << associados[i].cpf << "\n";
            cout << "Tipo: " << associados[i].tipo_socio << "\n";
            cout << "Data AssociaÃ§Ã£o: " << associados[i].dia_associacao << "/" << associados[i].mes_associacao << "/" << associados[i].ano_associacao << "\n";
            cout << "Quantidade Dependentes: " << associados[i].qntdDependentes << "\n";

            cout << "\nDigite as novas informaÃ§Ãµes (ou digite novamente as informaÃ§Ã£o que quer manter):\n";
            cout << "Novo nome: ";
            cin.ignore();
            getline(cin, associados[i].nome);
            cout << endl;
            cout << "Digite novo CPF: ";
            getline(cin, associados[i].cpf);
            cout << endl;
            cout << "Digite novo Tipo de AssociaÃ§Ã£o: ";
            getline(cin, associados[i].tipo_socio);
            cout << endl;
            cout << "Digite nova data de associaÃ§Ã£o: " << endl;
            cout << "dia:";
            getline(cin, associados[i].dia_associacao);
            cout << endl;
            cout << "mes:";
            getline(cin, associados[i].mes_associacao);
            cout << endl;
            cout << "ano:";
            getline(cin, associados[i].ano_associacao);
            cout << endl;
            cout << "Quantidade de Dependentes:";
            cin >> associados[i].qntdDependentes;
            associados[i].mensalidade = 200 + (30 * associados[i].qntdDependentes);

            salvarDadosAssociadosEmArquivo();
            return 0;
        }
    }

    cout << "Associado nÃ£o encontrado com o cÃ³digo fornecido.\n";
    return -1; // Retorna -1 para indicar falha
}

int alterarDadosDependentes(const char *nomeArquivo){
	
    int codigoDependente;

    cout << "Digite o código do dependente que deseja alterar: ";
    cin >> codigoDependente;

    // Procura o dependente pelo código
    for (size_t i = 0; i < dependentes.size(); ++i)
    {
        if (dependentes[i].codigo == codigoDependente)
        {
            // Mostra os dados atuais do dependente
            cout << "\nDados atuais do dependente:\n";
            cout << "Código: " << dependentes[i].codigo << "\n";
            cout << "Nome: " << dependentes[i].nome << "\n";
            cout<< "CPF: "<<dependentes[i].cpf_associado<< "\n";
            cout << "Data de Nascimento: " << dependentes[i].data_nasc << "\n";
            cout << "Sexo: " << dependentes[i].sexo << "\n";

            cout << "\nDigite as novas informações (ou digite novamente as informações que quer manter):\n";
            cout << "Novo nome: ";
            cin.ignore();
            getline(cin, dependentes[i].nome);
            cout << endl;
            cout << "Digite novo CPF Associado: ";
            cin.ignore();
            getline(cin, dependentes[i].cpf_associado);
            cout << endl;
            cout << "Digite nova Data de Nascimento: ";
            getline(cin, dependentes[i].data_nasc);
            cout << endl;
            cout << "Digite novo Sexo: ";
            getline(cin, dependentes[i].sexo);
            cout << endl;

            salvarDadosDependentesEmArquivo();
            return 0;
        }
    }

    cout << "Dependente não encontrado com o código fornecido.\n";
    return -1; // Retorna -1 para indicar falha
}

int alterarDadosVisitantes(const char *nomeArquivo){
	
    int codigoVisitante;

    cout << "Digite o código do visitante que deseja alterar: ";
    cin >> codigoVisitante;
		
    // Procura o visitante pelo código
    for (size_t i = 0; i < visitantes.size(); ++i){
    	
        if (visitantes[i].codigo == codigoVisitante)
        {
            // Mostra os dados atuais do visitante
            cout << "\nDados atuais do visitante:\n";
            cout << "Código: " << visitantes[i].codigo << "\n";
            cout << "Código Associado: " << visitantes[i].codigo_associado << "\n";
            cout << "Nome: " << visitantes[i].nome << "\n";
            cout << "Data de Nascimento: " << visitantes[i].data_nasc << "\n";
            cout << "Sexo: " << visitantes[i].sexo << "\n";
            cout << "Data de Visita Inicial: " << visitantes[i].data_visita_inicial << "\n";
            cout << "Data de Visita Final: " << visitantes[i].data_visita_final << "\n";

            cout << "\nDigite as novas informações (ou digite novamente as informações que quer manter):\n";
            cout << endl;
            cout << "Digite novo Código Associado: ";
            cin >> visitantes[i].codigo_associado;
            cout << endl;
            cout << "Digite novo Nome: ";
            cin.ignore();
            getline(cin, visitantes[i].nome);
            cout << endl;
            cout << "Digite nova Data de Nascimento: ";
            getline(cin, visitantes[i].data_nasc);
            cout << endl;
            cout << "Digite novo Sexo: ";
            getline(cin, visitantes[i].sexo);
            cout << endl;
            cout << "Digite nova Data de Visita Inicial: ";
            getline(cin, visitantes[i].data_visita_inicial);
            cout << endl;
            cout << "Digite nova Data de Visita Final: ";
            getline(cin, visitantes[i].data_visita_final);
            cout << endl;

            salvarDadosVisitantesEmArquivo();
            return 0;
        }
    }

    cout << "Visitante não encontrado com o código fornecido.\n";
    return -1; // Retorna -1 para indicar falha
}

void salvarDadosAssociadosEmArquivo(){
	
    fstream arquivo("dadosAssociados.txt", ios::out | ios::app ); 

    if (arquivo.is_open())
    {
        for (size_t i = 0; i < associados.size(); ++i)
        {
            const Associado &associado = associados[i];
            arquivo << "codigo:" << associado.codigo << " "<< "tipo:" << associado.tipo_socio << " "<< "cpf:" << associado.cpf << " "<< "diaA:" << associado.dia_associacao << " "<< "mesA:" << associado.mes_associacao << " "<< "anoA:" << associado.ano_associacao << " "<< "qtda dependentes:" << associado.qntdDependentes << " "<< "mensalidade:" << associado.mensalidade << " "<< "nome:" << associado.nome << "\n";
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de associados." << endl;
    }
}

void salvarDadosDependentesEmArquivo(){
	
	fstream arquivo("dadosDependentes.txt", ios::out | ios::app );

    if (arquivo.is_open())
    {
        for (size_t i = 0; i < dependentes.size(); ++i)
        {
            const Dependente &dependente = dependentes[i];
            arquivo << "codigo:" << dependente.codigo << " "<< "codExterno:" << dependente.codExterno << " "<< "cpf associado:" << dependente.cpf_associado << " "<< "nome:" << dependente.nome << " "<< "data_nasc:" << dependente.data_nasc << " "<< "sexo:" << dependente.sexo << "\n";
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de dependentes." << endl;
    }
}

void salvarDadosVisitantesEmArquivo(){
	
    fstream arquivo("dadosVisitante.txt", ios::out | ios::app );

    if (arquivo.is_open())
    {
        for (size_t i = 0; i < visitantes.size(); ++i)
        {
            const Visitante &visitante = visitantes[i];
            arquivo << "codigo:"<<visitante.codigo<< " " <<"cpf:"<< visitante.cpf << " " <<"codigo associado:"<< visitante.codigo_associado << " "<< "nome:"<<visitante.nome << " " <<"data nasc:"<< visitante.data_nasc << " " << "sexo:"<<visitante.sexo << " "<< "visita inicial:"<<visitante.data_visita_inicial << " " <<"visita final:"<< visitante.data_visita_final << "\n";
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de visitantes." << endl;
    }
}

void carregarDadosDoArquivo(){
	
    associados.clear();  // Limpa o vetor de associados
    dependentes.clear(); // Limpa o vetor de dependentes
    visitantes.clear();  // Limpa o vetor de visitantes
    
    fstream arquivoA, arquivoD, arquivoV;
    arquivoA.open("dadosAssociados.txt", ios::in | ios::out | ios::app);
    arquivoD.open("dadosDependentes.txt", ios::in | ios::out | ios::app);
    arquivoV.open("dadosVisitante.txt", ios::in | ios::out | ios::app);
    
}
