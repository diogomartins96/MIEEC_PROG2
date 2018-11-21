/*****************************************************************/
/*                       Lista de contentores                    */
/*****************************************************************/

#ifndef LISTA_H
#include "contentor.h"

/** 
* \brief registo para armazenar elementos da lista
* este registo contém um contentor e um apontador para o próximo elemento da lista
*/
typedef struct item_l
{
	/** \brief contentor armazenado */
	contentor* elemento;
  struct item_l *proximo;
} listaItem;

typedef struct
{
	listaItem *raiz;
	int tamanho;
} lista;

/**
 *  \brief cria uma nova lista vazia
 *  \return apontador para a lista
 */
lista* lista_nova();

/** 
 *  \brief elimina uma lista, libertando toda a memória ocupada
 *  \param l apontador para a lista
 *  \remark se lista = NULL retorna sem fazer nada
 */
void lista_apaga(lista *l);

/**
 *  \brief indica o comprimento da lista
 *  \param l apontador para a lista
 *  \return numero de elementos da lista ou -1 se lista = NULL
 */
int lista_tamanho(lista *l);

/** 
 *  \brief retorna o contentor armazenado na posicao especificada
 *  \param l apontador para a lista
 *  \param pos posicao do elemento na lista
 *  \return apontador para o contentor na posicao correspondente
 *  \remark se pos < 0 ou pos >= tamanho da lista, retorna NULL
 *  \remark considera-se que o primeiro elemento da lista esta' na posicao 0, o segundo na posicao 1, etc.
 */
contentor* lista_elemento(lista *l, int pos);

/** 
 *  \brief atribui o valor especificado a uma posicao 
 *  \param l apontador para a lista
 *  \param pos posicao do elemento da lista a modificar
 *  \param valor contentor pretendido
 *  \return -1 se pos < 0 ou pos >= tamanho da lista, e pos se bem sucedido 
 *  \remark considera-se que o primeiro elemento da lista esta' na posicao 0, o segundo na posicao 1, etc.
 */
int lista_atribui(lista *l, int pos, contentor* valor);

/**
 *  \brief insere um elemento na posicao especificada
 *  \param l apontador para a lista
 *  \param valor contentor a inserir
 *  \param pos posicao da lista onde se pretende inserir o novo elemento, se pos=-1 insere no fim da lista
 *  \return -1 se pos < 0 ou pos >= tamanho da lista, e pos se bem sucedido
 *  \remark considera-se que o primeiro elemento da lista esta' na posicao 0, o segundo na posicao 1, etc.
 */
int lista_insere(lista *l, contentor* valor, int pos);

/**
 *  \brief remove o elemento da posicao especificada
 *  \param  l apontador para a lista
 *  \param pos posicao da lista de onde se pretende remover um elemento
 *  \return -1 se pos < 0 ou pos >= tamanho da lista, e 0 se bem sucedido
 *  \remark considera-se que o primeiro elemento da lista esta' na posicao 0, o segundo na posicao 1, etc.
 */
int lista_remove(lista *l, int pos);

/**
 *  \brief devolve a posicao do primeiro elemento da lista com o contentor especificado
 *  \param  l apontador para a lista
 *  \param valor contentor a pesquisar
 *  \return posicao ou -1 se nao encontrar elemento
 *  \return -1 se pos < 0 ou pos >= tamanho da lista, e pos se bem sucedido
 */
int lista_pesquisa(lista *l, contentor* valor);

/**
 *  \brief ordena uma lista de contentores por ordem alfabetica de destino
 *  \param  l apontador para a lista
 *  \return -1 se ocorrer um erro ou 0 se for bem sucedido
 */
int lista_ordena(lista *l);

#define LISTA_H
#endif
