/**
 * @file main.c
 * @author vitor custódio
 * @brief Ficheiro main
 * @date 01-04-2023
 * 
 */

#include <stdlib.h>
#include "pc.h"

//! Não pode ser Alterado este ficheiro
int main(int argc, char const *argv[])
{
    //Cria o jogo e carrega opções
    Game *g=newGame(argc,argv);
    //Joga o jogo
    playGame(g);
    //Liberta recursos
    freeGame(g);
    return EXIT_SUCCESS;
}
