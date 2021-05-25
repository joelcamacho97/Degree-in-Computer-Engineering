fimTempo EQU 0x64 //timer = 0.2ms -> fimTempo=100*0.2ms=20ms
zero EQU 3 //3*0.2ms=0.6ms -> 0║
centoOitenta EQU 12 //12*0.2=2.4ms -> 180║
atraso EQU 0x0D //13*20ms = 0.260s ~1/4 de segundo

sensorLuz EQU P3.2; //pino de controlo do sensor
servo EQU P1.0; //pino de controlo do servo motor
led EQU P1.1; //pino do led

conta EQU 0; //contador que incrementa a cada 200us
conta2 EQU 0; //tempo de espera entre mudanчa de angulos
referencia EQU 3; //o servo motor comeчa nos 0║

atualiza EQU 1;

luzdetetada EQU 0; //o servo motor comeчa nos 0║

TempoL EQU 0x37 ; Valor do byte menos significativo para o temporizador
TempoH EQU 0x37 ; Valor do byte mais significativo para o temporizador

;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл primeira instuчуo apєs reset do microcontrolador
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
CSEG AT 0000H
	JMP INICIO

;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл se ocorrer interrupчуo externa
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
CSEG AT 0013H
	JMP INTERRUP_EXT0
	
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл tratamento da interrupчуo de temporizaчуo 0, para contar 20ms
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
CSEG AT 000BH
	JMP INTERRUP_TEMP0

;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл inicio do programa
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
CSEG AT 0050H ;coloca as instruчїes a partir do endereчo 50h
INICIO:
	MOV SP, #7 ;endereчo da stackpointer
	CALL INIT ;chama rotina de inicializaчїes
	
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл programa principal
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
PRINCIPAL:
	;if(conta == referencia)
	MOV A, referencia
	MOV B, R0
	CJNE A, B, segundo_if
		CLR servo
	
segundo_if:
	;if(conta == fimTempo)
	MOV A, R0
	MOV B, R2
	CJNE A, B, terceiro_if
		CLR A
		MOV R0, A
		SETB servo
		MOV A, R1
		INC A
		MOV R1, A

	terceiro_if:		;if(conta2 == atraso)
		MOV A, R1
		MOV B, R4
		CJNE A, B, PRINCIPAL
		
			MOV A, R5
			CJNE A, #01H, sub_else
				JNB sensorluz, fim_sub
					MOV R5, #00H
					SETB led
					JMP fim_sub
		sub_else:
			MOV A, referencia
			MOV B, centoOitenta
			CJNE A, B, compZero
				MOV atualiza, #02H
		compZero:
			MOV A, zero
			MOV B, referencia
			CJNE A, B, atual
				MOV atualiza, #01H
			
		atual:
			MOV A, atualiza
			CJNE A, #01H, sub_atual
				MOV A, referencia
				INC A
				MOV referencia, A
			JMP fim_sub
		sub_atual:
			MOV A, referencia
			DEC A
			MOV referencia, A
fim_sub:
	MOV A, R1
	CLR A
	MOV R1, A
	JMP PRINCIPAL
	
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл Rotina de inicializaчїes
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
INIT:
	MOV IE, #10000011b ; activa as interrupчїes globais, timer 0 e externa 0
	MOV TMOD, #00000010b ; Activa temporizador no modo 2, contador com registo de 8-bit (TL0) com auto reload
	;configuraчуo timer 200us
	MOV TL0, #TempoL ; Valor do byte menos significativo
	MOV TH0, #TempoH ; Valor do byte mais significativo
	;Configuracao Registo TCON
	SETB TR0 ; Activa o temporizador 0
	SETB IT0 ; A interrupчуo externa vai ser detectada na transiчуo descendente (0->1)
	
	MOV R0, #conta ;R0 - timer
	MOV R1, #conta2 ;R1 - conta2
	MOV R2, #fimTempo ;R1 - conta2
	MOV R4, #atraso
	MOV R5, #luzdetetada
	SETB led ;led desligado
	
	RET
	
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл tratamento interrupчуo externa
;ллллллллллллллллллллллллллллллллллллллллллллллллллл
INTERRUP_EXT0:
	MOV R5, #01H
	CLR led ;liga led
	RETI

	;ллллллллллллллллллллллллллллллллллллллллллллллллллл
;лл tratamento interrupчуo do timer0
;ллллллллллллллллллллллллллллллллллллллллллллллллллл	
INTERRUP_TEMP0:
	INC R0 ;incrementa a cada contagem de 200us
	RETI
	
END