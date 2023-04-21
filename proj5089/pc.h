/**
 * @file pc.c
 * @author Ruben Alves, Eliseu Candido, Esther Candido
 * @brief Tabuleiro de palavras cruzadas
 * @date 2023-04-20
 * 
 */

#ifndef PC_H
#define PC_H

#include <stdio.h>

// CONSTANTES DE DEFAULT

#define DIMENSION_DEFAULT 9 //Dimensão do tabuleiro default
#define NOT_DEFINED -1   

// Simbolos de Tabuleiro
#define SYMBOL_EMPTY '.'
#define SYMBOL_FORBIDDEN '#'
#define SYMBOL_X2 '2'
#define SYMBOL_X3 '3'
#define SYMBOL_X4 '4'
#define SYMBOL_WORD_X2 '$'
#define SYMBOL_WORD_X3 '!'
// Pontuação
#define IMPOSSIBLE_PLAY 0


/**
 * @brief Estrutura principal de jogo
 */
typedef struct _game
{
    int jogadasRealizadas;
    int score;//pontuação acumulada do jogo
    char **tabuleiro;
    int endPlaying; //! novo
    
    //Opções de jogo
    
    int dim;//dimensão do tabuleiro. Ou é dado ou calculado quando o tabuleiro é criado a partir de um ficheiro
    FILE *tabFinal;//Ficheiro onde gravar tabuleiro final
    FILE *tabInicial;//Ficheiro para carregar tabuleiro inicial
    int maxJogadas;//Máximo número de jogadas
    /* Outros campos que se considere necessário*/
    /* Outras estruturas podem ser criadas*/
    /* Outros nomes podem ser dados aos atributos*/

} Game;

/**
 * @brief Cria um jogo consoante as opções passadas pela linha de comandos
 * 
 * @param argc número de argumentos
 * @param argv argumentos
 * @return Game* Jogo
 */
Game *newGame(int argc, char const *argv[]);

/**
 * @brief Libertar memória alocada ao jogo
 * 
 * @param g Jogo
 */
void freeGame(Game *g);



/**
 * @brief Joga o jogo
 *
 * @param g Jogo
 */
void playGame(Game *g);

#endif