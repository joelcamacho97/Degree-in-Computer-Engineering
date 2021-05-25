#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <pthread.h>

#define buffer_max 2000


struct conf simuladorConf;
int socket_desc , client_sock , c , read_size;
char client_message[2000];

//controlam a simulação
int totalClientes = 0,
	clientesPrio = 0,
	clienteNormais = 0,
	corre = 0, 
	tempoSimulacao = 0,
	sair = 0;

pthread_t thread;
pthread_mutex_t lock; 

//função que cria utilizadores, tem que receber um apontador because yes
void *criaTarefaUtilizador(void *ptr){
    int idUtilizador;
	char buffer[buffer_max];
	int prob = rand()%100 + 1;
	int tipo;

	if(prob<=simuladorConf.PROB_PRIORITARIO)	tipo = simuladorConf.PRIORIDADE_MAX;  //cliente com prioridade
	else	tipo = simuladorConf.PRIORIDADE_MIN;

	
	if(tipo ==2){ // Prioritario
		pthread_mutex_lock(&lock);
    	totalClientes++;
		clientesPrio++;
    	idUtilizador = totalClientes;
		pthread_mutex_unlock(&lock); 

		sprintf(buffer, "Utilizador Prioritario %d chegou para ser testado\n", idUtilizador);
		printf("Utilizador Prioritario %d chegou para ser testado\n", idUtilizador);

	}else{
		pthread_mutex_lock(&lock);
		totalClientes++;
		clienteNormais++;
		idUtilizador = totalClientes;
		pthread_mutex_unlock(&lock);

		sprintf(buffer, "Utilizador normal %d chegou para ser testado\n", idUtilizador);
		printf("Utilizador normal %d chegou para ser testado\n", idUtilizador);
	}

    send(client_sock, buffer, buffer_max,0);
	/*	if( write(client_sock , buffer, 2000 , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}*/

	pthread_mutex_lock(&lock);
	tempoSimulacao++;
	printf("Utilizador %d terminou ...\n", tempoSimulacao);
	pthread_mutex_unlock(&lock); 

    return NULL;
    
}

void *recebe_comandos_monitor(void *arg)
{

	char buffer[2];
	
	//ciclo que fica à espera dos pedidos dos Monitor

    while( (read_size = recv(client_sock , client_message , buffer_max , 0)) > 0 )
	{
		buffer[read_size] = '\0';
		switch(atoi(client_message)) {
			case 1: //Iniciar
				printf("um\n");
				printf("Numero total de utilizadores normais: %d\n", totalClientes);
				printf("Numero total de utilizadores normais: %d\n", clienteNormais);
				printf("Numero total de utilizadores prioritarios: %d\n", clientesPrio);
				sprintf(client_message, "TC = %d CN = %d CP = %d \n", totalClientes, clienteNormais, clientesPrio);
				//write(client_sock , client_message , 2000);
				
				if( send(client_sock , client_message, buffer_max , 0) < 0)
				{
					puts("Send failed");
					return 1;
				}
				if( send(client_sock , "acabou" , strlen("acabou") , 0) < 0)
				{
				puts("Send failed");
				return 1;
				}

				// write(client_sock , totalClientes , 1000);
				break;
			case 2: //iniciar a simulação
				for (int i = 0; i <= 10; i++)
				{
					pthread_create(&thread, NULL, &criaTarefaUtilizador, &client_sock);
				}
				
				corre = 1;
				break;
			case 3:
				sair= 1;
				write(client_sock , "Saindo" , buffer_max);
				printf("sair\n");
			default:
				break;
		}
	}
	return NULL;
}

int main(int argc, char * argv[]){

    if(argc > 1) {  //le o simulador.conf
        Le_configs(argv[1]);
        // printf("%d", config.N_ISOLADOS);
        //printf("%d", TAM_MAX_FILA);
    }else {
        printf("Tem de adicionar o nome do ficheiro de configuração !!!\n");
        abort();
    }

    //SOCKETS ******************************************************************
    
	struct sockaddr_in server , client;

	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind function binds the socket to the address 
    //and port number specified in addr(custom data structure).

	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
    //criação da tarefa que irá tratar dos pedidos enviados pelo Monitor
	pthread_create(&thread, NULL, &recebe_comandos_monitor, &client_sock);

	//while(corre == 0 && sair == 0 && tempoSimulacao <= 10);

	while(1){

	if(tempoSimulacao == 10){
		if( send(client_sock , "acabou" , strlen("acabou") , 0) < 0)
		{
		puts("Send failed");
		return 1;
		}
		tempoSimulacao = 0;
	}


	};
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	close(client_sock);
    return 0; 

}

void Le_configs(char* files){
    
    if(strstr(files,".conf")){
            FILE *file;
            file = fopen(files,"r");
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
                    // fputs(linha,stdout);

                   //sscanf string scan aqui ira analizar a string linha e guardar tudo menos o =
                    sscanf(linha, "%[^=] = %d", name, &var_conf[i]);

                    i++;
                }

                    simuladorConf.TAM_MAX_FILA = var_conf[0];
                    simuladorConf.TEMPO_MEDIO_CHEGADA = var_conf[1];
                    simuladorConf.TEMPO_ESPERA_ISOLAMENTO = var_conf[2];
					simuladorConf.TEMPO_ESPERA_ISOLAMENTO_INFETADO = var_conf[3];
                    simuladorConf.PRIORIDADE_MIN = var_conf[4];
                    simuladorConf.PRIORIDADE_MAX = var_conf[5];
                    simuladorConf.TEMPO_TESTE = var_conf[6];
                    simuladorConf.P_TESTE_RAPIDO = var_conf[7];
                    simuladorConf.P_TESTE_LENTO = var_conf[8];
					simuladorConf.P_FICAR_PIOR = var_conf[9];
                    simuladorConf.TEMPO_SIMULACAO = var_conf[10];
                    simuladorConf.N_TESTES = var_conf[11];
					simuladorConf.PROB_DESISTIR = var_conf[12];
					simuladorConf.PROB_PRIORITARIO=var_conf[13];
					

                // printf("%d", simuladorConf.N_ISOLADOS);
                // printf("%d", simuladorConf.TAM_MAX_FILA);
                fclose(file);
            }
        } else printf("O ficheiro deverá ter a ext .conf\n");

    


	


}
