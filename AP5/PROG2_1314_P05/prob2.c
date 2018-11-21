#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

int vetor_conta_ocorrencia(vetor* v, const char* valor)
{
	return -1;
}

vetor* lista_vetor_filtra(lista *lst, char l)
{
	return NULL;
}

lista* lista_intercala(lista *l1, lista *l2)
{
	return NULL;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor* lerAtores(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	vetor* atores;
	
	if (ficheiro == NULL)
		return NULL;

	atores = vetor_novo();

	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		vetor_insere(atores,buffer,-1);
	}

	return atores;
}

lista* lerFilmes(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* filmes;
	
	if (ficheiro == NULL)
		return NULL;

	filmes = lista_nova();
	
	while(!feof(ficheiro)) 
	{	
		fgets(buffer, 255, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr) 
			*nlptr = '\0';
		
		lista_insere(filmes,buffer,-1);
	}

	return filmes;
}

int main()
{
	int i;
	FILE *fa, *ff, *ff2;
	vetor *atores, *resultado;
	lista *filmes, *filmes2, *l_intercala;
	
	fa = fopen("atores.txt","r");
	ff = fopen("filmes.txt","r");
	ff2 = fopen("filmes2.txt","r");
	
	atores = lerAtores(fa);
	filmes = lerFilmes(ff);
	filmes2 = lerFilmes(ff2);

	/* testes */
	
	puts("********************");
	/* testa conta ocorrencia */
	/* elemento existente */
	printf("conta ocorrencia: %d (esperado: 6)\n", vetor_conta_ocorrencia(atores, "Will Smith"));
	/* elemento não existente */
	printf("conta ocorrencia: %d (esperado: 0)\n", vetor_conta_ocorrencia(atores, "Will Smithy"));

	puts("********************");
	/* testa lista filtra */
	resultado = lista_vetor_filtra(filmes2, 'D');
	if(resultado == NULL)
		printf("filtragem da lista: (null)\n");
	else
	{
		for(i=0; i<vetor_tamanho(resultado); i++)
			puts(vetor_elemento(resultado, i));
	}

	puts("********************");
	/* teste intercala */
	l_intercala = lista_intercala(filmes, filmes);
	printf("intercala:\n%d (esperado: %d)\n", lista_tamanho(l_intercala), lista_tamanho(filmes)*2);
	l_intercala = lista_intercala(NULL, filmes2);
	printf("%d (esperado: %d)\n", lista_tamanho(l_intercala), lista_tamanho(filmes2));
	l_intercala = lista_intercala(filmes2, NULL);
	printf("%d (esperado: %d)\n", lista_tamanho(l_intercala), lista_tamanho(filmes2));
	l_intercala = lista_intercala(NULL, NULL);
	printf("%s (esperado: null)\n", l_intercala==NULL ? "null" : "not null");
	l_intercala = lista_intercala(filmes, filmes2);
	printf("%d (esperado: %d)\n", lista_tamanho(l_intercala), lista_tamanho(filmes2)+lista_tamanho(filmes));

	return 0;
}