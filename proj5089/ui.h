/**
 * @file pc.c
 * @author your name 
 * @brief description of file
 * @date 2022-04-27
 * 
 */

#include "pc.h"

#define ASK_COMMAND "Insira comando->"
#define PRINT_COMMAND_INCORRET puts("ERRO! Comando incorreto")
#define PRINT_FINAL_SCORE(score) printf("Fim do jogo. Total de pontos obtidos: %d\n", score);
#define PRINT_MOVE_INFO(move,col,line,dir,word,score) printf("Jogada %d: [%c%d%c] %s -> %d pontos\n",move,col,line,dir,word,score)


#define MAX_LINE 1024 //Para ler linhas de ficheiros. Nunca será maior que 1024s


/**
 * @brief Imprime no stdout a ajuda
 */
void printHelp();

/**
 * @brief Lê uma linha de entrada do STDIN
 * 
 * @param cmd comando a receber do utilizador 
 * @return int 
 */
int lerComando(char *cmd);

void printTabuleiro(Game *g);

void salvaTabuleiroFinal(Game *g);