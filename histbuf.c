#include "histbuf.h"
#include <stdio.h>
#include <string.h>
#include "comandos.h"

//Funcoes para o buffer circular de historico
void main_histbuf(int funcao,                       //Funcao a ser processada
                  char comandos[10][64][1024],      //String a ser concatenada
                  int *n_command,                   //numero de comandos
                  char entrada[1024],               //String de entrada crua
                  int* pipe,                        //Localizacao do pipe
                  int* bkgnd,                       //Flag de execucao em background
                  char* diretorio)                  //Diretorio corrente

{
    static int ultimo = 0;
    static char historico[10][10][64][1024];
    static char hist_string[10][1024] = {"","","","","","","","","",""};
    static int hist_ncommand[10] = {0,0,0,0,0,0,0,0,0,0};
    static int hist_pipe[10]= {0,0,0,0,0,0,0,0,0,0};
    static int hist_bkgnd[10][10];
    int aux1,aux2;

    //funcao 1 - add
    if (funcao == 1)
    {
        for (aux1 = 0; aux1<10; aux1++)
        {
            for(aux2 = 0; aux2<64; aux2++)
            {
                strcpy(historico[ultimo][aux1][aux2],comandos[aux1][aux2]);
            }
            hist_bkgnd[ultimo][aux1] = bkgnd[aux1];
        }
        //Adiciona outros parametros
        hist_ncommand[ultimo] = *n_command;
        hist_pipe[ultimo] = *pipe;
        //ADiciona string crua
        strcpy(hist_string[ultimo],entrada);
        //Aumenta posicao do ultimo elemento
        ultimo = (ultimo + 1)%10;
    }

    //Funcao 2 - show
    if (funcao == 2)
    {
        for (aux1=0; aux1<10; aux1++)
        {
            aux2 = ((ultimo+aux1)%10);
            printf( "%d  %s\n",aux1,hist_string[aux2]);
        }
    }

    //Funcao 3 - Recall
    if (funcao >= 10)
    {
        funcao = funcao - 10;
        if (funcao > 9)
        {
            printf("Erro: Evento desconhecido!\n");
        }
        else
        {
            //Processa pedido
        }
    }

    if (funcao==999)
    {
        hist_ncommand[1]++;
        hist_bkgnd[1][1]++;
        hist_pipe[1]++;
    }

}

//Frontend das funcoes de historico
//Adiciona string ao vetor de historico
void hist_add(char comandos[10][64][1024],      //String a ser concatenada
              int *n_command,                   //numero de comandos
              char entrada[1024],               //String de entrada crua
              int* pipe,                        //Localizacao do pipe
              int* bkgnd)                       //Flag de execucao em background

{
    main_histbuf(1, comandos, n_command, entrada,pipe,bkgnd,0);
}

//Adiciona string ao vetor de historico
void hist_show(void)
{
    main_histbuf(2, 0, 0, 0, 0, 0, 0);
}
