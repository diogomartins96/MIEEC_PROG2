#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "biblioteca-tp3.h"

int main(int argc, char** argv)
{
	FILE *f, *f_saida;
	robo_vetor vetor[TAMANHO_MAX_ROBOT];
	int numero_de_robos = 0, x_minimo = 0, x_maximo = 0, y_minimo = 0, y_maximo = 0, L, H, x_entrada, y_entrada, i, j, x, y, x_saida, y_saida, x_fonte, y_fonte, tamanho_vetor_primeira_parte, tamanho_vetor_segunda_parte, tamanho_caminho_curto;
	grafo* g;
	int *vetor_caminho_rapido_primeira_parte, *vetor_caminho_rapido_segunda_parte;
	char caminho_curto[TAMANHO_MAX_MOVIMENTOS] = {'\0'}, robo_mais_curto[17] = "0";
	char *caracter_teste, *caracter_teste_2;

	if(argc != 2)
	{
		printf("Numero de ficheiros lidos incorreto!\n");
		exit(1);
	}

	f = fopen(argv[1], "r");

	if(f == NULL)
	{
		printf("Impossivel abrir ficheiro!\n");
		exit(1);
	}

	f_saida = fopen("output.txt", "w");

	if(f == NULL)
	{
		printf("Impossivel criar ficheiro de saída!");
		exit(1);
	}

	funcao_ler(f, vetor, &numero_de_robos);

	fclose(f);

	tamanho_labirinto(vetor, numero_de_robos, &x_minimo, &x_maximo, &y_minimo, &y_maximo, &L, &H);

	char labirinto[H][L];

	//Preencher todas as posiçoes do labirinto com '*'.

	for(i = 0; i < H; i++)
	{
		for(j = 0; j < L; j++)
		{
			labirinto[i][j] = '*';
		}
	}

	//Encontrar a posição de entrada.

	if(x_minimo == 0)
	{
		x_entrada = 0;
		y_entrada = H + y_minimo - 1;
	}
	else if(x_maximo == 0)
	{
		x_entrada = L - 1;
		y_entrada = H + y_minimo - 1;
	}
	else if(y_minimo == 0)
	{
		y_entrada = H - 1;
		x_entrada = L - x_maximo - 1;
	}
	else if(y_maximo == 0)
	{
		y_entrada = 0;
		x_entrada = L - x_maximo - 1;
	}

	//Completar o labirinto.

	for(i = 0; i < numero_de_robos; i++)
	{
		j = 0;
		x = x_entrada;
		y = y_entrada;

		while(vetor[i].direcoes[j] != '\0')
		{

			switch(vetor[i].direcoes[j])
			{
				case 'U': y--; labirinto[y][x] = '.'; break;
				case 'D': y++; labirinto[y][x] = '.'; break;
				case 'R': x++; labirinto[y][x] = '.'; break;
				case 'L': x--; labirinto[y][x] = '.'; break;
				case '?': labirinto[y][x] = 'w'; x_fonte = x; y_fonte = y; break;
				case '!': labirinto[y][x] = 's'; x_saida = x; y_saida = y; break;
			}

			j++;
		}
	}

	labirinto[y_entrada][x_entrada] = 'e';

	//Encontrar o caminho mais curto usando um grafo.

	g = grafo_novo(L * H, NAODIRECIONADO);

	for(i = 0; i < H; i++)
	{
		for(j = 0; j < L - 1; j++)
		{
			if(labirinto[i][j] == '*' || labirinto[i][j+1] == '*') continue;

			grafo_adiciona(g, L*i+j, L*i+j+1);
		}
	}

	for(j = 0; j < L; j++)
	{
		for(i = 0; i < H - 1; i++)
		{
			if(labirinto[i][j] == '*' || labirinto[i+1][j] == '*') continue;

			grafo_adiciona(g, L*i+j, L*(i+1)+j);
		}
	}

	vetor_caminho_rapido_primeira_parte = grafo_bfs(g, L*y_entrada + x_entrada, L*y_fonte + x_fonte, &tamanho_vetor_primeira_parte);

	vetor_caminho_rapido_segunda_parte = grafo_bfs(g, L*y_fonte + x_fonte, L*y_saida + x_saida, &tamanho_vetor_segunda_parte);

	for(i = 0; i < tamanho_vetor_primeira_parte; i++)
	{
		if(vetor_caminho_rapido_primeira_parte[i+1] - vetor_caminho_rapido_primeira_parte[i] == 1)
			strcat(caminho_curto, "r");

		else if(vetor_caminho_rapido_primeira_parte[i+1] - vetor_caminho_rapido_primeira_parte[i] == -1)
			strcat(caminho_curto, "l");

		else if(vetor_caminho_rapido_primeira_parte[i+1] - vetor_caminho_rapido_primeira_parte[i] == L)
			strcat(caminho_curto, "d");

		else if(vetor_caminho_rapido_primeira_parte[i+1] - vetor_caminho_rapido_primeira_parte[i] == -L)
			strcat(caminho_curto, "u");
	}

	for(i = 0; i < tamanho_vetor_segunda_parte; i++)
	{
		if(vetor_caminho_rapido_segunda_parte[i+1] - vetor_caminho_rapido_segunda_parte[i] == 1)
			strcat(caminho_curto, "r");

		else if(vetor_caminho_rapido_segunda_parte[i+1] - vetor_caminho_rapido_segunda_parte[i] == -1)
			strcat(caminho_curto, "l");

		else if(vetor_caminho_rapido_segunda_parte[i+1] - vetor_caminho_rapido_segunda_parte[i] == L)
			strcat(caminho_curto, "d");

		else if(vetor_caminho_rapido_segunda_parte[i+1] - vetor_caminho_rapido_segunda_parte[i] == -L)
			strcat(caminho_curto, "u");
	}

	//Encontrar o robo que fez o caminho mais curto.

	tamanho_caminho_curto = tamanho_vetor_primeira_parte + tamanho_vetor_segunda_parte;

	for(i = 0; i < numero_de_robos; i++)
	{
		if(vetor[i].numero_movimentos + 2 == tamanho_caminho_curto)
		{
			caracter_teste = strchr (vetor[i].direcoes, '?');

			if(caracter_teste != NULL)
			{
				caracter_teste_2 = strchr (vetor[i].direcoes, '!');

				if(caracter_teste_2 != NULL)
					strcpy(robo_mais_curto, vetor[i].nome);
			}
		}
	}

	fprintf(f_saida, "%d %d\n", L, H);

	for(i = 0; i < H; i++)
	{
		for(j = 0; j < L; j++)
		{
			fprintf(f_saida, "%c", labirinto[i][j]);
		}

		fprintf(f_saida, "\n");
	}

	fprintf(f_saida, "%s\n", caminho_curto);

	fprintf(f_saida, "%s\n", robo_mais_curto);

	fclose(f_saida);
}
