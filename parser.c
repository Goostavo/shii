#include "parser.h"
#include <stdio.h>
#include <string.h>

int parser(char* entrada,                      //String digitada pelo usuário
           char com_matrix[10][64][1024],      //Matriz que guarda os comandos de forma legivel
           int* n_command,                     //numero de comandos
           int* pipe,                          //Localizacao do pipe
           int* bkgnd)                         //Flag de execucao em background
{
    int argumento = 0;                         //Indice da coluna da com_matrix
    int indice = 0;                            //Indice do caractere da string de entrada
    char temporario[1024];                     //string temporaria para n_commands e argumentos
    int indice_temp = 0;                       //Indice do caractere do vetor temporario

    //Limpa variáveis
    limpa_vetores(com_matrix,bkgnd);
    *n_command = 0;
    *pipe = 0;
    //Ignora espacos iniciais
    while(entrada[indice] == ' ')
    {
        indice++;
    }
    //corta espaços inúteis
    //STUB

    //Realiza leitura até o final da string
    while (entrada[indice] != '\0')
    {
        //caractere é diferente de espaço, pipe, ou '&' coloca letra no temporario
        if (entrada[indice] != ' ' && entrada[indice] != '&' && entrada[indice] != '|')
        {
            temporario[indice_temp] = entrada[indice];
            indice_temp++;
        }
        //Se for um caractere especial coloca na posicao da matriz
        else
        {
            temporario[indice_temp + 1] = '\0';         //Marca o fim da string
            strcpy(com_matrix[*n_command][argumento],temporario);
            //Se for espaço próxima palavra é um argumento
            if (entrada[indice] == ' ')
            {
                argumento++;
                indice_temp = 0;
            }
            if (entrada[indice] == '&')
            {
                bkgnd[*n_command] = 1;         //Seta flag como processar em background
                *n_command = *n_command + 1;
                argumento = 0;
                indice_temp = 0;
            }
            if (entrada[indice] == '|')
            {
                *pipe = *n_command+1;           //Seta flag que existe um pipe entre n_command e n_command+1
                *n_command = *n_command + 1;
                argumento = 0;
                indice_temp = 0;
            }
        }
        //Incremente o indice de leitura
        indice++;
    }
    for (*n_command = 0; *n_command<10; *n_command +=1)
    {
        for (argumento =0; argumento<= 10; argumento++)
        {
            printf("%s\t",com_matrix[*n_command][argumento]);
        }
        printf("\n");
    }printf("\n");
    //testa para erros
    //se erro
        return -1;
    //senao
        return 0;
}

void limpa_vetores(char com_matrix[10][64][1024], int bkgnd[10])
{
    int i=0, j=0;
    for (i=0;i<10;i++)
    {
        for (j=0;j<64;j++)
        {
            com_matrix[i][j][0] = '\0';
        }
        bkgnd[i] = 0;
    }
}
