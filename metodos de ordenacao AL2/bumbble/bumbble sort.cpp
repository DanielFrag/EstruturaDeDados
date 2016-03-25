#include <stdio.h>

int main(void)
{
	int vetor[] = {1, 8, 3, 9, 7, 2, 5, 4, 6, 0, 8, 5};
 
	int tamanho = 12, i, j, r;
	int aux;
	
	for(r = 0; r < 12; r++)
	{
	   printf("%d",vetor[r]);
 	}
	
	printf("\n\n\n");
	
	for(i=tamanho-1; i >= 1; i--)
	{
		for(j=0; j < i ; j++) 
		{
			if(vetor[j]>vetor[j+1])
			{
				aux = vetor[j];
       			vetor[j] = vetor[j+1];
        		vetor[j+1] = aux;
        		
        		for(r = 0; r < 12; r++)
				{
				   printf("%d",vetor[r]);
			 	}
		
				printf("\n");
				
				for(r = 0; r < 12; r++)
				{
				   if(r==j || r==j+1)
				   {
				   		printf("^");
				   }
				   else
				   {
				   		printf(" ");
				   }
			 	}
			 	
			 	printf("\n"); 
        	}        	
      	}

		printf("\n\n\n");
	}
 
	for(r = 0; r < 12; r++)
	{
	   printf("%d",vetor[r]);
 	}
}
