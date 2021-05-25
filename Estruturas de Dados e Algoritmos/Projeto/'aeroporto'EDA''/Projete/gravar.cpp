#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "aviao.h"
#include "Header.h"
#include "passageiro.h"
#include <conio.h>

using namespace std;

void gravar1()
{
	ficheiros();
	char* ficheiro;
	ficheiro = "avioes.txt";
	errno_t err;
	FILE *file;
	err = fopen_s (&file, ficheiro, "w");
	fprintf(file, aviaoproximaçao());

	fclose(file);

	/*ofstream myfile;
	myfile.open("avioes.txt");
	myfile << aviaoproximaçao() << endl;
	myfile.close();*/
	
}

void ficheiro3()
{
	ifstream myFile("avioes.txt");
	string line;
	int n = 0;
	myFile.is_open();
	while (getline(myFile, line)){
		cout << line << endl;
		n++;
	}
	myFile.close();
}


void tecla()
{
	int tecla;
	bool sair = false;
	int i=0;
	i++;

	while (!sair)
	{
		tecla = _getch();
		if (tecla == 27)
		{
			sair = true;
			exit(1);
		}
		else if (tecla == 224)
		{
			i = 0;
			system("cls");

			novoCiclo();

		};

	}
}