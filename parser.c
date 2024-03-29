#include "parser.h"
#include <stdio.h>
#include <string.h>
#include "histbuf.h"

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
    //Prepara string para o processamento
    prepara_string(entrada);

    //Realiza leitura até o final da string
    while (entrada[indice] != '\0')
    {
        //Caso seja o caractere nulo especial, ignora o caractere;
        if (entrada[indice] != (char)0xFF)
        {
            //caractere é diferente de espaço, pipe, ou '&' coloca letra no temporario
            if (entrada[indice] != ' ' && entrada[indice] != '&' && entrada[indice] != '|')
            {
                //Trata comando de histórico
                if (entrada[indice] == '!')
                {
                    if (indice_temp != 0 || argumento != 0) //Erro
                    {
                        printf("Erro de sintaxe!\n");
                        return -1;
                    }
                    else
                    {
                        //Analisa e concatena historico
                    }
                }
                //Trata espaços utilizados em parâmetros
                if (entrada[indice] == '\\' && entrada[indice+1] == ' ')
                {
                    indice++;
                    temporario[indice_temp] = ' ';
                    indice_temp++;
                }
                else
                {
                    temporario[indice_temp] = entrada[indice];
                    indice_temp++;
                }
            }
            //Se for um caractere especial coloca na posicao da matriz
            else
            {
                temporario[indice_temp] = '\0';         //Marca o fim da string
                strcpy(com_matrix[*n_command][argumento],temporario);
                indice_temp = 0;                        //Reseta vetor temporario
                //Se for espaço próxima palavra é um argumento
                if (entrada[indice] == ' ')
                {
                    argumento++;
                    if (argumento >= 64)    //Erro
                    {
                        printf("O shiii suporta apenas 64 argumentos por comando!\n");
                        return -1;
                    }
                }
                if (entrada[indice] == '&')
                {
                    bkgnd[*n_command] = 1;         //Seta flag como processar em background
                    *n_command = *n_command + 1;
                    argumento = 0;
                }
                if (entrada[indice] == '|')
                {
                    *pipe = *n_command+1;           //Seta flag que existe um pipe entre n_command e n_command+1
                    *n_command = *n_command + 1;
                    argumento = 0;
                }
            } //endif caractere especial
        }   //endif != 0xFF
        //Incrementa o indice de leitura
        indice++;
    }
    //Ultimo argumento
    if (indice_temp > 0)
    {
        temporario[indice_temp] = '\0';         //Marca o fim da string
        strcpy(com_matrix[*n_command][argumento],temporario);
    }
    //Testa por possíveis erros
    //Caso n_command e argumento estao vazios, faz somente uma quebra de linha
    if (*n_command == 0 && argumento == 0 && com_matrix[0][0][0] == '\0')
    {
        return -1;
    }
    //Comandos demais!
    if (*n_command >= 10)
    {
        printf("O shiii suporta apenas 10 comandos por vez!\n");
        return -1;
    }
    //senao
        hist_add(com_matrix,n_command,entrada,pipe,bkgnd);
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

//Transforma espaços desnecessário em um caractere especial
void prepara_string(char* entrada)
{
    int frente = 1; //Posicoes a frente
    int tras = 1;   //Posicoes a tras
    int indice = 0; //Indice de leitura
    //Ignora espacos iniciais
    while(entrada[indice] == ' ')
    {
        entrada[indice] = (char)0xFF;
        indice++;
    }

    //Transforma espaços inúteis em um caractere especial
    while(entrada[indice] != '\0')
    {
        //Caso tenha um caractere especial limpa espacos em volta
        if (entrada[indice] == '|' || entrada[indice] == '&')
        {
            //Limpa espacos antes do caractere
            while (entrada[indice-tras] == ' ')
            {
                entrada[indice-tras] = (char)0xFF;
                tras++;
            }
            //Limpa espacos depois do caractere
            while (entrada[indice+frente] == ' ')
            {
                entrada[indice+frente] = (char)0xFF;
                frente++;
            }
            //Reseta valores de frente e tras
            tras = 1; frente = 1;
        }
        //Transforma espaçoes multiplos em apenas 1
        else if (entrada[indice] == ' ')
        {
            while (entrada[indice+frente] == ' ')
            {
                entrada[indice+frente] = (char)0xFF;
                frente++;
            }
            frente = 1;         //Reseta vetor de indice as frente
        }
        indice++;
    }
}
