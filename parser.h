//Parser do shiii
#ifndef _PARSER_H_
#define _PARSER_H_

//Função que prepara a string de entrada previamente para evitar problemas durante
//as análises.
void prepara_string(char* entrada);

//Funcao para transformar a string de entrada em uma matriz de valores legiveis
//Retorna 0 caso ok, e -1 em caso de erro.
int parser(char* entrada, char com_matrix[10][64][1024], int* n_command, int* pipe, int* bkgnd);

//Funcao para limpar a matriz de comandos
void limpa_vetores(char com_matrix[10][64][1024], int bkgnd[10]);
#endif

