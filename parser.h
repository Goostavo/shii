//Parser do shiii
#ifndef _PARSER_H_
#define _PARSER_H_

//Funcao para transformar a string de entrada em uma matriz de valores legiveis
//Retorna 0 caso ok, e -1 em caso de erro.
int parser(char* entrada, char com_matrix[10][64][1024], int* n_command, int* pipe, int* bkgnd);

//Funcao para limpar a matriz de comandos
void limpa_vetores(char com_matrix[10][64][1024], int bkgnd[10]);
#endif

