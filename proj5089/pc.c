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



/**
 * @brief Converte todos os caracteres de uma string para maiúsculas.
 *
 * Esta função percorre cada caractere da string fornecida e o converte
 * para sua versão maiúscula, caso seja uma letra minúscula. A conversão
 * é feita usando a função toupper da biblioteca ctype.h.
 *
 * @param str Ponteiro para a string a ser convertida.
 */
void to_upper(char *str);  //! Novo

/**
 * @brief carrega as opções do jogo passado pela linha de comandos
 *
 * @param g Objeto jogo
 * @param argc
 * @param argv
 */
void loadOptions(Game *g, int argc, char const *argv[]); //!Feito

/**
 * Função para criar um tabuleiro de jogo a partir de um arquivo.
 * @param g: Ponteiro para a estrutura Game que armazena o tabuleiro e sua dimensão.
 * @param file: Ponteiro para o arquivo que contém a configuração do tabuleiro.
 */
void freeGame(Game *g); //!Feito

/**
 * Função para criar um tabuleiro de jogo a partir de um arquivo.
 * @param g: Ponteiro para a estrutura Game que armazena o tabuleiro e sua dimensão.
 * @param file: Ponteiro para o arquivo que contém a configuração do tabuleiro.
 */
void criarTabuleiroFromFile(Game *g, FILE *file); //!Feito

/**
 * @brief Cria e inicializa o tabuleiro do jogo.
 *
 * Esta função aloca memória para o tabuleiro do jogo, com base nas dimensões
 * fornecidas no objeto Game. Em seguida, inicializa todas as células do tabuleiro
 * com o caractere vazio (SYMBOL_EMPTY), que é definido como '.'.
 *
 * @param g Ponteiro para a estrutura do jogo (Game) onde o tabuleiro será criado.
 */
void criarTabuleiro(Game *g);   //!Feito

/**
 * @brief Define as regras para a colocação das palavras no tabuleiro do jogo.
 *
 * Esta função atribui os símbolos especiais às células do tabuleiro de acordo
 * com as regras do jogo. Os símbolos incluem:
 * - SYMBOL_WORD_X2 ('$'): Dobra o valor da palavra;
 * - SYMBOL_X4 ('4'): Quadruplica o valor da célula;
 * - SYMBOL_X2 ('2'): Dobra o valor da célula;
 * - SYMBOL_X3 ('3'): Triplica o valor da célula;
 * - SYMBOL_WORD_X3 ('!'): Triplica o valor da palavra;
 * - SYMBOL_FORBIDDEN ('#'): Célula proibida para a colocação de palavras.
 *
 * @param g Ponteiro para a estrutura do jogo (Game) que contém o tabuleiro.
 */
void rules(Game *g); //! Novo

/**
 * @brief Lê a coluna do comando e verifica se está dentro dos limites do tabuleiro.
 *
 * @param comando Ponteiro para a string do comando inserido pelo usuário.
 * @param posicaoInicial Ponteiro para a string que armazenará a posição inicial da palavra no tabuleiro.
 * @param dim Dimensão do tabuleiro (número de linhas e colunas).
 * @return Retorna o índice após a coluna na string do comando, ou -1 se a coluna for inválida.
 */
int lerColuna(char *comando, char *posicaoInicial, int dim) ;  //! Novo

/**
 * @brief Lê a linha do comando e verifica se está dentro dos limites do tabuleiro.
 *
 * @param g Ponteiro para a estrutura do jogo, que contém informações como a dimensão do tabuleiro.
 * @param comando Ponteiro para a string do comando inserido pelo usuário.
 * @param index Índice na string do comando onde a leitura da linha deve começar.
 * @param posicaoInicial Ponteiro para a string que armazenará a posição inicial da palavra no tabuleiro.
 * @return Retorna o índice após a linha na string do comando, ou -1 se a linha for inválida.
 */
int lerLinha(Game *g, char *comando, int index, char *posicaoInicial); //! Novo

/**
 * @brief Lê a direção (H ou V) do comando fornecido pelo usuário.
 * @param comando String com o comando inserido pelo usuário.
 * @param index Índice atualizado após ler a posição inicial.
 * @param direcao Ponteiro para armazenar a direção lida (H ou V).
 * @return Retorna 1 se a direção for válida, caso contrário, retorna 0.
 */
int lerDirecao(char *comando, int index, char *direcao) ;  //! Novo

/**
 * @brief Lê a palavra do comando fornecido pelo usuário.
 * @param comando String com o comando inserido pelo usuário.
 * @param index Índice atualizado após ler a posição inicial e a direção.
 * @param palavra Ponteiro para armazenar a palavra lida.
 */
int lerPalavra(char *comando, int index, char *palavra) ; //! Novo

/**
 * Verifica se existem espaços vazios consecutivos (3 ou mais) ou se há um caractere '!' no tabuleiro.
 * @param g: Ponteiro para a estrutura Game que armazena o tabuleiro e sua dimensão.
 * @return: Retorna 1 se houver espaços vazios consecutivos ou '!' encontrado, caso contrário, retorna 0.
 */
int verificarEspacosVazios(Game *g);

/**
 * @brief Insere um comando no jogo e atualiza a pontuação do jogador.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 */
int inserirComando(Game *g, char *col, int *line, char *dir, char *palavra) ;  //! Novo

/**
 * @brief Valida se uma palavra pode ser inserida no tabuleiro na posição e direção especificadas.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 * @param palavra A palavra a ser inserida.
 * @param direcao A direção da palavra a ser inserida ('H' para horizontal, 'V' para vertical).
 * @param posicaoInicial A posição inicial da palavra no tabuleiro.
 * @param tabuleiro O tabuleiro onde a palavra será inserida.
 * @return Retorna 1 se a palavra for válida e 0 caso contrário.
 */
int validarPalavra(Game *g,char *palavra, char direcao, char *posicaoInicial, char **tabuleiro);  //! Novo

/**
 * @brief Calcula a pontuação de uma letra individual.
 * @param letra A letra para a qual se deseja calcular a pontuação.
 * @return A pontuação da letra.
 */
int pontuacaoLetra(char letra);  //! Novo

/**
 * @brief Aplica as regras de multiplicação de pontos à palavra inserida no tabuleiro.
 * @param g Ponteiro para a estrutura do jogo.
 * @param palavra A palavra que foi inserida no tabuleiro.
 * @param tabuleiro Matriz que representa o tabuleiro do jogo.
 * @param linha A linha onde a palavra começa no tabuleiro.
 * @param coluna A coluna onde a palavra começa no tabuleiro.
 * @param direcao A direção em que a palavra foi inserida no tabuleiro ('H' para horizontal ou 'V' para vertical).
 * @return A pontuação da palavra após a aplicação das regras de multiplicação.
 */
int regrasMultiplicacao(Game *g, char *palavra, char **tabuleiro, int linha, int coluna, char direcao); //! Novo

/**
 * @brief Insere uma palavra no tabuleiro na posição e direção especificadas.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 * @param palavra A palavra a ser inserida.
 * @param direcao A direção da palavra a ser inserida ('H' para horizontal, 'V' para vertical).
 * @param posicaoInicial A posição inicial da palavra no tabuleiro.
 */
void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial);  //! Novo

void remove_spaces(char *s);



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
    g->endPlaying = 0;
    

    // carregar opções do jogo
    loadOptions(g, argc, argv);

    // Cria tabuleiro (consoante opções de jogo)
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
    char col;
    int line;
    char dir;
    char *palavra;

    // Aloca memória para a palavra
    palavra = (char *)malloc(20 * sizeof(char));

    if (g->tabInicial == NULL)
    {
        rules(g);
    }
    
    printTabuleiro(g);

    int pontos;
    do
    {
        pontos = inserirComando(g, &col, &line, &dir, palavra);        
        if (g->endPlaying == 1)
        {  printf("FECHOU NO END");
            break;
        }

        printTabuleiro(g);
             
        if (pontos != -1)
        {   printf("PASSOU NA JOGADA");
            PRINT_MOVE_INFO(g->jogadasRealizadas, col, line, dir, palavra, pontos);
        }

        // Verifica se há apenas um ponto restante no tabuleiro
        if (verificarEspacosVazios(g) <= 1 ) {
            printf("FECHOU NO VERIFICAR ESPACO");
            break;
        }


    } while (g->jogadasRealizadas < g->maxJogadas || g->maxJogadas == NOT_DEFINED);

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
    }
}


void criarTabuleiroFromFile(Game *g, FILE *file)
{
    // Verifica se o arquivo é válido
    if (file == NULL)
    {
        printf("Erro: arquivo não encontrado ou inválido.\n");
        return;
    }

    char c;
    int line_count = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            line_count++;
        }
    }
    g->dim = line_count;

  
    g->tabuleiro = malloc(sizeof(char *) * g->dim);
    for (int i = 0; i < g->dim; i++)
    {
        g->tabuleiro[i] = malloc(sizeof(char) * (g->dim + 1));
    }

    // Retorna o ponteiro do arquivo para o início
    fseek(file, 0, SEEK_SET);

    char line[254];
    for (int i = 0; i < g->dim; i++)
    {
        fgets(line, sizeof(line), file); // Lê uma linha do arquivo
        remove_spaces(line);            // Remove os espaços da linha

        // COLUNA DO TABULEIRO
        for (int j = 0; j < g->dim; j++)
        {
            // LINHA DO TABULEIRO
            if (i >= 9)
            {   
                g->tabuleiro[i][j] = line[j + 2]; // Copia o caractere para o tabuleiro, ignorando os dois primeiros caracteres
                continue;
            }
            
            g->tabuleiro[i][j] = line[j + 1]; // Copia o caractere para o tabuleiro, ignorando o primeiro caractere
        }
    }

}



void criarTabuleiro(Game *g)
{
    // Aloca memória para o tabuleiro com base nas dimensões fornecidas
    g->tabuleiro = malloc(g->dim * sizeof(char *));
    if (g->tabuleiro == NULL) {
        printf("Erro ao alocar memória para o tabuleiro.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < g->dim; i++) {
        g->tabuleiro[i] = malloc(g->dim * sizeof(char));
        if (g->tabuleiro[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d do tabuleiro.\n", i);
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


int lerColuna(char *comando, char *posicaoInicial, int dim) {
    // Verifica se o primeiro caractere é uma letra
    if (!isalpha(comando[0])) {
        printf("Erro: A coluna deve ser uma letra.\n");
        return -1;
    }

    // Verifica se a letra está dentro dos limites do tabuleiro
    char coluna = toupper(comando[0]);
    if (coluna < 'A' || coluna >= 'A' + dim) {
        printf("Erro: A coluna está fora dos limites do tabuleiro.\n");
        return -1;
    }

    // Armazena a coluna na posição inicial
    posicaoInicial[0] = coluna;

    return 1; // Retorna o índice após a coluna
}


int lerLinha(Game *g, char *comando, int index, char *posicaoInicial) {
    // Lê a linha da posição inicial
    int i = 0;
    char tmp[4] = {0};
    while (isdigit(comando[index])) {
        if (i < 3) {
            tmp[i++] = comando[index];
        }
        index++;
    }

    // Verifica se a linha é válida
    int linha = atoi(tmp); // atoi converte uma string em números
    if (linha < 1 || linha > g->dim) {
        printf("Erro: A linha deve ser um número.\n");
        return -1;
    }

    // Armazena a linha na posição inicial
    strcpy(&posicaoInicial[1], tmp);

    return index;
}


int lerDirecao(char *comando, int index, char *direcao) {
    // Armazena a direção
    *direcao = comando[index];

    // Verifica se a direção é válida
    if (*direcao != 'H' && *direcao != 'V') {
        printf("Erro: A direção deve ser H ou V.\n");
        return -1;
    }

    return 1;
}


int lerPalavra(char *comando, int index, char *palavra) {
    // Encontra o índice da posição do espaço no comando
    while (comando[index] != ' ' && comando[index] != '\0') {
        index++;
    }

    // Verifica se encontrou um espaço
    if (comando[index] != ' ') {
        printf("Erro: Deve ter um espaço.\n");
        return -1;
    }

    // Incrementa o índice para pular o espaço
    index++;

    // Copia a palavra do comando para a variável palavra
    strcpy(palavra, comando + index);

    return index;
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

   if (strcmp(comando, "END") == 0) {
        g->endPlaying = 1;
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    index = lerColuna(comando, posicaoInicial, g->dim);

    if (index == -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    index = lerLinha(g, comando, index, posicaoInicial);
    if (index == -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

    // Lê a direção (H ou V)
    if (!lerDirecao(comando, index, dir)) {
        free(comando);
        free(posicaoInicial);
        return -1;
    } 

    index++;

    // Lê a palavra a ser inserida
    index = lerPalavra(comando, index, palavra); 
    if (index <= -1) {
        free(comando);
        free(posicaoInicial);
        return -1;
    }

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
            if (g->tabuleiro[i][j] == '.') {
                pontosRestantes++;
            }
        }
    }

    // Retorna a quantidade de pontos restantes no tabuleiro
    return pontosRestantes;
}



int validarPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial, char **tabuleiro) {
    // Verifica se a palavra contém apenas caracteres válidos (letras)
    for (int j = 0; palavra[j] != '\0'; j++) {
        if (!isalpha(palavra[j])) {
            printf("Erro: Apenas letras.\n"); 
            return 0;
        }
    }

    // Verifica se a palavra tem pelo menos 2 caracteres
    if (strlen(palavra) < 3) {
        printf("Erro: Mais de 2 caracteres.\n");
        return 0;
    }

    // Verifica se a palavra cabe no tabuleiro na direção escolhida
    int tamanho_palavra = strlen(palavra);
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1;

    if (direcao == 'H') {
        if (coluna + tamanho_palavra > g->dim) {
            printf("Erro: Direçao incorreta.\n");
            return 0;
        }
    } else { // direcao == 'V'
        if (linha + tamanho_palavra > g->dim) {
            printf("Erro: Direçao incorreta.\n");
            return 0;
        }
    }

    
    int letrasIguais = 0;
for (int i = 0; palavra[i] != '\0'; i++) {
    if (direcao == 'H') {
        if (isalpha(tabuleiro[linha][coluna + i]) && tabuleiro[linha][coluna + i] != palavra[i]) {
            printf("Erro: Letra incompatível no tabuleiro.\n");
            return 0;
        } else if (tabuleiro[linha][coluna + i] == '#') {
            printf("Erro: Erro ##.\n");
            return 0;
        } else if (tabuleiro[linha][coluna + i] == palavra[i]) {
            letrasIguais++;
        }
    } else { // direcao == 'V'
        if (isalpha(tabuleiro[linha + i][coluna]) && tabuleiro[linha + i][coluna] != palavra[i]) {
            printf("Erro: Letra incompatível no tabuleiro.\n");
            return 0;
        } else if (tabuleiro[linha + i][coluna] == '#') {
            printf("Erro: ##.\n");
            return 0;
        } else if (tabuleiro[linha + i][coluna] == palavra[i]) {
            letrasIguais++;
        }
    }
}

if (letrasIguais == strlen(palavra)) {
    printf("Erro: Palavras iguais não são permitidas.\n");
    return 0;
}


    return 1;
}


void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial)
{
    /**
     * ! Novo 
     * Funçao para inserir palavra horizontal ou vertical
     */
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1; // atoi para converter corretamente para int
    /**
     * ! Decorar
     * &posicaoInicial[1]: Este é o endereço do segundo elemento do array 
     * posicaoInicial. Como o primeiro elemento contém a coluna (uma letra), o segundo elemento e os seguintes representam a linha (um ou mais números). O operador & retorna o endereço do elemento, então passamos esse endereço para a função atoi.
     * atoi(&posicaoInicial[1]): A função atoi converte uma string de caracteres representando números inteiros em um valor inteiro. Neste caso, estamos passando a parte da string posicaoInicial que contém os números da linha. A função retorna o valor inteiro correspondente.
     * atoi(&posicaoInicial[1]) - 1: Como os índices do array começam em 0, precisamos subtrair 1 do valor da linha para que ele corresponda à posição correta no array do tabuleiro. Por exemplo, se a linha inserida for 1, queremos que a posição no array seja 0.
     */

    if (direcao == 'H')   //Horizontal
    {
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha][coluna + i] = palavra[i];
        }
    }
    else if (direcao == 'V') //Vertical
    {
        for (int i = 0; palavra[i] != '\0'; i++)
        {
            g->tabuleiro[linha + i][coluna] = palavra[i];
        }
    }
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
        if (direcao == 'H' && tabuleiro[linha][coluna + i] == '2') {
            letraPontos *= 2;
        } else if (direcao == 'V' && tabuleiro[linha + i][coluna] == '2') {
            letraPontos *= 2;
        }

        // Regra para multiplicar por 3
        if (direcao == 'H' && tabuleiro[linha][coluna + i] == '3') {
            letraPontos *= 3;
        } else if (direcao == 'V' && tabuleiro[linha + i][coluna] == '3') {
            letraPontos *= 3;
        }

         // Regra para multiplicar por 4
        if (direcao == 'H' && tabuleiro[linha][coluna + i] == '4') {
            letraPontos *= 4;
        } else if (direcao == 'V' && tabuleiro[linha + i][coluna] == '4') {
            letraPontos *= 4;
        }

        // Regra para duplicar palavra
        if (direcao == 'H' && tabuleiro[linha][coluna + i] == '$') {
            multiplicadorPalavra *= 2;
        } else if (direcao == 'V' && tabuleiro[linha + i][coluna] == '$') {
            multiplicadorPalavra *= 2;
        }

        // Regra para triplicar palavra
        if (direcao == 'H' && tabuleiro[linha][coluna + i] == '!') {
            multiplicadorPalavra *= 3;
        } else if (direcao == 'V' && tabuleiro[linha + i][coluna] == '!') {
            multiplicadorPalavra *= 3;
        }

        pontos += letraPontos;
    }

    pontos *= multiplicadorPalavra;

    return pontos;
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
