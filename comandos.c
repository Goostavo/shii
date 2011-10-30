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

//diretorio -> Diretorio alvo
//cwd -> Diretório corrente
void command_cd(char *diretorio, char *cwd)
{
    int ret;
    ret=chdir(diretorio);
    //Em caso de erro, mostra uma mensagem.
    if(ret==-1)
        printf("Diretório não localizado\n");
    else
    {
        //Se tiver / como inicio a localizao é substituida
        if (diretorio[0]== '/')
            strcpy(cwd,diretorio);
        else //Senao é adicionada
        {
            strcat(cwd,"/");
            strcat(cwd,diretorio);
        }
    }
}

//Le a primeira coluna de dados, e processa o comando correspondente
//retorna a flag para finalizacao do shiii
int process(char com_matrix[10][64][1024],       //Matriz que guarda os comandos de forma legivel
             int* n_command,                     //numero de comandos
             int* pipe,                          //Localizacao do pipe
             int* bkgnd,                         //Flag de execucao em background
             char* diretorio)                    //Diretorio corrente
{
    int conta_comando = 0;
    while (conta_comando <= *n_command)
    {
        //Comando do bash CD
        if (!strcmp(com_matrix[conta_comando][0],"cd"))
        {
            command_cd(com_matrix[conta_comando][1],diretorio);
        }
        else if (!strcmp(com_matrix[conta_comando][0],"pwd"))
        {
            command_pwd();
        }
        else if (!strcmp(com_matrix[conta_comando][0],"wait"))
        {
            command_wait();
        }
        else if (!strcmp(com_matrix[conta_comando][0],"exit"))
        {
            printf("Adeus!\n");
            return 1;               //Finaliza o processamento prematuramente
        }
        conta_comando++;
    }//Fim while
    return 0;                       //retorna ok para continuar a shii
}


