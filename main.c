//Shiii - Shell interativa ínfima para iniciantes
//Autores: Gustavo Garcia e Vinícius Lana

#include <stdio.h>
#include <unistd.h>
#include "parser.h"
#include "comandos.h"

void inicializa(char* diretorio);

int main(void)
{
    char diretorio[1024];
    inicializa(diretorio);
    //parse();
    //proccess();

    return 0;
}

//Função que inicializa o sistema.
void inicializa(char* diretorio)
{
    printf("\nBem vindo a Shii - Shell Interativa Infima para iniciantes!\n");
    getcwd(diretorio,1024);
}
