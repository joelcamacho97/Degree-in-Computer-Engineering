#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Escrever_ficheiro(char* file);
void Ler_ficheiro(char* files);
struct conf Le_configs(char* files);
int criaSocket();
struct conf{
    int TAM_MAX_FILA;
    int TEMPO_MEDIO_CHEGADA;
    int TEMPO_ESPERA_ISOLAMENTO;
    int TEMPO_ESPERA_ISOLAMENTO_INFETADO;
    int PRIORIDADE_MIN;
    int PRIORIDADE_MAX;
    int TEMPO_TESTE;
    int P_TESTE_RAPIDO;
    int P_TESTE_LENTO;
    int P_FICAR_PIOR;
    int TEMPO_SIMULACAO;
    int N_TESTES;
    int PROB_DESISTIR;
    int PROB_PRIORITARIO;
    int UTILIZADORES
    
};