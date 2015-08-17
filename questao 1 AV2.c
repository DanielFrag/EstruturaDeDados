//Importação de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Definições de constantes simulando os valores lógicos TRUE e FALSE
#define TRUE 1
#define FALSE 0

//Definições de tipos
typedef struct No
{
	//unidades
	int n;

    //tipo da casa
	char tipo;

    //ponteiros para o próximo processo e para o processo anterior
	struct No *prox, *ant;
} TNo;

typedef struct jogador
{
	//contador
	int n, vida;

    //nome do jogador
	char nome[11];

    //ponteiros para a casa em que o jogador está
	struct No *casa;
} Tjogador;

//Protótipos das funções
int inserir (TNo **inicioDoTabuleiro, int numeroDeCasas, char tipoDaCasa);
TNo* removerNo (TNo **inicioDaFila, TNo *processoFinalizado);
void preencherTab(FILE *arq, TNo **inicio, int nBuracos);
void alocarJogadores (Tjogador jogadores[], int nJogadores, TNo *inicio);
void jogar(TNo **inicio, Tjogador jogadores[]);
void executarCasa (Tjogador *jog, TNo **inicio);
void exibirJogador(TNo *inicio, Tjogador *jogador);
void exibir (TNo *inicioDaFila);


/* =============================	MAIN 	===============================*/

int main ()
{
	int nJogadores;
	FILE *arq;
	TNo *inicio = NULL;
	Tjogador jogadores[5];



    arq = fopen("tabuleiro.txt", "r");

    if (!arq)
    {
        printf("Falha na abertura do arquivo");
        exit(0);
    }

    do
    {
        printf("Quantos jogadores serão (2 a 5)?\n");
        scanf("%i", &nJogadores);
    }while(nJogadores<2 || nJogadores>5);
    //chama as funções que irão preencher o tabuleiro enquanto houverem casas
	preencherTab(arq, &inicio, nJogadores-2);

    //pega os jogadores
    alocarJogadores (jogadores, nJogadores, inicio);

	jogar(&inicio, jogadores);

	getchar();

	return 0;
}

/* =============================	MANIPULAÇÃO DA LISTA 	==================================*/

void jogar(TNo **inicio, Tjogador jogadores[])
{
	int dado, rodada=1, i=-1;

	srand(time(NULL));
	printf("\n\n\nrodada %i\n", rodada);

	do
	{
		if(i<4 && jogadores[i+1].casa)
            i++;
        else
        {
            rodada++;
            printf("\n\n\nrodada %i\n", rodada);
            i=0;
        }

		if(jogadores[i].vida>-1 && jogadores[i].n == 0)
		{
            printf("\n%s, sua vez. Tecle enter para rolar os dados\n", jogadores[i].nome);
            getchar();

            dado = rand()%6 + 1;

            printf("Voce tirou %i\n", dado);
            exibir(*inicio);

            while(dado>0 && jogadores[i].casa->tipo != 'f')
            {
                jogadores[i].casa = jogadores[i].casa->prox;
                dado--;
            }

            exibirJogador(*inicio, &jogadores[i]);

            executarCasa (&jogadores[i], inicio);
        }
        else
        {
            if(jogadores[i].n)
                jogadores[i].n--;
        }
	}
	while(jogadores[i].casa->tipo != 'f');

	printf("%s campeao", jogadores[i].nome);
}

void executarCasa (Tjogador *jog, TNo **inicio)
{
    int mover;
    TNo *aux;

    switch(jog->casa->tipo)
    {
        case 'n':
            break;

        case 'b':
            jog->vida--;

            if(jog->vida < 0)
            {
                removerNo(inicio, jog->casa);
                printf("%s eliminado", jog->nome);
            }
            else
                printf("%s, acabou de gastar a sua vida", jog->nome);


            break;

        case 'e':
            jog->vida++;
            printf("vida extra\n");
            jog->casa = jog->casa->prox;
            removerNo(inicio, jog->casa->ant);
            break;

        case 'a':
            mover = jog->casa->n;

            while(mover && jog->casa->tipo != 'f')
            {
                jog->casa = jog->casa->prox;
                mover--;
            }
            exibirJogador(*inicio, jog);
            executarCasa(jog, inicio);
            break;

        case 'p':
            jog->n = jog->casa->n;
            break;

        case 'v':
            mover = jog->casa->n;

            while(mover && jog->casa != *inicio)
            {
                jog->casa = jog->casa->ant;
                mover--;
            }
            exibirJogador(*inicio, jog);
            executarCasa(jog, inicio);
            break;

    }
}


void exibirJogador(TNo *inicio, Tjogador *jogador)
{
	while(jogador->casa != inicio)
	{
		printf("    ");
		inicio = inicio->prox;
	}
	printf("^ %s voce esta aqui\n", jogador->nome);
}

void preencherTab(FILE *arq, TNo **inicio, int nBuracos)
{
	int numeroDeCasas, vidaExtra=1;
	char tipoDaCasa;


	 while(fscanf(arq, "%c ", &tipoDaCasa)==1)
	 {
		if(tipoDaCasa=='a' || tipoDaCasa=='v' || tipoDaCasa=='p')
			fscanf(arq, "%i ", &numeroDeCasas);
		else
			numeroDeCasas = 0;

		if(tipoDaCasa != 'b')
		{
            if(tipoDaCasa != 'e')
                inserir(inicio, numeroDeCasas, tipoDaCasa);
            else
            {
                if(vidaExtra)
                {
                    vidaExtra--;
                    inserir(inicio, numeroDeCasas, tipoDaCasa);
                }
            }
		}
		else
		{
			if(nBuracos > 0)
			{
				inserir(inicio, numeroDeCasas, tipoDaCasa);
				nBuracos--;
			}
		}
	 }
}

void alocarJogadores (Tjogador jogadores[], int nJogadores, TNo *inicio)
{
	int i=0;

	while(i<nJogadores)
	{
		printf("Nome do jogador %i (ate 10 caracteres): ", i+1);
		scanf("%s", jogadores[i].nome);

		jogadores[i].casa = inicio;
		jogadores[i].vida = 0;
		jogadores[i].n = 0;
		i++;
	}

	getchar();

	while(i<5)
	{
		strcpy(jogadores[i].nome, "**********");
		jogadores[i].casa = NULL;
		i++;
	}
}

int inserir (TNo **inicioDoTabuleiro, int numeroDeCasas, char tipoDaCasa)
{
    TNo* aux = (TNo*) malloc (sizeof(TNo));

    //falha na alocação de memória
	if (!aux)
	{
        return FALSE;
    }
    else
    {
        //preenche os dados do processo
		aux->n = numeroDeCasas;

		aux->tipo = tipoDaCasa;

        //fila nã está vazia. "aux" deve entrar como último elemento da fila
		if (*inicioDoTabuleiro)
        {
            //Ponteiros de "aux" devem apontar para o primeiro elemento da lista
			aux->prox = *inicioDoTabuleiro;

			//e para o último elemento da lista.
			aux->ant = (*inicioDoTabuleiro)->ant;

			//O ponteiro do primeiro elemento que aponta para o último elemento recebe "aux"
			aux->prox->ant = aux;

			//e o ponteiro do novo penúltimo elemento (era o último) que aponta para o último deve apontar para "aux"
			aux->ant->prox = aux;
        }
        //fila vazia. Insere o primeiro elemento
		else
        {
            aux->ant = aux->prox = (*inicioDoTabuleiro) = aux;
        }

        return TRUE;
    }
}

//Remover um processo da fila. Retorna o endereço do próximo processo
TNo* removerNo (TNo **inicioDaFila, TNo *no)
{
    TNo *aux = no->prox;

    //caso haja somente um nó na lista
	if(aux == no)
    {
        free(no);

		//esvazia a fila de processos
		aux = *inicioDaFila = NULL;
    }
    //caso haja mais de um elemento na lista
	else
    {
        //faz os elementos em volta de "no" apontarem um para o outro
		no->prox->ant = no->ant;

		no->ant->prox = no->prox;

        //se o "no" for o primeiro elemento
		if(no == (*inicioDaFila))
        {
            //move o início da fila para frente
			*inicioDaFila = aux;
        }
        free(no);
    }
    //retorna o elemento que vem depois de "no"
	return aux;
}

//Exibe todos os elementos da fila de processos
void exibir (TNo *inicio)
{
   TNo* aux = inicio;

   if (!aux)
   {
      printf("Tabuleiro vazio");
   }
   else
   {
      printf("Tabuleiro\n");

      do
      {
         printf ("%c%c  ", aux->tipo, aux->n==0?' ': aux->n+48);
         aux = aux->prox;
      }
      while (aux != inicio);

      printf ("\n");
   }

}
