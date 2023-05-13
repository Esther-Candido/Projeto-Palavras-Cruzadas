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

Lig *procura_ligacoes(Cidade *cidade, char *codigo_destino) /** ADICIONADO POR RUBEN */
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

Lig *percorre_ligacoes(Lig *cidade_atual) /** ADICIONADO POR RUBEN */
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
void adicionar_cidade(Mapa *m, char *codigo, char *nome) /** ADICIONADO POR RUBEN */
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
    memset(nova_cidade->codigo, '\0', CITY_ID + 1);
    strncpy(nova_cidade->codigo, codigo, CITY_ID);

    nova_cidade->nome = malloc((MAX_CITY_NAME + 1) * sizeof(char));
    memset(nova_cidade->nome, '\0', MAX_CITY_NAME + 1);
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

void altera_estado(Mapa *m, char *codigo, int estado) {  /* ADICIONADO POR ESTHER - O */

    /* Procura a cidade no mapa usando o código fornecido */
    Cidade *city = procura_cidade(m, codigo);

    /* Se a cidade não existe, exibe um erro e retorna */
    if (city == NULL)
    {
        ERROR_NO_CITY(codigo);
        return;
    }

    /* Atualiza o estado da cidade para o novo valor */
    city->estado = estado;

    /* Para entrega do projeto, apagar este print */
    printf("teste: O %s estado %d\n", city->nome, estado);
    
    
}

void devolve_info_cidade(Mapa *m, char *codigo, int estado) { /* ADICIONADO POR ESTHER, implementar mais..   - Y */

    /* Procura a cidade no mapa usando o código fornecido */
    Cidade *info = procura_cidade(m, codigo);

    /* Se a cidade não existe, exibe um erro e retorna */
    if (info == NULL)
    {
        ERROR_NO_CITY(codigo);
        return;
    }

    /* Exibe informações reduzidas sobre a cidade */
    if (estado == 0)
    {
        MSG_CITY_INFO_HEADER(info->codigo, info->estado, info->numLigacoes, info->nome);
        return;
    }

    /* Inicializa o ponteiro para percorrer as ligações da cidade */
    Lig *pesquisa = info->first;

    /* Exibe informações completas sobre a cidade e suas ligações */
    if (estado == 1)
    {
        MSG_CITY_INFO_HEADER(info->codigo, info->estado, info->numLigacoes, info->nome);
        while (pesquisa != NULL)
        {
            MSG_CITY_INFO_ITEM(pesquisa->destino, pesquisa->indiceTemporal, pesquisa->indiceEconomico, pesquisa->indiceTuristico);
            pesquisa = percorre_ligacoes(pesquisa);
        }
        return;
    }

}

void print_cidades(Mapa *m)/** ADICIONADO POR RUBEN */
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

void total_cidades(Mapa *m)/** ADICIONADO POR RUBEN */
{
    /* Caso o banco de dados esteja vazio */

    if (m->numCidades == 0)
    {
        ERROR_DB_EMPTY;
        return;
    }
    
    /* Imprime o número total de cidades no mapa */
    printf("%d", m->numCidades);
    
}

void adiciona_ligacao_cidade(Mapa *m, char *codigo_origem, char *cod_destino){ /* ADICIONADO POR ESTHER */

 Cidade *addliga_origem = procura_cidade(m, codigo_origem); /*origem*/
 Cidade *addliga2_destino = procura_cidade(m, cod_destino); /*destino*/

    /*Verifica se origem e destino existe, se as duas n existir -> exibe o print erro para as duas*/
    if (addliga_origem == NULL && addliga2_destino == NULL)
    {
        ERROR_NO_CITY(codigo_origem);
        ERROR_NO_CITY(cod_destino);
        return;
    }
    /*caso contrario, se for apenas origem -> exibe print apenas para origem */
     else if(addliga_origem == NULL)
    {
        ERROR_NO_CITY(codigo_origem);
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
        ERROR_CITY_REPEATED(codigo_origem);
        return;
    }

    /*Ponteiro para acessar as ligações*/
    Lig *liga = procura_ligacoes(addliga_origem, cod_destino);

        if (liga != NULL && strcmp(liga->destino, cod_destino) == 0){
                printf("Ligaçao repetida\n");
                return;
                }

    /*Criar estrutura para as ligações, alocar memoria*/
    Lig *nova_liga = malloc(sizeof(Lig));
    memset(nova_liga->destino, '\0', CITY_ID + 1);
    strncpy(nova_liga->destino, cod_destino, CITY_ID);

    nova_liga->indiceTemporal = 0;
    nova_liga->indiceEconomico = 0;
    nova_liga->indiceTuristico = 0;
    addliga_origem->numLigacoes++;

    /*Não existe Ligação? inserir ligação como unica na lista*/
    if (addliga_origem->first == NULL)
    {
        nova_liga->nextL = NULL; /* o nextL é igual vazio */
        nova_liga->prevL = NULL; /* o prevL é igual vazio */
        addliga_origem->first = nova_liga; /*id cidade origem da primeira é igual = NOVA_LIGA*/
        addliga_origem->last = nova_liga; /*id cidade origem da ultima é igual = NOVA_LIGA*/
        printf("teste: inseriu vazia lista\n");
        return;
    }

    /* Estrategia: Inserir as ligações no final da lista */
    addliga_origem->last->nextL = nova_liga;    /*ir no ponteiro da lig final e definir que a proxima ligação(nextL) sera a nova_liga. */
    nova_liga->prevL = addliga_origem->last; /*Voltar no ponteiro e definir que o nextL agora é o last*/
    nova_liga->nextL = NULL;  /*Deixar o nextL como NULL para dar abertura a receber novas ligações*/
    addliga_origem->last = nova_liga; /* a ligação LAST sera a nova_liga*/
    printf("inseriu lig na ultima\n");
    
}

void free_ligacao(Mapa *m, char *codigo_origem, char *codigo_last) /** RUBEN ADCIONADO **/
{

    /* Procura a cidade de origem no mapa */
    Cidade *first = procura_cidade(m, codigo_origem);

    /* Se a cidade de origem não for encontrada, exibe um erro e retorna */
    if (first == NULL) {
        ERROR_NO_CITY(codigo_origem);
        return;
    }

    /* Procura a ligação na cidade de origem */
    Lig *last = procura_ligacoes(first, codigo_last);

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

void alterar_in_turistico(Mapa *m, char *cidade_origem, char *cidade_destino, double indice)/* ADICIONADO POR ELISEU */
{
    
    Cidade *c1 = procura_cidade(m, cidade_origem);
    Cidade *c2 = procura_cidade(m, cidade_destino);

    if (c1 == NULL && c2 == NULL){
        ERROR_NO_CITY(cidade_origem);
        ERROR_NO_CITY(cidade_destino);
        return;
    }
    if (c1 == NULL){
        ERROR_NO_CITY(cidade_origem);
        return;
    }
    if (c2 == NULL){
        ERROR_NO_CITY(cidade_destino);
        return;
    }

    Lig *ligacao = c1->first;
    while (ligacao)
    {
        if (strcmp(ligacao->destino, c2->codigo) == 0){
            ligacao->indiceTuristico = indice;
            return;
        }
        ligacao = ligacao->nextL;
    }
    

    ERROR_NO_LINK(cidade_origem,cidade_destino);
    return;  
}

void alterar_in_economico(Mapa *m, char *cidade_origem, char *cidade_destino, double indice)/* ADICIONADO POR ELISEU */
{
    
    Cidade *c1 = procura_cidade(m, cidade_origem);
    Cidade *c2 = procura_cidade(m, cidade_destino);

    if (c1 == NULL && c2 == NULL){
        ERROR_NO_CITY(cidade_origem);
        ERROR_NO_CITY(cidade_destino);
        return;
    }
    if (c1 == NULL){
        ERROR_NO_CITY(cidade_origem);
        return;
    }
    if (c2 == NULL){
        ERROR_NO_CITY(cidade_destino);
        return;
    }

    Lig *ligacao = c1->first;
    while (ligacao)
    {
        if (strcmp(ligacao->destino, c2->codigo) == 0){
            ligacao->indiceEconomico = indice;
            return;
        }
        ligacao = ligacao->nextL;
    }
    

    ERROR_NO_LINK(cidade_origem,cidade_destino);
    return;
}

void alterar_in_temporal(Mapa *m, char *cidade_origem, char *cidade_destino, double indice)/* ADICIONADO POR ELISEU */
{
        Cidade *c1 = procura_cidade(m, cidade_origem);
    Cidade *c2 = procura_cidade(m, cidade_destino);

    if (c1 == NULL && c2 == NULL){
        ERROR_NO_CITY(cidade_origem);
        ERROR_NO_CITY(cidade_destino);
        return;
    }
    if (c1 == NULL){
        ERROR_NO_CITY(cidade_origem);
        return;
    }
    if (c2 == NULL){
        ERROR_NO_CITY(cidade_destino);
        return;
    }

    Lig *ligacao = c1->first;
    while (ligacao)
    {
        if (strcmp(ligacao->destino, c2->codigo) == 0){
            ligacao->indiceTemporal = indice;
            return;
        }
        ligacao = ligacao->nextL;
    }
    

    ERROR_NO_LINK(cidade_origem,cidade_destino);
    return;
}

void remover_cidade(Mapa *m, char *cidade)/* ADICIONADO POR ELISEU */
{
    Cidade *c = procura_cidade(m, cidade);
    if (c == NULL)
    {
        ERROR_NO_CITY(cidade);
        return;
    }
    

    /* Remove todas as ligações para a cidade a ser removida */
    Cidade *aux = m->firstC;
    
    while (aux)
    {
        Lig *ligacao = procura_ligacoes(aux,cidade);

        /* Se a ligação aponta para a cidade a ser excluída */
        if (ligacao) {
            /* Se for a primeira ligação */
            if (ligacao == aux->first && ligacao == aux->last){
                aux->first = NULL;
                aux->last = NULL;

            }
            else{
                if (ligacao == aux->first) {
                aux->first = ligacao->nextL;
                ligacao->nextL->prevL = NULL;
                } 
                
                /* Se for a última ligação */
                if (ligacao == aux->last) {
                    aux->last = ligacao->prevL;
                    ligacao->prevL->nextL = NULL;
                }
                
                /* Caso geral - Ligação no meio da lista */
                if (ligacao->prevL && ligacao->nextL) {
                    ligacao->prevL->nextL = ligacao->nextL;
                    ligacao->nextL->prevL = ligacao->prevL;
                }
                free(ligacao);
            }
            aux->numLigacoes--;
        }
        aux = aux->nextC;
    }

    Lig *ligacao = c->first;
    while (ligacao)
    {
        Lig *remover_lig = ligacao;
        ligacao = ligacao->nextL;

        free(remover_lig);
    }
    c->first = NULL;
    c->last = NULL;

    


    /* Se cheguei aqui existe e vou apagar a cidade */
    m->numCidades--;

    /* Case seja a única cidade */ 
    if (c->nextC == NULL && c->prevC == NULL)
    {
        free(c);
        m->firstC = NULL;
        m->lastC = NULL;
        return;
    }

    /* Caso seja a primeira */ 
    if (c == m->firstC)
    {
        c->nextC->prevC = NULL;
        m->firstC = c->nextC;
        free(c);
        return;
    }

    /*  Caso seja a última */
    if (c == m->lastC)
    {
        c->prevC->nextC=NULL;
        m->lastC=c->prevC;
        free(c);
        return;
    }
    
    /* se cheguei aqui */ 
    /* Caso Geral - Apagar no meio */ 
    c->prevC->nextC = c->nextC;
    c->nextC->prevC = c->prevC;
    free(c);
    return;
}

void guardar_file()/* ADICIONADO POR ELISEU */{}

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











