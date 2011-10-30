//Shiii - Shell interativa ínfima para iniciantes
//Autores: Gustavo Garcia e Vinícius Lana

#include <stdio.h>
#include <unistd.h>
#include "histbuf.h"
#include "parser.h"
#include "comandos.h"

//Funções básicas do sistema
void inicializa(char* diretorio);
void le_entrada(char* entrada, char* diretorio);

int main(void)
{
    int condicao_saida = 0;
    char diretorio[1024];           //Diretorio corrente
    char entrada[1024];             //Entrada feito pelo usuário
    char com_matrix[10][64][1024];  //Matriz de comandos depois de processada
    int n_command=0;                  //Numero de comandos da matriz
    int pipe;                       //Flag de pipe
    int bkgnd[10];                  //Matriz de flags de bkgnd

    inicializa(diretorio);
    //Loop para realizar interações
    while (condicao_saida == 0)
    {
        le_entrada(entrada,diretorio);
        parser(entrada, com_matrix, &n_command, &pipe, bkgnd);

        //proccess();
    }

    return 0;
}

//Inicializa variáveis e imprime mensagem inicial
void inicializa(char* diretorio)
{
    printf("\nBem vindo a Shii - Shell Interativa Infima para iniciantes!\n");
    getcwd(diretorio,1024);
}

//Mostra cabeçalho e le entrada de usuário
//entrada -> valor digitado pelo usuário
//diretorio -> diretorio corrente
void le_entrada(char* entrada, char* diretorio)
{
    printf("Shiii:%s$ ",diretorio);
    gets(entrada);
}
