#include "comandos.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void command_pwd(void)
{
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
}

void command_wait(void)
{
    pid_t pid;
    pid = waitpid(-1,0,0);
    while (pid != -1)
    {
        printf("Process %d Ended\n",pid);
        pid = waitpid(-1,0,0);
    }
}

void command_cd(char *diretorio)
{
    int ret;
    ret=chdir(diretorio);
    if(ret==-1)printf("Diretório não localizado");
}

//Le a primeira coluna de dados, e processa o comando correspondente
void process(char com_matrix[10][64][1024],      //Matriz que guarda os comandos de forma legivel
             int* n_command,                     //numero de comandos
             int* pipe,                          //Localizacao do pipe
             int* bkgnd)                         //Flag de execucao em background)
{
    int conta_comando = 0;
    while (conta_comando <= *n_command)
    {
        //Comando do bash CD
        if (!strcmp(com_matrix[conta_comando][0],"cd"))
        {
            printf("Funcao cd aqui!\n");
        }
        else if (!strcmp(com_matrix[conta_comando][0],"pwd"))
        {
            printf("Funcao pwd aqui!\n");
        }
        else if (!strcmp(com_matrix[conta_comando][0],"wait"))
        {
            printf("Funcao wait aqui!\n");
        }
        else if (!strcmp(com_matrix[conta_comando][0],"exit"))
        {
            printf("Funcao exit aqui!\n");
        }
        conta_comando++;
    }//Fim while
}
