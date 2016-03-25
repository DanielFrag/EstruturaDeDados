#include <stdio.h>
#include <stdlib.h>


void selection_sort(int num[], int tam) 
{ 
	int i, j, min, aux;
	for (i = 0; i < (tam-1); i++) 
	{
		min = i;
		for (j = (i+1); j < tam; j++)
		{
			if(num[j] < num[min])
			{
	        	min = j;
    		}
    	}
    	if (i != min)
		{
    		aux = num[i];
    		num[i] = num[min];
    		num[min] = aux;
    	}
  	}
}

int main ()
{
	int i, v[] = {1, 3, 8, 2, 7, 9, 5, 4, 6, 0, 8, 5};
	
	
	selection_sort(v, 12);
	
	for (i=0 ; i<12 ; i++)
	{
		printf ("%i", v[i]);
	}
	return 0;
}
