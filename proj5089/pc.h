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
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define SPACE ' '

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

/**
 * @brief Converte todos os caracteres de uma string para maiúsculas.
 *
 * Esta função percorre cada caractere da string fornecida e o converte
 * para sua versão maiúscula, caso seja uma letra minúscula. A conversão
 * é feita usando a função toupper da biblioteca ctype.h.
 *
 * @param str Ponteiro para a string a ser convertida.
 */
void to_upper(char *str);  
/**
 * @brief carrega as opções do jogo passado pela linha de comandos
 *
 * @param g Objeto jogo
 * @param argc
 * @param argv
 */
void loadOptions(Game *g, int argc, char const *argv[]);

/**
 * Função para criar um tabuleiro de jogo a partir de um arquivo.
 * @param g: Ponteiro para a estrutura Game que armazena o tabuleiro e sua dimensão.
 * @param file: Ponteiro para o arquivo que contém a configuração do tabuleiro.
 */
void freeGame(Game *g); 

/**
 * Função para criar um tabuleiro de jogo a partir de um arquivo.
 * @param g: Ponteiro para a estrutura Game que armazena o tabuleiro e sua dimensão.
 * @param file: Ponteiro para o arquivo que contém a configuração do tabuleiro.
 */
void criarTabuleiroFromFile(Game *g, FILE *file); 

/**
 * @brief Cria e inicializa o tabuleiro do jogo.
 *
 * Esta função aloca memória para o tabuleiro do jogo, com base nas dimensões
 * fornecidas no objeto Game. Em seguida, inicializa todas as células do tabuleiro
 * com o caractere vazio (SYMBOL_EMPTY), que é definido como '.'.
 *
 * @param g Ponteiro para a estrutura do jogo (Game) onde o tabuleiro será criado.
 */
void criarTabuleiro(Game *g);   

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
void rules(Game *g); 

/**
 * @brief Lê a coluna do comando e verifica se está dentro dos limites do tabuleiro.
 *
 * @param comando Ponteiro para a string do comando inserido pelo usuário.
 * @param posicaoInicial Ponteiro para a string que armazenará a posição inicial da palavra no tabuleiro.
 * @param dim Dimensão do tabuleiro (número de linhas e colunas).
 * @return Retorna o índice após a coluna na string do comando, ou -1 se a coluna for inválida.
 */
int lerColuna(char *comando, char *posicaoInicial, int dim) ;  

/**
 * @brief Lê a linha do comando e verifica se está dentro dos limites do tabuleiro.
 *
 * @param g Ponteiro para a estrutura do jogo, que contém informações como a dimensão do tabuleiro.
 * @param comando Ponteiro para a string do comando inserido pelo usuário.
 * @param index Índice na string do comando onde a leitura da linha deve começar.
 * @param posicaoInicial Ponteiro para a string que armazenará a posição inicial da palavra no tabuleiro.
 * @return Retorna o índice após a linha na string do comando, ou -1 se a linha for inválida.
 */
int lerLinha(Game *g, char *comando, int index, char *posicaoInicial); 

/**
 * @brief Lê a direção (H ou V) do comando fornecido pelo usuário.
 * @param comando String com o comando inserido pelo usuário.
 * @param index Índice atualizado após ler a posição inicial.
 * @param direcao Ponteiro para armazenar a direção lida (H ou V).
 * @return Retorna 1 se a direção for válida, caso contrário, retorna 0.
 */
int lerDirecao(char *comando, int index, char *direcao) ; 

/**
 * @brief Lê a palavra do comando fornecido pelo usuário.
 * @param comando String com o comando inserido pelo usuário.
 * @param index Índice atualizado após ler a posição inicial e a direção.
 * @param palavra Ponteiro para armazenar a palavra lida.
 */
int lerPalavra(char *comando, int index, char *palavra) ; 

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
int inserirComando(Game *g, char *col, int *line, char *dir, char *palavra) ;  

/**
 * @brief Valida se uma palavra pode ser inserida no tabuleiro na posição e direção especificadas.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 * @param palavra A palavra a ser inserida.
 * @param direcao A direção da palavra a ser inserida ('H' para horizontal, 'V' para vertical).
 * @param posicaoInicial A posição inicial da palavra no tabuleiro.
 * @param tabuleiro O tabuleiro onde a palavra será inserida.
 * @return Retorna 1 se a palavra for válida e 0 caso contrário.
 */
int validarPalavra(Game *g,char *palavra, char direcao, char *posicaoInicial, char **tabuleiro);  

/**
 * @brief Calcula a pontuação de uma letra individual.
 * @param letra A letra para a qual se deseja calcular a pontuação.
 * @return A pontuação da letra.
 */
int pontuacaoLetra(char letra);  

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
int regrasMultiplicacao(Game *g, char *palavra, char **tabuleiro, int linha, int coluna, char direcao); 

/**
 * @brief Insere uma palavra no tabuleiro na posição e direção especificadas.
 * @param g Ponteiro para a estrutura Game que contém informações do jogo.
 * @param palavra A palavra a ser inserida.
 * @param direcao A direção da palavra a ser inserida ('H' para horizontal, 'V' para vertical).
 * @param posicaoInicial A posição inicial da palavra no tabuleiro.
 */
void inserirPalavra(Game *g, char *palavra, char direcao, char *posicaoInicial);  

void remove_spaces(char *s);

#endif