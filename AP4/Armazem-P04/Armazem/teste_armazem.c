#include <stdio.h>
#include <stdlib.h>
#include "fila_contentores.h"
#include "armazem.h"

void imprimeArmazem(armazem *armz);

int main()
{
	int i;
	contentor *c1;
	lista *lst = lista_nova();
	armazem *armz = armazem_novo();

	printf("Armazem Portuario\n");
	c1 = contentor_novo("Brazil", 230);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("UK", 250);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("France", 530);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Spain", 710);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("China", 380);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Germany", 390);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Venezuela", 100);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Turkey", 80);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Netherlands", 380);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Iceland", 150);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Thailand", 270);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("India", 430);
	lista_insere(lst, c1, -1);
	c1 = contentor_novo("Finland", 200);
	lista_insere(lst, c1, -1);

	for (i = 0; i < lista_tamanho(lst); i++) {
		if (!descarregar_camiao(armz, lista_elemento(lst, i))) {
			printf("Armazem cheio\n");
			break;
		}
	}

	printf("\n\n* Dia 1: Valor da carga em armazem %.2f \n", referencia_seguro(armz));
	imprimeArmazem(armz);

	for (i = 0; i < 8; i++) {
		c1 = carregar_navio(armz);
		printf("Carregado contentor em navio.\n");
		contentor_imprime(c1);
	}
	
	printf("\n\n* Dia 2: Valor da carga em armazem %.2f \n", referencia_seguro(armz));
	imprimeArmazem(armz);
	
	while (!armazem_vazio(armz)) {
		c1 = carregar_navio(armz);
		printf("Carregado contentor em navio.\n");
		contentor_imprime(c1);
	}

	printf("\n\n* Historico:\n");
	ordenar_registo(armz);
	imprimir_registo(armz);
}

void imprimeArmazem(armazem *armz)
{
	int i, j, n;
	int *nContentores;
	filaItem *p;

	if(armz && armz->contentores)
	{
		nContentores = (int*)calloc(armz->contentores->tamanho, sizeof(int));
		n = armz->contentores->tamanho;

		p = armz->contentores->raiz;
		i = 0;
		while(p)
		{
			nContentores[i] = p->elemento->tamanho;
			p = p->proximo;
			i++;
		}

		printf("\n");
		for(j = armz->altura; j > 0; j--)
		{
			printf("  ");
			for(i = 0; i < n; i++)
			{
				if(nContentores[i] >= j)
					printf("[]  ");
				else
					printf("    ");
			}
			printf("\n");
		}
		printf("==");
		for(i = 0; i < armz->comprimento; i++)
		{
			printf("====");
		}
		printf("\n\n");

		free(nContentores);
	}
}