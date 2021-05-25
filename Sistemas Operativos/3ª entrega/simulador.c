#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <pthread.h>
#include <semaphore.h>  //semaforos

#define buffer_max 2000

	//sprintf(buffer, "%d 3 %d %d %d %d %d\n", (int)time(0), idCliente, empregado[idEmpregado].produto, tipo, tempoEsperaFila, idEmpregado+1);

struct sockaddr_in server , client;
struct conf simuladorConf;

int socket_desc , c , read_size;
char client_message[buffer_max];

//controlam a simulação
int** _global;
int** client_sock;

int totalClientes = 0,
	clientesPrio = 0,
	clienteNormais = 0,
	corre = 0, 
	tempoSimulacao = 0,
	sair = 0;

int dimension1 = 0,
	dimension2 = 7;

//tarefa
pthread_t thread;

//trincos

pthread_mutex_t lock, abrir, contar, _seg;

sem_t mutex;

int perc, no_r = 0;

void eu(){
	perc = (tempoSimulacao*100)/simuladorConf.UTILIZADORES;
		if(no_r == perc){
			printf("--> (%d%)\n", perc);
			no_r++;
		}
};

//remover semaforos com o mesmo nome
sem_unlink(fila_normal);
sem_unlink(fila_prioritaria);
sem_unlink(fila_desistencias);
sem_unlink(sem_testes);

//SEMAFOROS
sem_t fila_normal;
sem_t fila_prioritaria;
sem_t fila_desistencias;
sem_t sem_testes; //numero maximo de utilizadores que podem fazer testes ao mesmo tempo

//função que cria utilizadores, tem que receber um apontador 
void *criaTarefaUtilizador(void *ptr){

	eu();	

    int idUtilizador;
	char buffer[buffer_max];
	int prob = rand()%100 + 1;
	int tipo;

	int valor_semaforo;
	sem_getvalue(&mutex, &valor_semaforo);
  	//printf("Estão %d na fila !!!\n", valor_semaforo);
	if(valor_semaforo != 0)
		printf("A fila está livre, posso avançar !\n");
	else {
		printf("A fila está cheia !\n");
		int ficar = rand() % 101;
		if(ficar >= 50) printf("Mas eu vou esperar !\n");
		else printf("E eu não vou esperar !\n");
	}
	sem_wait(&mutex);


	if(prob<=simuladorConf.PROB_PRIORITARIO)	
		tipo = simuladorConf.PRIORIDADE_MAX;
	else
		tipo = simuladorConf.PRIORIDADE_MIN;

	if(tipo ==2){ // Prioritario
		pthread_mutex_lock(&lock);
    	totalClientes++;
		clientesPrio++;
    	idUtilizador = totalClientes;
		pthread_mutex_unlock(&lock);
	}else{
		pthread_mutex_lock(&lock);
		totalClientes++;
		clienteNormais++;
		idUtilizador = totalClientes;
		pthread_mutex_unlock(&lock);
	}    
	sprintf(buffer, "Utilizador Prioritario %d chegou para ser testado\n", idUtilizador);
	send(client_sock, buffer, buffer_max,0);

	//printf("Utilizador %d terminou ...\n", (tempoSimulacao + 1));
	pthread_mutex_lock(&contar);
	tempoSimulacao++;
	pthread_mutex_unlock(&contar);
	sem_post(&mutex);
    pthread_exit(NULL);	
}

void *estado_socket(void *arg){

	int vivo = 1;
	while(vivo){	
		pthread_mutex_lock(&_seg);
			int newdim =  dimension1;
		pthread_mutex_unlock(&_seg);
		struct sockaddr_in cli_addr;
		int sockfd=*((int *) arg), clilen=sizeof(cli_addr);

		unsigned short  rcvBuffer;

		if(recv(sockfd, &rcvBuffer, sizeof(unsigned int),0) == 0)	{
			for (int i = 0; i < newdim; i++)
			{
				//printf("%i = %i\n",	**_global, sockfd);
				//printf("%i = %i\n",	_global[i][0], sockfd);
				if(_global[i][0] == sockfd)	{
					_global[i][0] = -1;
					//printf("= %i\n",	_global[i][0]);
					//printf("encontrei\n");
					pthread_exit(NULL);
				}
			}
			printf("monitor: %i desligou-se !\n", (sockfd-4));
			vivo = 0;
		}
	}
	pthread_exit(NULL);
}

void *recebe_comandos_monitor(void *arg)
{

	/*int totalClientes = 0,
	clientesPrio = 0,
	clienteNormais = 0,
	corre = 0, 
	tempoSimulacao = 0,
	sair = 0;
*/
	struct sockaddr_in cli_addr;
	int n;

	int sockfd=*((int *) arg), clilen=sizeof(cli_addr);
	
	char buffer[2];
	
	//ciclo que fica à espera dos pedidos dos Monitor
	printf("monitor novo\n");
	
	//ciclo que fica à espera dos pedidos dos Monitor
	printf("??\n");
    while( (read_size = recv(client_sock , client_message , buffer_max , 0)) > 0 )
	{
		buffer[read_size] = '\0';
		switch(atoi(client_message)) {
			case 1: //Iniciar
				printf("um\n");
				printf("Numero total de utilizadores total: %d\n", totalClientes);
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

				sem_init(&mutex, 0, 4); // inicia semaforo

				printf("utilizadore %d\n",simuladorConf.UTILIZADORES);

				int perc, no_r = 0;

				printf("Espere que as tarefas se carreguem por completo ....\n");
				
				for (int i = 0; i < simuladorConf.UTILIZADORES; i++)	{
					pthread_create(&thread, NULL, &criaTarefaUtilizador, &client_sock);
				}
				
				printf("As tarefas já estão carregadas por completo ....\n");

				//corre = 1;

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
/*
void *salaTestes(void *arg){
	//numero de testes que podem ser feitos ao mesmo tempo
	int numTestes;
	numTestes = simuladorConf.N_TESTES;
	char buffer2[buffer_max];
	//if(clienteEsperaPrio >= 0){

		//sem_wait(&sem_testes);
	
		//sem_post(&fila_prioritaria);
		sprintf(buffer2, "Utilizador Prioritario esta a fazer o teste\n");
		send(client_sock, buffer2, buffer_max,0);
		printf("Utilizador Prioritario esta a fazer o teste\n");
		//clienteEsperaPrio--;

	//}else{

		//sem_wait(&sem_testes);

		//sem_post(&fila_normal);
		sprintf(buffer2, "Utilizador normal esta a fazer o teste\n");
		send(client_sock, buffer2, buffer_max,0);
		printf("Utilizador normal esta a fazer o teste\n");
		//clienteEsperaNormal--;

	}

	sem_post(&sem_testes);
	printf("Cliente acabou o teste\n");
	
	

}*/

int main(int argc, char * argv[]){

    if(argc > 1) {  //le o simulador.conf
        simuladorConf = Le_configs(argv[1]);
    }else {
        printf("Tem de adicionar o nome do ficheiro de configuração !!!\n");
        abort();
    }
    //SOCKETS ******************************************************************
    
	

	
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

	while(1){ //COM ESTE WHILE CONSEGUIMOS VARIAS CON. EM SIMULTANEO !!
	//Listen
	listen(socket_desc , 0);

	//printf("ola %s \n",socket_desc);
	//Accept and incoming connection
	
	
	puts("Waiting for incoming connections...");
	
	pthread_mutex_lock(&_seg);
	dimension1++;
	int newdim = dimension1;
	pthread_mutex_unlock(&_seg);

	//puts("1");
	client_sock  = realloc(client_sock,	newdim * sizeof(*client_sock));

	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock[newdim-1] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}

	puts("Connection accepted");
	
	//printf("meu socket é %i\n", &client_sock);

	

	int dec;
	//printf("ola %i \n",newdim);
	for (int i = 0; i < newdim-1; i++)	{

		if(_global[i][0] == -1)	{
			
			printf("Quer reaproveitar o centro de testagem %i\n", newdim-1);
			//codigo
			break;
			//scanf(dec);
			//_global[i][0] = -1;
			//printf("= %i\n",	_global[i][0]);
			//printf("encontrei\n");
			//pthread_exit(NULL);
		}

	}
	
	//puts("\n2");
	_global = realloc(_global,	newdim * sizeof(*_global));
	_global[newdim-1] = malloc(dimension2 * sizeof(_global[newdim-1]));
	


	//send(client_sock[newdim-1] , "acabou" , strlen("acabou") , 0);

	/*if(dec == 1){
		//VARIAVEIS GLOBAIS PARA CADA LOCAL DE TESTE (PARA CADA MONITOR)
		_global[newdim-1][0] = newdim-1; 	//socket
		_global[newdim-1][1] = 0; 				// totalClientes
		_global[newdim-1][2] = 0;  				// clientesPrio
		_global[newdim-1][3] = 0;  				// clienteNormais
		_global[newdim-1][4] = 0;  				// corre
		_global[newdim-1][5] = 0;  				// tempoSimulacao
		_global[newdim-1][6] = 0;  				// sair
	} else {*/

		//VARIAVEIS GLOBAIS PARA CADA LOCAL DE TESTE (PARA CADA MONITOR)
		_global[newdim-1][0] = client_sock[newdim-1]; 	//socket
		_global[newdim-1][1] = 0; 						// totalClientes
		_global[newdim-1][2] = 0;  						// clientesPrio
		_global[newdim-1][3] = 0;  						// clienteNormais
		_global[newdim-1][4] = 0;  						// corre
		_global[newdim-1][5] = 0;  						// tempoSimulacao
		_global[newdim-1][6] = 0;  						// sair
	//}

	char buffer[buffer_max];

	sprintf(buffer,"%i",newdim);
	
	//printf("ola -- %s", buffer);
	
	if( send(client_sock[newdim-1] , buffer , buffer_max , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}	

	pthread_create(&thread, NULL, &estado_socket, &client_sock[newdim-1]);
	//pthread_create(&thread, NULL, &recebe_comandos_monitor, &client_sock);

	
	}
	
    //criação da tarefa que irá tratar dos pedidos enviados pelo Monitor
	

	
	while(1){
	
	if(tempoSimulacao == simuladorConf.UTILIZADORES){
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
