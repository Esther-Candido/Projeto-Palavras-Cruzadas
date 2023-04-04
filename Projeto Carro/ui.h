#ifndef UI_H
#define UI_H

#define MAX_LINE 1000

/**
 * Faz o display da prompt e recebe o inteiro inserido pelo user
 * @param prompt String a escrever no ecrã
 * @return int inserido pelo user
*/
int get_int(char *prompt);

/**
 * Faz o display da prompt e recebe um double inserido pelo user
 * @param prompt String a escrever no ecrã
 * @return double inserido pelo user
*/
double get_double(char *prompt);

/**
 * @param str Onde se garava a string inserida pelo use
 * @return número de caracteres lidos
*/
int get_string(char *prompt,char *str, int dim);


#endif