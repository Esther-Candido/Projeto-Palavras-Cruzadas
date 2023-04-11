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

#define HORIZONTAL_WORD 2  //!ruben
#define VERTICAL_WORD 3     //!ruben

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

void rules(Game *g); //! Ruben

void inserirPalavra(Game *g, char *palavra, int direcao, char *posicaoInicial);


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
    rules(g);  //!ruben 

    // Mostra o tabuleiro
    printTabuleiro(g);

    // Solicita ao utilizador a palavra, a direção e a posição inicial
    char palavra[10];
    char direcao;
    char posicaoInicial[3];

    printf("Insira a palavra: ");
    scanf("%s", palavra);
    
    printf("Insira a direção ('h' para horizontal ou 'v' para vertical): ");
    scanf(" %c", &direcao);

    printf("Insira a posição inicial (exemplo: A1): ");
    scanf("%s", posicaoInicial);

    inserirPalavra(g, palavra, direcao, posicaoInicial);

    // Mostra o tabuleiro com as palavras inseridas
    printTabuleiro(g);

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
     * ! Ruben 
     * Cria tabuleiro default 9x9 conforme enunciado
     */

    g->tabuleiro = malloc(g->dim * sizeof(char *));
    for (int i = 0; i < g->dim; i++) {
        g->tabuleiro[i] = malloc(g->dim * sizeof(char));
    }
    // Inicializa todas as casas do tabuleiro com o valor  '.'
    for (int i = 0; i < g->dim; i++) {
        for (int j = 0; j < g->dim; j++) {
            g->tabuleiro[i][j] = SYMBOL_EMPTY;
        }
    }
}

void rules(Game *g){
    /**
     * ! Ruben 
     * Cria todas as regras 
     */
     for (int i = 0; i < g->dim; i++) {
        for (int j = 0; j < g->dim; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == g->dim - 1) || (i == g->dim - 1 && j == 0) || (i == g->dim - 1 && j == g->dim - 1)) {
                g->tabuleiro[i][j] = SYMBOL_WORD_X2; // Simbolo '$'
            } else if (i == g->dim / 2 && j == g->dim / 2) {
                g->tabuleiro[i][j] = SYMBOL_X4 ; // Simbolo '4'
            } else if (i == j || i == g->dim - 1 - j) {
                g->tabuleiro[i][j] = SYMBOL_X2; // Simbolo '2'
            } else if ((i == g->dim / 2 || j == g->dim / 2) && (i - j == g->dim / 2 || j - i == g->dim / 2)) {
                g->tabuleiro[i][j] = SYMBOL_X3; // Simbolo '3'
            } else if ((i == g->dim / 2 - 1 && j == g->dim / 2 )|| (i == g->dim / 2 + 1 && j == g->dim / 2 )|| (j == g->dim / 2 - 1 && i == g->dim / 2) || (j == g->dim / 2 + 1 && i == g->dim / 2)) {
                g->tabuleiro[i][j] = SYMBOL_WORD_X3; // Simbolo '!'
            } else if ((i == 1 && j == g->dim / 2 - 1) || (i == 1 && j == g->dim / 2 + 1) || (i == g->dim - 2 && j == g->dim / 2 - 1) || (i == g->dim - 2 && j == g->dim / 2 + 1)
                    || (j == 1 && i == g->dim / 2 - 1) || (j == 1 && i == g->dim / 2 + 1) || (j == g->dim - 2 && i == g->dim / 2 - 1) || (j == g->dim - 2 && i == g->dim / 2 + 1)) {
                g->tabuleiro[i][j] = SYMBOL_FORBIDDEN; //Simbolo '#'
            } 
        }
    }
}

void inserirPalavra(Game *g, char *palavra, int direcao, char *posicaoInicial) {
    int linha = posicaoInicial[1] - '1';
    int coluna = posicaoInicial[0] - 'A';

    printf("Palavra: %s, Direcao: %d, Posicao: %s, Linha: %d, Coluna: %d\n", palavra, direcao, posicaoInicial, linha, coluna);

    for (int i = 0; i < strlen(palavra); i++) {
        if (direcao == 'h') {
            g->tabuleiro[linha][coluna + i] = palavra[i];
        } else if (direcao == 'v') {
            g->tabuleiro[linha + i][coluna] = palavra[i];
        }
    }     
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
