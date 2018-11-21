/*****************************************************************/
/* Trabalho pratico 2 - Tab. Dispersao | PROG2 | MIEEC | 2013/14 */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"

// A seguinte funcao foi criada para facilitar a funcao tabela_apaga.

void lista_apaga(elemento* lista)
{
	elemento* auxiliar;

	while(lista != NULL)
	{
		auxiliar = lista->proximo;
		free(lista->obj);
		free(lista);
		lista = auxiliar;
	}
}

tabela_dispersao tabela_cria(int tamanho, hash_func *hfunc)
{
	if(hfunc == NULL) return NULL;

	tabela_dispersao nova_tabela = (tabela_dispersao) malloc(sizeof(tabela_dispersao));

	if(nova_tabela == NULL) return NULL;

	nova_tabela->elementos = (elemento**) malloc(tamanho*sizeof(elemento*));

	if(nova_tabela->elementos == NULL)
	{
		free(nova_tabela);
		return NULL;
	}

	nova_tabela->hfunc = hfunc;
	nova_tabela->tamanho = tamanho;

	return nova_tabela;
}

void tabela_apaga(tabela_dispersao td)
{
	if(td == NULL) return;

	int i;

	for(i = 0; i < td->tamanho; i++)
	{
		lista_apaga(td->elementos[i]);
	}

	free(td->elementos);
	free(td);
}

int tabela_adiciona(tabela_dispersao td, const objeto *valor)
{
	if(td == NULL) return TABDISPERSAO_INVALIDA;

	int posicao;

	posicao = td->hfunc(valor->chave, td->tamanho);

	objeto* novo_objeto = (objeto*) malloc(sizeof(objeto));

		if(novo_objeto == NULL) return TABDISPERSAO_ERRO;

		strcpy(novo_objeto->chave, valor->chave);
		strcpy(novo_objeto->valor, valor->valor);

	elemento* novo_elemento = (elemento*) malloc(sizeof(elemento));

		if(novo_elemento == NULL) return TABDISPERSAO_ERRO;

		novo_elemento->obj = novo_objeto;
		novo_elemento->proximo = NULL;

		if(td->elementos[posicao] == NULL)
		{
			td->elementos[posicao] = novo_elemento;
			return TABDISPERSAO_OK;
		}

		while(td->elementos[posicao] != NULL)
		{
			if(strcmp(td->elementos[posicao]->obj->chave, novo_elemento->obj->chave) == 0)
			{
				strcpy(td->elementos[posicao]->obj->valor, novo_elemento->obj->valor);
				free(novo_objeto);
				free(novo_elemento);

				return TABDISPERSAO_OK;
			}

			if(td->elementos[posicao]->proximo == NULL) break;

			td->elementos[posicao] = td->elementos[posicao]->proximo;
		}

		td->elementos[posicao]->proximo = novo_elemento;

		return TABDISPERSAO_OK;
}

int tabela_remove(tabela_dispersao td, const char *chave)
{
	if(td == NULL) return TABDISPERSAO_INVALIDA;

	int posicao;
	elemento* elemento_auxiliar;

	posicao = td->hfunc(chave, td->tamanho);

	if(td->elementos[posicao] == NULL) return TABDISPERSAO_NAOEXISTE;

	while(td->elementos[posicao] != NULL)
	{
		if(strcmp(td->elementos[posicao]->obj->chave, chave) == 0)
		{
			elemento_auxiliar = td->elementos[posicao]->proximo;
			free(td->elementos[posicao]->obj);
			free(td->elementos[posicao]);

			td->elementos[posicao] = elemento_auxiliar;

			return TABDISPERSAO_OK;
		}

		if(td->elementos[posicao]->proximo == NULL) break;

		td->elementos[posicao] = td->elementos[posicao]->proximo;
	}

    return TABDISPERSAO_NAOEXISTE;
}

int tabela_existe(tabela_dispersao td, const char *chave)
{
	if(td == NULL) return TABDISPERSAO_INVALIDA;

	int posicao;

	posicao = td->hfunc(chave, td->tamanho);

	if(td->elementos[posicao] == NULL) return TABDISPERSAO_NAOEXISTE;

	while(td->elementos[posicao] != NULL)
	{
		if(strcmp(td->elementos[posicao]->obj->chave, chave) == 0)
		{
			return TABDISPERSAO_EXISTE;
		}

		if(td->elementos[posicao]->proximo == NULL) break;

		td->elementos[posicao] = td->elementos[posicao]->proximo;
	}

    return TABDISPERSAO_NAOEXISTE;
}

const char* tabela_valor(tabela_dispersao td, const char *chave)
{
	if(td == NULL) return NULL;

	int posicao;

	posicao = td->hfunc(chave, td->tamanho);

	if(td->elementos[posicao] == NULL) return NULL;

	while(td->elementos[posicao] != NULL)
	{
		if(strcmp(td->elementos[posicao]->obj->chave, chave) == 0)
		{
			return td->elementos[posicao]->obj->valor;
		}

		if(td->elementos[posicao]->proximo == NULL) break;

		td->elementos[posicao] = td->elementos[posicao]->proximo;
	}

	return NULL;
}

int tabela_esvazia(tabela_dispersao td)
{
	if(td == NULL) return TABDISPERSAO_INVALIDA;

	int i;
	elemento* elemento_auxiliar;

	for(i = 0; i < td->tamanho; i++)
	{
		while(td->elementos[i] != NULL)
		{
			elemento_auxiliar = td->elementos[i]->proximo;

			free(td->elementos[i]->obj);
			free(td->elementos[i]);

			td->elementos[i] = elemento_auxiliar;
		}
	}

	return TABDISPERSAO_OK;
}

int tabela_numelementos(tabela_dispersao td)
{
	if(td == NULL) return TABDISPERSAO_INVALIDA;

	int i, numero_elementos = 0;

	for(i = 0; i < td->tamanho; i++)
	{
		while(td->elementos[i] != NULL)
		{
			numero_elementos++;

			td->elementos[i] = td->elementos[i]->proximo;
		}
	}

	return numero_elementos;
}

objeto* tabela_elementos(tabela_dispersao td, int *n)
{
	if(td == NULL) return NULL;

	objeto* vetor;

	vetor = (objeto*) malloc(sizeof(objeto));

	if(vetor == NULL) return NULL;

	int i;

	*n = 0;

	for(i = 0; i < td->tamanho; i++)
	{
		while(td->elementos[i] != NULL)
		{
			strcpy(vetor[*n].chave, td->elementos[i]->obj->chave);
			strcpy(vetor[*n].valor, td->elementos[i]->obj->valor);

			(*n)++;

			if(td->elementos[i]->proximo == NULL) break;

			vetor = (objeto*) realloc(vetor, (*n) + 1);


			td->elementos[i] = td->elementos[i]->proximo;
		}
	}

	if(*n == 0) return NULL;

	return vetor;
}

unsigned long hash_krm(const char* chave, int tamanho)
{
	unsigned int valor_hash = 7;

	while(*chave != '\0')
	{
		valor_hash += *chave;
		chave++;
	}

	return valor_hash % tamanho;
}

unsigned long hash_djbm(const char* chave, int tamanho)
{
	unsigned int valor_hash = 5347;

	while(*chave != '\0')
	{
		valor_hash = (valor_hash * 31) ^ *chave;
		chave++;
	}

	return valor_hash % tamanho;
}

/*================================================================================*/
void mostraTabela(tabela_dispersao td)
{
	int i;
	elemento * elem;
	printf("TABELA DE DISPERSAO (%d elementos)\n", tabela_numelementos(td));
	for (i = 0; i < td->tamanho; i++)
	{
		if (td->elementos[i])
		{
			printf("\t[%2d]", i);
			elem = td->elementos[i];
			while (elem)
			{
				printf(" : [\"%s\" :: \"%s\"]", elem->obj->chave, elem->obj->valor);
				elem = elem->proximo;
			}
			printf("\n");
		}
	}
	printf("\n");
}
