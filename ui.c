/**
 * @file ui.c
 * @author Vitor Custódio
 * @brief User interface
 * ! ficheiro não pode ser alterado
 * @date 2023-04-01
 * 
 */

#include <stdio.h>
#include <string.h>
#include "ui.h"



void printHelp()
{
    // Figlet gerado em https://www.askapache.com/online-tools/figlet-ascii/
    puts("******************************************************************************************************************");
    puts("#####    ##   #        ##   #    # #####    ##    ####      ####  #####  #    # ######   ##   #####    ##    ####");
    puts("#    #  #  #  #       #  #  #    # #    #  #  #  #         #    # #    # #    #     #   #  #  #    #  #  #  #");
    puts("#    # #    # #      #    # #    # #    # #    #  ####     #      #    # #    #    #   #    # #    # #    #  ####");
    puts("#####  ###### #      ###### #    # #####  ######      #    #      #####  #    #   #    ###### #    # ######      #");
    puts("#      #    # #      #    #  #  #  #   #  #    # #    #    #    # #   #  #    #  #     #    # #    # #    # #    #");
    puts("#      #    # ###### #    #   ##   #    # #    #  ####      ####  #    #  ####  ###### #    # #####  #    #  ####");
    puts("******************************************************************************************************************");
    puts("Utilização:");
    puts("\nOPÇÕES:");
    puts("-h\t\tAjuda para o utilizador");
    puts("-t <n>\t\tdimensões do tabuleiro.");
    puts("-n <nn>\t\tnúmero de jogadas máximo a realizar");
    puts("-i <filename>\tdefine ficheiro com o tabuleiro a usar em alternativa a jogar num tabuleiro criado default");
    puts("-o <filename>\tdefine ficheiro onde escrever o tabuleiro final.");
    puts("******************************************************************************************************************");
}

/**
 * lê o comando inserido pelo utilizador
 * @param local onde é gravado o comando
 * @return número de carateres em cmd
 * 
*/
int lerComando(char *cmd)
{
    char temp[MAX_LINE];

    printf("%s ", ASK_COMMAND);
    memset(temp, '\0', MAX_LINE);
    memset(cmd, '\0', MAX_LINE);
    if (fgets(temp, MAX_LINE, stdin)) // Testar se fgets leu
    {
        temp[strlen(temp) - 1] = '\0'; // para tirar o \n da leitura
        strncpy(cmd, temp, MAX_LINE);
    }
    return strlen(cmd);
}

void salvaTabuleiroFinal(Game *g)
{
    if (!g->tabFinal)
        return;
    for (int i = 0; i < g->dim; i++)
    {
        fprintf(g->tabFinal, "%2d", i + 1);
        for (int j = 0; j < g->dim; j++)
        {
            fprintf(g->tabFinal, "%2c", g->tabuleiro[i][j]);
        }
        fprintf(g->tabFinal, "\n");
    }
    char col = 'A';
    fprintf(g->tabFinal, "  ");
    for (int i = 0; i < g->dim; i++)
        fprintf(g->tabFinal, "%2c", col + i);
    fprintf(g->tabFinal, "\n");
}

void printTabuleiro(Game *g)
{
    for (int i = 0; i < g->dim; i++)
    {

        printf("%2d", i + 1);
        for (int j = 0; j < g->dim; j++)
        {
            printf("%2c", g->tabuleiro[i][j]);
        }
        printf("\n");
    }
    char col = 'A';
    printf("  ");
    for (int i = 0; i < g->dim; i++)
        printf("%2c", col + i);
    puts("");
}
