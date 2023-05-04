#include <stdlib.h>
#include <string.h>
#include "api.h"

/**
 * ######### Funções internas da biblioteca #########
 * ##################################################
 **/
Mapa *new_mapa() /** ADICIONADO POR RUBEN */
{
    Mapa *m = malloc(sizeof(Mapa));
    m->firstC = NULL;
    m->lastC = NULL;
    m->numCidades = 0;
    return m;
}

Cidade *procura_cidade(Mapa *m, char *codigo) /** ADICIONADO POR RUBEN */
{
    /* Inicializa o ponteiro aux com a primeira cidade do mapa */
    Cidade *aux = m->firstC;

    /* Itera através de todas as cidades no mapa */
    while (aux)
    {
        /* Compara o código da cidade atual com o código fornecido */
        if (strcmp(aux->codigo, codigo) == 0)
            /* Se os códigos forem iguais, retorna a cidade atual */
            return aux;

        /* Atualiza o ponteiro aux para a próxima cidade */
        aux = aux->nextC;
    }

    /* Se a cidade não for encontrada, retorna NULL */
    return NULL;
}

Cidade *percorre_cidades(Cidade *cidade_atual) /** ADICIONADO POR RUBEN */
{
    /** Retorna o ponteiro para a próxima cidade na lista **/
    if (cidade_atual != NULL)
    {
        return cidade_atual->nextC;
    }

    /** Retorna NULL se a cidade_atual for NULL **/
    return NULL;
}

Lig *search_link(Cidade *cidade, char *codigo_destino) /** ADICIONADO POR RUBEN */
{
    /* Inicializa o ponteiro aux com a primeira ligação da cidade */
    Lig *aux = cidade->first;

    /* Itera através de todas as ligações da cidade */
    while (aux) {
        /* Compara o código de destino da ligação atual com o código fornecido */
        if (strcmp(aux->destino, codigo_destino) == 0)
            /* Se os códigos de destino forem iguais, retorna a ligação atual */
            return aux;

        /* Atualiza o ponteiro aux para a próxima ligação */
        aux = aux->nextL;
    }

    /* Se a ligação não for encontrada, retorna NULL */
    return NULL;
}

Lig *percorre_links(Lig *cidade_atual) /** ADICIONADO POR RUBEN */
{
    /** Retorna o ponteiro para a próxima cidade na lista **/
    if (cidade_atual != NULL)
    {
        return cidade_atual->nextL;
    }

    /** Retorna NULL se a cidade_atual for NULL **/
    return NULL;
}


/**
 * ######### Implementação das Funções da Biblioteca#########
 * ###########################################################
 **/

void altera_Estado(Mapa *m, char codigo, int estado) { /** ADICIONADO POR ESTHER */

}

void free_mapa(Mapa *m) /** ADICIONADO POR RUBEN */
{
    
}

void add_city(Mapa *m, char *codigo, char *nome) /** ADICIONADO POR RUBEN */
{
   /** Utiliza a função procura_cidade para verificar se a cidade já existe **/
    Cidade *cidade_existente = procura_cidade(m, codigo);
    if (cidade_existente != NULL)
    {
        ERROR_CITY_REPEATED(codigo);
        return;
    }

    /** Inicializa o ponteiro auxiliar para percorrer a lista de cidades **/
    Cidade *aux = m->firstC;
    /** Declara um ponteiro para a nova cidade que será adicionada **/
    Cidade *nova_cidade;

    /** Percorre a lista de cidades até encontrar uma cidade com código maior ou até chegar ao final da lista **/
    while (aux)
    {
        /** Se o código da cidade atual na lista for maior que o novo, interrompe o loop **/
        if (strcmp(aux->codigo, codigo) > 0)
            break;

        /** Atualiza o ponteiro auxiliar para a próxima cidade na lista **/
        aux = aux->nextC;
    }

    /** Incrementa o contador de cidades **/
    m->numCidades++;
    /** Aloca memória para a nova cidade e inicializa seus atributos **/
    nova_cidade = malloc(sizeof(Cidade));
    strncpy(nova_cidade->codigo, codigo, CITY_ID);

    nova_cidade->nome = malloc((MAX_CITY_NAME + 1) * sizeof(char));
    strncpy(nova_cidade->nome, nome, MAX_CITY_NAME);
    nova_cidade->nome[MAX_CITY_NAME] = '\0';

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

void print_citys(Mapa *m)/** ADICIONADO POR RUBEN */
{
    /** Caso BaseDados Vazia**/
    if (m->firstC == NULL)
    {
        ERROR_DB_EMPTY;
    }
    
    /** Inicializa um ponteiro para a primeira cidade do mapa **/
    Cidade *print_city = m->firstC;

    /** Enquanto houver cidades no mapa, percorre a lista de cidades **/
    while (print_city)
    {
        /** Imprime as informações da cidade atual, incluindo código, estado, número de ligações e nome **/
        MSG_CITY_INFO_HEADER(print_city->codigo, print_city->estado, print_city->numLigacoes, print_city->nome);

        /** Atualiza o ponteiro para a próxima cidade na lista usando a função percorre_cidades **/
        print_city = percorre_cidades(print_city);
    }
    
}