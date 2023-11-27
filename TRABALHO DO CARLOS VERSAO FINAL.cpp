//Alunos: Bruno Rezende, Guilherme Pereira , Kawan Aureliano. 
//2ª Periodo - Sistema de Informação - UEMG PASSOS.

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <locale.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Associado{
	
    int codigo, qntdDependentes;
    string nome, cpf, dia_associacao, mes_associacao, ano_associacao, tipo_socio, data_nasc;
    float mensalidade;
};

struct Dependente{
	
    int codigo;
    string cpf_associado, nome, data_nasc, sexo,codExterno;
};

struct Visitante{
	
    int codigo, cpf, codigo_associado;
    string nome, data_nasc, sexo, data_visita_inicial, data_visita_final;
};

int contadorDeLinhas(const char *nomeArquivo);
void cadastrarAssociado();
void cadastrarDependente();
void cadastrarVisitante();
void relatorioDependentes();
void relatorioAssociados();
void relatorioAssociadosDependentes();
void relatorioVisitasPorAssociado();
void salvarDadosAssociadosEmArquivo();
void salvarDadosDependentesEmArquivo();
void salvarDadosVisitantesEmArquivo();
void carregarDadosDoArquivo();
void alterarDados();
int alterarDadosAssociados(const char *nomeArquivo);
int alterarDadosDependentes(const char *nomeArquivo);
int alterarDadosVisitantes(const char *nomeArquivo);
void avisoMaioridade();
int calcularIdade(const string& data_nasc);
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
        cout << "4. Aviso automatico de maioridade\n";
        cout << "5. Relatorio de dependentes\n";
        cout << "6. Relatorio de visitas por associado\n";
        cout << "7. Relatorio de associados\n";
        cout << "8. Relatorio de Dependentes por Associado\n";
        cout << "9. Alterar Dados\n.";
        cout << "10. Encerrar o programa\n";
        cout << "Escolha uma opcao (1-10): ";
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
            relatorioDependentes();
            break;
        case '6':
            relatorioVisitasPorAssociado();
            break;
        case '7':
            relatorioAssociados();
            break;
        case '8':
           relatorioAssociadosDependentes();
            break;
        case '9':
            alterarDados();
            break;
        case '10':
        	cout <<"Programa Encerrado.\n";
        default:
            cout << "Opcao Ivalida. Tente novamente.\n";
            break;
        }
    } while (escolha != '10');

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

    cout << "Digite o nome do associado (Utilize ' _ 'como espaco): ";
    cin >> cadastrarAssociadoStruct.nome;

    cout << "Digite o CPF: ";
    cin >> cadastrarAssociadoStruct.cpf;

    cout << endl;

    cout << "Insire a data de Associacao: ";
    cout << endl;

    cout << "Dia: ";
    cin >> cadastrarAssociadoStruct.dia_associacao;

    cout << "Mes: ";
    cin >> cadastrarAssociadoStruct.mes_associacao;

    cout << "Ano: ";
    cin >> cadastrarAssociadoStruct.ano_associacao;

    cout << endl;

    cout << "Insira o tipo de socio (Proprietario ou Contribuinte): ";
    cin >> cadastrarAssociadoStruct.tipo_socio;

    cout << endl;

    cadastrarAssociadoStruct.codigo = linhas + 1;
    cout << "O codigo do Associado Ã©: " << cadastrarAssociadoStruct.codigo;

    cout << endl;
    cout << endl;

    cout << "Digite quantos dependentes voce quer cadastrar: ";
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
    string anoAssociacao;

    cout << "Insira o nome do dependente(Utilize ' _ ' como espaco): ";
    cin >> cadastrarDependenteStruct.nome;
    
    cout<<endl;
    
    cout << "Digite o CPF do Associado: ";
	cin >> cadastrarDependenteStruct.cpf_associado;
	
	cout<<"Digite o ano de associação: ";
	cin>>anoAssociacao;
	
    cout << endl;

    cout << "Insira a data de nascimento (AAAA-MM-DD): ";
    cin >> cadastrarDependenteStruct.data_nasc;

    cout << endl;

    cout << "Insira o sexo (Masculino  ou Feminino): ";
    cin >> cadastrarDependenteStruct.sexo;

    cout << endl;

    cadastrarDependenteStruct.codigo = linhas + 1;
    cadastrarDependenteStruct.codExterno = anoAssociacao + static_cast<ostringstream*>(& (ostringstream() << cadastrarDependenteStruct.codigo))->str();
    cout << "O codigo do Dependente é: " << cadastrarDependenteStruct.codigo << endl;
    cout<< "seu codigo externo é:" << cadastrarDependenteStruct.codExterno<<endl;

    

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
		
    cout << "Insira o nome do Visitante(Utilize ' _ ' como espaco): ";
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

void alterarDados() {
    char op;

    cout << "Alterar dados de Associados, Dependentes ou dos Visitantes? (A/D/V): ";
    cin >> op;

    const char *nomeArquivo;

    switch (op) {
        case 'A':
        case 'a':
            nomeArquivo = "dadosAssociados.txt";
            alterarDadosAssociados(nomeArquivo);
            break;
        case 'D':
        case 'd':
            nomeArquivo = "dadosDependentes.txt";
            alterarDadosDependentes(nomeArquivo);
            break;
        case 'V':
        case 'v':
            nomeArquivo = "dadosVisitante.txt";
            alterarDadosVisitantes(nomeArquivo);
            break;
        default:
            cout << "Opcao Invalida";
    }
}


int alterarDadosAssociados(const char *nomeArquivo) {
    int codigoAssociado;
    cout << "Digite o código do associado que deseja alterar: ";
    cin >> codigoAssociado;

    fstream arquivo(nomeArquivo, ios::in | ios::out);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de associados.\n";
        return 0;
    }

    string linha;
    vector<string> linhasDoArquivo;

    // Lê todas as linhas do arquivo
    while (getline(arquivo, linha)) {
        linhasDoArquivo.push_back(linha);
    }

    arquivo.close();

    // Encontrar a posição da linha desejada
    size_t posicaoLinha = string::npos;
    for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
        size_t pos = linhasDoArquivo[i].find("codigo:" + static_cast<ostringstream*>( &(ostringstream() << codigoAssociado) )->str());
        if (pos != string::npos) {
            posicaoLinha = i;
            break;
        }
    }

    if (posicaoLinha == string::npos) {
        cout << "Associado não encontrado.\n";
        return 0;
    }
    
    cout << "\nDados atuais do associado:\n" << linhasDoArquivo[posicaoLinha] << "\n";


    // Pede ao usuário para digitar os novos dados
    Associado novoAssociado;
    cout << "\nDigite os novos dados do associado( ou reescreva os mesmos dados ):\n";
    cout << "Nome: ";
    cin >> novoAssociado.nome;
    cout << "CPF: ";
    cin >> novoAssociado.cpf;
    cout << "Dia de Associação: ";
    cin >> novoAssociado.dia_associacao;
    cout << "Mês de Associação: ";
    cin >> novoAssociado.mes_associacao;
    cout << "Ano de Associação: ";
    cin >> novoAssociado.ano_associacao;
    cout << "Tipo de Sócio: ";
    cin >> novoAssociado.tipo_socio;
    cout << "Quantidade de Dependentes: ";
    cin >> novoAssociado.qntdDependentes;

    // Calcula a nova mensalidade
    novoAssociado.mensalidade = 200 + (30 * novoAssociado.qntdDependentes);

    // Atualiza a linha no vetor de linhas
    ostringstream oss;
    oss << "codigo:" << codigoAssociado << " "
        << "tipo:" << novoAssociado.tipo_socio << " "
        << "cpf:" << novoAssociado.cpf << " "
        << "diaA:" << novoAssociado.dia_associacao << " "
        << "mesA:" << novoAssociado.mes_associacao << " "
        << "anoA:" << novoAssociado.ano_associacao << " "
        << "qtda dependentes:" << novoAssociado.qntdDependentes << " "
        << "mensalidade:" << novoAssociado.mensalidade << " "
        << "nome:" << novoAssociado.nome;

    linhasDoArquivo[posicaoLinha] = oss.str();

    // Reescreve todo o conteúdo atualizado no arquivo
    arquivo.open(nomeArquivo, ios::out | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de associados para escrita.\n";
        return 0;
    }

    for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
        arquivo << linhasDoArquivo[i] << '\n';
    }

    cout << "Dados do associado atualizados com sucesso.\n";

    arquivo.close();

    return 0;
}


int alterarDadosDependentes(const char *nomeArquivo) {
    int codigoDependente;
    cout << "Digite o código do dependente que deseja alterar: ";
    cin >> codigoDependente;

    fstream arquivo(nomeArquivo, ios::in | ios::out);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de dependentes.\n";
        return 0;
    }

    string linha;
    vector<string> linhasDoArquivo;

    // Lê todas as linhas do arquivo
    while (getline(arquivo, linha)) {
	    // Remove espaços extras do final da linha
	    linhasDoArquivo.push_back(linha);
}

    arquivo.close();

    // Encontrar a posição da linha desejada
    size_t posicaoLinha = string::npos;
    for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
        size_t pos = linhasDoArquivo[i].find("codigo:" + static_cast<ostringstream*>( &(ostringstream() << codigoDependente) )->str());
        if (pos != string::npos) {
            posicaoLinha = i;
            break;
        }
    }

    if (posicaoLinha == string::npos) {
        cout << "Dependente não encontrado.\n";
        return 0;
    }

	size_t posInicioCodExterno = linhasDoArquivo[posicaoLinha].find("codExterno:");
	size_t posFimCodExterno = linhasDoArquivo[posicaoLinha].find(" ", posInicioCodExterno);
	string codExternoAtual = linhasDoArquivo[posicaoLinha].substr(posInicioCodExterno + 10, posFimCodExterno - posInicioCodExterno - 10);

	cout << "\nDados atuais do Dependente:\n" << linhasDoArquivo[posicaoLinha] << "\n";
	
    // Pede ao usuário para digitar os novos dados
    Dependente novoDependente;
    cout << "\nDigite os novos dados do dependente ( ou reescreva os mesmos dados ):\n";
    cout << "Nome: ";
    cin >> novoDependente.nome;
    cout << "CPF do Associado: ";
    cin >> novoDependente.cpf_associado;
    cout << "Data de Nascimento (AAAA-MM-DD): ";
    cin >> novoDependente.data_nasc;
    cout << "Sexo: ";
    cin >> novoDependente.sexo;

    // Atualiza a linha no vetor de linhas
    ostringstream oss;
	oss << "codigo:" << codigoDependente << " "
	    << "codExterno:" << codExternoAtual << " "
	    << "cpf associado:" << novoDependente.cpf_associado << " "
	    << "nome:" << novoDependente.nome << " "
	    << "data_nasc:" << novoDependente.data_nasc << " "
	    << "sexo:" << novoDependente.sexo << " ";

    linhasDoArquivo[posicaoLinha] = oss.str();

    // Reescreve todo o conteúdo atualizado no arquivo
    arquivo.open(nomeArquivo, ios::out | ios::trunc);
	if (!arquivo.is_open()) {
	    cout << "Erro ao abrir o arquivo de dependentes para escrita.\n";
	    return 0;
	}
	
	for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
	    arquivo << linhasDoArquivo[i] << '\n';
	}
	
	cout << "Dados do dependente atualizados com sucesso.\n";
	
	arquivo.close();

    return 0;
}


int alterarDadosVisitantes(const char *nomeArquivo) {
    int codigoVisitante;
    cout << "Digite o código do visitante que deseja alterar: ";
    cin >> codigoVisitante;

    fstream arquivo(nomeArquivo, ios::in | ios::out);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de visitantes.\n";
        return 0;
    }

    string linha;
    vector<string> linhasDoArquivo;

    // Lê todas as linhas do arquivo
    while (getline(arquivo, linha)) {
        linhasDoArquivo.push_back(linha);
    }

    arquivo.close();

    // Encontrar a posição da linha desejada
    size_t posicaoLinha = string::npos;
    for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
        size_t pos = linhasDoArquivo[i].find("codigo:" + static_cast<ostringstream*>( &(ostringstream() << codigoVisitante) )->str());
        if (pos != string::npos) {
            posicaoLinha = i;
            break;
        }
    }

    if (posicaoLinha == string::npos) {
        cout << "Visitante não encontrado.\n";
        return 0;
    }
    
    cout << "\nDados atuais do Visitante:\n" << linhasDoArquivo[posicaoLinha] << "\n";

    // Pede ao usuário para digitar os novos dados
    Visitante novoVisitante;
    cout << "\nDigite os novos dados do visitante ( ou reescreva os mesmos dados ):\n";
    cout << "Nome: ";
    cin >> novoVisitante.nome;
    cout << "CPF: ";
    cin >> novoVisitante.cpf;
    cout << "Código do Associado: ";
    cin >> novoVisitante.codigo_associado;
    cout << "Data de Nascimento: ";
    cin >> novoVisitante.data_nasc;
    cout << "Sexo: ";
    cin >> novoVisitante.sexo;
    cout << "Data de Visita Inicial: ";
    cin >> novoVisitante.data_visita_inicial;
    cout << "Data de Visita Final: ";
    cin >> novoVisitante.data_visita_final;

    // Atualiza a linha no vetor de linhas
    ostringstream oss;
    oss << "codigo:" << codigoVisitante << " "
        << "cpf:" << novoVisitante.cpf << " "
        << "codigo associado:" << novoVisitante.codigo_associado << " "
        << "nome:" << novoVisitante.nome << " "
        << "data_nasc:" << novoVisitante.data_nasc << " "
        << "sexo:" << novoVisitante.sexo << " "
        << "visita inicial:" << novoVisitante.data_visita_inicial << " "
        << "visita final:" << novoVisitante.data_visita_final;

    linhasDoArquivo[posicaoLinha] = oss.str();

    // Reescreve todo o conteúdo atualizado no arquivo
    arquivo.open(nomeArquivo, ios::out | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de visitantes para escrita.\n";
        return 0;
    }

    for (size_t i = 0; i < linhasDoArquivo.size(); ++i) {
        arquivo << linhasDoArquivo[i] << '\n';
    }

    cout << "Dados do visitante atualizados com sucesso.\n";

    arquivo.close();

    return 0;
}

 void avisoMaioridade() {
    ifstream arquivo("dadosDependentes.txt");
    string linha;

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            int idade = calcularIdade(linha);
            if (idade >= 18) {
                cout << "Usuário maior de idade" << endl;
            } else {
                cout << "Usuário menor de idade" << endl;
            }
        }
        arquivo.close();
    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }
}

int calcularIdade(const std::string& data_nasc) {
    struct tm tm_nascimento = {0};
    istringstream iss(data_nasc);
    iss >> tm_nascimento.tm_year;
    iss.ignore(); // Ignorar o caractere '-' entre ano e mês
    iss >> tm_nascimento.tm_mon;
    iss.ignore(); // Ignorar o caractere '-' entre mês e dia
    iss >> tm_nascimento.tm_mday;

    tm_nascimento.tm_year -= 1900; // Ano em tm é desde 1900
    tm_nascimento.tm_mon -= 1; // Mês em tm é base 0 (janeiro = 0)

    time_t nascimento = mktime(&tm_nascimento);

    time_t t = time(NULL);
    tm* now = localtime(&t);
    time_t atual = mktime(now);

    int idade = (difftime(atual, nascimento) / (60 * 60 * 24 * 365));
    return idade;
}

	
	

void relatorioAssociados(){
	ifstream arquivoE;
	string linha;
	arquivoE.open("dadosAssociados.txt");
	if (arquivoE.is_open()){
	while (getline(arquivoE,linha)){
		cout<<linha<<endl;	}
	}else{
		cout<<"Nao foi encontrado dados para o relatorio"<<endl;
	}}

void relatorioDependentes(){
	ifstream arquivoE;
	string linha;
	arquivoE.open("dadosDependentes.txt");
	if (arquivoE.is_open()){
	while (getline(arquivoE,linha)){
		cout<<linha<<endl;	}
	}else{
		cout<<"Nao foi encontrado dados para o relatorio"<<endl;
	}
}

void relatorioAssociadosDependentes(){
	ifstream arquivoE("dadosDependentes.txt");
    string linha;
    
    if (arquivoE.is_open()) {
        string depentendeAssociado = "";
        int contador = 0;
        
        while (getline(arquivoE, linha)) {
            if (linha != depentendeAssociado) {
                if (!depentendeAssociado.empty()) {
                    cout << "Associado: " << depentendeAssociado << ", Dependente: " << contador << endl;
                }
                depentendeAssociado = linha;
                contador = 1;
            } else {
                contador++;
            }
        }
        
        if (!depentendeAssociado.empty()) {
            cout << "Associado: " << depentendeAssociado << ", Visitantes: " << contador << endl;
        }
        
        arquivoE.close();
    } else {
     cout << "Não foram encontrados dados para o relatório." << endl;
    }
}


void relatorioVisitasPorAssociado() {
   ifstream arquivoE("dadosVisitante.txt");
    string linha;
    
    if (arquivoE.is_open()) {
        string associadoAnterior = "";
        int contador = 0;
        
        while (getline(arquivoE, linha)) {
            if (linha != associadoAnterior) {
                if (!associadoAnterior.empty()) {
			cout << "Associado: " << associadoAnterior << ", Visitantes: " << contador << endl;
                }
                associadoAnterior = linha;
                contador = 1;
            } else {
                contador++;
            }
        }
        
        if (!associadoAnterior.empty()) {
            std::cout << "Associado: " << associadoAnterior << ", Visitantes: " << contador << endl;
        }
        
        arquivoE.close();
    } else {
     cout << "Não foram encontrados dados para o relatório." << endl;
    }
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
    
	}
	
