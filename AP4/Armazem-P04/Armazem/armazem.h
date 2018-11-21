/********************************************************************/
/*                define estrutura armazem e funcoes                */
/********************************************************************/

#ifndef ARMAZEM_H

#include "contentor.h"
#include "lista_contentores.h"
#include "fila_contentores.h"
#include "pilha_contentores.h"

/**
 * \brief estrutura armazem
 */
typedef struct {
	
	/** \brief numero maximo de pilhas de contentores (tamanho da fila) */
	int comprimento;

	/** \brief numero maximo de contentores numa pilha (tamanho da pilha) */
	int altura;
	
	/** \brief fila de pilhas de contentores (coluna) */
	fila* contentores;
	
	/** \brief lista de todos os contentores que passaram pelo armazem */
	lista* historico;

} armazem;

/* alinea b) */
/**
 *  \brief cria um novo armazem vazio
 *  \return apontador para o armazem ou NULL se erro na alocacao de memoria
 *  \remark armazem e' criado com capacidade para 4 pilhas de 3 contentores
 */
armazem* armazem_novo();

/* alinea c) */
/**
 *  \brief verifica se o armazem esta' vazio
 *  \param armz apontador para o armazem
 *  \return 1 se armazem vazio; 0 se contem contentores
 */
int armazem_vazio(armazem* armz);

/* alinea d) */
/**
 *  \brief verifica se o armazem pode receber mais contentores
 *  \param armz apontador para o armazem
 *  \return 1 se armazem nao pode receber mais contentores; 0 se pode
 */
int armazem_cheio(armazem* armz);

/* alinea e) */
/**
 *  \brief empilha contentor no armazem
 *  \param armz apontador para o armazem
 *  \param contr apontador para o contentor
 *  \return 1 se contentor foi descarregado; 0 se armazem cheio
 *  \remark contentor e' carregado na primeira pilha; quando a pilha
 *    esta' completa comeca a empilhar noutra; cada contentor descarregado
 *    e' guardado na lista de historico
 */
int descarregar_camiao(armazem* armz, contentor* contr);

/* alinea f) */
/**
 *  \brief retira um contentor do armazem para o navio
 *  \param armz apontador para o armazem
 *  \return apontador para o contentor retirado ou NULL se armazem vazio
 *  \remark contentor e' retirado da pilha mais proxima do navio
 */
contentor* carregar_navio(armazem* armz);

/**
 *  \brief ordena registo historico do armazem 
 *  \param armz apontador para o armazem
 *  \remark o historico e' ordenado por ordem alfabetica de destinos dos
 *    contentores; para o mesmo destino sao ordenados por ordem crescente
 *    dos seus valores
 */
void ordenar_registo(armazem* armz);

/* alinea g) */
/**
 *  \brief imprime o registo historico do armazem
 *  \param armz apontador para o armazem
 */
void imprimir_registo(armazem* armz);

/* alinea h) */
/**
 *  \brief avalia valor das encomendas guardadas no armazem
 *  \param armz apontador para o armazem
 *  \return valor das encomendas guardadas no armazem
 */
float referencia_seguro(armazem* armz);

#define ARMAZEM_H
#endif
