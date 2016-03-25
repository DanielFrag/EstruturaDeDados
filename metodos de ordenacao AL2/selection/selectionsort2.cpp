#include <stdio.h>
#include <stdlib.h>
#define TAM 12


void pri (int num[], int maximo, int eleit, int comp)
{
	int i;

	for(i=0 ; i<maximo ; i++)
   	{
		printf("%i", num[i]);
	}

	printf("\n");

	for(i=0 ; i<maximo ; i++)
	{
		if(i==eleit || i==comp)
		{
			printf("^");
		}
		else
		{
	    	printf(" ");
		}
	}

	printf("\n");

	return;
}

void selection_sort(int num[], int tam)
{
	int i, j, minimo, aux;
	for (i = 0; i < (tam-1); i++)
	{
		minimo = i;

		printf("minimo = %i\n", num[minimo]);

		for (j = (i+1); j < tam; j++)
		{
            pri (num, TAM, j, i);
			if(num[j] < num[minimo])
			{
	        	minimo = j;

	        	printf("minimo = %i\n\n\n", num[minimo]);
    		}

    	}


    	if (i != minimo)
		{
    		aux = num[i];
    		num[i] = num[minimo];
    		num[minimo] = aux;
    	}

    	pri (num, TAM, minimo, i);
    	printf ("\n");
    	//system ("PAUSE");
  	}
}

int main ()
{
	int i, v[] = {1, 3, 8, 2, 7, 9, 5, 4, 6, 0, 8, 5};

	for (i=0 ; i<TAM ; i++)
	{
		printf ("%i", v[i]);
	}

	printf ("\n\n\n\n\n");

	selection_sort(v, TAM);

	for (i=0 ; i<TAM ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
