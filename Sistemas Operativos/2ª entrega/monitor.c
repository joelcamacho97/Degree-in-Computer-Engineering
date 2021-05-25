#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define buffer_max 2000

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

/*  
  clilen = sizeof(cli_addr);
	newsockfd = accept(sock, (struct sockaddr *) &cli_addr,&clilen);
	if (newsockfd < 0)
	  perror("server: accept error");
		err_dump("server: accept error");
	
	pthread_t thread;
	pthread_create(&thread, NULL, simular, &newsockfd);

  //keep communicating with server
*/

}

int simular(){

  int corre = 1;

  char message[buffer_max] , server_reply[buffer_max];


  printf("\n");
  if(EstadoSimulacao == 0){
    printf("Estado atual => Simulacao parada\n");
  }else{
    printf("Estado atual => Simulacao a decorrer!\n");
  }
    printf("Escolha uma das opcoes: \n");
    printf("  1 - Estatisticas \n");
    printf("  2 - Simular acontecimentos \n");
    printf("  3 - Sair\n");
    printf("--> ");
    scanf("%s" , message);
      
  //Send some data
  if( send(sock , message , buffer_max , 0) < 0)
  {
    puts("Send failed");
    return 1;
  }

  while(corre){

    //Receive a reply from the server
    
    int ola;
    if( ola = recv(sock , server_reply , buffer_max , 0) < 0)
    {
      puts("recv failed");
      break;
    }

    puts(server_reply); 


    if( memcmp( server_reply, "acabou", strlen("acabou") ) == 0 ) {
      corre = 0;
    }

    //printf("tamanho: %i", ola);
   
  }

  printf("acabou !! \n");

}

int main(int argc, char * argv[]){
  
  criaSocket();

  while(!sair){
    printf("\n");
    if(EstadoSimulacao == 0){
      printf("Estado atual => Simulacao parada\n");
    }else{
      printf("Estado atual => Simulacao a decorrer!\n");
    }
    printf("Escolha uma das opcoes: \n");
    printf("  1 - Escrever no ficheiro \n");
    printf("  2 - Mostrar conteudos do ficheiro\n");
    printf("  3 - Comecar simulacao \n");
    printf("  4 - Sair \n");
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
          if(argc > 1){
            Escrever_ficheiro(argv[1]);
          }else printf("Tem de adicionar o nome do ficheiro que deseja escrever!!!\n");
        break;
        case 2:
          if(argc > 1){

            Ler_ficheiro(argv[1]);

          }else printf("Tem de adicionar o nome do ficheiro que deseja escrever !!!\n");
          break;
        case 3:
          printf("Simulacao!!!\n");
          EstadoSimulacao = 1;
          simular();
        break;
        case 4:
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


