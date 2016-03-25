#include <stdio.h>
#include <stdlib.h>
#define TAM 12

void printarNumerosDoVetor(int numeros[], int tam)
{
    int k;
    for (k=0 ; k<tam ; k++)
    {
        printf ("%i", numeros[k]);
    }
    printf("\n");
}

void printarPosicaoDosIndices(int tam, int indiceEsq, int indiceDir)
{
    int k;

    for (k=0 ; k<tam ; k++)
    {
        if(k==indiceEsq)
        {
            printf ("i");
        }
        else
        {
            if(k==indiceDir)
            {
                printf ("j");
            }
            else
            {
                printf(" ");
            }

        }

    }
    printf("\n");

}

void printarBlocoDeValoresComIndice(int valor[], int tam, int indiceEsq, int indiceDir)
{
    printarNumerosDoVetor(valor, tam);
    printarPosicaoDosIndices(tam, indiceEsq, indiceDir);
}

void printarPosicaoDoNumero(int posicao)
{
    while(posicao>0)
    {
        printf(" ");
        posicao--;
    }
    printf("^\n");
}

void quickSort(int valor[], int esquerda, int direita)
{
    int i, j, x, y, k;
    char e = ' ', s = '^';
    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];

    printarNumerosDoVetor(valor, TAM);
	printf("i = %i\n", i);
	printf("j = %i\n", j);
	printf("indice de referencia\n");
    printarNumerosDoVetor(valor, TAM);
    printarPosicaoDoNumero((esquerda + direita) / 2);
	printf("\n\n");

    while(i <= j)
    {
        while(valor[i] < x && i < direita)
        {
            printarBlocoDeValoresComIndice(valor, TAM, i, j);
            i++;
        }
        printarBlocoDeValoresComIndice(valor, TAM, i, j);
        printf("\nIndice da ESQUERDA ja atingiu o seu limite\n");

        while(valor[j] > x && j > esquerda)
        {
            printarBlocoDeValoresComIndice(valor, TAM, i, j);
            j--;
        }
        printarBlocoDeValoresComIndice(valor, TAM, i, j);
        printf("\nIndice da DIREITA ja atingiu o seu limite\n");

        printarBlocoDeValoresComIndice(valor, TAM, i, j);

        if(i <= j)
        {
            printf("\nPonto de mudanca encontrado\n");
            printf("valor do indice %i troca com o valor do indice %i\n", i, j);
            printarBlocoDeValoresComIndice(valor, TAM, i, j);
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
            printarNumerosDoVetor(valor, TAM);
            printf("atualiza o i para %i e o j para %i\n", i, j);
        }

        printf("\n\nresultado parcial:\n");
    	printarNumerosDoVetor(valor, TAM);

		printf("\n");
		//system ("PAUSE");
    }

    printarNumerosDoVetor(valor, TAM);
    printarPosicaoDoNumero((esquerda + direita) / 2);

    if(j > esquerda)
    {
    	printf("\nRecursiva da posicao %i ate a posicao %i\n", esquerda, j);
        quickSort(valor, esquerda, j);
    }
    if(i < direita)
    {
    	printf("\nRecursiva da posicao %i ate a posicao %i\n", i, direita);
        quickSort(valor,  i, direita);
    }
}

int main ()
{
	int i, v[] = {1, 3, 8, 5, 7, 0, 5, 4, 6, 9, 8, 2};


	quickSort(v, 0, 11);

	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
