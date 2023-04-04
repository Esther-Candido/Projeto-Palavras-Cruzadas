#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"

int get_int(char *prompt)
{
    printf("%s->", prompt);
    char line[MAX_LINE];
    memset(line, '\0', MAX_LINE);
    fgets(line, MAX_LINE - 1, stdin);
    int n = atoi(line);
    return n;
}

double get_double(char *prompt)
{
    printf("%s->", prompt);
    char line[MAX_LINE];
    memset(line, '\0', MAX_LINE);
    fgets(line, MAX_LINE - 1, stdin);
    double valor;
    sscanf(line, "%lf", &valor);
    return valor;
}

int get_string(char *prompt, char *str, int dim)
{
    //apresenta a mensagem ao user
    printf("%s->", prompt);
    //Cria e faz reset um array (String) para guardar o input do user
    char line[MAX_LINE];
    memset(line, '\0', MAX_LINE);
    //Lê do stdin o que o utilizador escrever e até carregar em enter (\n)
    fgets(line, MAX_LINE - 1, stdin);
    //Como o \n ficou gravado em line, retira-se o último caracter [a,b,c,\n, \0,...] => [a,b,c,\0,\0,....]
    //[a,b,c,d,\0] => line[1]=\0 => [a,\0,c,d,\0] = puts(line) => a
    line[strlen(line)-1]='\0';
    //Limpar o array de destino que foi passado à função
    memset(str,'\0',dim);
    //Vou copiar até um maximo de dim caracteres para o array recebido (destino)
    strncpy(str,line,dim);
    //retorna o número de caracteres lidos
    return strlen(str);
}