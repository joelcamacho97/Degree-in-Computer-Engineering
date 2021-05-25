#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

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

}

struct conf Le_configs(char* files){
    
    struct conf simuladorConf;
    int tamanho = 1;
    int* dados_config =  malloc(tamanho * sizeof(int));

    if(strstr(files,".conf")){
		
		FILE* fp = fopen (files, "r");
		
		if(fp == NULL)
		{
			printf("Nao foi possivel abrir o ficheiro de configuracao!\n");
			abort();
		}
		
		int dado, i = 0;
		char parametro[256], linha[1024];
		
		while(fgets(linha, sizeof(linha), fp) != NULL) 
		{
			if(sscanf(linha, "%s = %i", parametro, &dado) == 2){
				dados_config[i] = dado;			
				i++;
				tamanho++;
				dados_config = realloc(dados_config, tamanho  * sizeof(int));
			}
		}

		simuladorConf.TAM_MAX_FILA = dados_config[0];
		simuladorConf.TEMPO_MEDIO_CHEGADA = dados_config[1];
		simuladorConf.TEMPO_ESPERA_ISOLAMENTO = dados_config[2];
		simuladorConf.TEMPO_ESPERA_ISOLAMENTO_INFETADO = dados_config[3];
		simuladorConf.PRIORIDADE_MIN = dados_config[4];
		simuladorConf.PRIORIDADE_MAX = dados_config[5];
		simuladorConf.TEMPO_TESTE = dados_config[6];
		simuladorConf.P_TESTE_RAPIDO = dados_config[7];
		simuladorConf.P_TESTE_LENTO = dados_config[8];
		simuladorConf.P_FICAR_PIOR = dados_config[9];
		simuladorConf.TEMPO_SIMULACAO = dados_config[10];
		simuladorConf.N_TESTES = dados_config[11];
		simuladorConf.PROB_DESISTIR = dados_config[12];
		simuladorConf.PROB_PRIORITARIO=dados_config[13];
		simuladorConf.UTILIZADORES=dados_config[14];
    
	}	else printf("O ficheiro deverá ter a ext .conf\n");
    return simuladorConf;
}