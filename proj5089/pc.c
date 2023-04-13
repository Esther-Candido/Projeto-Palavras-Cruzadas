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
#include <ctype.h>
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

void to_upper(char *str);

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

int lerPosicaoInicial(char *comando, char *posicaoInicial); //! Ruben

int lerDirecao(char *comando, int index, char *direcao) ; //! Ruben

void lerPalavra(char *comando, int index, char *palavra) ; //! Ruben

void inserirComando(Game *g); //! Ruben

void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial); //! Ruben


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

     // Solicita ao utilizador para inserir o comando
    inserirComando(g);

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

void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial)
{
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1; // Use atoi para converter corretamente para int

    if (direcao == 'H')
    {
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha][coluna + i] = palavra[i];
        }
    }
    else if (direcao == 'V')
    {
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha + i][coluna] = palavra[i];
        }
    }
}


// Função para ler a coluna e a linha
int lerPosicaoInicial(char *comando, char *posicaoInicial) {
    // Verifica se o primeiro caractere é uma letra
    if (!isalpha(comando[0])) {
        printf("Erro: A coluna deve ser uma letra.\n");
        return 0;
    }

    // Armazena a coluna na posição inicial
    posicaoInicial[0] = comando[0];

    // Lê a linha da posição inicial
    int index = 1;
    int i = 0;
    char tmp[3];
    while (isdigit(comando[index])) {
        tmp[i++] = comando[index++];
    }
    tmp[i] = '\0';

    // Verifica se a linha é válida
    int linha = atoi(tmp); // atoi converte uma string em numeros
    if (linha < 1 || linha > DIMENSION_DEFAULT) {
        printf("Erro: A linha deve ser um número entre 1 e %d.\n", DIMENSION_DEFAULT);
        return 0;
    }

    // Armazena a linha na posição inicial
    strcpy(&posicaoInicial[1], tmp);
    posicaoInicial[3] = '\0';

    return index;
}

// Função para ler a direção
int lerDirecao(char *comando, int index, char *direcao) {
    // Armazena a direção
    *direcao = comando[index];

    // Verifica se a direção é válida
    if (*direcao != 'H' && *direcao != 'V') {
        printf("Erro: A direção deve ser 'H' ou 'V'.\n");
        return 0;
    }

    return 1;
}

// Função para ler a palavra
void lerPalavra(char *comando, int index, char *palavra) {
    // Copia a palavra do comando para a variável palavra
    strcpy(palavra, &comando[index + 1]);
}

void inserirComando(Game *g)
{
    // Aloca memória para as variáveis
    char *comando = (char *)malloc(30 * sizeof(char));
    char *posicaoInicial = (char *)malloc(4 * sizeof(char));
    char direcao;
    char *palavra = (char *)malloc(20 * sizeof(char));

    // Lê o comando do usuário
    printf("Insira comando-> ");
    fgets(comando, 30, stdin);
    comando[strcspn(comando, "\n")] = 0; // Remove o caractere de nova linha
    remove_spaces(comando);

    // Converte o comando para maiúsculas
    to_upper(comando);

    // Lê a posição inicial (coluna e linha)
    int index = lerPosicaoInicial(comando, posicaoInicial);
    if (index == 0) {
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }

    // Lê a direção (H ou V)
    if (!lerDirecao(comando, index, &direcao)) {
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }

    // Lê a palavra a ser inserida
    lerPalavra(comando, index, palavra);

    // Insere a palavra no jogo
    inserirPalavra(g, palavra, direcao, posicaoInicial);

    // Libera a memória alocada
    free(comando);
    free(posicaoInicial);
    free(palavra);
}


void to_upper(char *str)
{
    for (; *str; ++str)
    {
        *str = toupper((unsigned char)*str);
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
