#include <stdio.h>
#include <stdlib.h>


void quickSort(int valor[], int esquerda, int direita)
{
    int i, j, x, y;
    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];
 
    while(i <= j)
    {
        while(valor[i] < x && i < direita)
        {
            i++;
        }
        while(valor[j] > x && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickSort(valor, esquerda, j);
    }
    if(i < direita)
    {
        quickSort(valor,  i, direita);
    }
}

int main ()
{
	int i, v[] = {1, 3, 8, 2, 7, 9, 5, 4, 6, 0, 8, 5};
	
	
	quickSort(v, 0, 11);
	
	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
