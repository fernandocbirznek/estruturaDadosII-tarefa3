#include<stdio.h>
#include<stdlib.h>

void menu() {
	printf("\nEscolha uma das opcoes:\n");
	printf("1) Criar Lista;        2) Liberar Lista;      3) Inserir item;\n");
	printf("4) Consultar horario; 5) Consultar nome;  6) valor superior ao informado (ceiling);\n");
	printf("7) valor inferior ao informado (floor);   8) valor escolhido (select)\n");
	printf("9) valor minimo (min); 10) valor maximo (max) 11) valores entrei ntervalo (keys)\n");
}

typedef struct Bloco
{
	int hora;
	int min;
	int seg;
	char nome[20];
	struct Bloco *prox;
} Nodo;

typedef struct Header {
	int totalElementos;
	Nodo *inicio, *final;
} Cabecalho;

Nodo* Cria_Nodo() //aloca memória para o nodo
{
	Nodo *p;
	p = (Nodo*) malloc(sizeof(Nodo)); //alocação de memoria na área de heap em tempo de execução. Sizeof calcula o tamanho do que ta passando 
	if(!p)
	{
		printf("Problema de alocação");
		exit(0);
	}
	return p; //retorna o conteúdo de p (dado e prox) endereço 500
}

// 1) Criar lista
void inicializa_lista(Cabecalho *lista)//inicializa a lista, o **N = endereço que ocupa     N* = guarda o endereço que guarda o dado
{
	lista->totalElementos = 0;
	lista->inicio = NULL;
	lista->final = NULL;
}

// 2) LIBERAR LISTA
void libera_lista(Cabecalho *N){
    if(N != NULL){
        Nodo *novo;
        while(N->inicio != NULL){
            novo = N->inicio;
            N->inicio = N->inicio->prox;
            free(novo);
        }
        //free(N);
        printf("\nLista liberada\n"); 
    }  
}

// COMPARAR TEMPO
int comparar_tempo(Nodo *atual, Nodo *novo) {
	if(atual->hora > novo->hora)
		return 1;
	if(atual->hora < novo->hora)
		return 0;
	if(atual->min > novo->min)
		return 1;
	if(atual->min < novo->min)
		return 0;
	if(atual->seg > novo->seg)
		return 1;
	if(atual->seg < novo->seg)
		return 0;
	return 1;
}

// VALIDAR TEMPO
int validar_tempo(int hora, int min, int seg) {
	if(hora < 0 || hora > 23 || min < 0 || min > 59 || seg < 0 || seg > 59)
		return 1;
	return 0;
}

// INSERIR UM ITEM
void insere_item_lista(Cabecalho *N)
{
	Nodo *novo;
	novo = Cria_Nodo();
	int hora, min, seg, validar = 1;
	
	while(validar) {
		fflush(stdin);
		printf("\nInforme o valor a ser inserido na lista: \nNome: ");
		gets(novo->nome);	
		printf("\nInforme o valor da hora: ");
		scanf("%d", &hora);
		printf("\nInforme o valor dos minutos: ");
		scanf("%d", &min);
		printf("\nInforme o valor dos segundos: ");
		scanf("%d", &seg);
		validar = validar_tempo(hora, min, seg);
		if(validar)
			printf("\nHora somente entre 0 e 23, minutos entre 0 e 59 e segundos entre 0 e 59");
	}
	
	novo->hora = hora;
	novo->min = min;
	novo->seg = seg;
	
	if(N->inicio == NULL) {
		novo->prox = NULL;
		N->inicio = novo;
		N->final = novo;
	} else {
		Nodo *ant, *atual = N->inicio;
		int resultado;
		while (atual != NULL) {
			resultado = comparar_tempo(atual, novo);
			if(resultado == 1) {
				if(atual == N->inicio) {
					N->inicio = novo;
					novo->prox = atual;
				} else {
					ant->prox = novo;
					novo->prox = atual;
				}
				break;
			}
			ant = atual;
			atual = atual->prox;
			if(atual == NULL) {
				N->final = novo;
				ant->prox = novo;
				novo->prox = NULL;
			}
		}
		N->totalElementos++;
	}
	printf("\nItem inserido :) \n");
}

// CONSULTA HORARIO
void consulta_horario(Cabecalho *N) {
    Nodo *atual = N->inicio;
    int hora, min, seg, validar = 1;
	
	while(validar) {
		fflush(stdin);	
		printf("\nInforme o valor da hora: ");
		scanf("%d", &hora);
		printf("\nInforme o valor dos minutos: ");
		scanf("%d", &min);
		printf("\nInforme o valor dos segundos: ");
		scanf("%d", &seg);
		validar = validar_tempo(hora, min, seg);
		if(validar)
			printf("\nHora somente entre 0 e 23, minutos entre 0 e 59 e segundos entre 0 e 59");
	}
	
    while(atual != NULL){
    	if(atual->hora == hora && atual->min == min && atual->seg == seg){
    		printf("Na cidade com esse horario eh: %s", atual->nome);
    		return;
		}
    	atual = atual->prox;
    }
    printf("Nao existe cidade com esse horario");
}

// CONSULTA NOME
void consulta_nome(Cabecalho *N) {
    Nodo *atual = N->inicio;
    char nome[20];

	fflush(stdin);	
	printf("\nInforme o nome para buscar: ");
	gets(nome);

    while(atual != NULL){
    	if(atual->nome == nome){
    		printf("O horario da cidade com esse nome eh: %d:%d:%d", atual->hora, atual->min, atual->seg);
    		return;
		}
    	atual = atual->prox;
    }
    printf("Nao existe cidade com esse nome");
}

// CONSULTA VALOR SUPERIOR (CEILING) OU INFERIOR (FLOOR)    SE CHAVE == TRUE CALCULO O FLOOR
void valor_ceiling(Cabecalho *N, bool chave) {
    Nodo *ant, *atual = N->inicio;
    int hora, min, seg, validar = 1;
    
    while(validar) {
		fflush(stdin);	
		printf("\nInforme o valor da hora: ");
		scanf("%d", &hora);
		printf("\nInforme o valor dos minutos: ");
		scanf("%d", &min);
		printf("\nInforme o valor dos segundos: ");
		scanf("%d", &seg);
		validar = validar_tempo(hora, min, seg);
		if(validar)
			printf("\nHora somente entre 0 e 23, minutos entre 0 e 59 e segundos entre 0 e 59");
	}
	
	if(chave) {
		while(atual != NULL){
	    	if(atual->hora >= hora && atual->min >= min && atual->seg >= seg){
	    		if(ant == NULL) {
	    			printf("Nao existe horario abaixo desse citado");
	    			return;
				}
	    		printf("O tempo abaixo do citado (%d:%d:%d) eh: %d:%d:%d", hora, min, seg, ant->hora, ant->min, ant->seg);
	    		return;
			}
			ant = atual;
	    	atual = atual->prox;
	    }
	    printf("Nao existe horario abaixo desse citado");
	    return;
	}
	
    while(atual != NULL){
    	if(atual->hora >= hora && atual->min >= min && atual->seg >= seg){
    		printf("O tempo acima do citado (%d:%d:%d) eh: %d:%d:%d", hora, min, seg, atual->hora, atual->min, atual->seg);
    		return;
		}
    	atual = atual->prox;
    }
    printf("Nao existe horario acima desse citado");
}

int comparar_inf_sup(Nodo *atual, int horaSup, int minSup, int segSup, int horaInf, int minInf, int segInf) {
	int validar = 0;
	while(true) {
		if(atual->hora > horaInf)
			break;
		if(atual->hora < horaInf)
			return 0;
		if(atual->min > minInf)
			break;
		if(atual->min < minInf)
			return 0;
		if(atual->seg > segInf)
			break;
		if(atual->seg < segInf)
			return 0;
		break;
	}
	validar++;
	while(true) {
		if(atual->hora < horaSup)
			break;
		if(atual->hora > horaSup)
			return 0;
		if(atual->min < minSup)
			break;
		if(atual->min > minSup)
			return 0;
		if(atual->seg < segSup)
			break;
		if(atual->seg > segSup)
			return 0;
		break;
	}
	validar++;
	return validar;
}

// VALORES ENTRE UM INTERVALO (KEYS)
void valor_intervalo(Cabecalho *N, int horaSup, int minSup, int segSup, int horaInf, int minInf, int segInf) {
    Nodo *atual = N->inicio;
    int validar;
	while(atual != NULL){
		validar = comparar_inf_sup(atual, horaSup, minSup, segSup, horaInf, minInf, segInf);
    	if(validar == 2) {
    		printf("\n%d:%d:%d\n", atual->hora, atual->min, atual->seg);
		}
    	atual = atual->prox;
    }
}

// CONSULTAR HORARIO POR VALOR (SELECT)
void valor_escolhido(Cabecalho *N) {
    Nodo *atual = N->inicio;
    int valor, validar = 1, contador = 0;
    
    while(validar) {
		fflush(stdin);	
		printf("\nInforme um valor para buscarmos um horario ");
		scanf("%d", &valor);
		if(valor >= 0)
			validar = 0;
		if(validar)
			printf("\nSomente valores entre acima ou igual a zero\n");
	}

    while(atual != NULL){
    	if(contador == valor){
    		printf("O tempo escolhido eh: %d:%d:%d", atual->hora, atual->min, atual->seg);
    		return;
		}
		contador++;
    	atual = atual->prox;
    }
    printf("Nao existe horario acima desse citado");
}

// VALOR MINIMO E MAXIMO
void valor_min_max(Cabecalho *N, bool chave) {
	if (chave) {
		Nodo *atual = N->inicio;
		printf("O tempo minimo eh: %d:%d:%d", atual->hora, atual->min, atual->seg);
		return;
	}
	Nodo *atual = N->final;
	printf("O tempo maximo eh: %d:%d:%d", atual->hora, atual->min, atual->seg);
	return;
}

// IMPRIMIR LISTA
void imprime_lista(Cabecalho *N)
{
	Nodo *novo = N->inicio;
	if(N == NULL || N->inicio == NULL)
		printf("\n A lista está vazia!!");
	else
	{
		printf("\n   Horario   |   Cidade   \n");
		while(novo != NULL){
	        printf("\n   %d:%d:%d   |   %s   \n", novo->hora, novo->min, novo->seg, novo->nome);
        	novo = novo->prox;
    	}
	}
}

int main()
{
	Cabecalho MyList;
	int opcao, valor, retorno, hora, min, seg;
	char nome[20];
	do{
		menu();
		scanf("%d", &opcao);
		switch(opcao)
		{
			
			
			printf("4) Consultar horario; 5) Consultar nome;  6) valor superior ao informado (ceiling);\n");
	printf("7) valor inferior ao informado (floor);   8) valor escolhido (select)\n");
	printf("9) valor minimo (min); 10) valor maximo (max) 11) valores entre intervalo (keys)\n");
			
			
			case 1:
				inicializa_lista(&MyList); //inicializa a lista envia a lista que quero
				printf("\nLista criada lol\n");
				break;
			case 2:
				libera_lista(&MyList);
				break;
			case 3:
				insere_item_lista(&MyList);
				break;
			case 4:
				consulta_horario(&MyList);
				break;
			case 5:
				consulta_nome(&MyList);
				break;
			case 6:
				valor_ceiling(&MyList, false);
				break;
			case 7:
				valor_ceiling(&MyList, true);
				break;
			case 8:
				valor_escolhido(&MyList);
				break;
			case 9:
				valor_min_max(&MyList, true);
				break;
			case 10:
				valor_min_max(&MyList, false);
				break;
			case 11:
				{
					int validar = 1, horaInf, minInf, segInf, horaSup, minSup, segSup;
					while(validar) {
						fflush(stdin);	
						printf("\nInforme o valor da hora inferior: ");
						scanf("%d", &horaInf);
						printf("\nInforme o valor dos minutos inferior: ");
						scanf("%d", &minInf);
						printf("\nInforme o valor dos segundos inferior: ");
						scanf("%d", &segInf);
						validar = validar_tempo(horaInf, minInf, segInf);
						if(validar)
							printf("\nHora somente entre 0 e 23, minutos entre 0 e 59 e segundos entre 0 e 59");
					}
					validar = 1;
					while(validar) {
						fflush(stdin);	
						printf("\nInforme o valor da hora superior: ");
						scanf("%d", &horaSup);
						printf("\nInforme o valor dos minutos superior: ");
						scanf("%d", &minSup);
						printf("\nInforme o valor dos segundos superior: ");
						scanf("%d", &segSup);
						validar = validar_tempo(horaSup, minSup, segSup);
						if(validar)
							printf("\nHora somente entre 0 e 23, minutos entre 0 e 59 e segundos entre 0 e 59");
					}
					valor_intervalo(&MyList, horaSup, minSup, segSup, horaInf, minInf, segInf);
				}
				break;
			case 12:
				imprime_lista(&MyList);
				break;
			case 13:
				printf("\n\n\nSaindo do programa!\n");
				break;
			default:
				printf("\nOpcao Invalida!!!");
				break;
		}
	}while(opcao != 13);
	return 0;
}

