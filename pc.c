/**
 * @file pc.c
 * @author Ruben Alves, Eliseu Candido, Esther Candido
 * @brief Tabuleiro de palavras cruzadas
 * @date 2023-04-20
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "pc.h"
#include "ui.h"


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
    g->endPlaying = 0;
      
    loadOptions(g, argc, argv);

    if (g->tabInicial)
        criarTabuleiroFromFile(g,g->tabInicial);
    else
        criarTabuleiro(g);

    return g;
}


void freeGame(Game *g)
{
    if (g == NULL) 
        return;

    // Liberta a memória alocada para o tabuleiro
    if (g->tabuleiro != NULL)
    {
        for (int i = 0; i < g->dim; i++)
        {
            free(g->tabuleiro[i]);
        }
        free(g->tabuleiro);
    }

    // Liberta a memória alocada para a estrutura Game
    free(g);
}


void playGame(Game *g)
{
    // Declara variáveis para coluna, linha, direção e palavra
    char col;
    int line;
    char dir;
    char *palavra;

    // Aloca memória para a palavra
    palavra = (char *)malloc(20 * sizeof(char));

    // Exibe as regras do jogo apenas se não estiver usando um tabuleiro carregado de arquivo
    if (g->tabInicial == NULL)
    {
        rules(g);
    }

    // Imprime o tabuleiro inicial
    printTabuleiro(g);

    // Declara variável para armazenar os pontos obtidos em cada jogada
    int pontos;

    do
    {
        // Solicita ao jogador que insira um comando e retorna os pontos obtidos
        pontos = inserirComando(g, &col, &line, &dir, palavra);

        // Se o jogador escolher escrever "end", encerra o loop
        if (g->endPlaying == 1)
        {
            break;
        }

        // Imprime o tabuleiro após cada jogada
        printTabuleiro(g);

        // Se a jogada for válida, exibe informações sobre a jogada e os pontos obtidos
        if (pontos != -1)
        {
            PRINT_MOVE_INFO(g->jogadasRealizadas, col, line, dir, palavra, pontos);
        }

        // Verifica se há apenas um ponto restante no tabuleiro e, se sim, encerra o loop
        if (verificarEspacosVazios(g) <= 1 )
        {
            break;
        }

    } while (g->jogadasRealizadas < g->maxJogadas || g->maxJogadas == NOT_DEFINED);

    // Exibe a pontuação final do jogador
    PRINT_FINAL_SCORE(g->score);

    // Salva o tabuleiro final e a pontuação no arquivo
    salvaTabuleiroFinal(g);

    // Libera a memória alocada para a palavra
    free(palavra);

    // Fecha os arquivos abertos (tabInicial e tabFinal)
    if (g->tabInicial) fclose(g->tabInicial);
    if (g->tabFinal) fclose(g->tabFinal);
}


void loadOptions(Game *g, int argc, char const *argv[])
{
    if (argc == 1)
        return;


    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-') {
            switch (argv[i][1])
            {
            case 'h':
                printHelp();
                freeGame(g);
                exit(EXIT_FAILURE);
                break;

            case 't':
                if (i + 1 < argc) {
                    int tamanhoTabuleiro = atoi(argv[++i]);
                    if (tamanhoTabuleiro >= 7 && tamanhoTabuleiro <= 15 && tamanhoTabuleiro % 2 != 0) {
                        g->dim = tamanhoTabuleiro;
                    } else {
                        printHelp();
                        freeGame(g);
                        exit(EXIT_FAILURE);
                    }
                }
                break;

            case 'n':
                i++;
                int n = atoi(argv[i]);
                if (n < 0){
                    printHelp();
                    freeGame(g);
                    exit(EXIT_FAILURE);
                }
                g->maxJogadas = n;
                break;

            case 'i':
                i++;
                FILE *f1 = fopen(argv[i], "r");
                if (f1 == NULL){
                    printHelp();
                    freeGame(g);
                    exit(EXIT_FAILURE);
                }
                g->tabInicial = f1;
                break;

            case 'o':
                i++;
                FILE *f2 = fopen(argv[i], "w");
                if (f2 == NULL){
                    printHelp();
                    freeGame(g);
                    exit(EXIT_FAILURE);
                }
                g->tabFinal = f2;
                break;

            default:
                printHelp();
                exit(EXIT_FAILURE);
                break;
            }
        } else {
            // Trata o caminho do arquivo de tabuleiro
            FILE *f1 = fopen(argv[i], "r");
            if (f1 == NULL){
                printHelp();
                freeGame(g);
                exit(EXIT_FAILURE);
            }
            g->tabInicial = f1;
            
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


void criarTabuleiroFromFile(Game *g, FILE *file)
{
    char c;
    int line_count = 0;
    char line[MAX_LINE]; // Variável para armazenar cada linha lida do arquivo

    // Verifica se o arquivo é válido
    if (file == NULL)
    {
        PRINT_COMMAND_INCORRET; 
        return;
    }

    // Conta o número de linhas no arquivo para determinar a dimensão do tabuleiro
    //EOF -> constante que indica fim do ficheiro
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            line_count++;
        }
    }

    // Atribui a dimensão do tabuleiro com base na contagem de linhas
    g->dim = line_count;

    // Aloca espaço de memória para o tabuleiro
    g->tabuleiro = malloc(sizeof(char *) * g->dim);
    for (int i = 0; i < g->dim; i++)
    {
        g->tabuleiro[i] = malloc(sizeof(char) * (g->dim + 1));
    }

    // Retorna o ponteiro do arquivo para o início
    rewind(file);


    for (int i = 0; i < g->dim; i++)
    {
        fgets(line, sizeof(line), file); // Lê uma linha do arquivo
        remove_spaces(line);            // Remove os espaços da linha

        // Itera sobre as colunas do tabuleiro
        for (int j = 0; j < g->dim; j++)
        {
            // Se a linha do tabuleiro for maior ou igual a 9
            if (i >= 9)
            {
                // Copia o caractere para o tabuleiro, ignorando os dois primeiros caracteres
                g->tabuleiro[i][j] = line[j + 2];
                continue;
            }

            // Copia o caractere para o tabuleiro, ignorando o primeiro caractere
            g->tabuleiro[i][j] = line[j + 1];
        }
    }
}


void criarTabuleiro(Game *g)
{
    // Aloca memória para o tabuleiro com base nas dimensões fornecidas
    g->tabuleiro = malloc(g->dim * sizeof(char *));
    if (g->tabuleiro == NULL) {
        PRINT_COMMAND_INCORRET;
        exit(EXIT_FAILURE);
    }

    // Aloca memória para cada linha do tabuleiro
    for (int i = 0; i < g->dim; i++) {
        g->tabuleiro[i] = malloc(g->dim * sizeof(char));
        if (g->tabuleiro[i] == NULL) {
            PRINT_COMMAND_INCORRET;
            exit(EXIT_FAILURE);
        }
    }

    // Inicializa todas as casas do tabuleiro com o valor '.'
    for (int i = 0; i < g->dim; i++) {
        for (int j = 0; j < g->dim; j++) {
            g->tabuleiro[i][j] = SYMBOL_EMPTY;
        }
    }
}


void rules(Game *g){
    
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


void to_upper(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {

        str[i] = toupper(str[i]);

        i++;
    }
}


int lerColuna(char *comando, char *posicaoInicial, int dim) {

    // Verifica se o primeiro caractere é uma letra
    if (!isalpha(comando[0])) {
        PRINT_COMMAND_INCORRET;
        return -1;
    }

    // Verifica se a letra está dentro dos limites do tabuleiro
    char coluna = toupper(comando[0]);
    if (coluna < 'A' || coluna >= 'A' + dim) {
        PRINT_COMMAND_INCORRET;
        return -1;
    }

    // Armazena a coluna na posição inicial
    posicaoInicial[0] = coluna;

    return 1;
}


int lerLinha(Game *g, char *comando, int index, char *posicaoInicial) {
    // Lê a linha da posição inicial
    int i = 0;
    char tmp[4] = {0};

    // Enquanto o caractere na posição "index" do comando for um dígito
   for (i = 0; isdigit(comando[index]) && i < 3; i++, index++) {
        // Adiciona o caractere ao array tmp
        tmp[i] = comando[index];
    }

    // Converte a string em tmp para um número inteiro
    int linha = atoi(tmp); 

    // Verifica se a linha é válida (entre 1 e dimensão do tabuleiro)
    if (linha < 1 || linha > g->dim) {
        PRINT_COMMAND_INCORRET;
        return -1;
    }

    // Armazena a linha na posição inicial
    strcpy(&posicaoInicial[1], tmp);

    // Retorna o índice atualizado do comando
    return index;
}


int lerDirecao(char *comando, int index, char *direcao) {
    // Armazena a direção
    *direcao = comando[index];

    // Verifica se a direção é válida
    if (*direcao != HORIZONTAL && *direcao != VERTICAL) {
        PRINT_COMMAND_INCORRET;
        return -1;
    }

    return 1;
}


int lerPalavra(char *comando, int index, char *palavra) {
    // Encontra o índice da posição do espaço no comando
    while (comando[index] != SPACE && comando[index] != '\0') {
        index++;
    }

    // Verifica se encontrou um espaço
    if (comando[index] != SPACE) {
        PRINT_COMMAND_INCORRET;
        return -1;
    }

    // Incrementa o índice para pular o espaço
    index++;

    // Copia a palavra do comando para a variável palavra
    strcpy(palavra, comando + index);

    return index;
}


int validarPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial, char **tabuleiro) {
    // Verifica se a palavra cabe no tabuleiro na direção escolhida
    int tamanho_palavra = strlen(palavra);
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1;
    int letrasIguais = 0;

    // Verifica se a palavra contém apenas caracteres válidos (letras)
    for (int j = 0; palavra[j] != '\0'; j++) {
        if (!isalpha(palavra[j])) {
            PRINT_COMMAND_INCORRET; 
            return 0;
        }
    }

    // Verifica se a palavra tem pelo menos 3 caracteres
    if (strlen(palavra) < 3) {
        PRINT_COMMAND_INCORRET; 
        return 0;
    }

    // Verifica se a palavra cabe na posição horizontal ou vertical
    if (direcao == HORIZONTAL) {
        if (coluna + tamanho_palavra > g->dim) {
            PRINT_COMMAND_INCORRET; 
            return 0;
        }
    } else { // direcao == 'V'
        if (linha + tamanho_palavra > g->dim) {
            PRINT_COMMAND_INCORRET; 
            return 0;
        }
    }


    // Verifica se a palavra pode ser inserida no tabuleiro
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (direcao == HORIZONTAL) {
            if (isalpha(tabuleiro[linha][coluna + i]) && tabuleiro[linha][coluna + i] != palavra[i]) {
                PRINT_COMMAND_INCORRET; 
                return 0;
            } else if (tabuleiro[linha][coluna + i] == SYMBOL_FORBIDDEN ) {
                PRINT_COMMAND_INCORRET; 
                return 0;
            } else if (tabuleiro[linha][coluna + i] == palavra[i]) {
                letrasIguais++;
            }
        } else { // direcao == 'V'
            if (isalpha(tabuleiro[linha + i][coluna]) && tabuleiro[linha + i][coluna] != palavra[i]) {
                PRINT_COMMAND_INCORRET; 
                return 0;
            } else if (tabuleiro[linha + i][coluna] == SYMBOL_FORBIDDEN ) {
                PRINT_COMMAND_INCORRET; 
                return 0;
            } else if (tabuleiro[linha + i][coluna] == palavra[i]) {
                letrasIguais++;
            }
        }
    }

    // Se todas as letras são iguais, a palavra não é válida
    if (letrasIguais == strlen(palavra)) {
        PRINT_COMMAND_INCORRET; 
        return 0;
    }

    // Se passar por todas as verificações, a palavra é válida
    return 1;
}


int pontuacaoLetra(char letra) {
    // Array que contém os valores de pontos de cada letra (A-Z) em ordem alfabética
    int valorLetra[] = {2, 4, 3, 1, 2, 3, 1, 3, 2, 3, 7, 5, 4, 4, 2, 4, 6, 3, 3, 4, 6, 5, 9, 6, 7, 8};

    // Calcula o índice da letra no array valorLetra (0 para 'A', 1 para 'B', etc.)
    int letraIndex = letra - 'A';

    // Retorna a pontuação da letra com base no índice calculado
    return valorLetra[letraIndex];
}


int regrasMultiplicacao(Game *g, char *palavra, char **tabuleiro, int linha, int coluna, char direcao) {
    int pontos = 0;
    int multiplicadorPalavra = 1;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int letraPontos = pontuacaoLetra(palavra[i]);

        // Regra para multiplicar por 2
        if (direcao == HORIZONTAL && tabuleiro[linha][coluna + i] == SYMBOL_X2) {
            letraPontos *= 2;
        } else if (direcao == VERTICAL && tabuleiro[linha + i][coluna] == SYMBOL_X2) {
            letraPontos *= 2;
        }

        // Regra para multiplicar por 3
        if (direcao == HORIZONTAL && tabuleiro[linha][coluna + i] == SYMBOL_X3) {
            letraPontos *= 3;
        } else if (direcao == VERTICAL && tabuleiro[linha + i][coluna] == SYMBOL_X3) {
            letraPontos *= 3;
        }

         // Regra para multiplicar por 4
        if (direcao == HORIZONTAL && tabuleiro[linha][coluna + i] == SYMBOL_X4) {
            letraPontos *= 4;
        } else if (direcao == VERTICAL && tabuleiro[linha + i][coluna] == SYMBOL_X4) {
            letraPontos *= 4;
        }

        // Regra para duplicar palavra
        if (direcao == HORIZONTAL && tabuleiro[linha][coluna + i] == SYMBOL_WORD_X2) {
            multiplicadorPalavra *= 2;
        } else if (direcao == VERTICAL && tabuleiro[linha + i][coluna] == SYMBOL_WORD_X2) {
            multiplicadorPalavra *= 2;
        }

        // Regra para triplicar palavra
        if (direcao == HORIZONTAL && tabuleiro[linha][coluna + i] == SYMBOL_WORD_X3) {
            multiplicadorPalavra *= 3;
        } else if (direcao == VERTICAL && tabuleiro[linha + i][coluna] == SYMBOL_WORD_X3) {
            multiplicadorPalavra *= 3;
        }

        pontos += letraPontos;
    }

    pontos *= multiplicadorPalavra;

    return pontos;
}


void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial)
{
    // Converte a posição inicial de coluna (letra) para um índice numérico
    int coluna = posicaoInicial[0] - 'A';
    // Converte a posição inicial de linha (número) para um índice numérico
    int linha = atoi(&posicaoInicial[1]) - 1; 

    // Verifica se a direção é horizontal (H)
    if (direcao == HORIZONTAL)  
    {
        
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha][coluna + i] = palavra[i];
        }
    }
    // Verifica se a direção é vertical (V)
    else if (direcao == VERTICAL) 
    {
        
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha + i][coluna] = palavra[i];
        }
    }
}


int inserirComando(Game *g, char *col, int *line, char *dir, char *palavra) 
{
    // Aloca memória para as variáveis
    char *comando = (char *)malloc(30 * sizeof(char));
    char *posicaoInicial = (char *)malloc(4 * sizeof(char));
    int index;

    // Lê o comando do usuário
    printf(ASK_COMMAND);
    fgets(comando, 30, stdin);
    comando[strcspn(comando, "\n")] = 0; // Remove o caractere de nova linha

    // Converte o comando para maiúsculas
    to_upper(comando);

    // Verifica se o comando é "END"
    if (strcmp(comando, "END") == 0) {
        g->endPlaying = 1;
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Lê a coluna e retorna o índice atualizado
    index = lerColuna(comando, posicaoInicial, g->dim);

    // Verifica se houve erro na leitura da coluna
    if (index == -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Lê a linha e retorna o índice atualizado
    index = lerLinha(g, comando, index, posicaoInicial);

    // Verifica se houve erro na leitura da linha
    if (index == -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Lê a direção (H ou V) e atualiza o índice
    if (!lerDirecao(comando, index, dir)) {
        free(comando);
        free(posicaoInicial);
        return -1;
    } 

    index++;

    // Lê a palavra a ser inserida e retorna o índice atualizado
    index = lerPalavra(comando, index, palavra); 

    // Verifica se houve erro na leitura da palavra
    if (index <= -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Verifica se a palavra é válida
    if (!validarPalavra(g, palavra, *dir, posicaoInicial, g->tabuleiro)) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Inicializa a linha e a coluna com os valores da posição inicial
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1;

    // Calcula a pontuação da palavra antes de inseri-la no tabuleiro usando a função regrasMultiplicacao
    int pontos = regrasMultiplicacao(g, palavra, g->tabuleiro, linha, coluna, *dir);

    // Insere a palavra no tabuleiro
    inserirPalavra(g, palavra, *dir, posicaoInicial);
    
    // Atualiza a pontuação do jogador e incrementa o número de jogadas realizadas
    g->jogadasRealizadas++;
    g->score += pontos;

    // Preenche os valores nos ponteiros
    *col = posicaoInicial[0];
    *line = linha + 1;

    // Libera a memória alocada
    free(comando);
    free(posicaoInicial);

    return pontos;
}


int verificarEspacosVazios(Game *g) {
    int pontosRestantes = 0;

    // Verifica linhas e colunas
    for (int i = 0; i < g->dim; i++) {
        for (int j = 0; j < g->dim; j++) {
            if (g->tabuleiro[i][j] == SYMBOL_EMPTY) {
                pontosRestantes++;
            }
        }
    }

    // Retorna a quantidade de pontos restantes no tabuleiro
    return pontosRestantes;
}












