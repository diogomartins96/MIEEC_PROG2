#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo()
{
	return NULL;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	/* devolve vazio */
	return 1;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	/* devolve nao cheio */
	return 0;
}

/* alinea e) */
int descarregar_camiao(armazem* armz, contentor* contr)
{
	/* devolve nao ha' espaco */
	return 0;
}

/* alinea f) */
contentor* carregar_navio(armazem* armz)
{
	return NULL;
}

void ordenar_registo(armazem* armz)
{
	if(armz != NULL && armz->historico != NULL)
		lista_ordena(armz->historico);
}

/* alinea g) */
void imprimir_registo(armazem* armz)
{

}

/* alinea h) */
float referencia_seguro(armazem* armz) 
{
	return 0.0;
}


