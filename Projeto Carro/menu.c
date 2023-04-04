/**
 * @file menu.c
 * @author Vitor
 * @brief biblioteca de menus
 * @date 2023-03-24
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "ui.h"

void print_banner()
{
    puts("  ______     ___       ______        ______         ______         _______.");
    puts(" /      |   /   \\     |   _  \\     |   _  \\      /  __  \\      /       |");
    puts("|  ,----'  /  ^  \\    |  |_)  |    |  |_)  |    |  |  |  |    |   (----`");
    puts("|  |      /  /_\\  \\   |      /     |      /     |  |  |  |     \\   \\    ");
    puts("|  `----./  _____  \\  |  |\\  \\----.|  |\\  \\----.|  `--'  | .----)   | ");
    puts(" \\______/__/     \\__\\ | _| `._____|| _| `._____| \\______/  |_______/    ");
}

int display_main_menu()
{
    int opt = 0; // Opção selecionada pelo user
    puts("");
    puts("##########  MENU PRINCIPAL ##########");
    puts("1 - Mostrar Info Oficina");
    puts("2 - Menu de Gestão Carros");
    puts("3 - Menu de Pesquisa");
    puts("---------");
    puts("9 - Sair");
    puts("------------------------------------");
    do
    {
        opt = get_int("Insira a sua opção");
    } while (opt < 1 || (opt > 3 && opt != 9));

    return opt;
}

int display_gestao_menu()
{
    int opt = 0; // Opção selecionada pelo user
    puts("");
    puts("##########  MENU CARROS ##########");
    puts("1 - Inserir Carro");
    puts("2 - Apagar Carro");
    puts("3 - Editar Modelo Carro");
    puts("---------");
    puts("9 - Voltar ao menu principal");
    puts("----------------------------------");
    do
    {
        opt = get_int("Insira a sua opção");
    } while (opt < 1 || (opt > 3 && opt != 9));

    return opt;
}

int display_pesquisas_menu()
{
    int opt = 0; // Opção selecionada pelo user
    puts("");
    puts("##########  MENU PESQUISA ##########");
    puts("1 - Pesquisar Marca");
    puts("2 - Pesquisar Dono");
    puts("3 - Pesquisar Ano do Carro");
    puts("---------");
    puts("9 - Voltar ao menu principal");
    puts("-----------------------------------");
    do
    {
        opt = get_int("Insira a sua opção");
    } while (opt < 1 || (opt > 3 && opt != 9));

    return opt;
}
