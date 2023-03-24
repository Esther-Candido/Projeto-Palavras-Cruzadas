#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

void gerir_carros()
{
    int opt = 0;
    do
    {
        opt = display_gestao_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            puts("Inserir Carro");
            break;
        case 2:
            system("clear");
            puts("ApagarCarro");
            break;
        case 3:
            system("clear");
            puts("Editar Carro");
            break;
        }

    } while (opt != 9);
    system("clear");
}

void pesquisas()
{
    int opt = 0;
    do
    {
        opt = display_pesquisas_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            puts("Pesquisar Marca");
            break;
        case 2:
            system("clear");
            puts("Pesquisar Dono");
            break;
        case 3:
            system("clear");
            puts("Pesquisar Ano");
            break;
        }

    } while (opt != 9);
    system("clear");
}

int main(int argc, char const *argv[])
{
    system("clear");
    print_banner();
    int opt = 0;
    do
    {
        opt = display_main_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            puts("Info");
            break;
        case 2:
            system("clear");
            gerir_carros();
            break;
        case 3:
            system("clear");
            pesquisas();
            break;
        }
    } while (opt != 9);
    puts("Obrigado! A sair...");
    return EXIT_SUCCESS;
}