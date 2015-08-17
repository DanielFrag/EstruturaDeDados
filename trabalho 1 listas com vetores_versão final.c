//-----------------------------------------------------------------------------
//Estruturas de Dados   -   1/2015
//Professor Leonardo Vianna
//Aluno: Daniel Marcos Fragoso de Souza
//
//Trabalho 1: listas implementadas através de vetores, com critérios de
//ordenação crescente (sem o uso de nenhum algorítmo ordenador) e repetição
// em função do número que está sendo inserido (um número "N" pode ter "N"
// ocorrências na lista).
//-----------------------------------------------------------------------------

//Importação de bibliotecas
#include <stdio.h>
#include <stdlib.h>

//Definição de constantes
#define TRUE 1           //constantes simulando os valores lógicos TRUE e FALSE
#define FALSE 0

//Definição de tipos
typedef struct {
        int *p;
        int max, quant;
} TLista;

//Protótipos das funções
TLista inicializar (int tamanho);
int inserir (TLista *L, int num);
int remover (TLista *L, int num);
int alterar (TLista *L, int anterior, int novo);
int deslocarInserir (TLista *L, int passo, int aux, int num, int limite);
int auxDeAlteracao (TLista *L, int passo, int novo, int ant, int proxAnt, int proxNovo);
int buscar (TLista L, int num, int *ref);
int acharReferencia(TLista L, int indice, int num);
void exibir (TLista L);
int tamanho (TLista L);
int quantDeOcorren(TLista *L, int num, int maiorIndice);
void aumPosNaFila(TLista *L, int passo, int pos, int fim);
void dimPosNaFila(TLista *L, int passo, int prox, int fim);

int menu ();


//----------------------------Implementação da Main-----------------------------
int main ()
{
   int opcao, num1, num2;
   int pos, cap;
   TLista lista;

   printf ("Capacidade da lista: ");
   scanf ("%d", &cap);  getchar();

   lista = inicializar (cap);

   //Um menu será exibido ao usuário até que este opte pela saída do sistema
   do {
      //é exibido o menu ao usuário e retornada a alternativa escolhida
      opcao = menu ();

      switch (opcao) {
         //Inserir
         case 1: printf ("Entre com o número a ser inserido: ");
                 scanf ("%d", &num1); getchar();

                 if (inserir (&lista, num1) == TRUE) {
                    printf ("Elemento inserido com sucesso!\n");
                 } else {
                    printf ("ERRO: Elemento não inserido!\n");
                 }
                 break;

         //Remover
         case 2: printf ("Entre com o número a ser removido: ");
                 scanf ("%d", &num1); getchar();

                 if (remover (&lista, num1)) {  //o mesmo que remover (&lista, num1) > 0
                    printf ("Elemento removido com sucesso!\n");
                 } else {
                    printf ("ERRO: Elemento não removido!\n");
                 }
                 break;

         //Alterar
         case 3: printf ("Entre com o número a ser alterado: ");
                 scanf ("%d", &num1); getchar();

                 printf ("Entre com o novo número: ");
                 scanf ("%d", &num2); getchar();

                 if (alterar (&lista, num1, num2)) {
                    printf ("Elemento alterado com sucesso!\n");
                 } else {
                    printf ("ERRO: Elemento não alterado!\n");
                 }
                 break;

         //Buscar
         case 4: printf ("Entre com o número a ser buscado: ");
                 scanf ("%d", &num1); getchar();

                 //"cap" não é mais usada nesse momento
                 pos = buscar (lista, num1, &cap);

                 //O elemento foi encontrado e retornada a posição de sua
                 //primeira ocorrência
                 if (pos >= 0) {
                    printf ("Elemento encontrado na lista (posicao %d)!\n", pos);
                 } else {
                    printf ("ERRO: Elemento não encontrado!\n");
                 }
                 break;

         //Exibir
         case 5: exibir (lista);
                 break;

         //Tamanho
         case 6: printf ("Há %d elementos na lista!\n", tamanho(lista));
                 break;

         //Sair
         case 7: printf ("Fim do programa!\n");
                 break;

         //Opção inválida!
         default: printf ("Opção inválida! Tente novamente!\n");

      }
      getchar();
   } while (opcao != 7);
}

//--------------Implementação das funções de manipulação da lista---------------

//Inicializa a lista: aloca dinamicamente a quantidade de posições necessárias
TLista inicializar (int tamanho)
{
   TLista L;

   L.p = (int*) malloc (sizeof (int) * tamanho);
   L.quant = 0;
   L.max = tamanho;

   return L;
}

//Tenta inserir 'num' na lista, retornado TRUE ou FALSE indicando se a operação
//foi ou não realizada
int inserir (TLista *L, int num)
{
    int pos, aux, qtd;

    //se houver espaço e, como não existe quantidade de ocorrências negetiva,
    //"num" tem q ser poisitivo pois, está atrelado a sua própria quantidade
    //de ocorrências
    if(L->quant < L->max && num > 0)
    {
        if(L->quant > 0) //se a lista já tem elementos
        {
            pos = buscar(*L, num, &aux);

            if (pos == -1)//se o número não está na lista
            {
                deslocarInserir (L ,1 ,aux , num, L->quant);
                //de "aux" em diante, a lista deve ser deslocada
                //até que "aux" esteja vago
               // aumPosNaFila(L, 1, aux, L->quant);
                //L->p[aux] = num;
            }
            else //se o número já existe na lista
            {
                qtd = quantDeOcorren(L, num, aux-1);
                //quantas ocorrências existem

                if(qtd < num)
                {
                    deslocarInserir (L ,1 ,aux , num, L->quant);
                    //de "aux" em diante, a lista é copiada para
                    //uma posição à frente
                   // aumPosNaFila(L, 1, aux, L->quant);
                    //coloca "num" na posição "aux" (está vaga)
                   // L->p[aux] = num;
                }
                else
                {
                    //número de repetições atingiu o limite
                    return FALSE;
                }
            }

        }
        else //se não insere o primeiro elemento na lista
        {
            L->p[0] = num;
        }

        L->quant++;
        return TRUE;
    }
    return FALSE;
}

//Desloca a fila "passo" posições para trás e insere "num" "passo" vezes
//na lista
int deslocarInserir (TLista *L, int passo, int aux, int num, int limite)
{
    int i;

    aumPosNaFila(L,passo,aux,limite);
    //desloca a lista "passo" posições pra trás

    for (i=0 ; i < passo ; i++, aux++) //insere "num" "passo" vezes
    {
        L->p[aux] = num;
    }
    return passo;
}

//Remover todas as ocorrências de 'num', retornando o total de ocorrências.
//Logo, se o valor zero for retornado, indicará que o elemento não se
//encontrava na lista
int remover (TLista *L, int num)
{
    int maior, qtd, pos = buscar(*L, num, &maior);

    if(pos == -1) //se "num" não está na lista
    {
        qtd = 0;
    }
    else
    {
        qtd = quantDeOcorren(L, pos, maior-1);
        //quantas vezes "num" aparece na lista
        dimPosNaFila(L, qtd, maior,L->quant-1);
        //anda com a lista, copiando o conteúdo dos índices que estavam
        //depois de "num" para as posições que "num" ocupava
        L->quant = L->quant - qtd;
        //diminui "qtd" índices válidos no total da lista
    }

    return qtd;
}

//Altera todas as ocorrências do 'velho' por 'novo', retornando o
//número de alterações realizadas.
int alterar (TLista *L, int anterior, int novo)
{
    int auxNovo, auxAnt, qtdDoNovo, qtdDoAnt, cont;

    qtdDoAnt = buscar(*L, anterior, &auxAnt);
    //quantas vezes "anterior" está na lista

    if(qtdDoAnt != -1 && anterior != novo)
    //"anterior" precisa estar na lista e tem que ser diferente de "novo"
    {
        qtdDoAnt = quantDeOcorren(L, anterior, auxAnt-1);
        //quantas vezes pode-se alterar em função das aparições do "anterior"

        qtdDoNovo = buscar(*L, novo, &auxNovo);
        //busca "novo" na lista

        if(qtdDoNovo != -1) //se "novo" está na lista
        {
            qtdDoNovo = quantDeOcorren(L, novo, auxNovo-1);
            //verifica quantas vezes ele aparece
        }
        else //caso não esteja na lista
        {
            qtdDoNovo = 0;
        }

        qtdDoNovo = novo - qtdDoNovo;
        //quantas alterações são possíveis em função de "novo"

        if(qtdDoNovo == 0) //caso "novo" não possa ter mais repetições na lista
        {
            return 0;
        }
        else
        {
            //verifica-se qual é a menor quantidade de alterações possíveis antes de
            //chamar a "auxDeAlteracao", que preenche "cont" com o número de alterações
            if(qtdDoAnt >= qtdDoNovo)
            {
                cont = auxDeAlteracao (L, qtdDoNovo, novo, anterior, auxAnt, auxNovo);
            }
            else
            {
                cont = auxDeAlteracao (L, qtdDoAnt, novo, anterior, auxAnt, auxNovo);
            }
        }
    }
    else //se "anterior" não esta na lista ou é igual a "novo"
    {
        return 0;
    }
    return cont;
}

//Desloca os elementos do vetor que estão entre os índices "proxAnt" e "proxNovo" para
//frente ou para trás "passo" posições de acordo com a comparação entre "novo" e
//"anterior". Depois insere "novo" nas "passo" posições vagas.
int auxDeAlteracao (TLista *L, int passo, int novo, int ant, int proxAnt, int proxNovo)
{
    int i;
    if(ant < novo)
    {
        dimPosNaFila(L, passo, proxAnt, proxNovo-1);
        //todo o vetor a partir de "proxAnterior" será deslocado "passo" índices para
        //frente até que "proxNovo-1" (que é a última apaição de "num") tenha sido
        //deslocada

        proxNovo-=passo; //coloca "proxNovo" no menor índice vago pois a inserção
                        //será feita do menor índice para o maior.
    }
    else
    {
        aumPosNaFila(L,passo,proxNovo,proxAnt-1);
        //todo o vetor a partir do índice de "proxNovo" será deslocado "passo"
        //índices para tras até que "proxAnt-1" (que é a última aparição de "ant")
        //tenha sido substituida
    }
    for (i=proxNovo ; i < proxNovo + passo ; i++)
    {
        L->p[i] = novo;
    }
    return passo;
}

//Verifica se determinado elemento existe na lista através de uma busca
//binária. Caso exista, é retornada uma posição que contenha "num".
//Caso contário, -1 é retornado. "*ref" será a primeira posição que
//contenha um valor maior que "num".
int buscar (TLista L, int num, int *ref)
{
    int inicio=0, fim=L.quant-1, indice=0;


    while(inicio <= fim) //laço da busca binária
    {
        indice = (inicio+fim)/2;

        if (L.p[indice] > num)
        {
            fim = indice-1;
        }
        else
        {
            if(L.p[indice] < num)
            {
                inicio = indice + 1;
            }
            else
            {
                break; //Encontrou o número. O laço deve ser encerrado.
                //O 'break' foi utilizado para não adicionar uma
                //comparação no 'while' => (... && p[indice] != num).
                //O objetivo é reduzir 'n' comparações no laço.
            }
        }
    }

    *ref = acharReferencia(L, indice, num);
    //primeira posição com valor maior que "num"

    if (L.p[indice]==num) //se "num" está na lista
    {
        return indice;
    }
    else //"num" não encontrado
    {
        return -1;
    }
}

//Retorna o primeiro índice com valor maior que "num"
int acharReferencia(TLista L, int indice, int num)
{
    if(L.p[indice] <= num)
    //o conteúdo do índice atual é menor ou igual a "num"
    {
        while(indice < L.quant && L.p[indice] <= num)
        {
            indice++;
            //cresce o índice até o limite da lista, ou até achar
            //um índice com conteúdo maior que "num"
        }
    }
    else //o conteúdo do índice atual é maior que "num"
    {
        while(indice-1 > 0 && L.p[indice] == L.p[indice-1])
        {
            indice--;
            //decrementa o índice até o limite da lista, ou até achar
            //um "indice-1" com conteúdo menor ou igual a "num"
        }
    }

    return indice;
}

//Exibe todos os elementos da lista
void exibir (TLista L)
{
   int i;

   //Lista vazia
   if (L.quant == 0)
   {
      printf ("Lista vazia!\n");
   }
   else
   {
      printf ("Lista: ");
      for (i=0; i<L.quant; i++)
      {
         printf ("%d  ", L.p[i]);
      }
      printf ("\n");
   }
}

//Retorna o número de elementos que se encontram na lista
int tamanho (TLista L)
{
   return L.quant;
}

//Exibe um menu de operações ao usuário e retorna a opção selecionada
int menu ()
{
   int op;

   printf("\n\n\n\n");

   printf ("Menu de Operações:\n\n");
   printf ("1) Inserir\n2) Remover\n3) Alterar\n");
   printf ("4) Buscar\n5) Exibir\n6) Tamanho\n7) Sair\n\n");
   printf ("Entre com a opção: ");

   scanf ("%d", &op); getchar();
   return op;
}
//retorna a quantidade de ocorrências de um determinado número que já
//tenha sido encontrado na lista.
int quantDeOcorren(TLista *L, int num, int maiorIndice)
{
    int i, qtd = 1;

    while (maiorIndice-1 >= 0 && L->p[maiorIndice] == L->p[--maiorIndice])
    {
        qtd++;
    }

    return qtd;
}
//Desloca todos os elementos do vetor, que estão de "menorDesloc" até
//"últimoDaLista", "passo" posições a frente. Só pode ser chamada quando
//há ao menos "passo" posições de espaço livre no vetor
//(L.quant + passo <= L.max).
void aumPosNaFila (TLista *L, int passo, int menorDesloc, int ultimoDaLista)
{
    int copiado = ultimoDaLista - passo;
    //Acha o índice do conteúdo que deverá ser copiado para
    //o índice do maior elemento da sublista


    while(copiado >= menorDesloc) //enquanto não deslocar o menor valor
    {
        L->p[ultimoDaLista--]=L->p[copiado--];
        //a posição final da sublista recebe o valor que a precede
        //em "passo" posições
    }
    return;
}

//Desloca todos os elementos do vetor, que estão a partir de "prox",
//"passo" posições para trás, preenchendo os índices a partir de
//"pontoDeInsercao" com valores que estão a partir de "prox"
void dimPosNaFila (TLista *L, int passo, int prox, int ultimaCopia)
{
    int pontoDeInsercao = prox-passo;
    //Acha á partir de qual posição os números serão substituidos

    while(prox <= ultimaCopia)
    //enquanto o índice determinado por "prox" não chegar na "ultimaCopia"
    {
        L->p[pontoDeInsercao++]=L->p[prox++];
        //carrega o índice "pontoDeInsercao" com o que está em "prox"
    }
    return;
}
