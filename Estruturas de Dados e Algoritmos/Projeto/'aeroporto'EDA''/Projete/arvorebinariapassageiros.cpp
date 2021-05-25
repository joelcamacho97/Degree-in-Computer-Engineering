/*#include <iostream>
#include <string>
#include "passageiro.h"
using namespace std;

struct passageiros12 {
	struct Passageiro;
	struct nodo* esquerda,* direita;
};

struct passageiros12* novoNodo(struct Passageiro) {

	struct nodo* nodo = new nodo;
	passageiros12 -> dados = num;
	passageiros12 -> esquerda = Passageiro;
	passageiros12 -> direita = Passageiro;
	return(nodo);
};

struct nodo* inserirNodo(struct nodo* nodo, int num)
{
	if (nodo == NULL) {
		return(novoNodo(num));
	}
	else{
		if (num <= nodo->dados)
			nodo->esquerda = inserirNodo(nodo->esquerda, num);
		else
			nodo->direita = inserirNodo(nodo->direita, num);
	}
	return(nodo);
};*/