#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no
{
	int valor, nivel, fatorEquilibrio;
	struct no *d, *e;
}tNo;

typedef struct pont
{
    int altura;
    tNo *raiz;
}tPontArvore;

void exibirMenu();
int inserir(tPontArvore *semente, int num);
tNo* buscaAnterior(tNo *raiz, int num);
void imprimirEmOrdem(tNo *caixa);
void exibirEmNiveis(tPontArvore semente);
void imprimirEmNiveis(tNo *raiz, int nivelBuscado, int altura);
void darEspacos(int i);
tNo* busca(tNo *raiz, int num);
int removerNo (tPontArvore *semente, int num);
void atualizarNivelDosElementos(tNo *raiz);
int atualizarAltura(tNo *raiz, int altura);
void balancearArvore (tPontArvore *semente);
tNo* calcFatorEBalanceia(tNo *raiz, int *peso, tPontArvore *pImprimir);
tNo* balanceadorDeSubArvore(tNo* raiz, tPontArvore *pImprimir);
tNo* girarSentidoHorario(tNo* raiz);
tNo* girarSentidoAntihorario(tNo* raiz);

int main ()
{
    int numero, escolha;
    tPontArvore semente;

    semente.altura=0;
    semente.raiz=NULL;

    do
    {
        exibirMenu();
        scanf("%i", &escolha); getchar();

        switch(escolha)
        {
            case 1:
                printf("digite o numero a ser inserido (de 0 a 99): ");
                scanf("%i", &numero);
                if(numero<100 && numero>-1)
                    inserir(&semente, numero);
                else
                    printf("ERRO! Numero invalido.\n");
                break;
            case 2:
                imprimirEmOrdem(semente.raiz);
                break;
            case 3:
                exibirEmNiveis(semente);
                break;
            case 4:
                printf("digite o numero a ser removido: ");
                scanf("%i", &numero);
                removerNo(&semente, numero);
                break;
            case 5:
                balancearArvore(&semente);
                break;
            case 0:
                break;
            default:
                printf("opcao invalida\n");
                break;

        }
    }
    while(escolha!=0);

    return 0;
}

void exibirMenu()
{
    printf("Digite o numero da opcao que deseja\n");
    printf("1 Inserir\n2 Exibir em ordem\n3 Exibir como arvore\n4 Remove\n5 Balancear\n0 Encerra\n\n");
}

int inserir(tPontArvore *semente, int num)
{
    tNo *aux, *auxAnterior;

    aux = (tNo*) malloc(sizeof(tNo));

    if(!aux)
    {
        return 0;
    }
    //preenche o aux
    aux->fatorEquilibrio = 0;
    aux->valor = num;
    aux->d = aux->e = NULL;

    if(!(*semente).raiz) //se a árvore está vazia
    {
        (*semente).raiz = aux;
        aux->nivel = 1;
    }
    else //se não
    {
        auxAnterior = buscaAnterior((*semente).raiz, num); //busca o nó que deve apontar para a nova folha
        if(auxAnterior->valor == num || (auxAnterior->e && auxAnterior->e->valor == num) || (auxAnterior->d && auxAnterior->d->valor == num)) //Caso o valor já exista na árvore
        {
            free(aux); //não insere novamente
            return 0;
        }
        else
        {
            aux->nivel = auxAnterior->nivel + 1; //a nova folha recebe o nível ao qual faz parte
            if(auxAnterior->valor > num) //e é colocada na posição ordenada
                auxAnterior->e = aux;
            else
                auxAnterior->d = aux;
        }

    }


    if(semente->altura < aux->nivel) //atualiza a altura da árvore
        semente->altura = aux->nivel;

    return 1;
}

//Só deve ser chamada para elemento que estejam abaixo da raiz.
//Busca o nó que aponta para o número buscado
tNo* buscaAnterior(tNo *raiz, int num)
{
    tNo *aux;

    if(raiz) //se há elementos na árvore
    {
        do //até que "raiz" seja o nó que contenha: ou o elemento buscado, ou o valor nulo
        {
            aux = raiz; //aux sempre apontará para o elemento anterior
            if(raiz->valor > num)
                raiz = raiz->e;
            else
                if(raiz->valor < num)
                    raiz = raiz->d;
        }while(raiz && raiz->valor!=num);
    }
    else //se a árvore está vazia
        aux = NULL;

    return aux;
}

//imprime recusivamente todos os valores de uma árvore em ordem
void imprimirEmOrdem(tNo *caixa)
{
    if(!caixa)
    {
        return;
    }

    imprimirEmOrdem(caixa->e);
    printf(" %2i ", caixa->valor);
    imprimirEmOrdem(caixa->d);

    return;
}

//Chama a "imprimirEmNiveis()" sempre a partir da raiz da árvore enviando o nível a ser buscado para que esta exiba seus elementos,
//dando espaços entre eles de acordo com a sua altura na árvore. As duas funções juntas levam a uma complexidade O(n²)
void exibirEmNiveis (tPontArvore semente)
{
    int i;

    if(!semente.raiz) //árvore vazia
    {
        printf("Arvore vazia!\n");
        return;
    }

    printf("altura da arvore: %i\n\n", semente.altura);

    for(i=1 ; i<=semente.altura ; i++)
    {
        imprimirEmNiveis(semente.raiz, i, semente.altura);
        printf("\n"); //Coloca o nível seguinte em outra linha
    }

    return;
}

//Chama a "imprimirEmNiveis()" sempre a partir da raiz de uma sub árvore enviando o nível a ser buscado para que "imprimirEmNiveis()"
//exiba seus elementos e seus espaços entre de acordo com a sua altura na árvore. As duas funções juntas levam a uma complexidade O(n²)
void exibirSubArvoreEmNiveis(tNo* raiz, int alturaDaArvore)
{
    int i, alturaDaSubArvore = alturaDaArvore - (raiz->nivel) + 1;

    if(!raiz) //sub árvore vazia
    {
        printf("Sub arvore vazia!\n");
        return;
    }

    for(i=raiz->nivel ; i<=alturaDaArvore ; i++) //imprime do nível da sub árvore em diante
    {
        imprimirEmNiveis(raiz, i, alturaDaArvore);
        printf("\n"); //Coloca o nível seguinte em outra linha
    }

    return;
}

//Imprime em uma mesma linha todos os elementos de um nível da árvore. Caso algum braço da árvore não contenha elementos do
//nível que está sendo impresso é calculado e impresso uma quantidade de espaços vazios equivalente ao que o elemento ocuparia
void imprimirEmNiveis (tNo *raiz, int nivelBuscado, int altura)
{
    if(!raiz || raiz->nivel > nivelBuscado) //Caso base. 1ª condição: o endereço enviado não contém elemento
        return;                             //2ª condição: o endereço enviado contém um elemento do nível seguinte

    imprimirEmNiveis (raiz->e, nivelBuscado, altura); //recursividade a esquerda

    if(raiz->nivel == nivelBuscado) //se retornar pela segunda condição do OU lógico deve-se calcular a quantidade
                                    //de espaços antes e depois do número de acordo com o seu nível na árvore
    {
        darEspacos(pow(2, altura-raiz->nivel)-1); //dá espaços antes do número a ser impresso
        printf("%2i", raiz->valor); //imprime o número
        darEspacos(pow(2, altura-raiz->nivel)); //dá espaços depois do número a impresso
    }
    else //o elemento não é do nível buscado. Se tiver retornado da recursividade pela 1ª condição, precisa ser avaliado
    {
        if (!raiz->e) //Sem elementos do nível buscado a esquerda a quantidade de espaços em branco deve ser calculada
            darEspacos(pow(2, altura-raiz->nivel)); //calcula o número de elementos que o nível buscado teria neste braço
    }

    imprimirEmNiveis (raiz->d, nivelBuscado, altura);
    if (!raiz->d && raiz->nivel != nivelBuscado) //Retornou pela 1ª condição. Não há elementos do nível buscado a esquerda
        darEspacos(pow(2, altura-raiz->nivel));  //e o elemento da vez não é do nível buscado. Cálculo de espaços em branco.


    return;
}

void darEspacos(int i)
{
    while(i>0)
    {
        printf("  ");
        i--;
    }
    return;
}

//Retorna em que nível está o número buscado
tNo* busca (tNo *raiz, int num)
{
    while(raiz && raiz->valor!=num)
    {
        if(raiz->valor > num)
            raiz = raiz->e;
        else
            raiz = raiz->d;
    }

    return raiz;
}

//Remove apenas folhas. Caso o valor a ser removido não esteja em uma folha, o valor
//do nó é trocado com o da folha que contém o valor seguinte. E então a folha é removida
int removerNo (tPontArvore *semente, int num)
{
    tNo *aux, **ultimoGalho, *folha;

    aux = buscaAnterior((*semente).raiz, num);
    folha = busca(aux, num);

    if(!folha) //o elemento não está na árvore
        return 0;

    if(semente->raiz == folha && !folha->d && !folha->e) //o elemento está na raiz e está só
        semente->raiz = NULL;
    else
    {
        printf("anterior: %i\nnumero a ser removido: %i\n", aux->valor, folha->valor);

        if(aux->e == folha) //"aux" será fixado no nó que terá seu valor atualizado
        {
            ultimoGalho = &(aux->e); //"ultimoGalho" sempre deve indicar o campo que aponta
            aux = aux->e;            //para a folha. Ele receberá NULL qdo a folha for apagada
        }
        else
            if(aux->d == folha)
            {
                ultimoGalho = &(aux->d);
                aux = aux->d;
            }
/*            else
                ultimoGalho = &(semente->raiz); //é porque "aux" já é igual a folha. O elemento está na raiz
*/
        if(folha->e) //existem números menores que "num"
        {
            ultimoGalho = &(folha->e);
            folha = folha->e;
            while(folha->d)
            {
                ultimoGalho = &(folha->d);
                folha = folha->d;
            }
        }
        else
        {
            if(folha->d) //só existem números maiores que "num"
            {
                ultimoGalho = &(folha->d);
                folha = folha->d;
                while(folha->e)
                {
                    ultimoGalho = &(folha->e);
                    folha = folha->e;
                }
            }
        }
        aux->valor = folha->valor;

        if(!folha->d && !folha->e) //"*ultimoGalho" é realmente uma folha
            *ultimoGalho = NULL;
        else //"*ultimoGalho" não aponta para uma folha. Seus filhos não podem ficar orfãos
        {
            if(folha->d) //assume os filhos a direita de "folha"
                *ultimoGalho = folha->d;
            else ////assume os filhos a esquerda de "folha"
                *ultimoGalho = folha->e;

            (*ultimoGalho)->nivel--;
            atualizarNivelDosElementos(*ultimoGalho);
        }
    }
    free(folha);

    if(!atualizarAltura(semente->raiz, semente->altura))
        semente->altura--;

    return 1;
}

//Recebe um nó e atualiza o nível de todos os elementos que estão abaixo dele
void atualizarNivelDosElementos (tNo *raiz)
{
    if(raiz->e)
    {
        raiz->e->nivel = raiz->nivel + 1;
        atualizarNivelDosElementos (raiz->e);
    }
    if(raiz->d)
    {
        raiz->d->nivel = raiz->nivel + 1;
        atualizarNivelDosElementos (raiz->d);
    }
}

//Busca na árvore o primeiro elemento que contém o nível igual a altura
//desejada. A busca é interrompida assim que o nível desejado é encontrado
int atualizarAltura(tNo *raiz, int altura)
{
    if(raiz == NULL)
        return 0;
    if(raiz->nivel == altura)
        return 1;
    return atualizarAltura(raiz->e, altura) || atualizarAltura(raiz->d, altura);
}


//Chama a "calcFatorEBalanceia()" para que esta balanceie a árvore recursivamente
void balancearArvore (tPontArvore *semente)
{
    semente->raiz = calcFatorEBalanceia(semente->raiz, &(semente->altura), semente);
    semente->raiz = calcFatorEBalanceia(semente->raiz, &(semente->altura), semente);
}


//Atribui um peso para os galhos da direita e da esquerda de uma sub árvore, calcula o fator de balanceamento
//do nó, chama as rotações quando necessárias e envia para o nó pai o seu peso atravéz do "*peso"
tNo* calcFatorEBalanceia (tNo *raiz, int *peso, tPontArvore *pImprimir)
{
    int e, d;

    if(!raiz)
    {
        *peso = 0;
        return NULL;
    }

    raiz->e = calcFatorEBalanceia(raiz->e, &e, pImprimir);
    raiz->d = calcFatorEBalanceia(raiz->d, &d, pImprimir);

    if(e>d)
        *peso = 1 + e;
    else
        *peso = 1 + d;

    raiz->fatorEquilibrio = d - e;

    if(raiz->fatorEquilibrio > 1 || raiz->fatorEquilibrio < -1)
        return balanceadorDeSubArvore(raiz, pImprimir);
    else
        return raiz;

}

//Chama as rotações necessárias de acordo com o fator de balanceamento do nó e de seus filhos
tNo* balanceadorDeSubArvore(tNo* raiz, tPontArvore *pImprimir)
{
    tNo *aux;

    printf("precisa balancear o elemento %i que esta no nivel %i\n", raiz->valor, raiz->nivel);

    if(raiz->fatorEquilibrio > 1) //"raiz->fator" positivo
    {
        if(raiz->d->fatorEquilibrio < 0)
        {
            printf("fara a rotacao dupla\n");
            raiz->d = girarSentidoHorario(raiz->d);
            exibirSubArvoreEmNiveis(raiz, pImprimir->altura);
            getchar();
        }
        aux = girarSentidoAntihorario(raiz);

        if(!atualizarAltura(pImprimir->raiz, pImprimir->altura))
            pImprimir->altura--;

        exibirSubArvoreEmNiveis(aux, pImprimir->altura);
        getchar();
    }
    else //"raiz->fator" negativo
    {
        if(raiz->e->fatorEquilibrio > 0)
        {
            printf("fara a rotacao dupla\n");
            raiz->e = girarSentidoAntihorario(raiz->e);
            exibirSubArvoreEmNiveis(raiz, pImprimir->altura);
            getchar();
        }
        aux = girarSentidoHorario(raiz);

        if(!atualizarAltura(pImprimir->raiz, pImprimir->altura))
            pImprimir->altura--;

        exibirSubArvoreEmNiveis(aux, pImprimir->altura);
        getchar();
    }

    return aux;
}


//Faz a rotação no sentido horário da AVL
tNo* girarSentidoHorario (tNo* raiz)
{
    tNo *aux;

    printf("sentido horario\n");

    aux = raiz->e; //"aux" será a nova raiz

    printf("raiz %i do nivel %i\nraiz->e %i do nivel %i\n", raiz->valor, raiz->nivel, aux->valor, aux->nivel);

    raiz->e = aux->d; //"raiz->e" passa a guardar todos os filhos a direita de "aux"
    aux->d = raiz; //"aux->d" passa a guardar, além dos filhos que já tinha, "raiz"

    aux->nivel--;
    atualizarNivelDosElementos(aux);

    printf("no fim:\nraiz %i do nivel %i\nraiz->e %i do nivel %i\n", aux->valor, aux->nivel, raiz->valor, raiz->nivel);

    return aux; //nova raiz
}

//Faz a rotação no sentido antihorário da AVL
tNo* girarSentidoAntihorario (tNo* raiz)
{
    tNo *aux;

    aux = raiz->d; //"aux" será a nova raiz

    printf("raiz %i do nivel %i\nraiz->e %i do nivel %i\n", raiz->valor, raiz->nivel, aux->valor, aux->nivel);

    raiz->d = aux->e; //"raiz->d" passa a guardar todos os filhos a direita de "aux"
    aux->e = raiz; //"aux->e" passa a guardar, além dos filhos que já tinha, "raiz"

    aux->nivel--;
    atualizarNivelDosElementos(aux);

    printf("no fim\nraiz %i do nivel %i\nraiz->e %i do nivel %i\n", aux->valor, aux->nivel, raiz->valor, raiz->nivel);

    return aux; //nova raiz
}
