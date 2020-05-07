#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void create_matrix(int linhas, int colunas, int matrix[linhas][colunas])
{
	for(int i = 0; i < linhas; i++)
		for(int j = 0; j < colunas; j++)
			matrix[i][j] = rand()%10+1;
}

void print_matrix(int linhas, int colunas, int matrix[linhas][colunas])
{
	for(int i = 0; i < linhas; i++)
	{
		printf("\n");
		for(int j = 0; j < colunas; j++)
			printf("%d\t",matrix[i][j]);
	}
	printf("\n\n");
}

void find_n(int n, int linhas ,int colunas ,int matrix[linhas][colunas],int pids[linhas])
{
	int i, j;
	for(i = 0; i < linhas; i++)
	{
		pids[i]=fork();
		if(pids[i] < 0)
		{
			perror("Error in fork()");
			exit(1);
		}
		if(!pids[i])
		{
			for(j = 0; j < colunas; j++)
				if(matrix[i][j] == n) 
					printf("%d found at matriz[%d][%d] by process: %d\n", n, i+1, j+1, getpid());
			_exit(0);
		}
		else
		{
			waitpid(pids[i], NULL, 0); //corre sequencialmente;
		}
	}
}

int main (int argc,char** argv)
{
	if(argc < 2)
	{
		printf("erro no input\n");
		return 1;
	}

	srand((unsigned)time(NULL)); //pseudo-random seed

	int linhas = 5, colunas = 15;
	int n = atoi(argv[1]);
	int matrix[linhas][colunas];
	int pids[linhas];

	create_matrix(linhas, colunas, matrix);
	print_matrix(linhas, colunas, matrix);
	find_n(n, linhas, colunas, matrix, pids);

	return 0;
}
