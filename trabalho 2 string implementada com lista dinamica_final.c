/*

2015/1
ISTRIO - Noite - Estrutura de Dados
Professor: Leonardo Vianna

Alunos:
André Luiz Batista (1410478300071)
Daniel Marcos Fragoso de Souza (1410478300015)

2º trabalho para a AV1

Strings armazenadas sob a forma de uma lista dinâmica, um caracter por nó.

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    char c;
    struct no *prox;
}Tcaixa;

typedef struct str
{
    int tamanho;
    Tcaixa *primeiraLetra;
}Tstr;

//-----------------------------protótipo das funções------------------------

int inserirCaracter (Tstr *palavra, Tcaixa **aPartir, char letra);
int inserirEmLocalDefinido (Tstr *palavra, char letra, int pos);
int pegarPalavra (Tstr *indice);
void exibir (Tcaixa *letra1);
int inverterPalavra (Tstr *invertida, Tstr palavra);
Tcaixa** inverter (Tstr *invertida, Tcaixa *caixa, Tcaixa **proximo);
void removeCaixa(Tcaixa **anterior, Tcaixa *aux, int *tamanhoDaPalavra);
void limparLista(Tstr *palavra);
void limpa(Tcaixa **caixa, Tstr *palavra);
int removeOcorrDeUmCaracter (Tstr *palavra, char removido);
int removerSubString (Tstr *palavra, int posInicial, int qtdLetras);
void removeRepeticao (Tstr *palavra);
char* converterParaCharAst (Tstr *palavra);
int listaStrlen (Tstr *palavra);
int listaStrcat (Tstr *palavraDestino, Tstr *origem);
int listaStrcpy (Tstr *palavraDestino, Tstr *origem);
int listaStrcmp (Tstr *primeiraPalavra, Tstr *segundaPalavra);



//-----------------------------------main----------------------------------

int main()
{
    Tstr palavra, palavra2;
    int sinal;
    char *c;

    palavra.primeiraLetra =palavra2.primeiraLetra = NULL;
    palavra.tamanho =palavra2.tamanho = 0;

    sinal = pegarPalavra (&palavra);

    exibir(palavra.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra.tamanho);

    printf("inverte a palavra");
    inverterPalavra(&palavra2, palavra);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("compara duas palavras");
    printf("%i\n",listaStrcmp (&palavra, &palavra2));
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("limpa palavra");
    limparLista(&palavra);
    exibir(palavra.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra.tamanho);

    printf("remove o caracter 'e'");
    removeOcorrDeUmCaracter(&palavra2, 'e');
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("segunda letra removida");
    removeCaixa(&(palavra2.primeiraLetra->prox), palavra2.primeiraLetra->prox, &(palavra2.tamanho));
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("repeticao removida");
    removeRepeticao(&palavra2);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("inserir 'z' na terceira posição");
    inserirEmLocalDefinido(&palavra2, 'z', 3);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("inserir 'h' na ultima posição");
    inserirEmLocalDefinido(&palavra2, 'h',95);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("remover 3 caracteres a partir da segunda letra");
    removerSubString(&palavra2, 2, 3);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("converte para char*");
    c = converterParaCharAst(&palavra2);
    exibir(palavra2.primeiraLetra);
    printf("string: %s\n\n", c);

    printf("concatena palavra1 em palavra2");
    listaStrcat (&palavra2, &palavra);
    exibir(palavra2.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra2.tamanho);

    printf("copia para palavra o conteúdo de palavra2");
    listaStrcpy(&palavra, &palavra2);
    exibir(palavra.primeiraLetra);
    printf("Tamanho: %i\n\n", palavra.tamanho);

    return 0;
}

//----------------------------------funções----------------------------


//Aloca uma única caixa para inserir "letra" na lista. "aPartir" contém o
//endereço do campo ("prox" ou "primeirLetra") que deve apontar para a nova caixa
int inserirCaracter (Tstr *palavra, Tcaixa **aPartir, char letra)
{
    Tcaixa *aux; //ponteiro para a nova caixa
    int inserido=0; //sinalizador de sucesso (1) ou erro (0)

    if (aux = (Tcaixa*) malloc (sizeof(Tcaixa))) //alocação dinamica
    {
        aux->c = letra; //coloca a letra na nova caixa

        aux->prox = *aPartir; //faz o "prox" da nova caixa apontar para o mesmo
                              //endereço que o ponteiro da struct anterior

        *aPartir = aux; //faz o campo de endereço da struct anterior apontar
                        //para a nova caixa

        palavra->tamanho += ++inserido;// indica que houve sucesso
    }
    return inserido; //retorno do resultado
}

int pegarPalavra (Tstr *indice)
{
    char digitado;
    int confirmacao; //sinalizador de sucesso (1) ou erro (0)
    Tcaixa **aux = &(indice->primeiraLetra);

    do
    {
        digitado = getc(stdin);// lê do arquivo do teclado um caracter

        if(digitado != '\n')
        {
            confirmacao = inserirCaracter(indice, aux, digitado); //insere uma caixa com o caracter lido

            if (confirmacao) //testa para saber se o caracter foi inserido na lista
            {
                //indice->tamanho++; //atualiza o tamanho da palavra
                aux = &((*aux)->prox); //põe em "aux" o endereço do campo "prox" da caixa inserida
            }
        }

    }while (confirmacao && digitado != '\n'); //sairá somente se for digitado "enter" ou se
                                              //não conseguir inserir o caracter

    return confirmacao; //retorna sucesso ou erro
}

//Insere uma letra em uma posição específica da palavra
int inserirEmLocalDefinido (Tstr *palavra, char letra, int pos)
{
    Tcaixa **caixa = &(palavra->primeiraLetra);

    if( (pos == 0) || (pos > palavra->tamanho) )
    {
        pos = palavra->tamanho; //"caixa" será levado até o campo de
                                //endereço da última caixa
    }
    else
    {
        pos--; //"caixa" será levado até o campo de endereço da caixa
               //anterior a posição desejada
    }

    while(pos)
    {
        caixa = &((*caixa)->prox);
        pos--;
    }

    return inserirCaracter(palavra, caixa, letra);
}

//Chama a função inverter enviando: a palavra que deve conter o resultado
//da inverção; o endereço do primeiro caracter da palavra original; e, por
//referência, o campo que contém o endereço da primeira letra da palavra
//que deveconter o resultado da inversão. Retorna sucesso (1) ou erro (0)
int inverterPalavra (Tstr *invertida, Tstr palavra)
{
    inverter (invertida, palavra.primeiraLetra, &(invertida->primeiraLetra));

    if(palavra.tamanho == invertida->tamanho)
        return 1;
    else
        return 0;
}

//Vai do primeiro ao último caracter recursivamente e volta copiando os
//caracteres para a nova string. O ponteiro "proximo", que aponota para
//o campo que guarda o endereço de uma caixa, faz parte da string que
//contém o resultado da inversão, ou seja, faz parte da string invertida
Tcaixa** inverter (Tstr *invertida, Tcaixa *caixa, Tcaixa **proximo)
{
    if(!caixa) //caso base: último caracter está na chamada anterior;
    {
        return proximo; //endereço do campo "primeiraLetra" da "Tstr" invertida
    }
    else
    {
        proximo = inverter (invertida, caixa->prox, proximo);//chamadas recursivas:
        //Navegam até o último caracter e atualizam o ponteiro "proximo"

        inserirCaracter(invertida, proximo, caixa->c);

        proximo = &((*proximo)->prox); //faz o "proximo" apontar para o campo "prox"
                                       //da caixa que acabou de ser inserida
    }
    return proximo; //retorna, para a própria função, o "proximo" atualizado
}

//Remove uma única caixa da palavra a partir do seu endereço e do endereço
//do campo (da caixa anterior) que contém o ponteiro para a caixa a ser
//removida e atualiza o tamanho da palavra
void removeCaixa(Tcaixa **anterior, Tcaixa *aux, int *tamanhoDaPalavra)
{
    *anterior = aux->prox; //conteúdo do campo "prox", da caixa anterior, atualizado
                           //para apontar para o endereço seguinte a caixa removida
    free(aux); //libera o espaço de memória ocupado pela caixa removida
    (*tamanhoDaPalavra)--; //diminui o tamanho da palavra
    return;
}

//limpa a "*palavra" chamando a função "limpa"
void limparLista(Tstr *palavra)
{
    Tcaixa **caixa = &(palavra->primeiraLetra);

    limpa(caixa, palavra);

    return;
}

//Acha o último caracter recursivamente e volta excluindo cada caixa
void limpa(Tcaixa **caixa, Tstr *palavra)
{
    if(!(*caixa)) //caso base: último caracter está na chamada anterior;
    {
        return; //endereço do campo "primeiraLetra" da "Tstr" invertida
    }
    else
    {
        printf("\nentrei %c\n", (*caixa)->c);
        limpa( &((*caixa)->prox), palavra);
        removeCaixa(caixa, (*caixa), &(palavra->tamanho));
    }
    return; //retorna, para a própria função, o "proximo" atualizado
}

//Remove todas as ocorrências de um determinado caracter e rotorna essa quantidade
int removeOcorrDeUmCaracter (Tstr *palavra, char removido)
{
    Tcaixa **caixa = &(palavra->primeiraLetra); //caixa guarda o endereço do campo
                                                //que aponta para a primeira caixa
    int controle=0; //quantas remoções são feitas

    while(*caixa) //enquanto houver caixas não verificadas
    {
        if((*caixa)->c == removido) //caixa a ser removida encontrada
        {
            removeCaixa(caixa, (*caixa), &(palavra->tamanho));
            controle++;
        }
        else //"caixa" deve guardar o endereço do campo "prox" da próxima caixa
        {
            caixa = &(*caixa)->prox;
        }
    }
    return controle;
}

//Remove "qtdLetras" caracteres de "palavra" a partir da posição "posInicial"
int removerSubString (Tstr *palavra, int posInicial, int qtdLetras)
{
    Tcaixa **anterior = &(palavra->primeiraLetra);
    int controle = 0; //quantos caracteres são efetivamente removidos

    // "(*anterior) != NULL" é para evitar invasão de memória

    while(posInicial > 1 && (*anterior) != NULL) //para alcançar a caixa desejada
    {
        anterior = &((*anterior)->prox); //faz o "anterior" apontar para o campo
                                         //"prox" da caixa seguinte
        posInicial--; //atualiza condição de repetição, até que "anterior"
                      //chegue ao campo "prox" da caixa que antecede a substring
    }

    while(qtdLetras > 0 && (*anterior) != NULL) //para remover as caixas
    {
        removeCaixa(anterior, (*anterior), &(palavra->tamanho));
        qtdLetras--; //atualiza condição de repetição, até remover toda a substring
        controle++;
    }
    return controle;
}

//Remove todas as repetições de caracteres que possam haver na palavra
void removeRepeticao (Tstr *palavra)
{
    Tcaixa *aux, *corredor, *anterior = palavra->primeiraLetra; //ponteiros auxiliares

    if(anterior && anterior->prox) //havendo mais de um elemento na palavra
    {
        aux = anterior->prox; //"anterior" = primeira caixa / "aux" = segunda caixa

        while(aux) //enquanto não chegar ao fim da palavra
        {
            corredor = palavra->primeiraLetra; //corredor começa na primeira letra

            do //repetição que irá comparar a caixa de "aux" com as caixas
               //percorridas pelo corredor
            {
                if(corredor->c == aux->c) //"aux" é uma repetição. Deve ser removido
                {
                    removeCaixa(&(anterior->prox), aux, &(palavra->tamanho));
                    aux = NULL; //sinaliza que "aux" não faz mais parte da palavra
                }
                else
                {
                    corredor = corredor->prox; //atualiza corredor para a caixa seguinte
                }

            }while(aux && corredor != aux);//ou "aux" é removido ou "corredor" o alcança

            if(aux) //se "corredor" o alcançou
            {
                anterior = aux; //atualiza o anterior para "aux"
                aux = aux->prox; //anda com "aux" para o endereço da próxima caixa
            }
            else //se "aux" foi removido
            {
                aux = anterior->prox; //"aux" aponta para uma caixa diferente, mas que
                                      //ocupa a mesma posição da caixa que ele apontava
            }
        }
    }
    return;
}

//Converte a "palavra" para um vetor de caracteres
char* converterParaCharAst (Tstr *palavra)
{
    Tcaixa *aux = palavra->primeiraLetra; //endereço da primeira caixa
    int i=0; //contador do vetor
    char *c; //vetor a ser alocado

    c = (char*) malloc (palavra->tamanho * sizeof(char) + sizeof(char));
    //quantidade de caracteres de "palavra" mais um, para o '\0'

    if(!c)
        return NULL;

    while (aux) //enquanto houver caracter a ser lido
    {
        c[i] = aux->c; //copia cada caracter para o vetor em ordem
        i++; //atualiza o índice do vetor
        aux = aux->prox; //atualiza a caixa da lista
    }

    c[i]='\0'; //encerra a string

    return c;
}

int listaStrlen (Tstr *palavra)
{
    return palavra->tamanho;
}

int listaStrcat (Tstr *palavraDestino, Tstr *origem)
{
    Tcaixa **dest = &(palavraDestino->primeiraLetra), *orig = origem->primeiraLetra;
    int controle = 0;

    while(*dest) //Vai até a última caixa da "*palavraDestino"
        dest = &((*dest)->prox);

    while(orig) //Vai até o último caracter da "*origem"
    {
        inserirCaracter(palavraDestino, dest, orig->c); //Isere o caracter

        dest = &((*dest)->prox); //Atualiza o ponteiro "dest" para apontar para o
                                 //campo "prox" da última caixa
        orig = orig->prox; //Acha o próximo caracter da "*origem"
        controle++; //Atualiza a quantidade de inserções na "*palavraDestino"
    }

    return controle;
}

int listaStrcmp (Tstr *primeiraPalavra, Tstr *segundaPalavra)
{
    Tcaixa *primeira = primeiraPalavra->primeiraLetra, *segunda = segundaPalavra->primeiraLetra;

    //avalia se uma da palavras chegou ao fim e se há caracteres diferentes na mesma posição
    while(primeira && segunda && primeira->c == segunda->c)
    {
        primeira = primeira->prox;
        segunda = segunda->prox;
    }

    if(!primeira && !segunda) //são exatamente iguais
    {
        return 0;
    }
    else
    {
        if(!segunda) //a primeira é alfabeticamente maior
        {
            return 1;
        }
        else
        {
            if(!primeira) //a segunda é alfabeticamente maior
            {
                return -1;
            }
            else //compara o primeiro caracter difernte
            {
                return primeira->c - segunda->c;
            }
        }
    }
}

int listaStrcpy (Tstr *palavraDestino, Tstr *origem)
{
    Tcaixa **caixa = &(palavraDestino->primeiraLetra), *copiar = origem->primeiraLetra;
    int sinal=0; //Indicará o tamanho da palavra de destino

    limparLista(palavraDestino); //Zera a "*palavraDestino"

    //Enquanto não chegar ao fim da "*origem" e conseguir inserir em "*palavraDestino"
    while(copiar && inserirCaracter(palavraDestino, caixa, copiar->c))
    {
        caixa = &((*caixa)->prox); //Atualiza "caixa" com o endereço do
                                   //campo "prox" da caixa seguinte
        copiar = copiar->prox; //"copiar" aponta para a próxima caixa
        sinal++; //Mais um caracter inserido
    }

    if(!copiar) //se chegou ao fim da palavra "*origem"
    {
        return sinal;
    }
    else //retorna um erro
    {
        limparLista(palavraDestino);
        return 0;
    }
}

void exibir (Tcaixa *letra1)
{
   Tcaixa *aux = letra1;

   if (!aux)
   {
      printf ("vazia!\n");
   }
   else
   {
      printf ("\nPalavra: ");

      while (aux)
      {
         putc (aux->c, stdout); //escreve o caracter no arquivo de saída
         aux = aux->prox;
      }

      printf ("\n");
   }

}
