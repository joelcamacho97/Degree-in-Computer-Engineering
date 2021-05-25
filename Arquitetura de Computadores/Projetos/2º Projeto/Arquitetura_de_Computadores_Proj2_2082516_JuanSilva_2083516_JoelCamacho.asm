;PERIFÉRICOS
Username EQU 01A0H ;ENDEREÇO DO PERIFERICO DO USERNAME
Password EQU 01B0H ;ENDEREÇO DO PERIFERICO DA PASSWORD
NR_SEL EQU 1C0H ;ENDEREÇO DO SELETOR NR_SEL
Ok EQU 1D0H ;ENDEREÇO DO BOTÃO OK

;BASE DE DADOS
BasedeDados EQU 7000H ;ENDEREÇO DE INICIO DA BASE DE DADOS
numClientes EQU 10 ;NUMERO MAXIMO DE CLIENTES DA PIZZARIA
bd_user EQU 0 ;INDICE DO USERNAME DENTRO DA FICHA DE CLIENTE
bd_pass EQU 16 ;INDICE DA PASSWORD DENTRO DA FICHA DE CLIENTE
bd_valor EQU 32 ;INDICE DO VALOR DENTRO DA FICHA DE CLIENTE
tam EQU 48 ;TAMANHO DE CADA FICHA DE CLIENTE

;DISPLAY
Display EQU 200H ;ENDEREÇO ONDE COMEÇA E É APRESENTADO O DISPLAY
DisplayEnd EQU 26FH ;ENDEREÇO ONDE ACABA O DISPLAY
UserNoDisplay EQU 0230H ;ENDEREÇO ONDE É MOSTRADO O USERNAME INTRODUZIDO
PassNoDisplay EQU 0250H ;ENDEREÇO ONDE É MOSTRADO A PASSWORD INTRODUZIDO

posicaoValorgasto EQU 0235H ;ENDEREÇO ONDE É MOSTRADO O VALOR GASTO NO PAGAMENTO
posicaoDesconto EQU 0255H ;ENDEREÇO ONDE É MOSTRADO O DESCONTO NO PAGAMENTO

;CONSTANTES
CaracterVazio EQU 20H ;ASCII 20H É O ESPAÇO
CaracterAsterisco EQU 2AH ;ASCII 20H É O ASTERISCO
Nr_Caracteres EQU 8 ;NUMERO DE CARACTERES DO USERNAME / PASSWORD
MLogin EQU 1
MRegistar EQU 2
OCliente_pizza EQU 1
OCliente_sair EQU 2
OTamanho_peq EQU 1
OTamanho_grande EQU 2
Terminador EQU 00H
valorDesconto EQU 32H ;VALOR 50

StackPointer EQU 6000H

;UTILIZADOR JÁ REGISTADO POR DEFEITO
Place 7000H
	String "Juan"
Place 7010H
	String "1234"
Place 7020H
	String 20

;««««««««««««««««««««««««««««««««««««
;	MENUS DO PROJETO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
Place 2000H ;A PARTIR DO ENDEREÇO 2000 DA MEMORIA VAI ESTAR O MENU ABAIXO
MenuPizzaria:
	String "  MENU PIZZARIA "
	String "                "
	String "1. LOGIN        "
	String "2. REGISTAR     "
	String "                "
	String "                "
	String "                "
Place 2080H
MenuLogin:
	String "    MENU LOGIN  "
	String "                "
	String " USERNAME:      "
	String "                "
	String " PASSWORD:      "
	String "                "
	String "                "
Place 2160H
MenuRegisto:
	String "  MENU REGISTO  "
	String "                "
	String " USERNAME:      "
	String "                "
	String " PASSWORD:      "
	String "                "
	String "                "
Place 2240H
MenuCliente:
	String "  MENU CLIENTE  "
	String "                "
	String "1. PIZZAS       "
	String "2. SAIR         "
	String "                "
	String "                "
	String "                "
Place 2320H
MenuPizzas:
	String "  MENU PIZZAS   "
	String "                "
	String "1. PIZZA 1      "
	String "2. PIZZA 2      "
	String "3. PIZZA 3      "
	String "4. PIZZA 4      "
	String "5. PIZZA 5      "
Place 2400H
MenuTamanho:
	String "  MENU TAMANHO  "
	String "                "
	String "1. PEQUENA 5 EUR"
	String "2. GRANDE 8 EUR "
	String "                "
	String "                "
	String "                "
Place 2480H
MenuErro:
	String "    ATENCAO:    "
	String "                "
	String "     OPCAO      "
	String "     ERRADA     "
	String "                "
	String "                "
	String "                "
Place 2560H
MenuPassErrada:
	String "    ATENCAO:    "
	String "                "
	String "   PASSWORD     "
	String "   INVALIDA     "
	String "                "
	String "                "
	String "                "
Place 2640H
MenuUserEmUso:
	String "    ATENCAO:    "
	String "                "
	String "    USERNAME    "
	String "      EM        "
	String "   UTILIZACAO   "
	String "                "
	String "                "
Place 2720H
MenuUserErrado:
	String "    ATENCAO:    "
	String "                "
	String "    USERNAME    "
	String "                "
	String "    INVALIDO    "
	String "                "
	String "                "
Place 2800H
MenuUserRegistado:
	String "    ATENCAO:    "
	String "                "
	String "    CLIENTE     "
	String "   REGISTADO    "
	String "      COM       "
	String "   SUCESSO!     "
	String "                "
Place 2880H	
MenuPagamento:
	String "   PAGAMENTO:   "
	String "                "
	String " VALOR GASTO:   "
	String "                "
	String " DESCONTO:      "
	String "                "
	String "                "

;««««««««««««««««««««««««««««««««««««
;	INICIO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
Place 0000H
Inicio:
	MOV R0, Prinpicio
	JMP R0	
	
Place 4000H
Prinpicio:
	MOV SP, StackPointer
	CALL LimpaPerifericos
	CALL RotinaPizzaria ;APRESENTA DESDE INICIO O MENU PRINCIPAL PIZZARIA
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA PIZZARIA
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaPizzaria:	
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	CALL LimpaPerifericos
	MOV R2, MenuPizzaria ;MOSTRA MENU
	CALL MostraDisplay
pizzaria_Le_ok:
	MOV R0, Ok
	MOVB R1,[R0]
	CMP R1, 0
	JEQ pizzaria_Le_ok ;CICLO ATÉ O OK PASSAR A '1'
	MOV R2, NR_SEL
	MOVB R3, [R2]
	CMP R3, MLogin ;OPCAO = OPÇÃO DE LOGIN?
	JEQ ChamaRotinaLogin ;ESCOLHIDA A OPÇÃO DE LOGIN 
	CMP R3, MRegistar ;OPCAO = OPÇÃO DE REGISTO?
	JEQ ChamaRotinaRegisto ;ESCOLHIDA A OPÇÃO DE REGISTO 
	MOV R2, MenuErro ;NENHUMA OPÇÃO ESCOLHIDA
	CALL RotinaErro ;ERRO
ChamaRotinaRegisto: 
	CALL RotinaRegisto
ChamaRotinaLogin:
	CALL RotinaLogin
	
	POP R3
	POP R2
	POP R1
	POP R0
	RET
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA DE MENU CLIENTE
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»	
RotinaCliente:
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R4
	CALL LimpaPerifericos
	MOV R2, MenuCliente
	CALL MostraDisplay
cliente_Le_ok: 
	MOV R0, Ok
	MOVB R1,[R0]
	CMP R1, 0
	JEQ cliente_Le_ok ;CICLO ATÉ O OK PASSAR A '1'
	MOV R3, NR_SEL
	MOVB R4, [R3]
	CMP R4, OCliente_pizza ;OPCAO = OPÇÃO DE PIZZAS?
	JEQ ChamaRotinaPizzas
	CMP R4, OCliente_sair ;OPCAO = OPÇÃO DE LOGOUT?
	JEQ ChamaRotinaPizzaria
	MOV R2, MenuErro
	CALL RotinaErro
ChamaRotinaPizzas:
	CALL RotinaPizzas
ChamaRotinaPizzaria:
	CALL RotinaPizzaria
	POP R4
	POP R3
	POP R2
	POP R1
	POP R0
	RET
;««««««««««««««««««««««««««««««««««««
;	ROTINA DE MENU DE PIZZAS
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaPizzas: 
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R4
	CALL LimpaPerifericos
	MOV R2, MenuPizzas
	CALL MostraDisplay
pizzas_Le_ok:
	MOV R0, Ok
	MOVB R1, [R0]
	CMP R1, 0
	JEQ pizzas_Le_ok ;CICLO ATÉ O OK PASSAR A '1'
	
	MOV R3, NR_SEL
	MOVB R4, [R3]
	CMP R4, 0
	JEQ PizzaCompradaErro ;OPCAO = 0, ERRO
	CMP R4, 5
	JLE RotinaPizzaEscolhida ;OPCAO = UMA DAS CINCO PIZZAS (1 - 5)
	
PizzaCompradaErro:
	MOV R2, MenuErro
	CALL RotinaErro
		
RotinaPizzaEscolhida: 
	CALL RotinaTamanho
	
	POP R4
	POP R3
	POP R2
	POP R1
	POP R0
	RET

;««««««««««««««««««««««««««««««««««««
;	ROTINA DE TAMANHO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaTamanho: 	
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R4
	CALL LimpaPerifericos
	MOV R2, MenuTamanho
	CALL MostraDisplay
tamanho_Le_ok:
	MOV R0, Ok
	MOVB R1, [R0]
	CMP R1, 0
	JEQ tamanho_Le_ok ;CICLO ATÉ O OK PASSAR A '1'
	
	MOV R3, NR_SEL
	MOVB R4, [R3]
	CMP R4, OTamanho_peq 
	JEQ PizzaComprada ;TAMANHO = PEQUENA
	CMP R4, OTamanho_grande
	JEQ PizzaComprada ;TAMANHO = GRANDE
	MOV R2, MenuErro
	CALL RotinaErro
	
PizzaComprada:
	CALL RotinaPagamento
	
	POP R4
	POP R3
	POP R2
	POP R1
	POP R0
	RET
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA DE PAGAMENTO / APLICA DESCONTO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaPagamento: 
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R5
	PUSH R7
	;R4 - TAMANHO DA PIZZA
	;R6 - FICHA DO CLIENTE ATUAL
	MOV R3, bd_valor ;COLOCA EM R3 O INDICE DO VALOR NO HISTORICO DA BASE DE DADOS
	ADD R3, R6 ;COLOCA EM R3 O INDICE DO VALOR NO HISTORICO DA BASE DE DADOS DA FICHA DE CLIENTE PRETENDIDA
	MOV R7, valorDesconto
	CMP R4, OTamanho_peq
	JNE pizzagrande
	
pizzapequena: 
	MOV R5, 2 ;DESCONTO DA PIZZA PEQUENA
	ADD R3, 5
	CMP R3, R7
	JGE AplicaDesconto
	MOV R5, 0 ;NAO DESCONTA
	CALL RotinaMostraPagamento
	JMP fim_pag

AplicaDesconto:
	SUB R3, R7
	SUB R3, R5 ;DESCONTA
	CALL RotinaMostraPagamento
	JMP fim_pag
	
pizzagrande: 
	MOV R5, 4 ;DESCONTO DA PIZZA GRANDE
	ADD R3, 5
	CMP R3, R7
	JGE AplicaDesconto
	MOV R5, 0 ;NAO DESCONTA
	CALL RotinaMostraPagamento
	JMP fim_pag
	
fim_pag:
	POP R7
	POP R5
	POP R3
	POP R2
	POP R1
	POP R0
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA MOSTRA VALOR E MOSTRA DESCONTO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaMostraPagamento:
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R4
	PUSH R5
	PUSH R6
	;R5 - DESCONTO
	;R3 - VALOR GASTO
	CALL LimpaPerifericos ;LIMPA PERIFÉRICOS
	MOV R2, MenuPagamento ;COLOCA MENU DE LOGIN
	CALL MostraDisplay ;MOSTRA NO DISPLAY O MENU
	
	MOV R6, R3
	MOV R4, posicaoValorgasto
	CALL CONVERTE_NUM_CHAR
	
	MOV R6, R5
	MOV R4, posicaoDesconto
	CALL CONVERTE_NUM_CHAR
	
	MOV R0, Ok
	
ciclo_pagamento:
	MOVB R1, [R0]
	CMP R1, 1
	JNE ciclo_pagamento
	
	CALL RotinaCliente
	
	POP R6
	POP R5
	POP R4
	POP R2
	POP R1
	POP R0
	RET
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA CONVERTE (por corrigir)
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»	
CONVERTE_NUM_CHAR:
	;R6 - VALOR A CONVERTER
	;R4 - POSICAO A APRESENTAR 
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R5
	MOV R0, 10
	MOV R2, R4
	MOV R3, 0 ;CONTADOR = 0
	MOV R1, R6
	
PROXIMOCARACTER:
	MOV R4, R1
	MOD R4, R0 ;OBTEM O RESTO DA DIVISAO POR 10
	DIV R1, R0 ;OBTEM QUOCIENTE
	MOV R5, 48
	ADD R5, R4 ;OBTEM "RESTO+48"
	MOVB [R2], R5 ; COPIA ALGARISMO PARA DISPLAY
	ADD R3, 1 ;INCREMENTA O CONTADOR
	SUB R2, 1 ;DECREMENTA A POSIÇÃO
	CMP R1, 0 ;QUOCIENTE = 0?
	JNE PROXIMOCARACTER

FIM_ROTINA_CONVERTE:	
	POP R5
	POP R3
	POP R2
	POP R1
	POP R0
	RET
;««««««««««««««««««««««««««««««««««««
;	ROTINA DE LOGIN
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»	
RotinaLogin:
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R4
	PUSH R5
	PUSH R6
	PUSH R7
	CALL LimpaPerifericos ;LIMPA PERIFÉRICOS
	MOV R2, MenuLogin ;COLOCA MENU DE LOGIN
	CALL MostraDisplay ;MOSTRA NO DISPLAY O MENU

login_Le_ok:
	CALL RotinaUser ;COLOCA O USERNAME DO PERIFERICO NO DISPLAY CARACTER A CARACTER
	CALL RotinaPass ;COLOCA A PASSWORD DO PERIFERICO NO DISPLAY CARACTER A CARACTER, CONVERTENDO PARA '*'
	MOV R0, Ok
	MOVB R1, [R0]
	CMP R1, 0
	JEQ login_Le_ok ;CICLO ATÉ O OK PASSAR A '1'

VerificarUserLogin:
	MOV R1, BasedeDados ;INICIALIZA REGISTO DE BASE DA 1ª FICHA
	MOV R2, numClientes ;NÚMERO DE FICHAS DE UTILIZADORES DA PIZZARIA
	MOV R3, tam ;NÚMERO DE BYTES DE CADA FICHA DE UTILIZADOR
	MOV R4, Username ;USERNAME DO PERIFERICO
	MOV R7, Nr_Caracteres ;NUMERO DE CARACTERES A VERIFICAR
	MOV R6, BasedeDados ;CÓPIA DO REGISTO DE BASE DA 1ª FICHA
			
login_verifica_prox_caracter_user:
	MOVB R5, [R4] ;CARACTER DO USERNAME DO PERIFERICO
	MOVB R0, [R1] ;CARACTER DO USERNAME DA BASE DE DADOS DE DETERMINADA FICHA
	CMP R5, R0 ;COMPARA CARACTER DE AMBOS
	JNE login_procura_basededados_next ;PROXIMA FICHA DE CLIENTE
	ADD R4, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DO USERNAME DO PERIFERICO
	ADD R1, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DO USERNAME DA BASE DE DADOS DE DETERMINADA FICHA
	SUB R7, 1 ;MENOS UM CARACTER A VERIFICAR
	CMP R7, 0 ;CHEGOU AO FIM DO USERNAME (8 caracteres)
	JEQ VerificarPassLogin ;TODOS OS CARACTERES IGUAIS, USERNAME EXISTE, VERIFICA A PASS
	JMP login_verifica_prox_caracter_user ;CICLO PARA VERIFICAR CARACTER A CARACTER
		
login_procura_basededados_next: 
	ADD R6, R3 ;PASSA PARA A PROXIMA FICHA DE CLIENTE
	MOV R1, R6 ;COLOCA A APONTAR PARA A PROXIMA FICHA DE CLIENTE
	MOV R7, Nr_Caracteres ;REPOE NUMERO DE CARACTERES A VERIFICAR
	
	MOV R4, Username ;USERNAME DO PERIFERICO
	SUB R2, 1 ;MENOS UM CLIENTE A VERIFICAR
	CMP R2, 0 ;CHEGOU AO FIM DOS CLIENTES?
	JNE login_verifica_prox_caracter_user ;NAO, PASSA VOLTA A COMPARAR OS CARACTERES
		
	MOV R2, MenuUserErrado ;SIM, CHEGOU AO FIM E NAO ENCONTROU ESSE USERNAME
	CALL RotinaErro ;ERRO E MOSTRA MENSAGEM DE USERNAME INVALIDO

VerificarPassLogin:
	MOV R1, Password ;VOLTA A COLOCAR A APONTAR PARA O INICIO DA PASSWORD DO PERIFERICO
	MOV R3, bd_pass ;COLOCA EM R3 O INDICE DA PASSWORD DA BASE DE DADOS
	ADD R3, R6 ;COLOCA EM R3 O INDICE DA PASSWORD DA BASE DE DADOS DA FICHA DE CLIENTE PRETENDIDA
	MOV R7, Nr_Caracteres ;REPOE NUMERO DE CARACTERES A VERIFICAR
		
login_verifica_prox_caracter_pass:
	MOVB R0, [R1] ;CARACTER DA PASS DO PERIFERICO
	MOVB R4, [R3] ;CARACTER DA PASSWORD DA BASE DE DADOS DE DETERMINADA FICHA
	CMP R4, R0 ;COMPARA CARACTER DE AMBOS
	JNE login_pass_errada;PASSWORD ERRADA
	ADD R1, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DA PASSWORD DO PERIFERICO
	ADD R3, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DA PASSWORD DA BASE DE DADOS DE DETERMINADA FICHA
	SUB R7, 1 ;MENOS UM CARACTER A VERIFICAR
	CMP R7, 0 ;CHEGOU AO FIM DA PASSWORD (8 caracteres)
	JEQ ChamaRotinaCliente ;TODOS OS CARACTERES IGUAIS, PASSWORD CORRETA
	JMP login_verifica_prox_caracter_pass ;CICLO PARA VERIFICAR CARACTER A CARACTER

login_pass_errada:
	MOV R2, MenuPassErrada
	CALL RotinaErro	;MOSTRA MENSAGEM DE PASS ERRADA
	
ChamaRotinaCliente:		
	CALL RotinaCliente

	POP R7
	POP R6
	POP R5
	POP R4
	POP R3
	POP R2
	POP R1
	POP R0
	RET

;««««««««««««««««««««««««««««««««««««
;	ROTINA REGISTO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaRegisto:
	CALL LimpaPerifericos ;LIMPA PERIFERICOS
	MOV R2, MenuRegisto
	CALL MostraDisplay ;MOSTRA MENU DE REGISTO
	registo_Le_ok:
		CALL RotinaUser ;COLOCA O USERNAME DO PERIFERICO NO DISPLAY CARACTER A CARACTER
		CALL RotinaPass ;COLOCA A PASSWORD DO PERIFERICO NO DISPLAY CARACTER A CARACTER, CONVERTENDO PARA '*'
		MOV R0, Ok
		MOVB R1, [R0]
		CMP R1, 0
		JEQ registo_Le_ok ;CICLO ATÉ O OK PASSAR A '1'

RotinaVerificarUserRegisto:
	MOV R1, BasedeDados ;INICIALIZA REGISTO DE BASE DA 1ª FICHA
	MOV R2, numClientes ;NÚMERO DE FICHAS DE UTILIZADORES DA PIZZARIA
	MOV R3, tam ;NÚMERO DE BYTES DE CADA FICHA DE UTILIZADOR
	MOV R4, Username ;USERNAME DO PERIFERICO
	MOV R7, Nr_Caracteres 
	MOV R6, R1 ;COPIA DO REGISTO DE BASE DA 1ª FICHA
			
registo_verifica_prox_caracter_user:
	MOVB R5, [R4] ;CARACTER DO USERNAME DO PERIFERICO
	MOVB R0, [R1] ;CARACTER DO USERNAME DA BASE DE DADOS DE DETERMINADA FICHA
	CMP R5, R0 ;COMPARA CARACTER DE AMBOS
	JNE registo_procura_basededados_next ;VERIFICA PROXIMO CLIENTE
	ADD R4, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DO USERNAME DO PERIFERICO
	ADD R1, 1 ;PASSA A APONTAR PARA O ENDEREÇO DO PROXIMO CARACTER DO USERNAME DA BASE DE DADOS DE DETERMINADA FICHA
	SUB R7, 1 ;MENOS UM CARACTER A VERIFICAR
	CMP R7, 0
	JEQ registo_user_em_uso ;USERNAME TOTALMENTE IGUAL A BASE DE DADOS, LOGO ESTA EM USO
	JMP registo_verifica_prox_caracter_user ;CICLO PARA VERIFICAR SE HA UM USERNAME IGUAL
	
registo_user_em_uso:
	MOV R2, MenuUserEmUso
	CALL RotinaErro ;COLOCA NO DISPLAY A MENSAGEM DE UTILIZADOR EM USO

	
registo_procura_basededados_next: 
	MOV R4, Username ;VOLTA A COLOCAR A APONTAR PARA O INICIO DO USERNAME DO PERIFERICO
	MOV R7, Nr_Caracteres ;REPOE
	ADD R6, R3 ;PROXIMA FICHA DA BASE DE DADOS
	MOV R1, R6 ;COLOCA EM R1 PARA AVALIAR EM CIMA
	SUB R2, 1 ;MENOS UM CLIENTE A VERIFICAR
	CMP R2, 0
	JNE registo_verifica_prox_caracter_user ;CICLO DE VERIFICAR CARACTER A CARACTER

;VERIFICA PASSWORD		
MOV R1, Password ;PASSWORD DO PERIFERICO
MOV R2, 0 ;CONTADOR DE CARACTERES
	
registo_verifica_prox_caracter_pass:
	MOVB R0, [R1] ;CARACTER DA PASSWORD DO PERIFERICO
	CMP R0, Terminador
	JEQ registo_pass_invalida
	ADD R2, 1 ;INCREMENTA CONTADOR DE CARACTERES
	ADD R1, 1 ;PASSA A APONTAR PARA O PROXIMO CARACTER
	CMP R2, 3 ;VERIFICA SE A PASSWORD TEM 3 CARACTERES
	JNE registo_verifica_prox_caracter_pass ;CICLO PARA VERIFICAR SE TEM PELO MENOS 3 CARACTERES
		
AdicionaBasedeDados:
	MOV R1, Username ;VOLTA A COLOCAR A APONTAR PARA O INICIO DO USERNAME DO PERIFERICO
	MOV R3, BasedeDados ;COLOCA NOVAMENTE NO INICIO DA BASE DE DADOS
	MOV R7, BasedeDados ;COPIA DO INICIO DA BASE DE DADOS
	MOV R6, tam ;TAMANHO DE CADA FICHA
	
proxima_ficha_basededados:
	MOVB R5, [R3] 
	CMP R5, Terminador ;VERIFICA SE ESTA FICHA NAO ESTA OCUPADA
	JEQ add_prox_caracter_user ;ESTÁ LIVRE, PODE PREENCHER
	ADD R3, R6 ;PASSA PARA A PROXIMA FICHA
	ADD R7, R6 ;COPIA PARA USAR NO REGISTO
	JMP proxima_ficha_basededados
	
add_prox_caracter_user:
	MOVB R0, [R1]
	CMP R0, Terminador ;VERIFICA SE O USERNAME ACABOU
	JEQ AdicionaPassBasedeDados ;SE ACABOU O USERNAME, PASSA PARA A PASSWORD
	MOVB [R3], R0 ;COLOCA O PRIMEIRO CARACTER NA BASE DE DADOS
	ADD R1, 1 ;PASSA AO PROXIMO CARACTER DO PERIFERICO
	ADD R3, 1 ;PASSA A PROXIMA POSIÇÃO DA BASE DE DADOS
	JMP add_prox_caracter_user

registo_pass_invalida:
	MOV R2, MenuPassErrada ;PASSWORD INVALIDA
	CALL RotinaErro  ;APRESENTA MENSAGEM DE PASSWORD INVALIDA

AdicionaPassBasedeDados:
	MOV R1, Password ;VOLTA A COLOCAR A APONTAR PARA O INICIO DA PASSWORD DO PERIFERICO
	MOV R3, bd_pass ;COLOCA EM R3 O INDICE DA PASSWORD DA BASE DE DADOS
	ADD R3, R7 ;COLOCA EM R3 O INDICE DA PASSWORD DA BASE DE DADOS DA FICHA DE CLIENTE PRETENDIDA
	
	add_prox_caracter_pass:
		MOVB R0, [R1]
		CMP R0, Terminador ;VERIFICA SE A PASS ACABOU
		JEQ AdicionaSucess ;SE ACABOU A PASS, MENSAGEM DE SUCESSO
		MOVB [R3], R0 ;COLOCA O PRIMEIRO CARACTER DA PASS NA BASE DE DADOS
		ADD R1, 1 ;PASSA AO PROXIMO CARACTER DA PASS
		ADD R3, 1 ;PASSA A PROXIMA POSIÇÃO DA PASS DA BASE DE DADOS
		JMP add_prox_caracter_pass ;CICLO DE INTRODUZIR A PASSWORD NA BASE DE DADOS

AdicionaSucess:
	Call RotinaRegistoSucesso

;««««««««««««««««««««««««««««««««««««
;	ROTINA MOSTRA USERNAME NO DISPLAY
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»		
RotinaUser:
	PUSH R0
	PUSH R1
	PUSH R2
	MOV R1, Username
	MOV R2, UserNoDisplay
	registo_prox_caracter_user:
		MOVB R0, [R1]
		CMP R0, Terminador
		JEQ registo_acaba_user
		MOVB [R2], R0 ;coloca no display
		ADD R1, 1 ;passa a apontar para o endereço do proximo caracter
		ADD R2, 1 ;passa a apontar para onde por o proximo caracter
		JMP registo_prox_caracter_user
	registo_acaba_user:
	POP R2
	POP R1
	POP R0
	RET	
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA MOSTRA PASSWORD NO DISPLAY COMO '*'
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»	
RotinaPass:
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	MOV R1, Password
	MOV R2, PassNoDisplay
	registo_prox_caracter_pass:
		MOVB R0, [R1]
		CMP R0, Terminador
		JEQ registo_acaba_pass
		MOV R3, CaracterAsterisco
		MOVB [R2], R3 ;coloca no display o *
		ADD R1, 1 ;passa a apontar para o endereço do proximo caracter
		ADD R2, 1 ;passa a apontar para onde por o proximo caracter
		JMP registo_prox_caracter_pass
	registo_acaba_pass:
	POP R3
	POP R2
	POP R1
	POP R0
	RET	
	
;««««««««««««««««««««««««««««««««««««
;	ROTINA MOSTRA DISPLAY
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
MostraDisplay:
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	MOV R0, Display
	MOV R1, DisplayEnd
Ciclo:
	MOV R3, [R2]
	MOV [R0], R3
	ADD R0, 2
	ADD R2, 2
	CMP R0, R1
	JLE Ciclo
	POP R3
	POP R2
	POP R1
	POP R0
	RET
;««««««««««««««««««««««««««««««««««««
;	ROTINA LIMPA PERIFÉRICOS
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
LimpaPerifericos: 
	PUSH R0
	PUSH R1
	PUSH R2
	PUSH R3
	PUSH R4
	PUSH R5
	MOV R0, Username
	MOV R1, Password
	MOV R2, NR_SEL
	MOV R3, Ok
	MOV R4, 0
	MOV R5, Nr_Caracteres
limpa_proximo:	
	MOVB [R0], R4
	MOVB [R1], R4
	SUB R5, 1
	ADD R0, 1
	ADD R1, 1
	CMP R5, 0
	JNE limpa_proximo ;CICLO PARA LIMPAR USERNAME E PASSWORD
	
	MOVB [R2], R4
	MOVB [R3], R4
	POP R5
	POP R4
	POP R3
	POP R2
	POP R1
	POP R0
	RET
;««««««««««««««««««««««««««««««««««««
;	ROTINA LIMPA DISPLAY
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
LimpaDisplay:
	PUSH R0
	PUSH R1
	PUSH R2
	MOV R0, Display
	MOV R1, DisplayEnd
	MOV R2, CaracterVazio
CicloLimpa:
	MOVB [R0], R2
	ADD R0, 1
	CMP R0, R1
	JLE CicloLimpa
	POP R2
	POP R1
	POP R0
	RET
;««««««««««««««««««««««««««««««««««««
;	ROTINA ERRO OPCAO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaErro:
	PUSH R0
	PUSH R1
	PUSH R2
	CALL MostraDisplay
	CALL LimpaPerifericos
	MOV R0, Ok
ERRO:
	MOVB R1, [R0]
	CMP R1, 1
	JNE ERRO
	POP R2
	POP R1
	POP R0
	JMP Prinpicio
	RET	
;««««««««««««««««««««««««««««««««««««
;	REGISTO SUCESSO
;»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
RotinaRegistoSucesso:
	PUSH R0
	PUSH R1
	PUSH R2
	MOV R2, MenuUserRegistado
	CALL MostraDisplay
	CALL LimpaPerifericos
	MOV R0, Ok
SUCESSO:
	MOVB R1, [R0]
	CMP R1, 1
	JNE SUCESSO
	POP R2
	POP R1
	POP R0
	JMP RotinaCliente
	RET	