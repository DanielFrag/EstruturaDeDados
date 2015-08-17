/*
ISTRIO - ESD - Noite - 1.2015
Professor: Leonardo Vianna
Trabalho 4: Escalonamento de CPU

Alunos: Daniel Marcos/ Felipe Oliveira
*/
//Importação de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definições de constantes simulando os valores lógicos TRUE e FALSE
#define TRUE 1
#define FALSE 0

//Definição de tipos
typedef struct No
{
    int q, instanteDeEntrada; //q = unidades de quantum solicitadas pelo processo
                              //instanteDeEntrada = momento em que o processo entra no processador pela primeira vez
    char id[9]; //nome do processo
    struct No *prox, *ant; //ponteiros para o próximo processo e para o processo anterior
} TNo;

//Protótipos das funções
int inserir (TNo **inicioDaFila, int quantum, char *id);
TNo* removerNo (TNo **inicioDaFila, TNo *processoFinalizado);
void escalonarProcessos(TNo **inicioDaFila, int quantum);
void exibir (TNo *inicioDaFila);


//----------------------------Implementaçãp da Main-----------------------------
int main ()
{
    int q, quantumDoProcessador;
    char identificador[9];
    TNo *escalonador = NULL;
    FILE *arq;

    arq = fopen("processos.txt", "r");

    if (!arq)
    {
        printf("Falha na abertura do arquivo 'processos.txt'\n\n");
        exit(0);
    }

    fscanf(arq, "%i", &quantumDoProcessador);

    //chama as funções que irão preencher a fila enquanto houverem dados
    while(fscanf(arq, "%s %i", identificador, &q)==2 && inserir(&escalonador, q, identificador));

    printf("Quantum do processador = %i\n", quantumDoProcessador);
    exibir (escalonador);

    escalonarProcessos(&escalonador, quantumDoProcessador);
}

//--------------Implementação das funções de manipulação da lista---------------

//Insere um processo na fila
int inserir (TNo **inicioDaFila, int quantum, char* id)
{
    TNo* aux = (TNo*) malloc (sizeof(TNo));

    if (!aux) //falha na alocação de memória
    {
        return FALSE;
    }
    else
    {
        aux->q = quantum; //preenche os dados do processo
        strcpy(aux->id,id);
        aux->instanteDeEntrada = -1; //inicia com um instante de entrada no processador inválido

        if (*inicioDaFila) //fila não está vazia. "aux" deve entrar como último elemento da fila
        {
            aux->prox = *inicioDaFila;       //Ponteiros de "aux" devem apontar para o primeiro elemento da lista
            aux->ant = (*inicioDaFila)->ant; //e para o último elemento da lista.
            aux->prox->ant = aux; //O ponteiro do primeiro elemento que aponta para o último elemento recebe "aux"
            aux->ant->prox = aux; //e o ponteiro do novo penúltimo elemento (era o último) que aponta para o último deve apontar para "aux"
        }
        else //fila vazia. Insere o primeiro elemento
        {
            aux->ant = aux->prox = (*inicioDaFila) = aux;
        }

        return TRUE;
    }
}

//Remover um processo da fila. Retorna o endereço do próximo processo
TNo* removerNo (TNo **inicioDaFila, TNo *no)
{
    TNo *aux = no->prox;

    if(aux == no) //caso haja somente um nó na lista
    {
        free(no);
        aux = *inicioDaFila = NULL; //esvazia a fila de processos
    }
    else //caso haja mais de um elemento na lista
    {
        no->prox->ant = no->ant; //faz os elementos que estão em volta de "no" apontarem um para o outro
        no->ant->prox = no->prox;

        if(no == (*inicioDaFila)) //se o "no" for o primeiro elemento
        {
            *inicioDaFila = aux; //move o início da fila para frente
        }
        free(no);
    }
    return aux; //retorna o elemento que vem depois de "no"
}

//Escalona cada processo de acordo com o quantum do processador
//e o quantum solicitado pelos processos
void escalonarProcessos(TNo **inicioDaFila, int quantum)
{
    TNo *aux = (*inicioDaFila);
    int t=0, tempoDeProcessamento;

    while(aux) //enquanto houverem processos
    {
        tempoDeProcessamento = quantum; //tempo que um processo vai ter de processador

        if(aux->instanteDeEntrada < 0)  //se o instante de entrada for inválido, ou seja, o processo ainda não usou o processador,
            aux->instanteDeEntrada = t; //insere o instante em que o processo entrou no processador pela primeira vez

        while(tempoDeProcessamento && aux->q) //ou o processo usa todo o seu tempo ou já pode ser encerrado
        {
            aux->q--;
            tempoDeProcessamento--;
            t++; //incrementa o tempo de uso total do processador
        }

        if(!(aux->q)) //se o processo atual já foi encerrado
        {
            printf("%s, iniciou no quantum %i e foi finalizado no quantum %i\n", aux->id, aux->instanteDeEntrada, t-1);
            aux = removerNo(inicioDaFila, aux); //remove ele da fila
        }
        else
            aux = aux->prox; //chama o próximo processo da lista
    }
}

//Exibe todos os elementos da fila de processos
void exibir (TNo *inicio)
{
   TNo* aux = inicio;

   if (!aux)
   {
      printf ("\nFila vazia!\n");
   }
   else
   {
      printf ("\nFila de Processos\n");

      do
      {
         printf ("%s: q = %d\n", aux->id, aux->q);
         aux = aux->prox;
      }
      while (aux != inicio);

      printf ("\n\n");
   }

}
