#include<reg51.h>
#include <stdio.h>
#include <string.h>

void uart_init();				//Initialize UART
void timer_init(); 			// Timer 2 in mode 2
void uart_tx(char x);		//Transmission function
char uart_rx();					//Receiving function
void uart_msg(char *p);   			//String transmission
void newLine();

void main(void){
	
	bit test = 0;  // for now it's zero, but later on it will be from an input pin
	
	while(1){
			
			if(!test){
			
				// CODE FOR TRAINING 
			}
			
			if(test){
			
				// CODE FOR TESTING
			}
		
		
	}
}

void uart_init(){
	 SCON = 0x50;
	 timer_init();
}

void timer_init(){
	
	TMOD = 0x20;
	TH1 = 0xFD;
	TR1 = 1;
}

void uart_tx(char x){
	SBUF = x;
	
	while(!TI);
	
	TI = 0;
}

char uart_rx(){
	char x;
	//REN = 1;
	while(!RI);
	x = SBUF;
	RI = 0;
	return x;
}

void uart_msg(char *p){
	
	while(*p != 0){
		uart_tx(*p);
		p++;
	}
}

void newLine(){
	uart_tx(0x0D);
}
