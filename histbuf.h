//Buffer circular para guardar o histórico
#ifndef _HISTBUF_H_
#define _HISTBUF_H_

//Funcoes para o buffer circular de historico
void main_histbuf(int funcao,                       //Funcao a ser processada
                  char comandos[10][64][1024],      //String a ser concatenada
                  int *n_command,                   //numero de comandos
                  char entrada[1024],               //String de entrada crua
                  int* pipe,                        //Localizacao do pipe
                  int* bkgnd,                       //Flag de execucao em background
                  char* diretorio);                  //Diretorio corrente

//Adiciona ao historico
void hist_add(char comandos[10][64][1024], int *n_command, char entrada[1024],int* pipe,int* bkgnd);

//Mostra historico
void hist_show(void);

//Roda uma entrada do Historico
void hist_recall(int numero, char* diretorio);


#endif


