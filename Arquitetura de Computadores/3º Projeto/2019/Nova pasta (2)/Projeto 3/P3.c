#include <reg51.h>
#define fimTempo 100 //timer = 0.2ms -> fimTempo=100*0.2ms=20ms
#define frequencia 50 //timer = 0.2ms -> frequencia=50*0.2ms=10ms
#define atraso 25 //50*20ms = 1s

bit botao 	= 0; //pino do botão
bit ligar 	= 0;

sbit luz 		= P1^0; //pino de controlo do luz motor
sbit S1 		= P1^1;
sbit S2 		= P3^2;
bit trinco 	= 0;
bit trinco2 = 0;

//sbit MICRO 	= P3^3;
bit palma = 0;

unsigned char palmas = 0;
unsigned char conta2 = 0;
unsigned char conta3 = 0;
unsigned char conta = 0; //contador que incrementa a cada 200us
unsigned char conta_intensidade = 0;
unsigned char referencia = 50; //o luz motor começa nos 0º
//declaração de funções
void Init(void);

void Init(void)
{
//Configuracao Registo IE
EA = 1; //ativa interrupcoes globais
ET0 = 1; // ativa interrupcao timer 0
EX1 = 1; // ativa interrupcao externa 0
//Configuracao Registo TMOD
TMOD &= 0xF0; //limpa os 4 bits do timer 0 (8 bits – auto reload)
TMOD |= 0x02; //modo 2 do timer 0
//Configuracao Timer 0
TH0 = 0x38; //Timer 0 - 200us
TL0 = 0x38;
//Configuracao Registo TCON
TR0 = 1; //comeca o timer 0
IT1 = 1; //interrupcao externa activa a falling edge
}

//interrupcao externa
void External0_ISR(void) interrupt 2
{
	palma = 1;
}
//interrupcao tempo
void Timer0_ISR(void) interrupt 1
{
	conta++; //incrementa a cada contagem de 200us
	conta3++;
	if(ligar == 1)	conta_intensidade++;
}

void main(void) {
//inicializações
Init();
luz = 0;
while(1) //loop infinito
{
	
	if(S1 == 0 ){
	if(trinco == 0){ // btn carrega a 0
			luz = ~luz;
			trinco = 1;
		
			if (luz == 1)	{
				conta_intensidade = 0;
				ligar = 1;
			} else ligar = 0;
		}}else{
	
	if(S1 == 1) {
		if(trinco == 1){
		trinco = 0;
	}}}
	
	if(conta == fimTempo){
		conta = 0;
		conta2++;
	}

	if(palma == 1) {
		if(palmas == 0){
		
		
		}
		if((conta3 >= 25 && conta2 <= atraso)){
			palmas++;
			conta3 = 0;
		}else{
			conta2 = 0;
			conta3 = 0;
			palmas = 0;
		}
		palma = 0;
	} 
	if(palmas == 2){
		if(luz == 0){
			luz = 1;
			ligar = 1;
		}
		else {
			luz = 0;
			ligar = 0;
		}
		palmas = 0;
	}	
	
	
	if(S2 == 0 && trinco2 == 0) {
		if(referencia > 10){
			referencia = referencia - 10;
		} else referencia = 50;
		trinco2 = 1;
	} else if ((S2 == 1 && trinco2 == 1)) trinco2 = 0;

	
 if(ligar == 1){
		if(conta_intensidade > referencia && conta_intensidade < frequencia){
			luz = 0;
		}else if (conta_intensidade >= frequencia ){
			conta_intensidade = 0;
			luz = 1;
			} else luz = 1;
	}

}	
}