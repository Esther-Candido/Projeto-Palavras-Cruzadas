#include <stdlib.h>
#include <string.h>
#include "api.h"

/**
 * ######### Funções internas da biblioteca #########
 * ##################################################
 **/

Mapa *new_mapa()
{
    Mapa *m = malloc(sizeof(Mapa));
    m->firstC = NULL;
    m->lastC = NULL;
    m->numCidades = 0;
    return m;
}

void free_mapa(Mapa *m)
{
    
}

/**
 * ######### Implementação das Funções da Biblioteca#########
 * ###########################################################
 **/