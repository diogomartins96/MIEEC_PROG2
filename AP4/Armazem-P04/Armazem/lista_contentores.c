
#include "lista_contentores.h"
#include <string.h>
#include <stdlib.h>

listaItem* lista_novo_elemento(contentor* contr)
{
	/* aloca memoria para a estrutura listaItem */
	listaItem *item = (listaItem *) malloc(sizeof(listaItem));
	if(item == NULL) 
		return NULL;

	/* cria novo contentor */
	item->elemento = contentor_novo(contr->destino, contr->valor);
	if(item->elemento == NULL) 
	{
		free(item);
		return NULL;
	}

	/* item ainda nao tem proximo */
	item->proximo = NULL;

	return item;
}

lista* lista_nova()
{
	/* cria lista */
	lista *lst = (lista*) malloc(sizeof(lista));
	if(lst == NULL)
		return NULL;
	
	/* lista esta' vazia */
	lst->raiz = NULL;
	lst->tamanho = 0;

  return lst;
}


void lista_apaga(lista *lst)
{
	listaItem *item;
	
	if(lst==NULL)
		return;

	/* percorre toda a lista e liberta memoria de
	   cada contentor e respectiva string */
	while(lst->raiz)
	{
		item = lst->raiz;
		lst->raiz = lst->raiz->proximo;
		contentor_apaga(item->elemento);
		free(item);
	}
	
	free(lst);

	return;
}


int lista_tamanho(lista *lst)
{
	if (lst == NULL)
		return -1;

	return lst->tamanho;
}


contentor* lista_elemento(lista *lst, int pos)
{ 
	int i=0;
	listaItem *item;

	if (lst == NULL || pos < 0)
		return NULL;
	
	item = lst->raiz;

	/* procura item na posicao pos */
	for (i = 0; i < pos && item != NULL; i++)
		item = item->proximo;
	
	/* se item e' NULL entao nao existe posicao pos */
	if (item == NULL)
		return NULL;

	return item->elemento;
}


int lista_atribui(lista *lst, int pos, contentor* contr)
{
	int i=0;
	listaItem *item;

	if (lst == NULL || pos < 0)
		return -1;

	item = lst->raiz;

	/* procura item na posicao pos */
	for (i = 0; i < pos && item != NULL; i++)
		item = item->proximo;

	/* se item e' NULL entao nao existe posicao pos */
	if (item == NULL)
		return -1;

	/* realoca o espaco */
	item->elemento->destino = (char *) realloc(item->elemento->destino, sizeof(char) * (strlen(contr->destino)+1));
	
	/* copia contentor */
	strcpy(item->elemento->destino, contr->destino);
	item->elemento->valor = contr->valor;

	return pos;
}


int lista_insere(lista *lst, contentor* contr, int pos)
{
	int i=0;
	listaItem *curr = NULL, *temp;

	if (contr == NULL)
		return -1;
		
	if (lst == NULL || pos < -1 || pos >= lst->tamanho)
		return -1;
	
	temp = lst->raiz;

	/* cria novo item */
	curr = lista_novo_elemento(contr);
	
	if (curr == NULL)
        return -1;
	
	lst->tamanho++;
	
	/* caso especial: inserir no fim da lista */
	if(pos == -1)
	{
		/* se e' primeiro elemento */
		if (temp == NULL)
		{
			lst->raiz = curr;    
		}
		else
		{
			/* percorre lista ate' chegar ao ultimo item */
			while (temp->proximo != NULL) 
			{
				temp = temp->proximo;  
			}
			temp->proximo = curr;
		}
		
		return lst->tamanho-1;
	}

	/* caso especial: inserir no inicio da lista */
	if (pos == 0) 
	{
		curr->proximo = temp;  
		lst->raiz = curr;
        return pos;
	}

	/* procura item na posicao pos-1 */
	for (i = 0; i < pos-1 && temp != NULL; i++)
		temp = temp->proximo;  

	/* troca apontadores para inserir item */
	curr->proximo = temp->proximo;
  temp->proximo = curr;
 
	return pos;
}


int lista_remove(lista *lst, int pos)
{
	int i = 0;
	listaItem *prev, *curr;

	if (lst == NULL || pos < 0 || pos >= lst->tamanho)
		return -1;
	
	curr = lst->raiz;
	
	lst->tamanho--;

	/* caso especial: remover item no inicio da lista */
	if(pos == 0)
	{
		lst->raiz = curr->proximo;
		contentor_apaga(curr->elemento);
		free(curr);
		return 0;
	}

	/* procura item na posicao pos-1 */
	for(i = 0; i < pos && curr->proximo; i++)
	{
		prev = curr;
		curr = curr->proximo;
	}

	prev->proximo = curr->proximo;

	/* liberta memoria associada ao item removido */
	contentor_apaga(curr->elemento);
	free(curr);

	return 0;
}


int lista_pesquisa(lista *lst, contentor* contr)
{
  int i=0;
	listaItem *aux;
	
	if(lst == NULL)
		return -1;

	/* pesquisa sequencial */
	for (aux = lst->raiz; aux != NULL; aux = aux->proximo, i++) 
	{
		if ((strcmp(aux->elemento->destino, contr->destino) == 0)
				&& (aux->elemento->valor == contr->valor))
			return i;
	}
	return -1;
}

int lista_ordena(lista *lst)
{
  listaItem *next, *curr, *left, *prev_left;
	
	if(lst == NULL)
		return -1;

	curr = lst->raiz;

    for (next = curr->proximo; next!= NULL; next = curr->proximo) 
    {
		/* o ultimo elemento do lado direito e o primeiro do lado esq. estao desordenados */
		if (strcmp(curr->elemento->destino, next->elemento->destino) > 0)       
    { 
			/* remove o primeiro elemento do lado direito (desordenado) */
      curr->proximo = next->proximo;
			/* posiciona o apontador left no inicio do lado esquerdo, i.e. inicio da lista */
      prev_left = left = lst->raiz;      
            
			/* enquanto nao chegar ao penultimo elemento do lado esquerdo */
			while (next->proximo != curr)   
      {
        if (strcmp(left->elemento->destino, next->elemento->destino) > 0) 
        {
          next->proximo = left;   /* insere 'a esquerda */
					
					/* se inseriu no inicio da lista, e' necessario alterar o apontador raiz */
          if (left == lst->raiz)     
            lst->raiz = next;
          else 
            prev_left->proximo = next;                  
                    
			    /* ja ordenou e sai do ciclo while */
					break;
        }

				/* avanca para o elemento seguinte do lado esquerdo */
        prev_left = left;
        left = left->proximo;
      }
    }
    else 
			/* o elemento esta ordenado e avanca para o elemento seguinte do lado direito */
      curr = curr->proximo;
    }
	
	return 0;
}
