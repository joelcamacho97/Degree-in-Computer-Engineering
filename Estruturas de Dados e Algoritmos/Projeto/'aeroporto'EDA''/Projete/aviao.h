#include <iostream>
#include <string>


; using namespace std;

struct aviao1 {
	string *nome, *modelo, *origem, *destino, *capacidade;
	struct Passageiro;
};

struct Listadeavioes
{
	char* aviaoproximaçao;
	char *aviaopista;
	char *aviaodescolar;
	Listadeavioes* next;
};

void ficheiros();
char * vectoraviao();
struct aviao1  randAviao();
void printList(Listadeavioes* head);
struct Listadeavioes LIST();
Listadeavioes * insereInicio(Listadeavioes* head, char* dados);
Listadeavioes* removerInicio(Listadeavioes * head);
Listadeavioes * insereInicio(Listadeavioes* head, char* dados);
void insereFim(Listadeavioes * head, char* dados);
char* aviaoproximaçao();
char* aviaopista();
char* aviaodescolar();
