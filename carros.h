#ifndef CARROS_H
#define CARROS_H

/**
 * !Estrutura de dados
*/

#define TEXT_LEN 50 //cada string possui no máximo 50 carct.

typedef struct carro Carro;
typedef struct garagem Garagem;

typedef struct carro{
    int id; //Número sequencial a atribuir pelo sistema
    char *matricula;
    char *marca;
    char *modelo;
    double valor;
    int ano;
}Carro;


typedef struct garagem{
    char *nome;
    int num_carros;
    int max_carros;
    Carro **carros;
    double valor_total;
    int next_id;
}Garagem;

/**
 * !Funções públicas
*/

/**
 * Criar uma garagem para n Carros
 * @param dim dimensão da garagem. Nº de carros máximo
 * @return ponteiro para garagem
*/
Garagem *newGaragem(int dim, char *nome);

/**
 * Limpa a memória da garagem
 * @param g ponteiro para garagem
*/
void free_garagem(Garagem *g);

/**
 * Escreve no ecrá informação da garagem
 * (Nome da garagem)
 * (Número de carros existentes)
 * (Valor dos carros existentes)
 * (lugares vagos na garagem)
 * (vosso critério imprimir lista de carros existentes - info reduzida)
 * @param g ponteiro para garagem
*/
void print_info_garagem(Garagem *g);


/**
 * Insere um carro se a garagem tiver vaga. Se não tiver não insere e dá erro
 * @param g Garagem
 * @param matricula do carro
 * etc
*/
void inserir_carro(Garagem *g,char *matricula, char *marca, char* modelo, int ano, double valor);

/**
 * Se carro existir apaga e escreve a matricula apagada
 * Se carro não existir dá mensagem de erro
*/
void apagar_carro(Garagem *g, int id);

/**
 * Se carro existir substitui o modelo
 * Se carro não existir (id) dá mensagem de erro
*/
void editar_modelo(Garagem *g, int id, char *modelo);

/**
 * strstr()
 * Imprime lista de carros que correspondem à pesquisa
*/
void pesquisar_marca(Garagem *g, char *pesquisa);

/**
 * Imprime todos os campos da estrutura carro.
 * Se o carro com o ida existir imprime a ficha.
 * Caso contrario dá erro
*/
void ficha_carro(Garagem *g, int id);

/**
 * strstr()
 * Imprime lista de carros do ano em causa
*/
void pesquisar_ano(Garagem *g, int ano);

#endif