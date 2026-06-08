#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <fstream>
#include <sstream>

#define RED "\033[31m"	// coloca o texto vermelho
#define RESET "\033[0m"	// volta ao branco padrão	
#define GREEN "\033[32m"	// coloca o texto verde
#define YELLOW "\033[33m"	// coloca o texto amarelo
#define BLUE "\033[94m"		// coloca o texto azul
#define BOLD "\033[1m"		// coloca o texto negrito
#define CIANO "\033[96m"	// coloca o texto ciano

using namespace std;

// struct para data de nascimento do aluno
struct Data{
	string dia;
	string mes;
	string ano;
};

// struct com informações de aluno
struct Aluno{
	string nome;
	string id;
	Data aniversario;
};

// struct com informações de disciplina
struct Disciplina{
	string nome;
	string id;
	string professor;
};

// struct com informações de inscrição de aluno
struct Inscricao{
	string id_aluno;
	string id_disciplina;
	string nota_final;
};

// função para mostrar alunos (opção 1 do menu alunos)
void mostrar_alunos(){
	ifstream fich_alunos("ficheiro_alunos.csv");
	if(! fich_alunos.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro, verifique o ficheiro."<<RESET<<endl;
	}else{
		string linha;
		Aluno a1;
		cout<<endl<<CIANO<<" - - M O S T R A R - A L U N O S - -"<<RESET<<endl;
		while(getline(fich_alunos,linha)){
			istringstream ss(linha);
			getline(ss,a1.nome,',');
			getline(ss,a1.id,',');
			getline(ss,a1.aniversario.dia,'/');
			getline(ss,a1.aniversario.mes,'/');
			getline(ss,a1.aniversario.ano,',');
			cout<<BOLD<<endl<<"Nome: "<<RESET<<a1.nome<<endl;
			cout<<BOLD<<"ID aluno: "<<RESET<<a1.id<<endl;
			cout<<BOLD<<"Data nascimento: "<<RESET<<a1.aniversario.dia<<BOLD<<"/"<<RESET<<a1.aniversario.mes<<BOLD<<"/"<<RESET<<a1.aniversario.ano<<endl;
			cout<<CIANO<<endl<<"---------------------------------------------"<<RESET<<endl;
		}
	}
}

// função adicionar inscrição (opção 2 do menu inscricoes)
void adicionar_inscricao(){
	ofstream fich_inscricoes("ficheiro_inscricoes.csv", ios::app);
	if(! fich_inscricoes.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro das inscrições."<<RESET<<endl;
	}else if(fich_inscricoes.is_open()){
		Inscricao i1;
		Inscricao i2;
		string linha;
		bool ja_existe = false;
		cout<<endl;
		cout<<CIANO<<" - - A D I C I O N A R - I N S C R I Ç Ã O - -"<<RESET<<endl;
		cout<<"        Preencha os seguintes campos"<<endl<<endl;
		cout<<BOLD<<" ID aluno: "<<RESET;
		getline(cin,i1.id_aluno);	// lê o ID do aluno
		cout<<BOLD<<" ID disciplina: "<<RESET;
		getline(cin,i1.id_disciplina);	// lê o ID da disciplina
		cout<<BOLD<<" Nota final (0-20): "<<RESET;
		getline(cin,i1.nota_final);	// lê a nota final do aluno na disciplina
		ifstream fich_inscricoes_leitura("ficheiro_inscricoes.csv");
		while(getline(fich_inscricoes_leitura,linha)){
			istringstream ss(linha);
			getline(ss,i2.id_aluno,',');
			getline(ss,i2.id_disciplina,',');
			getline(ss,i2.nota_final,',');
			if(i1.id_aluno == i2.id_aluno){
				if(i1.id_disciplina == i2.id_disciplina){
					ja_existe = true;
					cout<<endl<<RED<<"O aluno já está inscrito na disciplina."<<RESET<<endl;
				}
			}
		}
		fich_inscricoes_leitura.close();
		if(ja_existe == false){
			fich_inscricoes<<i1.id_aluno<<",";
			fich_inscricoes<<i1.id_disciplina<<",";
			fich_inscricoes<<i1.nota_final<<endl;
			fich_inscricoes.close();
		}
	}
}

// função para adicionar aluno (opção 2 do menu alunos)
void adicionar_aluno(){
	ofstream fich_alunos("ficheiro_alunos.csv", ios::app);
	if(! fich_alunos.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro."<<RESET<<endl;
	}else if(fich_alunos.is_open()){
		Aluno a1;	// aluno novo
		Aluno a2;	// verifica se já tem algum aluno com o mesmo ID do a1
		string linha;	// linha do ficheiro alunos para ler
		bool ja_existe = false;
		cout<<endl;
		cout<<CIANO<<" - - A D I C I O N  A R - A L U N O - -"<<RESET<<endl;
		cout<<"     Preencha os seguintes campos"<<endl;
		cin.ignore();
		cout<<BOLD<<" ID aluno: "<<RESET;
		getline(cin,a1.id);
		cout<<endl;
		cout<<BOLD<<" Nome: "<<RESET;
		getline(cin,a1.nome);		// lê o ID do aluno novo
		cout<<endl;
		cout<<BOLD<<" Data de nascimento: "<<RESET;
		getline(cin,a1.aniversario.dia);	// lê o dia do aniversário
		cout<<BOLD<<"/"<<RESET;
		getline(cin,a1.aniversario.mes);	// lê o mês do aniversário
		cout<<BOLD<<"/"<<RESET;
		getline(cin,a1.aniversario.ano);	// lê o ano do aniversário
		cin.ignore();
		ifstream fich_alunos_leitura("ficheiro_alunos.csv");	// abre o ficheiro alunos só para ler
		while(getline(fich_alunos_leitura,linha)){	// lê linha por linha do ficheiro alunos
			istringstream ss(linha);
			getline(ss,a2.id,',');
			if(a2.id == a1.id){		// indica que já existe algum aluno com o ID do aluno novo
				ja_existe = true;
				cout<<endl<<RED<<"O ID já existe no ficheiro."<<RESET<<endl;
			}
		}
		fich_alunos_leitura.close();
		if(ja_existe == false){		// indica que não existe nenhum aluno com o ID do aluno novo
			fich_alunos<<a1.id<<",";
			fich_alunos<<a1.nome<<",";
			fich_alunos<<a1.aniversario.dia<<"/"<<a1.aniversario.mes<<"/"<<a1.aniversario.ano<<endl;
			fich_alunos.close();
			bool opcao_valida = false;	// para verificar se a opção é válida
			char opcao;
			cout<<endl<<" Quer inscrever o aluno numa disciplina (Y/N)? ";
			cin>>opcao;	// opção inserida
			opcao = toupper(opcao);
			if(opcao == 'Y'){	// inscreve o aluno numa disciplina
				opcao_valida = true;	// indica que a opção inserida é válida (é Y ou N)
				system("cls");
				adicionar_inscricao();
				system("pause");
			}else if(opcao == 'N'){	// o aluno não fica inscrito em nenhuma disciplina
				opcao_valida = true;	// indica que a opção inserida é válida (é Y ou N)
				system("cls");
				system("color 4");
				cout<<endl<<RED<<" O aluno não está inscrito em nenhuma disciplina!"<<RESET<<endl;
				system("pause");
				system("cls");
			}
			if(opcao_valida == false){	// se a opção inserida for diferente de Y ou N
				cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl;
			}
		}
	}
}

// função para procurar aluno por ID (opção 3 do menu alunos)
void procurar_aluno(){
	ifstream fich_alunos("ficheiro_alunos.csv");
	if(! fich_alunos.is_open()){	// verifica se é possível abrir o ficheiro alunos
		cout<<endl<<RED<<"Não foi possívelo abrir o ficheiro alunos."<<RESET<<endl;
	}else if(fich_alunos.is_open()){
		char opcao;
		bool encontrado = false;	// bool para verificar se o aluno tá no ficheiro
		cout<<CIANO<<" - - - P R O C U R A R - U M - A L U N O - - -"<<RESET<<endl;
		cout<<BOLD<<" 1 -> Procurar através do ID do aluno"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Procurar através do nome do aluno"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar à página anterior"<<RESET<<endl;
		cout<<CIANO<<" - - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
		cout<<BOLD<<" Insira a sua opção: "<<RESET;
		cin>>opcao;
		cin.ignore();
		if(opcao == '1'){
			string procurar_id;
			string linha;
			Aluno a1;
			system("cls");
			cout<<endl<<BOLD<<" Insira o ID do aluno: "<<RESET;
			getline(cin,procurar_id);	// lê o ID para procurar
			while(getline(fich_alunos,linha)){	// faz a leitura do ficheiro alunos
				istringstream ss(linha);
				getline(ss,a1.id,',');	// lê o ID do aluno
				getline(ss,a1.nome,',');	// lê o nome de cada aluno
				getline(ss,a1.aniversario.dia,'/'); // lê o dia do aniversário de cada aluno
				getline(ss,a1.aniversario.mes,'/');	// lê o mes do aniversário de cada aluno
				getline(ss,a1.aniversario.ano,',');	// lê o ano de aniversário de cada aluno
			
				// se o ID inserido for igual ao ID lido do ficheiro alunos
				if(a1.id == procurar_id){	// verifica se o ID do aluno existe no ficheiro dos alunos
					encontrado = true;	// indica que o aluno foi encontrado
					cout<<endl<<endl;
					cout<<BOLD<<GREEN<<" - - A L U N O - E N C O N T R A D O - -"<<RESET<<endl;
					cout<<BOLD<<"Nome: "<<RESET<<a1.nome<<endl;	// nome do aluno 
					cout<<BOLD<<"ID aluno: "<<RESET<<a1.id<<endl;	// ID do aluno
					cout<<BOLD<<"Data nascimento: "<<RESET<<a1.aniversario.dia<<BOLD<<"/"<<RESET<<a1.aniversario.mes<<BOLD<<"/"<<RESET<<a1.aniversario.ano<<endl;	// aniversário do aluno
				}
			}
			// se o ID não foi encotrado no ficheiro alunos
			if(encontrado == false){
				cout<<endl<<RED<<"Não foi encontrado nenhum aluno!"<<RESET<<endl;
			}
		}else if(opcao == '2'){
			string procurar_nome;
			string linha;
			Aluno a1;
			system("cls");
			cout<<endl<<BOLD<<" Insira o nome do aluno: "<<RESET<<endl;
			getline(cin,procurar_nome);
			while(getline(fich_alunos,linha)){	// faz a leitura do ficheiro alunos
				istringstream ss(linha);
				getline(ss,a1.id,',');	// lê o ID do aluno
				getline(ss,a1.nome,',');	// lê o nome de cada aluno
				getline(ss,a1.aniversario.dia,'/'); // lê o dia do aniversário de cada aluno
				getline(ss,a1.aniversario.mes,'/');	// lê o mes do aniversário de cada aluno
				getline(ss,a1.aniversario.ano,',');	// lê o ano de aniversário de cada aluno
			
				// se o nome inserido for igual ao nome lido do ficheiro alunos
				if(a1.nome == procurar_nome){
					encontrado = true;	// indica que o aluno foi encontrado
					cout<<endl<<endl;
					cout<<BOLD<<GREEN<<" - - A L U N O - E N C O N T R A D O - -"<<RESET<<endl;
					cout<<BOLD<<"Nome: "<<RESET<<a1.nome<<endl;	// nome do aluno 
					cout<<BOLD<<"ID aluno: "<<RESET<<a1.id<<endl;	// ID do aluno
					cout<<BOLD<<"Data nascimento: "<<RESET<<a1.aniversario.dia<<BOLD<<"/"<<RESET<<a1.aniversario.mes<<BOLD<<"/"<<RESET<<a1.aniversario.ano<<endl;	// aniversário do aluno
				}
			}
			if(encontrado == false){
				while(getline(fich_alunos,linha)){	// faz a leitura do ficheiro alunos
					procurar_nome[0] = toupper(procurar_nome[0]); 
					istringstream ss(linha);
					getline(ss,a1.id,',');	// lê o ID do aluno
					getline(ss,a1.nome,',');	// lê o nome de cada aluno
					getline(ss,a1.aniversario.dia,'/'); // lê o dia do aniversário de cada aluno
					getline(ss,a1.aniversario.mes,'/');	// lê o mes do aniversário de cada aluno
					getline(ss,a1.aniversario.ano,',');	// lê o ano de aniversário de cada aluno
				
					// se o nome inserido for igual ao nome lido do ficheiro alunos
					if(a1.nome == procurar_nome){
						encontrado = true;	// indica que o aluno foi encontrado
						cout<<endl<<endl;
						cout<<BOLD<<GREEN<<" - - A L U N O - E N C O N T R A D O - -"<<RESET<<endl;
						cout<<BOLD<<"Nome: "<<RESET<<a1.nome<<endl;	// nome do aluno 
						cout<<BOLD<<"ID aluno: "<<RESET<<a1.id<<endl;	// ID do aluno
						cout<<BOLD<<"Data nascimento: "<<RESET<<a1.aniversario.dia<<BOLD<<"/"<<RESET<<a1.aniversario.mes<<BOLD<<"/"<<RESET<<a1.aniversario.ano<<endl;	// aniversário do aluno
					}
				}
			}
			// se o aluno não foi encotrado no ficheiro alunos
			if(encontrado == false){
				cout<<endl<<RED<<"Não foi encontrado nenhum aluno!"<<RESET<<endl;
			}
		}
	}
}

// função para apagar aluno (opção 4 do menu alunos)
void eliminar_aluno(){
	string id_apagar;	// é o ID do aluno a eliminar
	string linha_alunos;
	string linha_inscricoes;
	Aluno a1;
	Inscricao i1;
	int abrir_ficheiros = 0;	// indica se não foi possível abrir os ficheiros
	bool id_encontrado_alunos = false;	// indica para verificar se o ID do aluno foi encontrado no fich_alunos
	bool id_encontrado_inscricoes = false;	// indica para verificar se o ID do aluno foi encontrado no fich_inscricoes
	ifstream fich_alunos("ficheiro_alunos.csv");	// abre o ficheiro alunos só para ler as coisas
	if(! fich_alunos.is_open()){
		abrir_ficheiros = abrir_ficheiros + 1;
	}
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");	// abre o ficheiro inscricoes só para ler
	if(! fich_inscricoes.is_open()){
		abrir_ficheiros = abrir_ficheiros + 1;
	}
	ofstream fich_temp_inscricoes("temporario_inscricoes.csv",ios::app);	// abre o ficheiro temporario das inscricoes
	if(! fich_temp_inscricoes.is_open()){
		abrir_ficheiros = abrir_ficheiros + 1;
	}
	ofstream fich_temp_alunos("temporario_alunos.csv",ios::app);	// ficheiro temporario dos alunos
	if(! fich_temp_alunos.is_open()){
		abrir_ficheiros = abrir_ficheiros + 1;
	}
	if(abrir_ficheiros == 0){
		cout<<endl;
		cin.ignore();
		cout<<CIANO<<" - - E L I M I N A R - A L U N O - -"<<RESET<<endl<<endl;
    	cout<<BOLD<<"Insira o ID do aluno: "<<RESET;
    	getline(cin,id_apagar);
    	while(getline(fich_inscricoes,linha_inscricoes)){
    		istringstream ss(linha_inscricoes);
    		getline(ss,i1.id_aluno,',');
    		getline(ss, i1.id_disciplina,',');
    		getline(ss,i1.nota_final,',');
    		if(i1.id_aluno == id_apagar){
    			id_encontrado_inscricoes = true;	// o ID do aluno foi encontrado no ficheiro das inscricoes
    			continue;	// isto mete na linha de baixo para escrever no ficheiro novo
			}
			fich_temp_inscricoes<<i1.id_aluno<<","<<i1.id_disciplina<<","<<i1.nota_final<<endl;
		}
    	while(getline(fich_alunos,linha_alunos)){
    		istringstream ss(linha_alunos);
    		getline(ss,a1.nome,',');
    		getline(ss,a1.id,',');
    		getline(ss,a1.aniversario.dia,'/');
    		getline(ss,a1.aniversario.mes,'/');
    		getline(ss,a1.aniversario.ano,',');
    		if(a1.id == id_apagar){
				id_encontrado_alunos = true;	// o ID do aluno foi encontrado no ficheiro alunos
				continue;	// isto avança para a outra linha para escrever no ficheiro novo
			}
			fich_temp_alunos<<a1.nome<<","<<a1.id<<","<<a1.aniversario.dia<<"/"<<a1.aniversario.mes<<"/"<<a1.aniversario.ano<<","<<endl;
		}
		if(id_encontrado_alunos == true){
			remove("ficheiro_alunos.csv");	// apaga o ficheiro dos alunos
			rename("temporario_alunos.csv","ficheiro_alunos.csv");	// troca o nome do ficheiro temporário dos alunos
		}else if(id_encontrado_alunos == false){
			cout<<endl<<RED<<"Não existe nenhum aluno com esse ID."<<RESET<<endl;
		}
		if(id_encontrado_inscricoes == true){
			remove("ficheiro_inscricoes.csv");	// apaga o ficheiro das inscrições
			rename("temporario_inscricoes.csv","ficheiro_inscricoes.csv");	// troca o nome do ficheiro temporário das inscrições
		}else if(id_encontrado_inscricoes == false){
			cout<<endl<<RED<<"O ID não existe no ficheiros inscrições."<<RESET<<endl;
		}
		fich_temp_alunos.close();	// fecha o ficheiro tmeporário dos alunos
		fich_alunos.close();	// fecha o ficheiro dos alunos
		fich_temp_inscricoes.close();	// fecha o ficheiro temporário das inscrições
		fich_inscricoes.close();	// fecha o ficheiro das inscrições
	}else{
		cout<<endl<<RED<<"Não foi possível abrir os ficheiros necessários."<<RESET<<endl;
	}
}

// apagar tudo e adicionar aluno novo ao ficheiro alunos
void eliminar_adicionar_aluno(){
		ofstream fich_alunos("ficheiro_alunos.csv");
		if(! fich_alunos.is_open()){
			cout<<endl<<RED<<"Não foi possível abrir o ficheiro dos alunos."<<RESET<<endl;
		}
		ofstream temp_alunos("temporario_alunos.csv",ios::app);
		if(! temp_alunos.is_open()){
			cout<<endl<<RED<<"Não foi possível abrir o ficheiro temporário."<<RESET<<endl;
		}else{
			char op;
			cout<<endl;
			cout<<CIANO<<" - - A P A G A R - & - A D I C O N A R - -"<<RESET<<endl<<endl;
			cin.ignore();
			cout<<BOLD<<"Quer apagar o ficheiro alunos (Y/N)? "<<RESET<<endl;
			cin>>op;
			op = toupper(op);
			if(op == 'Y'){
				char op2;
				system("cls");
				remove("ficheiro_alunos.csv");	// apaga o ficheiro alunos
				rename("temporario_alunos.csv","ficheiro_alunos.csv");	// troca o nome do temp_alunos para fich_alunos
				cout<<endl<<BOLD<<"Quer adicionar um aluno novo (Y/N)? "<<RESET;
				cin>>op2;
				if(op == 'Y'){
					system("cls");
					cin.ignore();
					adicionar_aluno();
				}else if(op == 'N'){
					system("cls");
					cout<<endl<<RED<<"O ficheiro alunos está vazio!"<<RESET<<endl;
				}
			}else if(op == 'N'){
				cout<<endl<<RED<<"O ficheiro alunos não foi apagado."<<RESET<<endl;	
			}
		}
}

// menu estatísticas dos alunos
void estatisticas_alunos(){
	ifstream fich_alunos("ficheiro_alunos.csv");
	if(! fich_alunos.is_open()){
		cout<<RED<<"Não foi possível abrir o ficheiro alunos."<<RESET<<endl;
	}else if(fich_alunos.is_open()){
		char op;
		string linha;
		Aluno a1;
		int total_alunos = 0;
		float media_idades = 0;
		string idades;
		int soma_idades = 0;
		int mais_velho = 0;
		int mais_novo = 0;
		string id_maisvelho;
		string id_maisnovo;
		string nome_maisvelho;
		string nome_maisnovo;
		string dia_maisvelho;
		string dia_maisnovo;
		string mes_maisvelho;
		string mes_maisnovo;
		string ano_maisvelho;
		string ano_maisnovo;
		getline(fich_alunos,linha);
		while(getline(fich_alunos,linha)){
			istringstream ss(linha);
			getline(ss,a1.id,',');
			getline(ss,a1.nome,',');
			getline(ss,a1.aniversario.dia,'/');
			getline(ss,a1.aniversario.mes,'/');
			getline(ss,a1.aniversario.ano);
			total_alunos++;
			idades = a1.aniversario.ano;
			int soma_das_idades = stoi(idades);
			soma_idades += 2026 - soma_das_idades;
			if(a1.aniversario.ano >= ano_maisvelho){
				ano_maisvelho = a1.aniversario.ano;
				mais_velho = stoi(ano_maisvelho);
				id_maisvelho = a1.id;
				nome_maisvelho = a1.nome;
				dia_maisvelho = a1.aniversario.dia;
				mes_maisvelho = a1.aniversario.mes;
				ano_maisvelho = a1.aniversario.ano;
			}else if(a1.aniversario.ano <= ano_maisnovo){
				ano_maisnovo = a1.aniversario.ano;
				mais_novo = stoi(ano_maisnovo);
				id_maisnovo = a1.id;
				nome_maisnovo = a1.nome;
				dia_maisnovo = a1.aniversario.dia;
				mes_maisnovo = a1.aniversario.mes;
				ano_maisnovo = a1.aniversario.ano;
			}
		}
		media_idades = soma_idades / total_alunos;
		cin.ignore();
		cout<<endl<<CIANO<<" - - E S T A T Í S T I C A S - A L U N O S - -"<<RESET<<endl;
		cout<<BOLD<<" 1 -> Ver total de alunos"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Ver média das idades"<<RESET<<endl;
		cout<<BOLD<<" 3 -> Ver aluno mais velho"<<RESET<<endl;
		cout<<BOLD<<" 4 -> Ver aluno mais novo"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar à página anterior"<<RESET<<endl;
		cout<<BOLD<<" S -> Sair do programa"<<RESET<<endl;
		cout<<CIANO<<"- - - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
		cout<<" Insira a sua opção: "<<RESET;
		cin>>op;
		cin.ignore();
		op = toupper(op);
		
		switch(op){
			// opção 1 (total de alunos)
			case '1':
				cout<<BOLD<<" Total de alunos: "<<RESET<<total_alunos<<endl;
				break;
				
			// opção 2 (média de idades)	
			case '2':
				cout<<endl<<BOLD<<" Média das idades: "<<RESET<<media_idades<<endl;
				break;
			
			// opção 3 (aluno mais velho)	
			case '3':
				system("cls");
				cout<<endl<<YELLOW<<" « A L U N O - M A I S - V E L H O »"<<RESET<<endl;
				cout<<BOLD<<" ID aluno: "<<RESET<<id_maisvelho<<endl;
				cout<<BOLD<<" Nome: "<<RESET<<nome_maisvelho<<endl;
				cout<<BOLD<<" Data de nascimento: "<<RESET<<dia_maisvelho<<BOLD<<"/"<<RESET<<mes_maisvelho<<BOLD<<"/"<<RESET<<ano_maisvelho<<endl;
				break;
				
			// opção 4 (aluno mais novo)	
			case '4':
				system("cls");
				cout<<endl<<YELLOW<<" « A L U N O - M A I S - N O V O »"<<RESET<<endl;
				cout<<BOLD<<" ID aluno: "<<RESET<<id_maisnovo<<endl;
				cout<<BOLD<<" Nome: "<<RESET<<nome_maisnovo<<endl;
				cout<<BOLD<<" Data de nascimento: "<<RESET<<dia_maisnovo<<BOLD<<"/"<<RESET<<mes_maisnovo<<BOLD<<"/"<<RESET<<ano_maisnovo<<endl;
				break;
			
			// opção 'V' (voltar à página anterior)	
			case 'V':
				return;
				break;
				
			// opção 'S' (sair do programa)
			case 'S':
				cout<<endl<<GREEN<<"Fim do programa!"<<RESET<<endl;
				exit(0);
				break;
			
			// opção inválida	
			default:
				cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl;
				break;
		}
	}
}



// função para mostrar disciplinas (opção 1 do menu disciplinas)
void mostrar_disciplinas(){
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro."<<RESET<<endl;
	}else if(fich_disciplinas.is_open()){
		string linha;
		Disciplina d1;
		system("cls");
		cout<<endl;
		cout<<CIANO<<" - - M O S T R A R - D I S C I P L I N A S - -"<<RESET<<endl<<endl;
		while(getline(fich_disciplinas,linha)){
			istringstream ss(linha);
			getline(ss,d1.id,',');
			getline(ss,d1.nome,',');
			getline(ss,d1.professor,',');
			cout<<BOLD<<"  ID disciplina: "<<RESET<<d1.id<<endl;
			cout<<BOLD<<"  Disciplina: "<<RESET<<d1.nome<<endl;
			cout<<BOLD<<"  Professor: "<<RESET<<d1.professor<<endl;
			cout<<CIANO<<"---------------------------------------------"<<RESET<<endl;
		}
	}
}

// função para adicionar disciplina (opção 2 do menu disciplinas)
void adicionar_disciplina(){
	ofstream fich_disciplinas("ficheiro_disciplinas.csv", ios::app);
	if(! fich_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro das disciplinas."<<RESET<<endl;
		fich_disciplinas.close();
	}else if(fich_disciplinas.is_open()){
		string linha;
		Disciplina d1;
		Disciplina d2;
		bool ja_existe = false;
		cout<<endl;
		cout<<CIANO<<" - - A D I C I O N A R - D I S C I P L I N A - -"<<RESET<<endl;
		cout<<"     Preencha os seguintes campos"<<endl;
		cout<<BOLD<<" Nome da disciplina: "<<RESET;
		getline(cin,d1.nome);
		cout<<BOLD<<" ID da disciplina: "<<RESET;
		getline(cin,d1.id);
		cout<<BOLD<<" Professor: "<<RESET;
		getline(cin,d1.professor);
		ifstream fich_disciplinas_leitura("ficheiro_disciplinas.csv");
		while(getline(fich_disciplinas_leitura,linha)){
			istringstream ss(linha);
			getline(ss,d2.id,',');
			getline(ss,d2.nome,',');
			getline(ss,d2.professor,',');
			if(d1.id == d2.id){
				ja_existe = true;
				cout<<RED<<endl<<"Essa disciplina já existe."<<RESET<<endl;
			}
		}
		fich_disciplinas_leitura.close();
		if(ja_existe == false){
			fich_disciplinas<<d1.id<<",";
			fich_disciplinas<<d1.nome<<",";
			fich_disciplinas<<d1.professor<<endl;
			fich_disciplinas.close();
			fich_disciplinas.close();
		}
	}
}

// função para procurar disciplina (opção 3 do menu disciplinas)
void procurar_disciplina(){
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro das disciplinas."<<RESET<<endl;
	}else{
		bool encontrada = false;	// bool para indicar se a disciplina foi encontrada
		char opcao;
		cout<<endl;
		cout<<CIANO<<" - - P R O C U R A R - D I S C I P L I N A - -"<<RESET<<endl;
		cout<<BOLD<<" 1 -> Procurar pelo ID"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Procurar pelo nome"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar ao menu principal"<<RESET<<endl;
		cout<<CIANO<<" - - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
		cout<<BOLD<<" Insira a sua opção: "<<RESET<<endl;
		cin>>opcao;
		opcao = toupper(opcao);
		if(opcao == '1'){
			cin.ignore();
			string id_procurar;
			string linha;
			Disciplina d1;
			system("cls");
			cout<<endl<<BOLD<<" Insira o ID da disciplina: "<<RESET;
			getline(cin,id_procurar);
			while(getline(fich_disciplinas,linha)){
				istringstream ss(linha);
				getline(ss,d1.id,',');
				getline(ss,d1.nome,',');
				getline(ss,d1.professor,',');
				if(d1.id == id_procurar){
					encontrada = true;
					cout<<endl<<endl;
					cout<<BOLD<<GREEN<<" - - D I S C I P L I N A - E N C O N T R A D A - -"<<RESET<<endl<<endl;
					cout<<BOLD<<" ID disciplina: "<<RESET<<d1.id<<endl;
					cout<<BOLD<<" Disciplina: "<<RESET<<d1.nome<<endl;
					cout<<BOLD<<" Professor: "<<RESET<<d1.professor<<endl;
				}
			}
			if(encontrada == false){
				cout<<endl<<RED<<"A disciplina não foi encontrada!"<<RESET<<endl;
			}
		}else if(opcao == '2'){
			system("cls");
			Disciplina d1;
			string linha;
			string nome_procurar;
			cin.ignore();
			cout<<endl<<BOLD<<" Insira o nome da disciplina: "<<RESET;
			getline(cin,nome_procurar);
			while(getline(fich_disciplinas,linha)){
				istringstream ss(linha);
				getline(ss,d1.id,',');
				getline(ss,d1.nome,',');
				getline(ss,d1.professor,',');
				if(d1.nome == nome_procurar){
					encontrada = true;
					cout<<endl<<endl;
					cout<<BOLD<<GREEN<<" - - D I S C I P L I N A - E N C O N T R A D A - -"<<RESET<<endl<<endl;
					cout<<BOLD<<" ID disciplina: "<<RESET<<d1.id<<endl;
					cout<<BOLD<<" Disciplina: "<<RESET<<d1.nome<<endl;
					cout<<BOLD<<" Professor: "<<RESET<<d1.professor<<endl;
				}
			}
			if(encontrada == false){
				nome_procurar[0] = toupper(nome_procurar[0]);
				while(getline(fich_disciplinas,linha)){
					istringstream ss(linha);
					getline(ss,d1.id,',');
					getline(ss,d1.nome,',');
					getline(ss,d1.professor,',');
					if(d1.nome == nome_procurar){
						encontrada = true;
						cout<<endl<<endl;
						cout<<BOLD<<GREEN<<" - - D I S C I P L I N A - E N C O N T R A D A - -"<<RESET<<endl<<endl;
						cout<<BOLD<<" ID disciplina: "<<RESET<<d1.id<<endl;
						cout<<BOLD<<" Disciplina: "<<RESET<<d1.nome<<endl;
						cout<<BOLD<<" Professor: "<<RESET<<d1.professor<<endl;
					}
				}
			}
			if(encontrada == false){
				cout<<endl<<RED<<" A disciplina não foi encontrada!"<<RESET<<endl;
			}
		}else if(opcao == 'V'){
			system("cls");
			return;
		}
	}
}

// função para apagar disciplina (opção 4 do menu disciplinas)
void eliminar_disciplina(){
	int verificar_fich = 0;
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro disciplinas."<<RESET;
		verificar_fich++;
	}
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro inscrições."<<RESET;
		verificar_fich++;
	}
	ofstream temp_inscricoes("temporario_inscricoes.csv",ios::app);
	if(! temp_inscricoes.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro temporário inscroções."<<RESET;
		verificar_fich++;
	}
	ofstream temp_disciplinas("temporario_disciplinas.csv",ios::app);
	if(! temp_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro temporário disciplinas."<<RESET;
		verificar_fich++;
	}else if(verificar_fich == 0){
		bool disciplina_existe = false;
		string id_procurar;
		Disciplina d1;
		Inscricao i1;
		string linha_disciplinas;
		string linha_inscricoes;
		cout<<endl;
		cout<<endl<<CIANO<<" - - E L I M I N A R - D I S C I P L I N A - -"<<RESET<<endl<<endl;
		cout<<BOLD<<" Insira o ID da disciplina: "<<RESET;
		getline(cin,id_procurar);
		while(getline(fich_disciplinas,linha_disciplinas)){
			istringstream ss(linha_disciplinas);
			getline(ss,d1.id,',');
			getline(ss,d1.nome,',');
			getline(ss,d1.professor,',');
			if(d1.id == id_procurar){
				disciplina_existe = true;
				continue;
			}
			temp_disciplinas<<d1.id<<","<<d1.nome<<","<<d1.professor<<endl;
		}
		if(disciplina_existe == false){
			temp_disciplinas.close();
			fich_disciplinas.close();
			fich_inscricoes.close();
			temp_inscricoes.close();
			cout<<endl<<RED<<"Não existe nenhuma disciplina com esse ID."<<RESET<<endl;
		}else if(disciplina_existe == true){
			remove("ficheiro_disciplinas.csv");
			rename("temporario_disciplinas.csv","ficheiro_disciplinas.csv");
			while(getline(fich_inscricoes,linha_inscricoes)){
				istringstream ss(linha_inscricoes);
				getline(ss,i1.id_aluno,',');
				getline(ss,i1.id_disciplina,',');
				getline(ss,i1.nota_final,',');
				if(i1.id_disciplina == id_procurar){
					continue;
				}
				temp_inscricoes<<i1.id_aluno<<","<<i1.id_disciplina<<","<<i1.nota_final<<endl;
			}
			fich_disciplinas.close();
			temp_disciplinas.close();
			fich_inscricoes.close();
			temp_inscricoes.close();
		}
	}
}

void eliminar_adicionar_disciplina(){
	int verificar_fich = 0;
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		verificar_fich++;
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro disciplinas."<<RESET<<endl;
	}
	ofstream temp_disciplinas("temporario_disciplinas.csv",ios::app);
	if(! temp_disciplinas.is_open()){
		verificar_fich++;
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro temporário disciplinas."<<RESET<<endl;
	}else if(verificar_fich == 0){
		char opcao;
		cin.ignore();
		cout<<endl<<CIANO<<" - - A P A G A R - & - A D I C I O N A R - -"<<RESET<<endl<<endl;
		cout<<BOLD<<" Quer apagar todas as disciplinas (Y/N)? "<<RESET;
		cin>>opcao;
		opcao = toupper(opcao);
		if(opcao == 'Y'){
			temp_disciplinas.close();
			ofstream temp_disciplinas("temporario_disciplinas.csv",ios::app);
			remove("ficheiro_dsisciplinas.csv");
			rename("temporario_inscricoes.csv","ficheiro_inscricoes.csv");
			temp_disciplinas.close();
			cout<<endl<<endl<<RED<<"O ficheiro disciplinas foi eliminado com sucesso!"<<RESET<<endl;
		}else if(opcao == 'N'){
			cout<<endl<<RED<<"Cancelou a eliminação do ficheiro disciplinas."<<RESET<<endl;
		}
	}
}

// menu estatídticas das disciplinas
void estatisticas_disciplinas(){
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro disciplinas."<<RESET<<endl;
	}else if(fich_disciplinas.is_open()){
		string linha;
		Disciplina d1;
		int total_disciplinas = 0;
		int total_professores = 0;
		getline(fich_disciplinas,linha);
		while(getline(fich_disciplinas,linha)){
			istringstream ss(linha);
			getline(ss,d1.id,',');
			getline(ss,d1.nome,',');
			getline(ss,d1.professor,',');
			total_disciplinas++;
			total_professores++;
		}
		char op;
		cout<<endl<<endl<<CIANO<<" - - E S T A T Í S T I C A S - D I S C I P L I N A S - -"<<RESET<<endl;
		cout<<BOLD<<" 1 -> Total de disciplinas"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Total de professores"<<RESET<<endl;
		cout<<BOLD<<" 3 -> Disciplina com mais alunos"<<RESET<<endl;
		cout<<BOLD<<" 4 -> Disciplina com menos alunos"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar à página anterior"<<RESET<<endl;
		cout<<BOLD<<" S -> Sair do programa"<<RESET<<endl;
		cout<<CIANO<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
		cout<<BOLD<<" Insira a sua opção: "<<RESET;
		cin>>op;
		op = toupper(op);
		switch(op){
			case '1':
				cout<<endl<<BOLD<<" Total de disciplinas: "<<RESET<<total_disciplinas<<endl;
				break;
				
			case '2':
				cout<<endl<<BOLD<<" Total de professores: "<<RESET<<total_professores<<endl;
				break;
				
			case '3':
				system("cls");
				
				break;
				
			case '4':
				break;
				
			case 'V':
				return;
				break;
				
			case 'S':
				cout<<endl<<"Fim do programa!"<<endl;
				break;
				
			default:
				cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl;
				break;
		}
		system("pause");
	}
}

// função para mostrar inscrições (opção 1 do menu inscricoes)
void mostrar_inscricoes(){
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro inscrições."<<RESET<<endl;
		fich_inscricoes.close();
	}else if(fich_inscricoes.is_open()){
		string linha;
		Inscricao i1;
		cout<<endl;
		cout<<CIANO<<" - - M O S T R A R - I N S C R I Ç Õ E S - -"<<RESET<<endl<<endl;
		while(getline(fich_inscricoes,linha)){
			istringstream ss(linha);
			getline(ss,i1.id_aluno,',');
			getline(ss,i1.id_disciplina,',');
			getline(ss,i1.nota_final,',');
			cout<<BOLD<<"ID aluno: "<<RESET<<i1.id_aluno<<endl;
			cout<<BOLD<<"ID disciplina: "<<RESET<<i1.id_disciplina<<endl;
			cout<<BOLD<<"Nota final: "<<RESET<<i1.nota_final<<endl;
			cout<<CIANO<<"------------------------------"<<RESET<<endl;
		}
		fich_inscricoes.close();
	}
	
}

// função para procurar inscrição (opção 3 do menu inscricoes)
void procurar_inscricao(){
	int ficheiros = 0;
	ifstream fich_alunos("ficheiro_alunos.csv");
	if(! fich_alunos.is_open()){
		ficheiros++;
		fich_alunos.close();
	}
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		ficheiros++;
		fich_inscricoes.close();
	}
	ifstream fich_disciplinas("ficheiro_disciplinas.csv");
	if(! fich_disciplinas.is_open()){
		ficheiros++;
		fich_disciplinas.close();
	}
	if(ficheiros == 0){
		bool encontrado_alunos = false;
		bool encontrado_inscricoes = false;
		char opcao;
		cout<<endl;
		cout<<CIANO<<" - - P R O C U R A R - I N S C R I Ç Ã O - -"<<RESET<<endl<<endl;
		cout<<BOLD<<" 1 -> Procurar pelo nome do aluno"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Procurar pelo ID do aluno"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar ao início"<<RESET<<endl;
		cout<<CIANO<<" - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
		cin>>opcao;
		opcao = toupper(opcao);
		if(opcao == '1'){
			Inscricao i1;
			Inscricao i2;
			Aluno a1;
			string linha_alunos;
			string linha_inscricoes;
			string nome_procurar;
			string id_do_aluno;
			string line;
			cin.ignore();
			cout<<endl<<BOLD<<"Insira o nome do aluno: "<<RESET;
			getline(cin,nome_procurar);
			while(getline(fich_alunos,linha_alunos)){
				istringstream ss(linha_alunos);
				getline(ss,a1.id,',');
				getline(ss,a1.nome,',');
				getline(ss,a1.aniversario.dia,'/');
				getline(ss,a1.aniversario.mes,'/');
				getline(ss,a1.aniversario.ano,'/');
				if(a1.nome == nome_procurar){
					encontrado_alunos = true;
					while(getline(fich_inscricoes,linha_inscricoes)){
						getline(ss,i1.id_aluno,',');
						getline(ss,i1.id_disciplina,',');
						getline(ss,i1.nota_final,',');
						if(i1.id_aluno == a1.id){
							encontrado_inscricoes = true;
							id_do_aluno = i1.id_aluno;
						}
					}
				}
			}
			if(encontrado_inscricoes = true){
				system("cls");
				cout<<endl<<GREEN<<" - - I N S C R I Ç Ã O - E N C O N T R A D A - -"<<RESET<<endl<<endl;
				cout<<BLUE<<" - - A L U N O - -"<<RESET<<endl;
				cout<<BOLD<<" Nome: "<<RESET<<nome_procurar<<endl;
				cout<<BOLD<<" ID aluno: "<<RESET<<id_do_aluno<<endl<<endl;
				cout<<BLUE<<" - - D I S C I PL I N A S - -"<<RESET<<endl;
				while(getline(fich_inscricoes,line)){
					istringstream ss(line);
					getline(ss,i2.id_aluno,',');
					getline(ss,i2.id_disciplina,',');
					getline(ss,i2.nota_final,',');
					if(i2.id_aluno == id_do_aluno){
						string linha_disciplinas;
						Disciplina d1;
						while(getline(fich_disciplinas,linha_disciplinas)){
							istringstream ss(linha_disciplinas);
							getline(ss,d1.id,',');
							getline(ss,d1.nome,',');
							getline(ss,d1.professor,',');
							if(d1.id == i2.id_disciplina){
								cout<<BOLD<<" Disciplina: "<<RESET<<d1.nome<<endl;
								cout<<BOLD<<" ID disciplina: "<<RESET<<d1.id<<endl;
								cout<<BOLD<<" Professor: "<<RESET<<d1.professor<<endl;
								cout<<BLUE<<" - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
							}
						}
					}
				}
			}
			if(encontrado_inscricoes == false){
				cout<<endl<<RED<<" Não foi encontrada nenhuma inscrição."<<RESET<<endl;
			}
		}else if(opcao == '2'){
			string id_procurar;	// ID inserido para procurar
			Inscricao i1;
			Aluno a1;
			Disciplina d1;
			Inscricao inscricao_encontrado;
			Disciplina disciplina_encontrado;
			string linha_alunos;
			string linha_inscricoes;
			string linha_disciplinas;
			string nome_aluno;	// guarda o nome do aluno
			bool aluno_encontrado = false;
			bool inscricao_encontrada = false;
			cin.ignore();
			cout<<endl<<BOLD<<" Insira o ID do aluno: "<<RESET;
			getline(cin,id_procurar);
			while(getline(fich_alunos,linha_alunos));
			istringstream ss(linha_alunos);
			getline(ss,a1.id,',');
			getline(ss,a1.nome,',');
			getline(ss,a1.aniversario.dia,',');
			getline(ss,a1.aniversario.mes,',');
			getline(ss,a1.aniversario.ano,',');
			if(a1.id == id_procurar){
				aluno_encontrado = true;
				nome_aluno = a1.nome;
				while(getline(fich_inscricoes,linha_inscricoes)){
					istringstream ss(linha_inscricoes);
					getline(ss,i1.id_aluno,',');
					getline(ss,i1.id_disciplina,',');
					getline(ss,i1.nota_final,',');
					if(i1.id_aluno == id_procurar){
						inscricao_encontrada = true;
					}
				}
			}
			if(inscricao_encontrada == true){
				cout<<GREEN<<" - - I N S C R I Ç Ã O - E N C O N T R A D A - -"<<RESET<<endl<<endl;
				cout<<BLUE<<" - - A L U N O - -"<<RESET<<endl;
				cout<<BOLD<<" Nome: "<<RESET<<nome_aluno<<endl;
				cout<<BOLD<<" ID aluno: "<<RESET<<id_procurar<<endl<<endl;
				cout<<BLUE<<" - - D I S C I P L I N A S - -"<<RESET<<endl;
				while(getline(fich_inscricoes,linha_inscricoes)){
					istringstream ss(linha_inscricoes);
					getline(ss,inscricao_encontrado.id_aluno,',');
					getline(ss,inscricao_encontrado.id_disciplina,',');
					getline(ss,inscricao_encontrado.nota_final,',');
					if(inscricao_encontrado.id_aluno == id_procurar){
						while(getline(fich_disciplinas,linha_disciplinas)){
							istringstream ss(linha_disciplinas);
							getline(ss,disciplina_encontrado.id,',');
							getline(ss,disciplina_encontrado.nome,',');
							getline(ss,disciplina_encontrado.professor,',');
							if(disciplina_encontrado.id == inscricao_encontrado.id_disciplina){
								cout<<BOLD<<" Disciplina: "<<RESET<<endl;
								cout<<BOLD<<" ID disciplina: "<<RESET<<endl;
								cout<<BOLD<<" Professor: "<<RESET<<endl;
								cout<<BLUE<<" - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
							}
						}
					}
				}
			}
			if(inscricao_encontrada == false){
				cout<<endl<<RED<<" A inscrição não foi encontrada."<<RESET<<endl;
			}
		}else if(opcao == 'V'){
			system("cls");
			return;
		}	
	}else if(ficheiros > 0){
		cout<<endl<<RED<<"Não foi possível abrir os ficheiros necessários."<<RESET<<endl;
	}
}

// função para eliminar uma inscrição (opção 3 do menu inscrições)
void eliminar_inscricao(){
	bool inscricao_existe = false;
	int verificar_ficheiros = 0;
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		verificar_ficheiros++;
		cout<<RED<<"Não foi possível abrir o ficheiro inscrições."<<RESET<<endl;
		fich_inscricoes.close();
	}
	ofstream temp_inscricoes("temporario_inscricoes.csv",ios::app);
	if(! temp_inscricoes.is_open()){
		verificar_ficheiros++;
		cout<<RED<<"Não foi possível abrir o ficheiro temporário das inscrições."<<RESET<<endl;
		temp_inscricoes.close();
	}else if(verificar_ficheiros = 0){
		string linha;
		string id_procurar;
		Inscricao i1;
		cout<<endl;
		cout<<CIANO<<" - - E L I M I N A R - I N S C R I Ç Ã O - -"<<RESET<<endl<<endl;
		cout<<BOLD<<" Insira o ID do aluno: "<<RESET;
		getline(cin,id_procurar);
		while(getline(fich_inscricoes,linha)){
			istringstream ss(linha);
			getline(ss,i1.id_aluno,',');
			getline(ss,i1.id_disciplina,',');
			getline(ss,i1.nota_final,',');
			if(i1.id_aluno == id_procurar){
				inscricao_existe = true;
				continue;
			}
			temp_inscricoes<<i1.id_aluno<<","<<i1.id_disciplina<<","<<i1.nota_final<<endl;
		}
		fich_inscricoes.close();
		temp_inscricoes.close();
	}
}

void eliminar_adicionar_inscricao(){
	int verificar_ficheiros = 0;
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		verificar_ficheiros++;
		cout<<RED<<"Não foi possível abrir o ficheiro inscrições."<<RESET<<endl;
	}
	ofstream temp_inscricoes("temporario_inscricoes.csv",ios::app);
	if(! temp_inscricoes.is_open()){
		verificar_ficheiros++;
		cout<<RED<<"Não foi possível abrir o ficheiro temporário inscrições."<<RESET<<endl;
	}else if(verificar_ficheiros = 0){
		char opcao;
		cout<<endl<<endl;
		cout<<CIANO<<" - - A P A G A R - T U D O - & - A D I C I O N A R - N O V O - -"<<RESET<<endl<<endl;
		cout<<BOLD<<" Quer apagar todas as inscrições (Y/N)? "<<RESET;
		cin>>opcao;
		if(opcao == 'Y'){
			char op;
			remove("ficheiro_inscricoes.csv");
			rename("temporario_inscricoes.csv","ficheiro_inscricoes.csv");
			temp_inscricoes.close();
			cout<<endl<<BOLD<<"Quer adicionar uma inscrição ao ficheiro (Y/N)? "<<RESET;
			cin>>op;
			if(op == 'Y'){
				system("cls");
				Inscricao i1;
				string linha;
				cout<<endl<<CIANO<<" - - N O V A - I N S C R I Ç Ã O - -"<<RESET<<endl;
				cout<<"                 preencha os seguintes campos"<<endl<<endl;
				cout<<BOLD<<" ID aluno: "<<RESET;
				getline(cin,i1.id_aluno);
				cout<<BOLD<<" ID disciplina: "<<RESET;
				getline(cin,i1.id_disciplina);
				cout<<BOLD<<" Nota final: "<<RESET;
				getline(cin,i1.nota_final);
				ofstream fich_inscricoes("ficheiro_inscricoes.csv",ios::app);
				fich_inscricoes<<"ID_aluno,ID_disciplina,Nota Final"<<endl;
				fich_inscricoes<<i1.id_aluno<<","<<i1.id_disciplina<<","<<i1.nota_final<<endl;
				fich_inscricoes.close();
			}else if(op == 'N'){
				cout<<endl<<GREEN<<"O ficheiro inscrições está vazio."<<RESET<<endl;
				fich_inscricoes.close();
				temp_inscricoes.close();
			}
		}
	}
}

void estatisticas_inscricoes(){
	ifstream fich_inscricoes("ficheiro_inscricoes.csv");
	if(! fich_inscricoes.is_open()){
		cout<<endl<<RED<<"Não foi possível abrir o ficheiro inscrições."<<RESET<<endl;
	}else if(fich_inscricoes.is_open()){
		string linha;
		Inscricao i1;
		int total_inscricoes = 0;
		while(getline(fich_inscricoes,linha)){
			istringstream ss(linha);
			getline(ss,i1.id_aluno,',');
			getline(ss,i1.id_disciplina,',');
			getline(ss,i1.nota_final,',');
			total_inscricoes++;
		}
		char op;
		cout<<endl;
		cout<<CIANO<<" - - E S T A T Í S T I C A S - I N S C R I Ç Õ E S - -"<<RESET<<endl;
		cout<<BOLD<<" 1 -> Total de inscrições"<<RESET<<endl;
		cout<<BOLD<<" 2 -> Aluno inscrito em mais disciplinas"<<RESET<<endl;
		cout<<BOLD<<" 3 -> Aluno inscrito em menos disciplinas"<<RESET<<endl;
		cout<<BOLD<<" V -> Voltar à página anterior"<<RESET<<endl;
		cout<<BOLD<<" S -> Sair do programa"<<RESET<<endl;
		cout<<CIANO<<"-------------------------------------------------------"<<RESET<<endl;
		cout<<" Insira a sua opção: ";
		cin>>op;
		op = toupper(op);
		switch(op){
			
			// opção 1 (total de disciplinas)
			case '1':
				cout<<endl<<BOLD<<" Total de disciplinas: "<<RESET<<total_inscricoes<<endl;
				break;
				
			// opção 2 (aluno inscrito em mais disciplinas)
			case '2':
				system("cls");
				break;
			
			// opção 3 (aluno inscrito em menos disciplinas)	
			case '3':
				system("cls");
				break;
			
			// opção 'V' (voltar à página anterior)
			case 'V':
				
				return;
				break;
			
			// opção 'S' (sair do programa)	
			case 'S':
				cout<<endl<<GREEN<<"Fim do programa!"<<RESET<<endl;
				exit(0);
				break;
			
			// opção inválida	
			default:
				cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl;
				break;
		}
	}
}

// menu estatísticas
void menu_estatisticas(){
	char op;
	system("cls");
	cout<<endl;
	cout<<YELLOW<<" - - M E N U - E S T A T Í S T I C A S - -"<<RESET<<endl;
	cout<<CIANO<<" 1 -> Estatísticas dos alunos"<<RESET<<endl;
	cout<<CIANO<<" 2 -> Estatísticas das disciplinas"<<RESET<<endl;
	cout<<CIANO<<" 3 -> Estatísticas das inscrições"<<RESET<<endl;
	cout<<CIANO<<" V -> Voltar à página anterior"<<RESET<<endl;
	cout<<CIANO<<" S -> Sair"<<RESET<<endl;
	cout<<YELLOW<<"- - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
	cout<<BOLD" Insira a opção: "<<RESET;
	cin>>op;
	switch(op){
		
		// opção 1 (estatísticas dos alunos)
		case '1':
			system("cls");
			estatisticas_alunos();
			break;
			
		// opção 2 (estatísticas das disciplinas)	
		case '2':
			system("cls");
			estatisticas_disciplinas();
			break;
		
		// opção 3 (estatísticas das inscrições)	
		case '3':
			system("cls");
			estatisticas_inscricoes();
			break;
		
		// opção 'V' (voltar à página anterior)
		case 'V':
			system("cls");
			return;
			break;
		
		// opção 'S' (sair do programa)	
		case 'S':
			cout<<endl<<GREEN<<" Fim do programa!"<<RESET<<endl;
			system("pause");
			exit(0);
			break;
		
		// opção inválida	
		default:
			cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl;
			break;
	}
	system("pause");
}


// menu dos alunos (opção 1 do menu principal)
void menu_alunos(){
	char op;
	system("cls");
	cout<<endl;
	cout<<YELLOW<<" - -  M E N U - D O S - A  L U N O S - -"<<RESET<<endl;
	cout<<CIANO<<" 1 -> Mostrar alunos"<<RESET<<endl;
	cout<<CIANO<<" 2 -> Adicionar novo aluno"<<RESET<<endl;
	cout<<CIANO<<" 3 -> Procurar um aluno"<<RESET<<endl;
	cout<<CIANO<<" 4 -> Eliminar um aluno"<<RESET<<endl;
	cout<<CIANO<<" 5 -> Apagar tudo e inserir novo"<<RESET<<endl;
	cout<<CIANO<<" V -> Voltar à página anterior"<<RESET<<endl;
	cout<<CIANO<<" S -> Sair do programa"<<RESET<<endl;
	cout<<YELLOW<<" - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
	cout<<BOLD<<" insira a opção: "<<RESET;
	cin>>op;
	op = toupper(op);
	
	switch(op){
		
		// opção 1 (mostrar os alunos)
		case '1':
			system("cls");
			mostrar_alunos();
			break;
		
		// opção 2 (adicionar um aluno novo)	
		case '2':
			system("cls");
			adicionar_aluno();
			break;
		
		// opção 3 (procurar um aluno)
		case '3':
			system("cls");
			procurar_aluno();
			break;
			
		// opção 4 (eliminar um aluno)
		case '4':
			system("cls");
			eliminar_aluno();
			break;
			
		// opção 5 (eliminar e adicionar aluno)
		case '5':
			system("cls");
			eliminar_adicionar_aluno();
			break;
				
		// opção 'V' (voltar à página anterior)
		case 'V':
			system("cls");
			return;
			break;
		
		// opção 'S' (sair do programa)
		case 'S':
			cout<<endl<<"Fim do programa!"<<endl;
			exit(0);
			break;
			
		// opção inválida
		default:
			cout<<endl<<RED<<"Opção inválida!"<<endl<<endl;
			break;
		}
	system("pause");
}

// menu das disciplinas (opção 2 do menu principal)
void menu_disciplinas(){
	char op;
	system("cls");
	cout<<endl;
	cout<<YELLOW<<" - -  M E N U - D A S - D I S C I P L I N A S - -"<<RESET<<endl;
	cout<<CIANO<<" 1 -> Mostrar disciplinas"<<RESET<<endl;
	cout<<CIANO<<" 2 -> Adicionar nova disciplina"<<RESET<<endl;
	cout<<CIANO<<" 3 -> Procurar uma disciplina"<<RESET<<endl;
	cout<<CIANO<<" 4 -> Eliminar uma disciplina"<<RESET<<endl;
	cout<<CIANO<<" 5 -> Apagar tudo e inserir nova"<<RESET<<endl;
	cout<<CIANO<<" V -> Voltar à página anterior"<<RESET<<endl;
	cout<<CIANO<<" S -> Sair do programa"<<RESET<<endl;
	cout<<YELLOW<<" - - - - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
	cout<<BOLD<<" Insira a opção: "<<RESET;
	cin>>op;
	op = toupper(op);
	
	switch(op){
		
		// opção 1 (mostrar disciplinas)	
		case '1':
			system("cls");
			mostrar_disciplinas();
			break;
		
		// opção 2 (adicionar disciplina)	
		case '2':
			system("cls");
			adicionar_disciplina();
			break;
		
		// opção 3 (procurar disciplina)	
		case '3':
			system("cls");
			procurar_disciplina();
			break;
		
		// opção 4 (eliminar disciplina)	
		case '4':
			system("cls");
			eliminar_disciplina();
			break;
		
		// opção 5 (eliminar e adicionar disciplina)
		case '5':
			system("cls");
			eliminar_adicionar_disciplina();
			break;
		
		// opção 'V' (voltar à página anterior)	
		case 'V':
			system("cls");
			return;
			break;
		
		// opção 'S' (sair do programa)	
		case 'S':
			cout<<"Fim do programa!"<<endl;
			exit(0);	// é uma coisa nova que aprendi
			break;
		
		// opção inválida	
		default:
			cout<<endl<<RED<<"Opção inválida!"<<endl<<endl;
			break;
	}
	system("pause");
}

// menu das inscrições (opção 3 do menu principal)
void menu_inscricoes(){
	char op;
	system("cls");
	cout<<endl;
	cout<<YELLOW<<" - -  M E N U - D A S - I NS C R I Ç Õ E S - -"<<RESET<<endl;
	cout<<CIANO<<" 1 -> Mostrar inscrições"<<RESET<<endl;
	cout<<CIANO<<" 2 -> Adicionar nova inscrição"<<RESET<<endl;
	cout<<CIANO<<" 3 -> Procurar uma inscrição"<<RESET<<endl;
	cout<<CIANO<<" 4 -> Eliminar uma inscrição"<<RESET<<endl;
	cout<<CIANO<<" 5 -> Apagar tudo e inserir nova"<<RESET<<endl;
	cout<<CIANO<<" V -> Voltar à página anterior"<<endl;
	cout<<CIANO<<" S -> Sair do programa"<<RESET<<endl;
	cout<<YELLOW<<" - - - - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
	cout<<BOLD<<" Insira a sua opção: "<<RESET;
	cin>>op;
	op = toupper(op);
	
	switch(op){
		case '1':	// mostrar as inscrições todas
			system("cls");
			mostrar_inscricoes();
			break;
			
		case '2':	// adicionar uma inscrição nova
			system("cls");
			adicionar_inscricao();
			break;
			
		case '3':	// procurar uma inscrição
			system("cls");
			procurar_inscricao();
			break;
		
		case '4':	// eliminar uma inscrição
			system("cls");
			eliminar_inscricao();
			break;
			
		case '5':	// eliminar e meter uma inscrição nova
			system("cls");
			eliminar_adicionar_inscricao();
			break;

		case 'V':	// voltar ao menu principal
			system("cls");
			return;
			break;
			
		case 'S':	// sair do programa
			cout<<"Fim do programa!"<<endl;
			exit(0);	// é uma coisa nova que aprendi que fecha o programa
			break;
		
		default:	// opção inválida
			cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl<<endl;
			break;
	}
	system("pause");
}

// menu principal
void menu_principal(char op){
	system("cls");
	cout<<endl;
	cout<<BLUE<<" - -  M E N U - P R I N C I P A L - -"<<RESET<<endl;
	cout<<YELLOW<<" 1 -> Menu alunos"<<RESET<<endl;
	cout<<YELLOW<<" 2 -> Menu disciplinas"<<RESET<<endl;
	cout<<YELLOW<<" 3 -> Menu inscrições"<<RESET<<endl;
	cout<<YELLOW<<" 4 -> Ver estatísticas"<<RESET<<endl;
	cout<<YELLOW<<" S -> Sair do programa"<<RESET<<endl;
	cout<<BLUE<<" - - - - - - - - - - - - - - - - - - -"<<RESET<<endl;
	cout<<BOLD<<" Insira a sua opção: "<<RESET;
	cin>>op;
	op = toupper(op);
	
	switch(op){
		case '1':	// menu alunos
			menu_alunos();
			break;
			
		case '2':	// menu disciplinas
			menu_disciplinas();
			break;
			
		case '3':	// menu inscrições
			menu_inscricoes();
			break;
		
		case '4':	// menu estatísticas
			menu_estatisticas();
			break;
		
		case 'S':	// sair
			cout<<"Fim do programa!"<<endl;
			exit(0);	// é uma coisa nova que aprendi para fechar o programa
			break;
			
		default:	// opção inválida
			cout<<endl<<RED<<"Opção inválida!"<<RESET<<endl<<endl;
			break;
	}
	system("pause");
}

int main(){
	setlocale(LC_ALL,"portuguese");
	char opcao;
	while(opcao != 'S'){
		menu_principal(opcao);
	}
}
