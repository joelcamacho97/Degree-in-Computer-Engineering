#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
int main(int argc, char * argv[]){

    if(argc > 1){
        if(strstr(argv[1],".conf")){
            FILE *file;
            file = fopen(argv[1],"r");
            char name[40];
            int var_conf[15];
            
            if(file == NULL){
                printf("Nao foi possivel abrir o ficheiro de configuracao!\n");
                abort();
            } else{
                int i = 0;
                char linha[150];
                //vai continuar ate chegar ao fim do ficheiro
                while(fgets(linha, 150, file)){
                    
                    //fgets apanha uma linha de cada vez do ficheiro e guarda no char linha
                    //assim ja não mostra um linha branca
                    fputs(linha,stdout);

                   //sscanf string scan aqui ira analizar a string linha e guardar tudo menos o =
                    sscanf(linha, "%[^=] = %d", name, &var_conf[i]);

                    i++;
                }
                    TAM_MAX_FILA = var_conf[0];
                    N_INFETADOS = var_conf[1];
                    N_INTERNADOS = var_conf[2];
                    N_ISOLADOS = var_conf[3];
                    TEMPO_MEDIO_CHEGADA = var_conf[4];
                    TEMPO_ESPERA_ISOLAMENTO = var_conf[5];
                    PRIORIDADE_MIN = var_conf[6];
                    PRIORIDADE_REG = var_conf[7];
                    PRIORIDADE_MAX = var_conf[8];
                    TEMPO_TESTE = var_conf[9];
                    P_TESTE_RAPIDO = var_conf[10];
                    P_TESTE_LENTO = var_conf[11];

                // printf("%d", N_ISOLADOS);
                // printf("%d", TAM_MAX_FILA);
                fclose(file);
            }
        } else printf("O ficheiro deverá ter a ext .conf\n");
    } else printf("Tem de adicionar o nome do ficheiro de configuração !!!\n");
    return 0;
}
