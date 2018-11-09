#include<reg51.h>
#include <stdio.h>
#include <string.h>

void uart_init();				//Initialize UART
void timer_init(); 			// Timer 2 in mode 2
void uart_tx(char x);		//Transmission function
char uart_rx();					//Receiving function
void uart_msg(char *p);   			//String transmission
void newLine();
void wait4Letter(char x);
void startTimer();
//void endTimer();

int overFlows = 0x0000;

void Timer0_ISR(void) interrupt 1 {
	TR0 = 0;
	//uart_msg("OverFlow Detected");
	overFlows ++;
	TF0 = 0;
	TR0 = 1;
	
}

void main(void){
	
	unsigned char x ;
	bit test = 0;  // for now it's zero, but later on it will be from an input pin
	bit user = 0 ; // for now it's user zero
	
	uart_init();
	
	startTimer();
	wait4Letter('a');
	//endTimer();
	
	while(1){
			if(!test){
			
				// CODE FOR TRAINING 
			}
			
			if(test){
			
				// CODE FOR TESTING
			}
		
		
	}
}

void wait4Letter(char x){

	while(1){
		char y = uart_rx();
		uart_tx(y);
			
		if(y == x){
			uart_msg("recieved");
			uart_tx(x);
			return;
		}
		else{
			uart_msg("Wrong character !");
		}
	}
}

void startTimer(){
	TH0 = 0x00;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void uart_init(){
	 SCON = 0x50;
	 timer_init();
}

void timer_init(){
	TMOD = 0x22;
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
