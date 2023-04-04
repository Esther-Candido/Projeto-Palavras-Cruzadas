#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "carros.h"
#include "ui.h"

void gerir_carros(Garagem *g)
{
    char marca[TEXT_LEN];
    char modelo[TEXT_LEN];
    int ano,id ;
    char matricula[TEXT_LEN];
    double valor;
    int opt = 0;
    do
    {
        opt = display_gestao_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            get_string("Insira a matricula",matricula,TEXT_LEN);
            get_string("Insira a marca",marca,TEXT_LEN);
            get_string("Insira o modelo",modelo,TEXT_LEN);
            ano=get_int("Insira o ano da viatura");
            valor=get_double("Insira o valor");
            inserir_carro(g,matricula,marca,modelo,ano,valor);
            break;
        case 2:
            system("clear");
            id = get_int("Insira ID do Carro");
            apagar_carro(g,id);
            break;
        case 3:
            system("clear");
            id = get_int("Insira ID do Carro");
            get_string("Insira novo modelo",modelo,TEXT_LEN);
            editar_modelo(g,id,modelo);
            break;
        }

    } while (opt != 9);
    system("clear");
}

void pesquisas(Garagem *g)
{
    int opt = 0;
    int ano,id;
    char marca[TEXT_LEN];
    do
    {
        opt = display_pesquisas_menu();
        switch (opt)
        {
        case 1:
            system("clear");
            get_string("Insira marca",marca,TEXT_LEN);
            pesquisar_marca(g, marca);
            break;
        case 2:
            system("clear");
            id = get_int("Insira ID do Carro");
            ficha_carro(g,id);

            break;
        case 3:
            system("clear");
            ano = get_int("Insira ano do carro");
            pesquisar_ano(g,ano);
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
    free_garagem(g);
    puts("Obrigado! A sair...");
    return EXIT_SUCCESS;
}