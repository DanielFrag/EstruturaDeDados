#include <stdio.h>
#include <stdlib.h>


void merge(int vec[], int vecSize)
{
    int mid;
    int i, j, k, z;
    int* tmp;

    //printf ("%p\n", vec);

    //printa o vetor principal
    for (z=0 ; z<vecSize ; z++)
	{
		printf ("%i", vec[z]);
	}
	printf("\n\n");

    //aloca um vetor temporario com o msm tamanho do vetor a ser ordenado
    tmp = (int*) malloc(vecSize * sizeof(int));
    //teste de alocacao de memoria
    if (tmp == NULL)
    {
        exit(1);
    }
    //acha o meio do vetor
    mid = vecSize / 2;

    i = 0;
    j = mid;
    k = 0;
    //"i" percorre o vetor do inicio até a metade e "j" da metade até o fim
    //compara o valor da posicao "i" com o da posicao "j" e escolhe o menor valor para coloca-lo no vetor temporário
    //o indice do valor escolhido é incrementado
    while (i < mid && j < vecSize)
    {
        if (vec[i] <= vec[j])
        {
            tmp[k] = vec[i++];
        }
        else
        {
            tmp[k] = vec[j++];
        }
        ++k;
    }
    //coloca os valores restantes no vetor temporário
    if (i == mid)
    {
        while (j < vecSize)
        {
            tmp[k++] = vec[j++];
        }
    }
    else
    {
        while (i < mid)
        {
            tmp[k++] = vec[i++];
        }
    }
    //printa a ordenação do vetor
    for (z=0 ; z<vecSize ; z++)
	{
		printf ("%i", tmp[z]);
	}
    //passa o resultado do vetor temporário para o original
    for (i = 0; i < vecSize; ++i)
    {
        vec[i] = tmp[i];
    }


	printf("\nfim da ordenacao\n\n");

	//system ("PAUSE");

    //libera o espaco na memoria que o vetor temporario usou
    free(tmp);
}
//funcao que divide recursivamente o vetor na metade
void mergeSort(int vec[], int vecSize)
{
    int mid;

    if (vecSize > 1)
    {
        //quebra o vetor em dois pedacos
        mid = vecSize / 2;
        printf("tamanho do vetor = %i\n", vecSize);
        //manda ordenar a primeira parte do vetor
        mergeSort(vec, mid);
        //manda ordenar a segunda parte do vetor
        mergeSort(vec + mid, vecSize - mid);
        merge(vec, vecSize);
    }
    else
    {
        printf("Vetor com apenas uma posicao. Caso base atingido.\n");
    }
}

int main ()
{
    int i, v[] = {1, 8, 3, 9, 7, 2, 5, 4, 6, 0, 8, 5};

	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}

	printf("\n\n\n");

	mergeSort(v, 12);

	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
