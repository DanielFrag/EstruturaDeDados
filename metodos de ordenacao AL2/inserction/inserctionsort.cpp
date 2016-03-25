#include <stdio.h>
#include <stdlib.h>

void printarNumerosDoVetor(int numeros[], int tam)
{
    int k;
    for (k=0 ; k<tam ; k++)
    {
        printf ("%i", numeros[k]);
    }
    printf("\n");
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

void printarVetorDuranteMovimentacao(int vetor[], int tam, int posEmBranco)
{
    int k;
    for (k=0 ; k<tam ; k++)
    {
        if(k==posEmBranco)
            printf (" ");
        else
            printf ("%i", vetor[k]);
    }
    printf("\n");
}

void insertionSort(int numeros[], int tam)
{
   int i, j, eleito, temp;

    for (i = 1; i < tam; i++)
    {
        eleito = numeros[i];
        printf("numero gravado em 'eleito': %i\n\n", eleito);

        printarNumerosDoVetor(numeros, tam);
        printarPosicaoDoNumero(i);

        j = i - 1;

        while ((j>=0) && (eleito < numeros[j]))
        {
            numeros[j+1] = numeros[j];
            printarVetorDuranteMovimentacao(numeros, tam, j);
            j--;
        }

        numeros[j+1] = eleito;
        printarNumerosDoVetor(numeros, tam);
        printf("\n\n\n");
    }
}


int main ()
{
	int i, v[] = {9, 8, 3, 1, 7, 2, 5, 4, 6, 0, 8, 5};

	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}

	printf("\n\n\n");

	insertionSort(v, 12);

	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
