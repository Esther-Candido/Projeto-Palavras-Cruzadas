/**
 * @file menu.h
 * @author Vitor
 * @brief biblioteca de menus
 * @date 2023-03-24
 *
 */


#ifndef MENU_H
#define MENU_H

/**
 * Escreve o banner
*/
void print_banner();

/**
 * Escreve menu no ecrã e devolve a opção escolhida pelo user
 * @return int opção escolhida
*/
int display_main_menu();

/**
 * Escreve menu no ecrã e devolve a opção escolhida pelo user
 * @return int opção escolhida
*/
int display_gestao_menu();

/**
 * Escreve menu no ecrã e devolve a opção escolhida pelo user
 * @return int opção escolhida
*/
int display_pesquisas_menu();


#endif