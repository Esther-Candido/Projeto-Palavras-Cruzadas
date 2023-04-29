#include <stdlib.h>
#include <string.h>
#include "api.h"

/**
 * ######### Funções internas da biblioteca #########
 * ##################################################
 **/



/**
 * ######### Implementação das Funções da Biblioteca#########
 * ###########################################################
 **/

Mapa *new_mapa() /** ADICIONADO POR RUBEN */
{
    Mapa *m = malloc(sizeof(Mapa));
    m->firstC = NULL;
    m->lastC = NULL;
    m->numCidades = 0;
    return m;
}

void free_mapa(Mapa *m) /** ADICIONADO POR RUBEN */
{
    
}
void add_city(Mapa *m, char *codigo, char *nome) /** ADICIONADO POR RUBEN */
{
    /** Inicializa o ponteiro auxiliar para percorrer a lista de cidades **/
    Cidade *aux = m->firstC;
    /** Declara um ponteiro para a nova cidade que será adicionada **/
    Cidade *nova_cidade;

    /** Percorre a lista de cidades até encontrar uma cidade com código maior ou até chegar ao final da lista **/
    while (aux)
    {
        /** Verifica se a cidade já existe e, caso exista, exibe uma mensagem de erro e retorna **/
        if (strcmp(aux->codigo, codigo) == 0)
        {
            ERROR_CITY_REPEATED(codigo);
            return;
        }

        /** Se o código da cidade atual na lista for maior que o novo, interrompe o loop **/
        if (strcmp(aux->nome, nome) > 0)
            break;

        /** Atualiza o ponteiro auxiliar para a próxima cidade na lista **/
        aux = aux->nextC;
    }

    /** Incrementa o contador de cidades **/
    m->numCidades++;
    /** Aloca memória para a nova cidade e inicializa seus atributos **/
    nova_cidade = malloc(sizeof(Cidade));
    strncpy(nova_cidade->codigo, codigo, CITY_ID);
    nova_cidade->nome = malloc(strlen(nome) + 1);
    strcpy(nova_cidade->nome, nome);
    nova_cidade->numLigacoes = 0;
    nova_cidade->estado = 1;

    /** Se a lista de cidades estiver vazia, insere a nova cidade como única na lista **/
    if (m->firstC == NULL)
    {
        nova_cidade->nextC = NULL;
        nova_cidade->prevC = NULL;
        m->firstC = nova_cidade;
        m->lastC = nova_cidade;
        return;
    }
     
    /** Se aux for NULL, insere a nova cidade no final da lista **/
    if (aux == NULL)
    {
        m->lastC->nextC = nova_cidade;
        nova_cidade->prevC = m->lastC;
        nova_cidade->nextC = NULL;
        m->lastC = nova_cidade;
        return;
    }
    /** Se aux for a primeira cidade da lista, insere a nova cidade antes dela **/
    if (aux->prevC == NULL)
    {
        nova_cidade->nextC = m->firstC;
        nova_cidade->prevC = NULL;
        m->firstC->prevC = nova_cidade;
        m->firstC = nova_cidade;
        return;
    }
    
    /** Insere a nova cidade antes da cidade aux, atualizando os ponteiros **/
    nova_cidade->nextC = aux;
    nova_cidade->prevC = aux->prevC;
    aux->prevC->nextC = nova_cidade;
    aux->prevC = nova_cidade;
}

void print_citys(Mapa *m) /** ADICIONADO POR RUBEN IMCOMPLETO!*/
{

    Cidade *aux = m->firstC;
    while (aux)
    {
        MSG_CITY_INFO_HEADER(aux->codigo,aux->estado,aux->numLigacoes,aux->nome);
        aux = aux->nextC;
    }

}