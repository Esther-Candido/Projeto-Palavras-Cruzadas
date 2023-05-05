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

void altera_estado(Mapa *m, char *codigo, int estado) {  /* ADICIONADO POR ESTHER - O */

    Cidade *city = procura_cidade(m, codigo);
    
    if (city == NULL)
    {
        ERROR_NO_CITY(codigo);
        return;  
    }

    /* onde o estado é igual o estado para ocorrer a alteração */
    city->estado = estado;

    /* Para entrega do projeto, apagar este print*/
    printf("teste: O %s estado %d\n", city->nome, estado);
    
    
}

void devolve_info_cidade(Mapa *m, char *codigo) { /* ADICIONADO POR ESTHER, implementar mais..   - Y */
}

void adiciona_ligacao_cidade(Mapa *m, char *codigo, char *cod_destino){ /* ADICIONADO POR ESTHER //////  id_origem, id_destino = char codigo!!  - C  */

 
 Cidade *addliga_origem = procura_cidade(m, codigo); /*origem*/
 Cidade *addliga2_destino = procura_cidade(m, cod_destino); /*destino*/

    /*Verifica se origem e destino existe, se as duas n existir -> exibe o print erro para as duas*/
    if (addliga_origem == NULL && addliga2_destino == NULL)
    {
        ERROR_NO_CITY(codigo);
        ERROR_NO_CITY(cod_destino);
        return;
    }
    /*caso contrario, se for apenas origem -> exibe print apenas para origem */
     else if(addliga_origem == NULL)
    {
        ERROR_NO_CITY(codigo);
        return;  
    }
    /*caso contrario, se for apenas destino -> exibe print apenas para destino */
    else if (addliga2_destino == NULL)
    {
        ERROR_NO_CITY(cod_destino);
        return; 
    }

    /* Vai aparecer cidade duplicada, pois verificamos se os codigo da cidade origem = destino é igual*/
    if(addliga_origem == addliga2_destino){
        ERROR_CITY_REPEATED(codigo);
        return;
    }

    
    Lig *liga = search_link(addliga_origem, cod_destino);

   if (liga != NULL && strcmp(liga->destino, cod_destino) == 0){
        printf("Ligaçao repetida\n");
        return;
        }



/*  não são criadas duas ligações de
lisboa para o Porto do tipo 2 x LIS->POR, mas pode haver uma LIS->POR e
outra POR->LIS); */


}


void free_mapa(Mapa *m)/** RUBEN ADCIONADO **/ {
    /* Inicializa o ponteiro percorre_cidades com a primeira cidade do mapa */
    Cidade *percorre_cidades = m->firstC;

    /* Itera através de todas as cidades no mapa */
    while (percorre_cidades) {
        /* Inicializa o ponteiro percorre_links com a primeira ligação da cidade atual */
        Lig *percorre_links = percorre_cidades->first;

        /* Itera através de todas as ligações da cidade atual */
        while (percorre_links) {
            /* Armazena o ponteiro para a próxima ligação */
            Lig *prox_lig = percorre_links->nextL;

            /* Libera a memória alocada para a ligação atual */
            free(percorre_links);

            /* Atualiza o ponteiro percorre_links para a próxima ligação */
            percorre_links = prox_lig;
        }

        /* Armazena o ponteiro para a próxima cidade */
        Cidade *prox_cidade = percorre_cidades->nextC;

        /* Libera a memória alocada para a cidade atual */
        free(percorre_cidades);

        /* Atualiza o ponteiro percorre_cidades para a próxima cidade */
        percorre_cidades = prox_cidade;
    }

    /* Reinicializa o mapa */
    m->firstC = NULL;
    m->lastC = NULL;
    m->numCidades = 0;
}

void free_link(Mapa *m, char *codigo_origem, char *codigo_last) /** RUBEN ADCIONADO **/
{

    /* Procura a cidade de origem no mapa */
    Cidade *first = procura_cidade(m, codigo_origem);

    /* Se a cidade de origem não for encontrada, exibe um erro e retorna */
    if (first == NULL) {
        ERROR_NO_CITY(codigo_origem);
        return;
    }

    /* Procura a ligação na cidade de origem */
    Lig *last = search_link(first, codigo_last);

    /* Se a ligação não for encontrada, exibe um erro e retorna */
    if (last == NULL) {
        ERROR_NO_LINK(codigo_origem,codigo_last);
        return;
    }

    /* Se a lista de ligações estiver vazia, não faz nada */
    if (first->first == NULL) {
        return;
    }

    /* Diminui o contador de ligações da cidade de origem */
    first->numLigacoes--;

    /* Se last for a primeira ligação da lista, atualiza a primeira ligação */
    if (last->prevL == NULL) {
        first->first = last->nextL;

        /* Atualiza o ponteiro prevL da próxima ligação, se houver */
        if (last->nextL) {
            last->nextL->prevL = NULL;
        }

        /* Libera a memória da ligação last */
        free(last);
        return;
    }

    /* Se last for a última ligação da lista, atualiza a última ligação */
    if (last->nextL == NULL) {
        first->last = last->prevL;
        last->prevL->nextL = NULL;

        /* Libera a memória da ligação last */
        free(last);
        return;
    }

    /* Remove a ligação last da lista, atualizando os ponteiros */
    last->prevL->nextL = last->nextL;
    last->nextL->prevL = last->prevL;

    /* Libera a memória da ligação last */
    free(last);
}

void total_citys(Mapa *m)/** RUBEN ADCIONADO **/

{
    if (m->numCidades==0)
    {
        ERROR_DB_EMPTY;
        return;
    }
    printf("%d",m->numCidades);
    
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

void alterar_in_turistico()/* ADICIONADO POR ELISEU */{}
void alterar_in_economico()/* ADICIONADO POR ELISEU */{}
void alterar_in_temporal()/* ADICIONADO POR ELISEU */{}
void apagar_cidade()/* ADICIONADO POR ELISEU */{}
void guardar_file()/* ADICIONADO POR ELISEU */{}