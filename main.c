#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "carros.h"
#include "ui.h"

void gerir_carros(Garagem *g)
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
            puts("Editar modelo");
            break;
        }

    } while (opt != 9);
    system("clear");
}

void pesquisas(Garagem *g)
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
            puts("Ficha de Carro");
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
    Garagem *g=newGaragem(20, "Garagem do Vitor");

    int opt = 0;
    do
    {
        opt = display_main_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            print_info_garagem(g);
            break;
        case 2:
            system("clear");
            gerir_carros(g);
            break;
        case 3:
            system("clear");
            pesquisas(g);
            break;
        }
    } while (opt != 9);
    puts("Obrigado! A sair...");
    return EXIT_SUCCESS;
}