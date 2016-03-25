 #include <stdio.h>

int main(void)
{
	int vetor[12] = {1, 8, 3, 9, 7, 2, 5, 4, 6, 0, 8, 5};
	int tamanho = 12;
	int aux, i, j;
	
	for(i=tamanho-1; i >= 1; i--)
	{  
		for(j=0; j < i ; j++)
		{
			if(vetor[j]>vetor[j+1])
			{
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
	
}
