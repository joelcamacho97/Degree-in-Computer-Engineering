#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include "Header.h"
#include "passageiro.h"
#include "aviao.h"
#include <vector>

using namespace std;


string *load_strings(string nomeficheiro, int *tamanho) {

	ifstream file(nomeficheiro);

	int n = 1 + count(istreambuf_iterator<char>(file),
		istreambuf_iterator<char>(), '\n');

	if (!file.is_open()) {
		cout << "NOT OPEN" << endl;
		return NULL;
	}

	file.seekg(0, ios_base::beg);

	string line, *lines = new string[n];
	
	int i = 0;
	while (i < n)
		file >> lines[i++];

	*tamanho = n;

	return lines;
}

int n_nome, n_modelo, n_origem, n_destino, n_capacidade;
string *nome, *modelo, *origem, *destino, *capacidade;

void ficheiros() {

	nome = load_strings("voo.txt", &n_nome),
	modelo = load_strings("modelo.txt", &n_modelo),
	origem = load_strings("origem.txt", &n_origem),
	destino = load_strings("destino.txt", &n_destino),
	capacidade = load_strings("capacidade.txt", &n_capacidade);

}

struct aviao1 randAviao() {
	aviao1 n;
	n.nome = &nome[rand() % n_nome];
	n.modelo = &modelo[rand() % n_modelo];
	n.origem = &origem[rand() % n_origem];
	n.destino = &destino[rand() % n_destino];
	n.capacidade = &capacidade[rand() % n_capacidade];

	return n;
};



char* aviaoproximaçao()
{
	ficheiros2();
	int n=10;
	for (int i = 0; i < n; i++)
	{
		struct aviao1 a = randAviao();
		cout << "Voo : " << *a.nome << endl;
		cout << "Modelo : " << *a.modelo << endl;
		cout << "Origem : " << *a.origem << endl;
		cout << "Destino : aeroporto EDA" << endl;
		cout << "Passageiro: " << endl; 
		cout << "   " << endl;
		Passag();
		cout << "-------------------------------------" << endl;

	}
	char *p1 = new char[n];
	return p1;
}

char* aviaopista()
{
	ficheiros2();
	int n = 7;
	for (int i = 0; i < n; i++)
	{
		struct aviao1 a = randAviao();
		cout << "voo : " << *a.nome << endl;
		cout << "Modelo : " << *a.modelo << endl;
		cout << "oringem : aetoporto EDA" << endl;
		cout << "destino : " << *a.destino << endl;
		cout << "Passageiro: " << endl;
		cout << "   " << endl;
		Passag();
		cout << "-------------------------------------" << endl;
	}
	char *p2 = new char[n];
	return p2;
}

char* aviaodescolar()
{
	ficheiros2();
	int n = 5;
	for (int i = 0; i < n; i++)
	{
		struct aviao1 a = randAviao();
		cout << "voo : " << *a.nome << endl;
		cout << "Modelo : " << *a.modelo << endl;
		cout << "origem : " << *a.origem << endl;
		cout << "Destino : " << *a.destino << endl;
		cout << "Passageiro: " << endl;
		cout << "   " << endl;
		Passag();
		cout << "-------------------------------------" << endl;

	}

	char *p3 = new char[n];
	return p3;
}


char* novoaviao()
{
	ficheiros2();
	int n = 1;
		struct aviao1 a = randAviao();
		cout << "voo : " << *a.nome << endl;
		cout << "Modelo : " << *a.modelo << endl;
		cout << "origem : " << *a.origem << endl;
		cout << "Destino : " << *a.destino << endl;
		cout << "Passageiro: " << endl;
		cout << "   " << endl;
		Passag();
		cout << "-------------------------------------" << endl;

	char *p3 = new char[n];
	return p3;
}

/*
char * aviao()
{
	struct Listadeavioes a = LIST();

	char *paviaoaproximaçao = aviaoproximaçao();
	char *paviaopista = aviaopista();
	char *paviaodescolar = aviaodescolar();

	return paviaoaproximaçao, paviaopista, paviaodescolar;

}/*

/*
void passagdoaviao()
{
	char *pPassag = ;
	pPassag++;
	cout << pPassag << endl;

}*/



struct Listadeavioes LIST()
{
	Listadeavioes l;

	l.aviaoproximaçao = aviaoproximaçao();
	l.aviaopista = aviaopista();
	l.aviaodescolar = aviaodescolar();

	return l;
}


void novoCiclo()
{

	Listadeavioes * head = new Listadeavioes;
	head->next = NULL;
	
		insereFim(head, novoaviao());
		
}


/*
void removeFim (Listadeavioes * head) {
	Listadeavioes * iterator = head;

	while (iterator->next->next != NULL)
		iterator = iterator->next;

	Listadeavioes * temp = iterator->next;
	iterator->next = NULL;
	delete temp;
}
*/


void printList(Listadeavioes* head) {

	Listadeavioes* current = head->next; //”opcional..”


	while (current != NULL)//enquanto não chegar ao fim da LL
	{
		cout << current->aviaoproximaçao << endl;
		current = current->next;
	}
	cout << "NULL" << endl;
}


Listadeavioes* removerInicio(Listadeavioes * head) {
	Listadeavioes * temp = head;
	head = head->next;
	delete temp;
	return head;
}


Listadeavioes * insereInicio(Listadeavioes* head, char* dados) {

	Listadeavioes* newAviao;
	newAviao = new Listadeavioes;
	newAviao-> aviaoproximaçao = dados;
	newAviao->aviaopista = dados;
	newAviao->aviaodescolar = dados;

	newAviao->next = head->next;
	head->next = newAviao;

	return head;
}


void insereFim (Listadeavioes * head, char* dados) {

	Listadeavioes * iterator = head;

	while (iterator->next != NULL)
		iterator = iterator->next;

	Listadeavioes * newAviao = new Listadeavioes;
	newAviao->next = NULL;
	newAviao->aviaoproximaçao = dados;
	newAviao->aviaopista = dados;
	newAviao->aviaodescolar = dados;

	iterator->next = newAviao;

}