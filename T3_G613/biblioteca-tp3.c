#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "biblioteca-tp3.h"

tabela_dispersao tabela_cria(int tamanho, hash_func *hfunc)
{
    /* aloca memoria para a estrutura tabela_dispersao */
    if (hfunc == NULL)
        return NULL;

    tabela_dispersao t = (tabela_dispersao) malloc(sizeof (struct tab_dispersao));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elemento_tabela_dispersao **) calloc(tamanho, sizeof (elemento_tabela_dispersao*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;
    t->hfunc = hfunc;
    t->tamanho_de_robots = 0;

    return t;
}

void tabela_apaga(tabela_dispersao td)
{
    int i;
    elemento_tabela_dispersao *elem, *aux;

    if (td == NULL) return;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            free(elem->robo);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int tabela_adiciona(tabela_dispersao td, const char * nome, int index_robo)
{
    int indice;
    elemento_tabela_dispersao * elem;

    if (!td || !nome) return -1;

    /* calcula hash para o robo a adicionar */
    indice = td->hfunc(nome, td->tamanho);

    /* verifica se o robo ja' existe na lista */
    elem = td->elementos[indice];
    while (elem != NULL && strcmp(elem->robo->nome, nome) != 0)
        elem = elem->proximo;

    if (elem == NULL)
    {
        /* novo robo, chave nao existe na lista */

    	if(td->tamanho_de_robots >= TAMANHO_MAX_ROBOT)
    	{
    		printf("Número máximo de robos atingido!\n");
    		return -1;
    	}
        /* aloca memoria para o elemento */
        elem = (elemento_tabela_dispersao*) malloc(sizeof (elemento_tabela_dispersao));
        if (elem == NULL)
            return -1;

        /* aloca memoria para o valoreto */
        elem->robo = (robo_tabela_dispersao*) malloc(sizeof (robo_tabela_dispersao));
        if (elem->robo == NULL)
            return -1;

        /*copia nome e index */
        strcpy(elem->robo->nome, nome);
        elem->robo->index = index_robo;

        /* insere no inicio da lista */
        elem->proximo = td->elementos[indice];
        td->elementos[indice] = elem;
        (td->tamanho_de_robots)++;
    }

    return 1;
}

int tabela_valor(tabela_dispersao td, const char *nome)
{
    int indice;
    elemento_tabela_dispersao * elem;

    if (!td) return -2;

    /* calcula hash para o robo a encontrar */
    indice = td->hfunc(nome, td->tamanho);

    /* percorre lista na posicao indice e retorna o index do robo se encontrar */
    elem = td->elementos[indice];

    while(elem != NULL)
    {
        if (!strcmp(elem->robo->nome, nome))
            return elem->robo->index;
        elem = elem->proximo;
    }
    return -1;
}

unsigned long hash_krm(const char* chave, int tamanho)
{
    unsigned long h, i;
    h = 7;
    i = 0;

    while(chave[i])
        h += chave[i++];

    return h % tamanho;
}

//A seguinte função foi criada para facilitar a análise do código do programa e tem como objetivo ler os dados do ficheiro de entrada e guarda-los num vetor.

void funcao_ler(FILE* ficheiro, robo_vetor* vetor, int* numero_robos)
{
	char str[50], nome[17], direcao[3];
	char *primeira_parte, *segunda_parte;
	int valor_do_robo, valor_da_funcao_adiciona;
	tabela_dispersao nova_tabela;

	nova_tabela = tabela_cria(1000, hash_krm);

	while(fgets(str, 50, ficheiro) != NULL)
	{
		primeira_parte = strtok(str, ",");
		segunda_parte = strtok(NULL, ",");

		while(*segunda_parte == ' ')
			segunda_parte++;

		strcpy(nome, primeira_parte);
		strcpy(direcao, segunda_parte);

		segunda_parte = direcao;

		while(*segunda_parte != '\n')
			segunda_parte++;

		*segunda_parte = '\0';

		if(strlen(nome) > 16)
		{
			printf("Nome do robot demasiado grande");
			exit(1);
		}

		valor_do_robo = tabela_valor(nova_tabela, nome);

		if(valor_do_robo == -2) exit(1);

		if(valor_do_robo == -1)
		{
			valor_da_funcao_adiciona = tabela_adiciona(nova_tabela, nome, *numero_robos);

			if(valor_da_funcao_adiciona == -1)
				exit(1);

			valor_do_robo = *numero_robos;

			strcpy(vetor[valor_do_robo].nome, nome);

			vetor[valor_do_robo].direcoes = (char*) malloc(100000 * sizeof(char));
			strcpy(vetor[valor_do_robo].direcoes, direcao);

			vetor[valor_do_robo].numero_movimentos = 1;

			(*numero_robos)++;
		} else
		{
			if(vetor[valor_do_robo].numero_movimentos >= TAMANHO_MAX_MOVIMENTOS)
			{
				printf("Número máximo de movimentos atingido!\n");
				exit(1);
			}

			vetor[valor_do_robo].direcoes = strcat(vetor[valor_do_robo].direcoes, direcao);

			(vetor[valor_do_robo].numero_movimentos)++;
		}
	}

	tabela_apaga(nova_tabela);
}

// A seguinte função foi criada para facilitar a análise do código do programa e tem como objetivo calcular o tamanho L(largura) e tamanho H(altura) do labirinto.

void tamanho_labirinto(robo_vetor* vetor, int numero_robos, int* x_minimo, int* x_maximo, int* y_minimo, int* y_maximo, int* L, int* H)
{
	int i, coordenada_x, coordenada_y, j;

	for(i = 0; i < numero_robos; i++)
	{
		coordenada_x = 0;
		coordenada_y = 0;
		j = 0;

		while(vetor[i].direcoes[j] != '\0')
		{
			switch(vetor[i].direcoes[j])
			{
			    case 'U': coordenada_y++; break;
			    case 'D': coordenada_y--; break;
			    case 'R': coordenada_x++; break;
			    case 'L': coordenada_x--; break;
			}

			if(coordenada_y > *y_maximo) *y_maximo = coordenada_y;
			else if(coordenada_y < *y_minimo) *y_minimo = coordenada_y;

			if(coordenada_x > *x_maximo) *x_maximo = coordenada_x;
			else if(coordenada_x < *x_minimo) *x_minimo = coordenada_x;

			j++;
		}
	}

	*L = (*x_maximo - *x_minimo) + 1;
	*H = (*y_maximo - *y_minimo) + 1;

	if((*L)*(*H) > TAMANHO_MAX_CELULAS || (*L) > TAMANHO_MAX_CELULAS || (*H) > TAMANHO_MAX_CELULAS)
	{
		printf("Tamanho máximo de células excedido!\n");
		exit(1);
	}
}
