#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

int opcao;
int sair = 0;
time_t data;
int main(int argc, char * argv[]){
  printf("ola %i \n", argc);


  while(!sair){
    printf("\n");
    printf("Escolha uma das opcoes: \n");
    printf("  1 - Escrever no ficheiro \n");
    printf("  2 - Mostrar acontecimentos \n");
    printf("  3 - Sair \n");

    scanf("%d", &opcao);
    for (;;)
    {
      //o getchar basicamente pega em qualquer charater do stdin
      //Como temos fgets mais a frente isto garante que o programa espere pelo input do utilizador
      //O código basicamente da skip de todos os caracteres até que a próxima nova linha ou EOF seja alcançada
      int c = getchar(); 
      if (c == '\n' || c == EOF)
      break;
    }
      switch(opcao){
        case 1:
          if(argc > 1){
            // if(strstr(argv[1],".conf")){
                printf("Ficheiro %s irá para escrita\n", argv[1]);
                // printf("%d", TAM_MAX_FILA);
                FILE *file;
                char digitado[100], c;
                file = fopen(argv[1],"a+");
                if(file == NULL){
                  printf("Nao foi possivel abrir o ficheiro de configuracao!\n");
                  abort();
                }else{
                  printf("\n");
                  printf("Escreva algo para adicionar ao ficheiro %s \n", argv[1]);
                  time(&data);
                  fputs(ctime(&data), file);
                  fgets(digitado, 100, stdin);
                    for (int i=0;digitado[i];i++){
                      c = digitado[i];
                      fputc(c, file);
                    }
                  fclose(file);
                }
            // }else printf("O ficheiro deverá ter a ext .conf\n");
          }else printf("Tem de adicionar o nome do ficheiro de configuração !!!\n");
        break;
        case 2:
          if(argc > 1){
            FILE *file2;
            file2 = fopen(argv[1],"r");

            char linha[150];
            while(fgets(linha, 150, file2)){
              fputs(linha,stdout);
            }
            fclose(file2);
          }else printf("Tem de adicionar o nome do ficheiro de configuração !!!\n");
          break;
        case 3:
          printf("vais sair!!!\n");
          sair = 1;
          break;
        default:
          printf("Opcao invalida :/\n");
          break;
    }
  }
  return 0;
}
