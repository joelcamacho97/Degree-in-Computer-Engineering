#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <semaphore.h>

#define buffer_max 2000

int tempo;

int opcao;
int sair = 0;
int EstadoSimulacao = 0;
int sock, clilen, newsockfd;

int criaSocket(){
  
  struct sockaddr_in server, cli_addr;
  int received_int = 0;

  sock = socket(AF_INET , SOCK_STREAM , 0);
  if (sock == -1)
  {
    printf("Nao foi possivel criar o socket :-(");
  }
  puts("Socket criado");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons( 8888 );

  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
    perror("connect failed. Error");
    return 1;
  }

  puts("Conectado\n");

}

int simular(){

  int corre = 1;

  char message[buffer_max] , server_reply[buffer_max];


  printf("\n");
  if(EstadoSimulacao == 0){
    printf("Estado atual => Simulacao parada\n\n");
  }else{
    printf("Estado atual => Simulacao a decorrer!\n\n");
  }
    printf("%i\n", (time(0)-tempo) );
    printf("######################################\n");
    printf("####  Escolha uma das opcoes:     ####\n");
    printf("####  1 -> Simular acontecimentos ####\n");
    printf("####  2 -> Estatisticas           ####\n");
    printf("####  3 -> Sair                   ####\n");
    printf("######################################\n");
    printf("--> ");
    scanf("%s" , message);

  if( send(sock , message , buffer_max , 0) < 0)
  {
    puts("Send failed");
    return 1;
  }


  while(corre){
    int tamanho;
    if(tamanho = recv(sock , server_reply , buffer_max , 0) < 0) {
      puts("recv failed");
      break;
    } else  {
        if( memcmp( server_reply, "acabou", strlen("acabou") ) == 0 ) {
        printf("acabou !! \n");
        corre = 0;
        } else puts(server_reply); 
      } 
    }
}

void estatistica()
{
  /*
	printf("\nEstatísticas da loja\n");
	if(EstadoSimulacao == 1)
		printf("\n1. Estado atual: Simulação a decorrer.\n");
	else
		printf("\n1. Estado atual: Simulação terminada.\n");
	
	printf("2. Nº total de pacientes: %d\n", g_clientes);
	printf("3. Nº total de pacientes normais: %d\n", g_clientes_normais);
	printf("4. Nº total de pacientes prioritários: %d\n", g_clientes_prioritarios);
	printf("5. Nº de pacientes que desistiram devido ao tempo: %d\n", g_desistenciasTempo);
	printf("6. Nº de pacientes que desistiram devido ao produto ser caro: %d\n", g_desistenciasPreco);
	
	printf("7. Nº total de empregados: %d\n", g_empregados);
	
	int i;
	printf("8. # | Nome do Produto | Nº de produtos comprados | Nº de produtos em stock: \n");
	for(i = 0; i < numProdutos; i++) 
		printf("\t%d. Produto %c: %d comprados | %d em stock\n", i+1, i+ASCII, produtosComprados[i], produtos[i]);
	
	getMedia(1);
	printf("9. Tempo médio de espera de clientes na fila: %s\n", media);
	
	getMedia(2);
	printf("10. Tempo médio de espera de clientes na fila prioritária: %s\n", media);
	
	if(sair == 1)
		printf("\nAcabou a simulação. [2] para sair.\n\n");*/
  
}

int main(int argc, char * argv[]){
  
  criaSocket();
  tempo = time(0);

  while(!sair){
  char message[buffer_max] , server_reply[buffer_max];

  int tamanho;
  if(tamanho = recv(sock , server_reply , buffer_max, 0) < 0) {
    puts("recv failed");
    break;
  }

    printf("####################################\n");
    printf("####  CENTRO DE TESTAGEM Nº %s  ####\n", server_reply);
    printf("####  1 -> Simulação          ####\n");
    printf("####  2 -> Sair               ####\n");
    printf("##################################\n");
    printf("--> ");
    scanf("%d", &opcao);
    
    for (;;)
    {
      int c = getchar(); 
      if (c == '\n' || c == EOF)
      break;
    }
      switch(opcao){
        case 1:
          EstadoSimulacao = 1;
          simular();
        break;
        case 2:
          printf("vais sair!!!\n");
          close(sock);
          sair = 1;
          break;
        default:
          printf("Opcao invalida :/\n");
          break;
    }
  }
  return 0;
}


