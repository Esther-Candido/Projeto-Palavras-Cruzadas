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


/**
 * @brief Retira espaços de uma string.
 * Retirado de stackoverflow
 * https://stackoverflow.com/questions/1726302/remove-spaces-from-a-string-in-c
 * @param s String
 */
void remove_spaces(char *s);    //! Feito

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
void loadOptions(Game *g, int argc, char const *argv[]);    //TODO Incompleto

void freeGame(Game *g); //!Feito

void criarTabuleiroFromFile(Game *g) ; //TODO Incompleto

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
 * @brief Lê a posição inicial (coluna e linha) do comando fornecido pelo usuário.
 * @param g Ponteiro para a estrutura do jogo.
 * @param comando String com o comando inserido pelo usuário.
 * @param posicaoInicial String para armazenar a posição inicial (coluna e linha).
 * @return Retorna o índice atualizado após ler a posição inicial, caso contrário, retorna 0.
 */
int lerPosicaoInicial(Game *g,char *comando, char *posicaoInicial);  //! Novo

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
void lerPalavra(char *comando, int index, char *palavra) ;  //! Novo

/**
 * @brief Insere um comando no jogo e atualiza a pontuação do jogador.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 */
void inserirComando(Game *g);  //! Novo

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
        criarTabuleiroFromFile(g);
    else
        criarTabuleiro(g);

    // devolve jogo
    
    return g;
}

void freeGame(Game *g)
{
    if (g == NULL) return;

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
    
    rules(g);  //!ruben 

    // Mostra o tabuleiro
    printTabuleiro(g);
    
    do
    {
     // Solicita ao utilizador para inserir o comando
    inserirComando(g);

    if (g->endPlaying == 1) {
        printf("Jogo encerrado pelo jogador.\n");
        break;
    }

    // Mostra o tabuleiro com as palavras inseridas
    printTabuleiro(g);  
    printf("Jogada %d realizada.\n", g->jogadasRealizadas);
    
        
     } while (g->jogadasRealizadas < g->maxJogadas || g->maxJogadas==NOT_DEFINED);

     PRINT_FINAL_SCORE(g->score);
   
    
    // TODO: Função que joga o jogo.
    // !Pode invocar outras funçoes que serão criadas pelos alunos
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
                    printf("Dimensão do tabuleiro inválida. Insira um número ímpar entre 7 e 15.\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;
        case 'n':
            if (i + 1 < argc) {
                g->maxJogadas = atoi(argv[++i]);
            }
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
    // Aloca memória para o tabuleiro com base nas dimensões fornecidas
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


int lerPosicaoInicial(Game *g,char *comando, char *posicaoInicial) {
    /**
     * ! Novo
     * Função para ler a coluna e a linha
     */

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
    if (linha < 1 || linha > g->dim) {
        printf("Erro: A linha deve ser um número entre 1 e %d.\n", g->dim);
        return 0;
    }

    // Armazena a linha na posição inicial
    strcpy(&posicaoInicial[1], tmp);
    posicaoInicial[3] = '\0';

    return index;
}


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
    int coluna, linha;

    // Lê o comando do usuário
    printf("Insira comando-> ");
    fgets(comando, 30, stdin);
    comando[strcspn(comando, "\n")] = 0; // Remove o caractere de nova linha

    remove_spaces(comando);

    
    // Converte o comando para maiúsculas
    to_upper(comando);

    // Verifica se o comando é "end"
      if (strcmp(comando, "END") == 0) {
        g->endPlaying = 1;
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }


    // Lê a posição inicial (coluna e linha)
    int index = lerPosicaoInicial(g, comando, posicaoInicial);

    if (index == 0) {
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }

    // Inicializa a linha e a coluna com os valores da posição inicial
    coluna = posicaoInicial[0] - 'A';
    linha = atoi(&posicaoInicial[1]) - 1;

    // Lê a direção (H ou V)
    if (!lerDirecao(comando, index, &direcao)) {
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }

    // Lê a palavra a ser inserida
    lerPalavra(comando, index, palavra);

    if (!validarPalavra(g, palavra, direcao, posicaoInicial, g->tabuleiro)) {
        free(comando);
        free(posicaoInicial);
        free(palavra);
        return;
    }

    // Inicializa a linha e a coluna com os valores da posição inicial
    coluna = posicaoInicial[0] - 'A';
    linha = atoi(&posicaoInicial[1]) - 1;

    // Calcula a pontuação da palavra antes de inseri-la no tabuleiro usando a função regrasMultiplicacao
    int pontos = regrasMultiplicacao(g, palavra, g->tabuleiro, linha, coluna, direcao);

    // Insere a palavra no tabuleiro
    inserirPalavra(g, palavra, direcao, posicaoInicial);

    // Atualiza a pontuação do jogador e incrementa o número de jogadas realizadas
    g->jogadasRealizadas++;
    g->score += pontos;

    // Exibe a pontuação do jogador
    printf("Pontos obtidos nesta jogada: %d\n", pontos);
    printf("Pontuação total: %d\n", g->score);

    // Libera a memória alocada
    free(comando);
    free(posicaoInicial);
    free(palavra);
}


int validarPalavra(Game *g,char *palavra, char direcao, char *posicaoInicial, char **tabuleiro) {
    // Verifica se a palavra contém apenas caracteres válidos (letras)
    for (int j = 0; palavra[j] != '\0'; j++) {
        if (!isalpha(palavra[j])) {
            printf("Erro: A palavra deve conter apenas letras.\n");
            return 0;
        }
    }

    // Verifica se a palavra tem pelo menos 2 caracteres
    if (strlen(palavra) < 3) {
        printf("Erro: A palavra deve ter pelo menos 2 caracteres.\n");
        return 0;
    }

    // Verifica se a palavra cabe no tabuleiro na direção escolhida
    int tamanho_palavra = strlen(palavra);
    int coluna = posicaoInicial[0] - 'A';
    int linha = atoi(&posicaoInicial[1]) - 1;

    if (direcao == 'H') {
        if (coluna + tamanho_palavra > g->dim) {
            printf("Erro: A palavra excede o limite do tabuleiro.\n");
            return 0;
        }
    } else { // direcao == 'V'
        if (linha + tamanho_palavra > g->dim) {
            printf("Erro: A palavra excede o limite do tabuleiro.\n");
            return 0;
        }
    }

    
   int letrasIguais = 0;

    for (int i = 0; palavra[i] != '\0'; i++) {
        if (direcao == 'H') {
            if (isalpha(tabuleiro[linha][coluna + i]) && tabuleiro[linha][coluna + i] != palavra[i]) {
                printf("Erro: A posição já está ocupada por outra letra.\n");
                return 0;
            } else if (tabuleiro[linha][coluna + i] == '#') {
                printf("Erro: A posição está ocupada pelo símbolo '#'.\n");
                return 0;
            } else if (tabuleiro[linha][coluna + i] == palavra[i]) {
                letrasIguais++;
            }
        } else { // direcao == 'V'
            if (isalpha(tabuleiro[linha + i][coluna]) && tabuleiro[linha + i][coluna] != palavra[i]) {
                printf("Erro: A posição já está ocupada por outra letra.\n");
                return 0;
            } else if (tabuleiro[linha + i][coluna] == '#') {
                printf("Erro: A posição está ocupada pelo símbolo '#'.\n");
                return 0;
            } else if (tabuleiro[linha + i][coluna] == palavra[i]) {
                letrasIguais++;
            }
        }
    }

    if (letrasIguais > 1) {
        printf("Erro: Apenas uma letra pode ser igual.\n");
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
