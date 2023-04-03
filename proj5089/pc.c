/**
 * @file pc.c
 * @author your name
 * @brief description of file
 * @date 2022-04-27
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pc.h"
#include "ui.h"

/* ############################################ */
/* ####### Declaração funções internas #########*/

/**
 * @brief Retira espaços de uma string.
 * Retirado de stackoverflow
 * https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
 * @param s String
 */
void remove_spaces(char *s);

/**
 * @brief carrega as opções do jogo passado pela linha de comandos
 *
 * @param g Objeto jogo
 * @param argc
 * @param argv
 */
void loadOptions(Game *g, int argc, char const *argv[]);

void criarTabuleiroFromFile(Game *g);

void criarTabuleiro(Game *g);

/* ############################################ */
/* ##### Implementação funções públicas #######*/

Game *newGame(int argc, char const *argv[])
{
    Game *g = malloc(sizeof(Game));
    g->jogadasRealizadas = 0;
    g->score = 0;
    g->tabuleiro = NULL;
    g->dim = DIMENSION_DEFAULT;
    g->tabFinal = NULL;
    g->tabInicial = NULL;
    g->maxJogadas = NOT_DEFINED;

    // carregar opções do jogo
    loadOptions(g, argc, argv);

    // Cria tabuleiro (consoante opções de jogo)
    if (g->tabInicial)
        criarTabuleiroFromFile(g);
    else
        criarTabuleiro(g);

    // devolve jogo
    return g;
}

void freeGame(Game *g)
{
    // Liberta recursos do jogo
}

void playGame(Game *g)
{
    // TODO: Função que joga o jogo.
    // !Pode invocar outras funçoes que serão criadas pelos alunos
}

/* ############################################ */
/* ##### Implementação funções internas #######*/

void loadOptions(Game *g, int argc, char const *argv[])
{

    if (argc == 1)
        return;
    for (int i = 1; i < argc; i++)
    {
        switch (argv[i][1])
        {
        case 'h':
            printHelp();
            freeGame(g);
            exit(EXIT_FAILURE);
            break;
        case 't':
                //TODO: A fazer pelo aluno
            break;
        case 'n':
                //TODO: A fazer pelo aluno
            break;
        case 'i':
                //TODO: A fazer pelo aluno
            break;
        case 'o':
                //TODO: A fazer pelo aluno
            break;
        default:
            printHelp();
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void criarTabuleiroFromFile(Game *g)
{
    /**
     * TODO: A fazer pelo aluno
     * Terá que ler oo ficheiro e criar a matriz tabuleiro
     */
}

void criarTabuleiro(Game *g)
{
    /**
     * TODO: A fazer pelo aluno
     * Cria tabuleiro default 9x9 conforme enunciado
     */
}

void remove_spaces(char *s)
{
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while ((*s++ = *d++));
}
