#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"

/* Pela Análise da API*/
#define MAX_LINE 56


/* atributos da linha de comandos*/
char *attr1, *attr2, *attrnome, *attrindice;
char *comando; /*recebe uma linha do stdin*/
/*ficheiro de dados*/
char *fileName;
Mapa *m;

void executeCommand(char *line)
{
    
    switch (line[0])
    {
    case 'A': /*Adiciona Cidade*/

        sscanf(line,"A %s %[^\n]", attr1,attrnome);
        add_city(m,attr1,attrnome);
        
        break;
    case 'O': /*Altera estado da cidade*/
        
        break;
    case 'Y': /*Informação sobre a cidade*/
        
        break;
    case 'Z': /*Lista Todas as Cidades*/
             
        print_citys(m);
        
        break;
    case 'N': /*Lista Todas as Cidades*/
        
        break;
    case 'C': /*Cria ligação entre cidades*/
       
        break;
    case 'I': /*apaga ligação entre cidades*/
        
        break;
    case 'T': /*Altera indice turistico*/
        
        break;
    case 'E': /*altera indice económico*/
        
        break;
    case 'H': /*Altera indice temporal*/
        
        break;
    case 'P': /*Apaga Cidade*/
        
        break;
    case 'R': /*Melhor Rota entre duas cidades*/
        
        break;
    case 'G': /*Guarda a base de dados*/
        
        break;
    case 'X': /*sai da aplicação*/
        /* não esquecer libertar a memória*/

        exit(EXIT_SUCCESS);
        break;
    case '#': /*Comentário não executar*/
        break;
    default:
        break;
    }
}

void importDataFile() /*Abre o ficheiro e executa as linhas para carregar o programa*/
{
    FILE *f;
    f = fopen(fileName, "r");
    /*caso ficheiro não exista*/
    if (!f)
        return;

    while (fgets(comando, MAX_LINE, f))
    {
        executeCommand(comando);
        memset(comando, '\0', MAX_LINE * sizeof(char) + 1);
    }
    fclose(f);
}

int main(int argv, char *argc[])
{
    char *extension;

    /*FIX ME - Inicia SGO*/
    m = new_mapa();
    /*##### NÃO ALTERAR DAQUI PARA BAIXO #####*/
    /*Aloca memória para receber atributos*/
    comando = malloc(MAX_LINE * sizeof(char) + 1); /*recebe uma linha do stdin*/
    attr1 = malloc(CITY_ID * sizeof(char) + 1);
    attr2 = malloc(CITY_ID * sizeof(char) + 1); /*tb utilizado para ler o estado*/
    attrnome = malloc(MAX_CITY_NAME * sizeof(char) + 1);
    attrindice = malloc(MAX_INDICE_LENGHT * sizeof(char) + 1);
    fileName = malloc(MAX_FILE_NAME + 1);

    /*Caso tenha sido passado ficheiro pela linha de comando carrega*/
    if (argv == 2)
    {
        strncpy(fileName, argc[1], MAX_FILE_NAME);
        if (strlen(fileName) < 4)
        {
            ERROR_FILE_EXTENSION(fileName);
            memset(fileName, '\0', MAX_FILE_NAME);
            strncpy(fileName, "data.sgo", MAX_FILE_NAME);
        }
        else
        {
            extension = &fileName[strlen(fileName) - 4];
            if (strcmp(extension, ".sgo"))
            {
                ERROR_FILE_EXTENSION(fileName);
                memset(fileName, '\0', MAX_FILE_NAME);
                strncpy(fileName, "data.sgo", MAX_FILE_NAME);
            }
            else
            {
                importDataFile(); 
            }
        }
    }
    else
        strncpy(fileName, "data.sgo", MAX_FILE_NAME);

    while (fgets(comando, MAX_LINE, stdin))
    {
        executeCommand(comando);
        memset(comando, '\0', MAX_LINE * sizeof(char) + 1);
    }
    return EXIT_SUCCESS;
}
