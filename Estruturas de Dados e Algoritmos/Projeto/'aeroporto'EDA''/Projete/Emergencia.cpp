#include <iostream>
#include <string>
#include "Header.h"
#include "aviao.h"

using namespace std;


int length(Listadeavioes* head)
{
	Listadeavioes* current = head;
	int count = 0;

	while (current->next != NULL)
	{
		count++;
		current = current->next;
	}

	head = NULL;
	return count;
}

/*
void insereFim(Listadeavioes * head, char* dados) {

	Listadeavioes * iterator = head;

	while (iterator->next != NULL)
		iterator = iterator->next;

	Listadeavioes * newAviao = new Listadeavioes;
	newAviao->next = NULL;
	newAviao->aviaoproximaçao = dados;
	newAviao->aviaopista = dados;
	newAviao->aviaodescolar = dados;

	iterator->next = newAviao;

}*/


void removeFim(Listadeavioes * head) {
	Listadeavioes * iterator = head;

	while (iterator->next->next != NULL)
		iterator = iterator->next;

	Listadeavioes * temp = iterator->next;
	iterator->next = NULL;
	delete temp;
}

/*
Listadeavioes* removerInicio(Listadeavioes * head) {
	Listadeavioes * temp = head;
	head = head->next;
	delete temp;
	return head;
}*/


void removeMeio(Listadeavioes * const head, int pos) {
	if (pos == 0) {
		removerInicio(head);
	}
	else if (pos == 1) {
		removeFim(head);
	}
	else {
		int pos_count = 0;
		Listadeavioes * iterator = head;
		while (iterator->next != NULL && pos_count != pos) {
			iterator = iterator->next;
			pos_count++;
		}

		cout << endl << "removing" << endl;
		Listadeavioes * temp = iterator->next;
		//prints
		cout << "iterator " << iterator->aviaoproximaçao << endl;
		cout << "temp " << temp->aviaoproximaçao << endl;
		cout << "iterator->next->next " << iterator->next->next->aviaoproximaçao << endl;

		iterator->next = iterator->next->next;
		delete temp;
	}
}

/*
Listadeavioes * insereInicio(Listadeavioes* head, char* dados) {

	Listadeavioes* newAviao;
	newAviao = new Listadeavioes;
	newAviao->aviaoproximaçao = dados;
	newAviao->aviaopista = dados;
	newAviao->aviaodescolar = dados;

	newAviao->next = head->next;
	head->next = newAviao;

	return head;
}
*/

void insereMeio(Listadeavioes* head, char* dados, int pos)
{
	int tamanho = length(head);

	if (tamanho == 0) {
		insereInicio(head, dados);
	}
	else if (pos == tamanho - 1) {
		insereFim(head, dados);
	}
	else if (pos >= tamanho) {
		cout << " erro fim de lista " << pos << tamanho << endl;
	}
	else {

		Listadeavioes * iterator = head;
		int pos_count = 0;
		while (iterator->next != NULL && pos != pos_count) {
			iterator = iterator->next;
			pos_count++;
		}

		Listadeavioes * newNode = new Listadeavioes;
		newNode->aviaoproximaçao = dados;
		newNode->next = iterator->next;

		iterator->next = newNode;

	}
}
