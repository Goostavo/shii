//Comandos do shell
#ifndef _COMANDOS_H_
#define _COMANDOS_H_
//Esta função exibi o diretório corrente da shell
//Parametros de entrada : sem parametros
//Valor de retorno : Não retorna valor
void command_pwd(void);

//Esta função faz com que a shell espere o término de todos os processos em execução
//Assim que os processos vão sendo finalizados, são exibidos os pid's dos mesmos.
//Parametros de entrada : sem parametros
//Valor de retorno : Não retorna valor
void command_wait(void);

//Esta função muda o diretório corrente da shell
//Parametros de entrada : Caminho do Diretório e diretorio corrente (cwd)
//Valor de retorno : Caso o diretório seja inexistente, exibe mensagem ao usuário.
void command_cd(char *diretorio, char *cwd);

//Função para verificar os vetores de funções e processar as mesmas
//retorna a flag para finalizacao do shiii
int process(char com_matrix[10][64][1024], int* n_command, int* pipe, int* bkgnd, char* diretorio);

//Função para execução de aplicativo
//Valor de retorno:Caso aplicativo não exista, retorna 1.Se não, retorna 0.
void executa_aplicativo(char com_matrix[10][64][1024],int conta_comando,int* bkgnd, int* pipe_flag);

#endif
