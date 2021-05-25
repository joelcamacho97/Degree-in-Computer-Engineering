#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>
#include "Header.h"
#include <ctime>
#include "aviao.h"
#include "passageiro.h"
using namespace std;

int main()
{
	ficheiros();
	ficheiros2();
	srand(time(NULL));
	setlocale(LC_ALL, "Portuguese");

	cout << "                        " << "#############################################" << endl;
	cout << "                        " << "###                                       ###" << endl;
	cout << "                        " << "###            Aeroporto EDA              ###" << endl;
	cout << "                        " << "###              By:                      ###" << endl;
	cout << "                        " << "###                                       ###" << endl;
	cout << "                        " << "###              Afonso                   ###" << endl;
	cout << "                        " << "###               Lee                     ###" << endl;
	cout << "                        " << "###              Ricardo                  ###" << endl;
	cout << "                        " << "###               V�tor                   ###" << endl;
	cout << "                        " << "###                                       ###" << endl;
	cout << "                        " << "#############################################" << endl;
	cout << endl;
	cout << endl;

	bool sair = false;
	char opcao;
	cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << "-> para gerar ciclo" << "     " << "(S)air" << endl;

	cout << "############################ Em aproxima��o ##############################" << endl;
	aviaoproxima�ao();
	cout << "############################ Na pista ############################" << endl;
	aviaopista();
	cout << "############################ A descolar ############################" << endl;
	aviaodescolar();
	do{
		std::cin >> opcao;
		system("cls");
		switch (opcao)
		{
		case 'e':
			cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << " -> para gerar ciclo" << "     " << "(S)air" << endl;
			cout << "Emerg�ncia: " << endl;
			break;

		case 'o':
			cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << " -> para gerar ciclo" << "     " << "(S)air" << endl;
			cout << "Op��es: " << endl;
			char opcoes;
			cout << "(P) Todos os Passageiros" << "       " << "(Q)Passageiros" << "       "<< "(V)oos" << "       " << "(S)air" << endl;

			std::cin >> opcoes;
			switch (opcoes)
			{
			case 'p':
				cout << "Passageiros:" << endl;
				
				break;
			case 'v':
				cout << "Voos:" << endl;
				
				break;
			case 's':
				cout << "" << endl;
				sair = false;
				break;
			default:
				cout << "Escolha uma op��o v�lida!" << endl;
			
			};
			break;
		case 'g':
			cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << " -> para gerar ciclo" << "     " << "(S)air" << endl;
			cout << "Gravar dados do aeroporto" << endl;
			gravar1();
			break;
		case 'j':
			cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << " -> para gerar ciclo" << "     " << "(S)air" << endl;
			cout << "avioes gravados: " << endl;
			ficheiro3();
			break;
		case 's':
			cout << "Obrigado!" << endl;
			sair = true;
			break;
		default:
			cout << "(E)merg�ncia" << "     " << "(O)p��es" << "     " << "(G)ravar" << "      " << "(j) Para ver a grava��o" << "     " << " -> para gerar ciclo" << "     " << "(S)air" << endl;
			cout << "Escolha uma op��o v�lida!" << endl;
		}
	} 
	while (!sair);
	
	return 0;
	std::cin.sync();
	std::cin.get();

}