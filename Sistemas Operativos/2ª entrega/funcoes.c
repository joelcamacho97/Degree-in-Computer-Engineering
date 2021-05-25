#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

// struct conf simuladorConf;
void Escrever_ficheiro(char* files){

    FILE *file;
    file = fopen(files,"a+");
    time_t data;
    char digitado[100], c;
    if(file == NULL){

        printf("Nao foi possivel abrir o ficheiro de configuracao!\n");
        abort();

    }else{

        printf("\n");
        printf("Escreva algo para adicionar ao ficheiro %s \n", files);


        time(&data);
        fputs(ctime(&data), file);

        fgets(digitado, 100, stdin);
        for (int i=0;digitado[i];i++){
            c = digitado[i];
            fputc(c, file);
        }
        fclose(file);
    }

}



void Ler_ficheiro(char* files){

    FILE *file2;
    file2 = fopen(files,"r");
    if(file2 == NULL){

        printf("Nao foi possivel abrir o ficheiro !\n");
        abort();

    }else{
        char linha[150];

        while(fgets(linha, 150, file2)){
            fputs(linha,stdout);
        }

        fclose(file2);
    }
    // printf("%d", simuladorConf.N_ISOLADOS);
    // printf("%d", simuladorConf.TAM_MAX_FILA);

}

// void Le_configs(char* files){
    
//     if(strstr(files,".conf")){
//             FILE *file;
//             file = fopen(files,"r");
//             char name[40];
//             int var_conf[15];
            
//             if(file == NULL){
//                 printf("Nao foi possivel abrir o ficheiro de configuracao!\n");
//                 abort();
//             } else{
//                 int i = 0;
//                 char linha[150];
//                 //vai continuar ate chegar ao fim do ficheiro
//                 while(fgets(linha, 150, file)){
                    
//                     //fgets apanha uma linha de cada vez do ficheiro e guarda no char linha
//                     //assim ja não mostra um linha branca
//                     fputs(linha,stdout);

//                    //sscanf string scan aqui ira analizar a string linha e guardar tudo menos o =
//                     sscanf(linha, "%[^=] = %d", name, &var_conf[i]);

//                     i++;
//                 }

//                     simuladorConf.TAM_MAX_FILA = var_conf[0];
//                     simuladorConf.N_INFETADOS = var_conf[1];
//                     simuladorConf.N_INTERNADOS = var_conf[2];
//                     simuladorConf.N_ISOLADOS = var_conf[3];
//                     simuladorConf.TEMPO_MEDIO_CHEGADA = var_conf[4];
//                     simuladorConf.TEMPO_ESPERA_ISOLAMENTO = var_conf[5];
//                     simuladorConf.PRIORIDADE_MIN = var_conf[6];
//                     simuladorConf.PRIORIDADE_REG = var_conf[7];
//                     simuladorConf.PRIORIDADE_MAX = var_conf[8];
//                     simuladorConf.TEMPO_TESTE = var_conf[9];
//                     simuladorConf.P_TESTE_RAPIDO = var_conf[10];
//                     simuladorConf.P_TESTE_LENTO = var_conf[11];

//                 printf("%d", simuladorConf.N_ISOLADOS);
//                 printf("%d", simuladorConf.TAM_MAX_FILA);
//                 fclose(file);
//             }
//         } else printf("O ficheiro deverá ter a ext .conf\n");

// }