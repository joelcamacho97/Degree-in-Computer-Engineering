#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include "Header.h"
#include "aviao.h"
#include "passageiro.h"
using namespace std;


string *caregar_strings(string nomeficheiro, int *tamanho) {

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

int n_primNome, n_segNome, n_Nacionalidade;
string *primNome, *segNome, *Nacionalidade;

void ficheiros2() {
		primNome = caregar_strings("primeiro_nome.txt", &n_primNome),
		segNome = caregar_strings("segundo_nome.txt", &n_segNome),
		Nacionalidade = caregar_strings("nacionalidade.txt", &n_Nacionalidade);
}

int bilhete;

struct Passageiro randPassagerio()
{
	Passageiro p;
	p.primNome = &primNome[rand() % n_primNome];
	p.segNome = &segNome[rand() % n_segNome];
	p.Nacionalidade = &Nacionalidade[rand() % n_Nacionalidade];
	p.bilhete = bilhete = rand() % 100+1;
	return p;
};

char * Passag()
{
	for (int i = 0; i < rand() % 10 + 5; i++)
	{
		struct Passageiro p = randPassagerio();
		cout << "Primeiro Nome : " << *p.primNome << endl;
		/*cout << "Segundo Nome : " << *p.segNome << endl;
		cout << "Nacionalidade : " << *p.Nacionalidade << endl;
		cout << "bilhete : " << p.bilhete << endl;*/
	}
	char *p = new char;

	return p;
}

struct listadepassageiros ListPass()
{
	listadepassageiros p;

	p.passageiros1 = Passag();

	return p;
}


/*
void Passag2()
{
	for (int i = 0; i < 20; i++)
	{
		struct Passageiro p = randPassagerio();
		cout << "Primeiro Nome : " << *p.primNome << endl;
		cout << "Segundo Nome : " << *p.segNome << endl;
		cout << "Nacionalidade : " << *p.Nacionalidade << endl;
		cout << "bilhete : " << p.bilhete << endl;
		cout << "       " << endl;
	}
}*/
