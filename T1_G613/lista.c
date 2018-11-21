/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2013/14          */      
/*****************************************************************/

#include "lista.h"
#include <string.h>
#include <stdlib.h>

/* Criamos a seguinte função para que facilitasse outras funções reduzindo as linhas de código */

elemento* busca_elemento(lista *lst, int pos)
{
	elemento* atual = lst->raiz;
	int i;

	if ((pos < 0) || (pos >= lst->tamanho)) return NULL;

	for(i = 0; i < pos; i++) atual = atual->proximo;

	return atual;
}


lista* lista_nova()
{
    lista* nova = (lista*) malloc(sizeof(lista));

    if(nova == NULL) return NULL;

    nova->raiz = NULL;
    nova->tamanho = 0;
    
	return nova;
}


void lista_apaga(lista *lst)
{
	elemento *aux;

	if(lst == NULL) return;

	while(lst->raiz != NULL)
	{
		aux = lst->raiz;
		lst->raiz = lst->raiz->proximo;

		free(aux->str);
		free (aux);
	}

	free(lst);
}


int lista_tamanho(lista *lst)
{
	if(lst == NULL) return -1;

	return lst->tamanho;
}


const char* lista_elemento(lista *lst, int pos)
{
	elemento* atual = busca_elemento(lst, pos);

	if(atual == NULL) return NULL;

	return atual->str;
}


int lista_atribui(lista *lst, int pos, const char* str)
{
	elemento* atual = busca_elemento(lst, pos);

	free(atual->str);

	atual->str = strdup(str);

	return pos;
}


int lista_insere(lista *lst, const char* valor, int pos)
{
	elemento *anterior, *atual, *insere = (elemento*) malloc(sizeof(elemento));

	int tamanho = lst->tamanho + 1;

	insere->str = strdup(valor);

	if(pos == -1)
	{
		if(lst->tamanho == 0)
			{
				atual = lst->raiz;

				lst->raiz = insere;
				insere->proximo = atual;

				lst->tamanho = tamanho;

				return pos;
			}


		anterior = busca_elemento(lst, lst->tamanho - 1);

		anterior->proximo = insere;
		insere->proximo = NULL;

		lst->tamanho = tamanho;

		return lst->tamanho - 1;
	}

	if(pos == 0)
	{
		atual = lst->raiz;

		lst->raiz = insere;
		insere->proximo = atual;

		lst->tamanho = tamanho;

		return pos;
	}

	anterior = busca_elemento(lst, pos - 1);
	atual = busca_elemento(lst, pos);

	if (anterior == NULL || atual == NULL)
	{
		return -1;
	}

	anterior->proximo = insere;
	insere->proximo = atual;

	lst->tamanho = tamanho;

	return pos;
}


int lista_remove(lista *lst, int pos)
{
	elemento *anterior = busca_elemento(lst, pos - 1), *atual = busca_elemento(lst, pos);

	if(pos == 0)
	{
		lst->raiz = atual->proximo;

		free(atual->str);
		free(atual);

		(lst->tamanho)--;

		return 0;
	}

	if(anterior == NULL || atual == NULL) return -1;

	anterior->proximo = atual->proximo;

	free(atual->str);
	free(atual);

	(lst->tamanho)--;

	return 0;
}


int lista_pesquisa(lista *lst, const char* str, int origem)
{
	elemento *atual = lst->raiz;

	int i, pos = -1;


	if(origem == INICIO)
	{
		for(i = 0; i < lst->tamanho; i++)
		{
			if(strcmp(atual->str, str) == 0) return i;

			atual = atual->proximo;
		}

		return -1;
	}

	if(origem == FIM)
	{
		for(i = 0; i < lst->tamanho; i++)
		{
			if(strcmp(atual->str, str) == 0) pos = i;

			atual = atual->proximo;
		}

		return pos;
	}

	return -1;
}


int lista_ordena(lista *lst)
{
	elemento *elemento_atual, *proximo_elemento , *elemento_auxiliar, *elemento_anterior, *elemento_anterior_auxiliar;
	int i,j;

	if(lst == NULL) return -1;
	if(lst->tamanho == 0 || lst->tamanho == 1) return 0;

	for(i = 0; i < lst->tamanho - 1; i++)
	{
		elemento_atual = busca_elemento(lst, i);
		proximo_elemento = elemento_atual->proximo;

		for(j = i ; j < lst->tamanho; j++)
		{
			if(strcmp(proximo_elemento->str, elemento_atual->str) < 0)
			{
				if(j == i)
				{
					elemento_auxiliar = proximo_elemento->proximo;
					proximo_elemento->proximo = elemento_atual;
					elemento_atual->proximo = elemento_auxiliar;
					elemento_anterior = busca_elemento(lst,i - 1);
					elemento_anterior->proximo = proximo_elemento;
				}

				else
				{
					elemento_anterior_auxiliar = busca_elemento(lst, j);
					elemento_anterior = busca_elemento(lst, i - 1);
					elemento_auxiliar = proximo_elemento->proximo;
					proximo_elemento->proximo = elemento_atual->proximo;
					elemento_atual->proximo = elemento_auxiliar;
					elemento_anterior_auxiliar->proximo = elemento_anterior->proximo;
					elemento_anterior->proximo = proximo_elemento;
				}

				proximo_elemento = elemento_atual;
				elemento_atual = elemento_anterior->proximo;
			}

			elemento_auxiliar = proximo_elemento->proximo;

			if(elemento_auxiliar != NULL) proximo_elemento = elemento_auxiliar;
		}
	}

	return 0;
}


int lista_compara(lista *lst1, lista *lst2)
{
	elemento *elemento_lista_1, *elemento_lista_2;
	int i;

	if(lst1->tamanho != lst2->tamanho) return 0;

	for(i = 0; i < lst1->tamanho; i++)
	{
		elemento_lista_1 = busca_elemento(lst1, i);
		elemento_lista_2 = busca_elemento(lst2, i);

		if(strcmp(elemento_lista_1->str, elemento_lista_2->str) == 0) return 1;

		return 0;
	}
	return -1;
}


lista* lista_inverte(lista *lst)
{
	lista* invertida = lista_nova();
	int i;

	if(invertida == NULL) return NULL;

	for(i = lst->tamanho - 1; i >= 0 ; i--)
	{
		lista_insere(invertida, busca_elemento(lst, i)->str, -1);
	}

	return invertida;
}
