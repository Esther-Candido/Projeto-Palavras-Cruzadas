#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carros.h"


/**
 * Criar uma garagem para n Carros
 * @param dim dimensão da garagem. Nº de carros máximo
 * @return ponteiro para garagem
*/
Garagem *newGaragem(int dim, char *nome){
    Garagem *g=malloc(sizeof(Garagem));
    g->max_carros=dim;
    g->carros=0;
    g->valor_total=0.0;
    g->next_id=1;
    g->nome=malloc(strlen(nome)+1);
    memset(g->nome,'\0',strlen(nome)+1);
    strcpy(g->nome, nome);
    g->carros=malloc(sizeof(Carro *)*dim);
    for (int i = 0; i < dim; i++)
        g->carros[i]=NULL;
    return g;
}

/**
 * Limpa a memória da garagem
 * @param g ponteiro para garagem
*/
void free_garagem(Garagem *g){

}

/**
 * Escreve no ecrá informação da garagem
 * (Nome da garagem)
 * (Número de carros existentes)
 * (Valor dos carros existentes)
 * (lugares vagos na garagem)
 * (vosso critério imprimir lista de carros existentes - info reduzida)
 * @param g ponteiro para garagem
*/
void print_info_garagem(Garagem *g){
    puts("---Info da Garagem---");
    printf("### %s ###\n", g->nome);
    printf("Valor: %lf, Carros:%d\n",g->valor_total,g->num_carros);
}


/**
 * Insere um carro se a garagem tiver vaga. Se não tiver não insere e dá erro
 * @param g Garagem
 * @param matricula do carro
 * etc
*/
void inserir_carro(Garagem *g,char *matricula, char *marca, char* modelo, int ano, double valor){

}

/**
 * Se carro existir apaga e escreve a matricula apagada
 * Se carro não existir dá mensagem de erro
*/
void apagar_carro(Garagem *g, int id){

}

/**
 * Se carro existir substitui o modelo
 * Se carro não existir (id) dá mensagem de erro
*/
void editar_modelo(Garagem *g, int id, char *modelo){

}

/**
 * strstr()
 * Imprime lista de carros que correspondem à pesquisa
*/
void pesquisar_marca(Garagem *g, char *pesquisa){

}

/**
 * Imprime todos os campos da estrutura carro.
 * Se o carro com o ida existir imprime a ficha.
 * Caso contrario dá erro
*/
void ficha_carro(Garagem *g, int id){

}

/**
 * strstr()
 * Imprime lista de carros do ano em causa
*/
void pesquisar_ano(Garagem *g, int ano){

}

