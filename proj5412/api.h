#ifndef API_H
#define API_H
#include <stdio.h>

/*dimensão dos campos*/
#define CITY_ID 3 /* Tipo AAA*/
#define MAX_CITY_NAME 50
#define MAX_INDICE_LENGHT 6 /*entre 0.01 e 999.99*/
#define MAX_FILE_NAME 100 /*tamanho da string passada como argumento ao programa*/

/*MENSAGENS API*/
#define MSG_TOTAL_CITIES(TOTAL) printf("%d\n",TOTAL);
#define MSG_CITY_INFO_HEADER(CITY,STATUS,LINKS,NAME) printf("%s (%d): Existem %d ligações a partir de %s\n",CITY,STATUS,LINKS,NAME);
#define MSG_CITY_INFO_ITEM(TO_CITY,IH,IE,IT) printf("\t->%s: %.2f %.2f %.2f\n",TO_CITY,IH,IE,IT);
#define MSG_ROUTE_HEADER(FROM,TO,INDEX,VALUE) printf("%s->%s %c=%.2f\n",FROM,TO,INDEX,VALUE);
#define MSG_ROUTE_ITEM(PATH) printf("\t%s\n",PATH);
#define MSG_FILE_SAVED(filename) printf("SGO gravado no ficheiro %s\n",filename);

/*MENSAGENS DE ERRO*/
#define ERROR_CITY_REPEATED(CITY) printf("*Cidade %s duplicada\n", CITY);
#define ERROR_NO_CITY(CITY) printf("*Cidade %s inexistente\n", CITY);
#define ERROR_CITY_INACTIVE(CITY) printf("*Cidade %s inativa\n", CITY);
#define ERROR_NO_LINK(FROM,TO) printf("*Ligação %s->%s inexistente\n",FROM,TO);
#define ERROR_NO_ROUTE(FROM,TO) printf("*%s->%s sem ligação\n",FROM,TO);
#define ERROR_DB_EMPTY printf("*Base de dados vazia\n");
#define ERROR_FILE_EXTENSION(filename) printf("*Ficheiro %s não suportado\n",filename);


/*Strings formatadas para salvar sgo num ficheiro*/
#define ADD_CITY "A %s %s\n"
#define CHANGE_CITY_STATE "O %s %d\n"
#define ADD_LINK "C %s %s\n"
#define CHANGE_TURISTIC_INDEX "T %s %s %.2f\n"
#define CHANGE_ECONOMIC_INDEX "E %s %s %.2f\n"
#define CHANGE_TIME_INDEX "H %s %s %.2f\n"

/* Modelo de Dados */


/* Estrutura de uma ligação entre cidades */
typedef struct lig {
    /* Controle */
    struct lig *nextL; /* Ponteiro para a próxima ligação na lista encadeada */
    struct lig *prevL; /* Ponteiro para a ligação anterior na lista encadeada */

    /* Payload */
    float indiceTemporal; /* Índice temporal da ligação */
    float indiceEconomico; /* Índice econômico da ligação */
    float indiceTuristico; /* Índice turístico da ligação */

    char destino[CITY_ID]; /* Código de identificação da cidade destino da ligação */
} Lig;

/* Estrutura de uma cidade */
typedef struct cidade {
    /* Controle */
    struct cidade *nextC; /* Ponteiro para a próxima cidade na lista encadeada */
    struct cidade *prevC; /* Ponteiro para a cidade anterior na lista encadeada */

    Lig *first; /* Ponteiro para a primeira ligação na lista de ligações desta cidade */
    Lig *last;  /* Ponteiro para a última ligação na lista de ligações desta cidade */

    /* Payload */
    char codigo[CITY_ID]; /* Código de identificação da cidade com 3 caracteres */
    char *nome; /* Ponteiro para o nome da cidade (alocado dinamicamente com malloc) */
    int estado; /* Estado da cidade, podendo ser 1 (ativo) ou 0 (inativo) */
    int numLigacoes; /* Número de ligações que a cidade possui */
} Cidade;

/* Estrutura do mapa contendo todas as cidades */
typedef struct mapa {
    /* Controle */
    Cidade *firstC; /* Ponteiro para a primeira cidade na lista encadeada */
    Cidade *lastC;  /* Ponteiro para a última cidade na lista encadeada */
    /* Payload */
    int numCidades; /* Número total de cidades no mapa */

} Mapa;





/**
 * API - Declaração das funções públicas
 * 
 **/

/**
 * @brief Cria um novo mapa, inicializando seus campos e alocando memória para a estrutura Mapa
 * 
 * @return Ponteiro para a estrutura Mapa recém-criada
 */
Mapa *new_mapa(); 

void change_indice(Mapa *m, char *codigo_origem, char *codigo_last, float indice, char type);

/**
 * @brief Adiciona uma nova cidade ao mapa, mantendo a lista de cidades em ordem alfabética
 * 
 * @param m Ponteiro para o mapa onde a cidade será adicionada
 * @param codigo Código da cidade a ser adicionada
 * @param nome Nome da cidade a ser adicionada
 */
void adicionar_cidade(Mapa *m,char *codigo,char *nome);  

/**
 * @brief Altera o estado de uma cidade no mapa
 * 
 * @param m Ponteiro para o mapa onde a cidade está localizada
 * @param codigo Código da cidade cujo estado será alterado
 * @param estado Novo estado da cidade (1 para ativo, 0 para inativo)
 */
void altera_estado(Mapa *m, char *codigo, int estado); 

/**
 * @brief Exibe informações sobre uma cidade no mapa
 * 
 * @param m Ponteiro para o mapa onde a cidade está localizada
 * @param codigo Código da cidade cujas informações serão exibidas
 * @param estado Nível de detalhamento das informações (0 para reduzido, 1 para completo)
 */
void devolve_info_cidade(Mapa *m, char *codigo, int estado); 

/**
 * @brief Imprime informações sobre todas as cidades no mapa
 * 
 * @param m Ponteiro para o mapa que contém as cidades
 */
void print_cidades(Mapa *m); 

/**
 * @brief Imprime o número total de cidades no mapa
 * 
 * @param m Ponteiro para o mapa que contém as cidades
 */
void total_cidades(Mapa *m);

/**
 * @brief Adiciona uma ligação entre duas cidades no mapa
 * 
 * @param m Ponteiro para o mapa que contém as cidades
 * @param codigo_origem Código da cidade de origem
 * @param cod_destino Código da cidade de destino
 */
void adiciona_ligacao_cidade(Mapa *m, char *codigo, char *cod_destino);

/**
 * @brief Remove uma ligação entre duas cidades no mapa e libera a memória alocada
 * 
 * @param m Ponteiro para o mapa que contém as cidades
 * @param codigo_origem Código da cidade de origem
 * @param codigo_last Código da cidade de destino
 */
void free_ligacao(Mapa *m, char *codigo_origem, char *codigo_last);

void change_turismo(Mapa *m,char *codigo_origem, char *codigo_last, float indice_t);

void change_economico(Mapa *m,char *codigo_origem, char *codigo_last, float indice_e);

void change_temporal(Mapa *m,char *codigo_origem, char *codigo_last, float indice_h);

/**
 * @brief Remove uma cidade e todas as suas ligações do mapa e libera a memória alocada
 * 
 * @param m Ponteiro para o mapa que contém as cidades
 * @param cidade Código da cidade a ser removida
 */
void remover_cidade(Mapa *m, char *cidade); 

void guardar_file(); 

/**
 * @brief Libera a memória alocada para todas as cidades e ligações do mapa e reinicializa o mapa
 * 
 * @param m Ponteiro para o mapa que contém as cidades e ligações
 */
void free_mapa(Mapa *m);


#endif