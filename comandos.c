#include "comandos.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
    int ret; int aux;
    ret=chdir(diretorio);
    //Em caso de erro, mostra uma mensagem.
    if(ret==-1)
        printf("Diretório não localizado\n");
    else
    {
        //Se tiver / como inicio a localizao é substituida
        if (diretorio[0]== '/')
            strcpy(cwd,diretorio);
        else //Senao é adicionada/substituida
        {
            if (!strcmp(diretorio,".."))
            {
                //Remove o ultimo diretorio da string
                aux = strlen(cwd)-1;
                while (cwd[aux] != '/')
                {
                    aux--;
                }
                if (aux == 0)                   //Está ou foi para o diretório raiz
                {
                    strcpy(cwd,"/");
                }
                else
                {
                    strncpy(diretorio,cwd,aux);
                    strcpy(cwd,diretorio);
                    cwd[aux]='\0';                  //Adiciona fim de string
                }
            }
            else
            {
                strcat(cwd,"/");
                strcat(cwd,diretorio);
            }
        }
    }
}

void executa_aplicativo(char com_matrix[10][64][1024],       //Matriz que guarda os comandos de forma legivel
                       int conta_comando,                   //Localização do comando na matriz de comandos
                       int* bkgnd,                          //Flag de execucao em background
                       int* pipe_flag)
{
    int fd[2];      //Parametro usado pelo pipe()
    pid_t pid;
    int erro;       //Flag de erro
    char *argv[64];
    int aux = 0;

    //Aloca memória para argv
    for (aux=0; aux<64; aux++)
    {
       argv[aux] = malloc (1024 * sizeof (char));
    }

    aux = 0;
    while(com_matrix[conta_comando][aux][0] != '\0')
    {
            strcpy(argv[aux],com_matrix[conta_comando][aux]);
            aux++;
    }
    *(argv+aux) = (char*)NULL;            //Adiciona NULL no fim.

    //Se há um pipe entre os processos
    if(*pipe_flag!=0)
    {
        pipe(fd);//Criação do pipe
        if(!fork())//Cria processo filho 1
        {
            close(fd[1]);
            dup2(fd[0], 0);//Configura o parametro fd[0] como entrada padrão.
            erro=execvp(argv[0],(char**)argv);
            if(erro==-1)//Se o aplicativo não existe
            {
                printf("Comando ou Aplicativo não existente\n");
            }//endif erro

        }
        else if(!fork())
        {
            close(fd[0]);//Cria o processo filho 2
            dup2(fd[1], 1);//Configura o parametro fd[1] como saida padrão.
            erro=execvp(argv[0],(char**)argv);
            if(erro==-1)//Se o aplicativo não existe
            {
                printf("Comando ou Aplicativo não existente\n");
            }//endif erro
        }
            else
            {
                close(fd[0]);
                close(fd[1]);
            }


    }//Este procedimento faz com que o primeiro processo leia através da entrada padrão a saida padrão do segundo processo.

    //Se não há um pipe.
    else
    {
        pid=fork();     //Cria processo filho
        if(pid==0)      //No processo filho, executa-se o aplicativo.
        {
            erro=execvp(argv[0],(char**)argv);
            //Caso aplicativo ou comando inexistente, retorna 1.
            if(erro==-1)
            {
                printf("Comando ou Aplicativo não existente\n");
            }//endif erro
        }//endif
        else            //No processo pai, se nao estiver em background espera termino
        {
            if (bkgnd[conta_comando] == 0)
                waitpid(pid,0,0);
        }
    }

    //Desaloca memória para argv
    for (aux=0; aux<64; aux++)
    {
       free(argv[aux]);
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
        else
        {
            executa_aplicativo(com_matrix,conta_comando,bkgnd,pipe);
        }
        conta_comando++;
    }//Fim while
    return 0;                       //retorna ok para continuar a shii
}





