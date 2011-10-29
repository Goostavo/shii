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
//Parametros de entrada : Caminho do Diretório
//Valor de retorno : Não retorna valor
void command_cd(char *diretorio);

#endif
