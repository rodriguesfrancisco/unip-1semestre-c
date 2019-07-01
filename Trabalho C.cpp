#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int cadastroRecurso();
void exibirRecursos(int recursos);
void solicitarRecurso(int recursos, int cadastrados);
void cadastroProfessores(int cadastrados);
int validaEscolha(int escolha, int recursosDisponiveis);
void imprimirSolicitacao(int recursosDisponiveis, int recursosEscolhidos);
char respostaOpcao();
bool validaOpcao(char opcao);

char nomeRecurso[16][120], caracteristicasRecurso[16][120], nomeProfessor[10][120], emailProfessor[10][120], telefone[120];
char predio[50][120], dataUso[50][120], horaIni[50][120], horaFin[50][120];
int idTipoRecurso[30], matricula[50], qtdRecurso[30], solicitacao[50], sala[50];

main(){
	int escolha, cadastrados, contRecursos;
	char opcao;
	bool repete;

	cadastrados = 0; contRecursos = 0;
	do{
        printf("(1) - Cadastro de recursos \n");
		printf("(2) - Solicitacao de recursos \n");
		printf("(3) - Listar solicitacoes \n");
		printf("(4) - Sair \n");
		printf("Digite uma opcao: \n");
		scanf("%d", &escolha);

		switch (escolha) {
			case 1:
				contRecursos = cadastroRecurso();
                break;

			case 2:
			    if (contRecursos > 0){
                    solicitarRecurso(contRecursos, cadastrados);
			    } else{
                    printf("Nao ha recursos cadastrados. \n");
			    }
				break;

			case 3:
				printf("Sistema em desenvolvimento!\n");
				break;

			case 4:
				repete = false;
				break;

			default:
				printf("Nao existe essa opcao! \n");
		}
		setbuf(stdin, NULL);
		if (escolha > 0 && escolha < 4){
            opcao = respostaOpcao();
            repete = validaOpcao(opcao);
		}
	} while (repete == true);
}

int cadastroRecurso(){
	int totalRecursos;
	char opcao;

	printf("--------Cadastre seus recursos-------- \n");

	totalRecursos = 0;
	do{
        printf("************************************* \n");
		printf("Digite o id do recurso: \n");
        scanf("%d", &idTipoRecurso[totalRecursos]);
        setbuf(stdin, NULL);
		printf("Digite o nome do recurso: \n");
		gets(nomeRecurso[totalRecursos]);
		printf("Digite a quantidade de recursos : \n");
		scanf("%d", &qtdRecurso[totalRecursos]);
		setbuf(stdin, NULL);
		printf("Descreva o recurso %s: \n", nomeRecurso[totalRecursos]);
		gets(caracteristicasRecurso[totalRecursos]);
		printf("Quer cadastrar um novo recurso? \n");
        scanf("%c", &opcao);
		totalRecursos ++;
	} while(opcao == 'S' || opcao =='s');
    return totalRecursos;
}

void exibirRecursos(int recursos){
    int i;
    printf("--------Recursos disponiveis-------- \n");
    for(i=0; i<recursos; i++){
        printf("************************************* \n");
        printf("Recurso %d : %s \n", idTipoRecurso[i], nomeRecurso[i]);
        printf("Quantidade de recursos: %d \n", qtdRecurso[i]);
        printf("Caracteristicas do recurso: %s \n", caracteristicasRecurso[i]);
        printf("************************************* \n");
        printf("\n\n");
    }
}

void cadastroProfessores(int cadastrados){
	int identificador, totalProfessores;
	char resposta;

	totalProfessores = cadastrados;
	printf("--------Cadastro de Professores--------\n");
	printf("Digite sua matricula(Apenas numeros): \n");
    scanf("%d", &identificador);
	matricula[totalProfessores] = identificador;
	printf("Digite o seu nome: \n");
	scanf(" %s", &nomeProfessor[totalProfessores]);
    setbuf(stdin, NULL);
	printf("Digite o seu e-mail \n");
	gets(emailProfessor[totalProfessores]);
    setbuf(stdin, NULL);
	printf("Digite seu telefone: \n");
    scanf("%d", &telefone[totalProfessores]);

}

void solicitarRecurso(int recursos, int cadastrados){
	char resposta;
	int i, escolha, cont, recursosEscolhidos, recursosDisponiveis, totalPessoas;
	bool encontrou;

    recursosDisponiveis = recursos;
	//Listagem de recursos
	i = 0; recursosEscolhidos = 0;

    exibirRecursos(recursosDisponiveis);
    printf("Escolha o tipo de recurso: \n");
    scanf("%d", &escolha);
    escolha = validaEscolha(escolha, recursosDisponiveis);
    recursosEscolhidos++;
    setbuf(stdin, NULL);
    solicitacao[i] = escolha;
    totalPessoas = cadastrados;
	cadastroProfessores(totalPessoas);
	setbuf(stdin, NULL);
    printf("Digite o predio: (A/B/C/D/E) \n");
    gets(predio[i]);
    setbuf(stdin, NULL);
    printf("Digite a sala: \n");
    scanf("%d", &sala[i]);
    setbuf(stdin, NULL);
    printf("Digite a data do uso: \n");
    gets(dataUso[i]);
    setbuf(stdin, NULL);
    printf("Digite a hora inicial do uso: \n");
    gets(horaIni[i]);
    setbuf(stdin, NULL);
    printf("Digite a hora final do uso: \n");
    gets(horaFin[i]);
    setbuf(stdin, NULL);
	imprimirSolicitacao(recursosDisponiveis, recursosEscolhidos);
}

int validaEscolha(int escolha, int recursosDisponiveis){
    int cont;
    bool encontrou;

    do{
        cont = 0;
        do{
            if (escolha == idTipoRecurso[cont]){
                encontrou = true;
            } else{
                encontrou = false;
                cont++;
            }
        } while(cont < recursosDisponiveis && encontrou == false);
        if (encontrou == false){
            printf("Recurso nao encontrado! Escolha outro: \n");
            scanf("%d", &escolha);
            setbuf(stdin, NULL);
        }
    } while (encontrou == false);

    return escolha;
}

void imprimirSolicitacao(int recursosDisponiveis, int recursosEscolhidos){
	char date[9], time[9];
    int i, contador;
    bool encontrou = false;

    i = 0;
    printf("--------Comprovante de solicitacao do professor %s !-------- \n", nomeProfessor[i]);
    for (contador = 0; contador < recursosDisponiveis; contador++){
        if(solicitacao[i] == idTipoRecurso[contador]){
            printf("Identidade do recurso escolhido: %d \n", idTipoRecurso[contador]);
            printf("Recurso - %s \n", nomeRecurso[contador]);
            printf("Caracteristicas- %s \n", caracteristicasRecurso[contador]);
        }
    }
    _strdate(date);
    printf("Data da solicitacao : %s\n", date);
    _strtime(time);
    printf("Hora da solicitacao: %s\n", time);
    printf("Predio: %s\n", predio[i]);
    printf("Sala: %d\n", sala[i]);
    printf("Data do uso: %s\n", dataUso[i]);
    printf("Hora inicial: %s\n", horaIni[i]);
    printf("Hora final do uso: %s\n", horaFin[i]);
}

char respostaOpcao(){
    char resposta;

    printf("Quer escolher uma nova opcao? Digite S para continuar e N para sair \n");
    scanf("%c", &resposta);

    return resposta;
}

 bool validaOpcao(char opcao){
    bool repetir;

    if (opcao == 'S' || opcao == 's'){
        repetir = true;
    } else{
        repetir = false;
    }

    return repetir;
 }
