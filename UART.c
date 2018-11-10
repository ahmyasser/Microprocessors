#include<reg51.h>
#include <stdio.h>
#include <string.h>

void uart_init();				//Initialize UART
void timer_init(); 			// Timer 2 in mode 2
void uart_tx(char x);		//Transmission function
char* toString(int integer);
char uart_rx();					//Receiving function
void uart_msg(char *p);   			//String transmission
void newLine();
void  startTimer();		//to start timer 
void Timer0_ISR(void); //the timer handling 
void wait4Letter(char x); //handling reciving the values
void stopTimer();  // to stop the timer

int totalTime= 0 ;			//incremented everytime the timer does overflow
bit receive = 1 ;				//true if the value received is right

void main(void){	
	//unsigned char y ;
	unsigned char i;
	bit test = 0;  // for now it's zero, but later on it will be from an input pin
	bit user = 0;   //for now it's zero, but later on it will be from an input pin
	unsigned char user1 ;
	unsigned char user2 ;	
	unsigned int times1[7] ; //store times for user 1
	unsigned int times2[7] ;//store times for user 2
	unsigned char testingTimes[7]; //store testing time
	unsigned char password  [7] = "aaaaaaa";  //to store the password
	
	uart_init();

				
				// CODE FOR TRAINING

		for(i = 0 ; (i < sizeof(password)/sizeof(password[i]) && receive) ;i++){		
			startTimer();
			wait4Letter(password[i]);
	    if(!test)
			{						
				if(user)
				{
						times1[i]= totalTime ;
				}
				else
				{
						times2[i]= totalTime ;
				}
			}				
			
			// CODE FOR TESTING
			else{
					
					testingTimes[i] = totalTime ;
			}
				stopTimer();					
			uart_msg(toString(times2[i]));
	}
		if(test)
		{
			if ((testingTimes[i] - times2[i]) > (testingTimes[i] - times1[i]))
			{
					user1++	;				
			}
			else
			{	
				user2++ ;
			}	
			user= user2 > user1 ;
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


void startTimer(){
	TH0 = 0x00;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void stopTimer(){
	TR0 = 0;
	ET0 = 0;
	EA = 0;
	TH0 = 0x00;
	totalTime=0;
}

void Timer0_ISR(void) interrupt 1 {
	TR0 = 0;
	//uart_msg("OverFlow Detected");
	totalTime ++;
	TF0 = 0;
	TR0 = 1;
	
}


void uart_tx(char x){
	SBUF = x;
	
	while(!TI);
	
	TI = 0;
}

char* toString(int temp){
	int new_value[8]; 
	char buf_temp[8];
	int x;
	for ( x = 0; x < 8; x++) { 
		new_value[7-x] = temp % 10;
		temp = temp / 10;
	  buf_temp[7-x] = new_value[7-x] +48; 
	}	
	return buf_temp ;

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
			receive = 0 ; 
		}
	}
}
