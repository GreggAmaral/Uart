#include "mini_uart.h"
#include <stddef.h> 						// Include de lib para usar tipo size_t	
#include <stdint.h>
#include <stdio.h>

void *memset(void *s, int c, size_t n) {			//Criando funcao memset para nao usarmos lib padroes.
    unsigned char *p = s;
    while(n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

int count_gpio (int vetor[]){					// Verifica a quantidade de gpios ativas	
	int count = 0;
	for (int i = 0; i < 30; i++) {
        	if (vetor[i] != 0) {
        		count++;
        	}
    	}
	return count;
}

void kernel_main(void)
{
	uart_init();
	int GPIOs_ativas [30] = {0};				// Vetor de GPIOs ativas
								// Estado de todas as GPIOs |5 end|1 io|1 HL|1 Res|
	uint8_t GPIOs_s[30] = 	{0b00000000,			//GPIO 0
				0b00001000,			//GPIO 1
				0b00010000,			//GPIO 2
				0b00011000,			//GPIO 3
				0b00100000,			//GPIO 4
				0b00101000,			//GPIO 5
				0b00110000,			//GPIO 6
				0b00111000,			//GPIO 7
				0b01000000,			//GPIO 8
				0b01001000,			//GPIO 9
				0b01010000,			//GPIO 10
				0b01011000,			//GPIO 11		
				0b01100000,			//GPIO 12
				0b01101000,			//GPIO 13
				0b01110000,			//GPIO 14
				0b01111000,			//GPIO 15
				0b10000000,			//GPIO 16
				0b10001000,			//GPIO 17
				0b10010000,			//GPIO 18
				0b10011000,			//GPIO 19
				0b10100000,			//GPIO 20
				0b10101000,			//GPIO 21
				0b10110000,			//GPIO 22
				0b10111000,			//GPIO 23
				0b11000000,			//GPIO 24
				0b11001000,			//GPIO 25
				0b11010000,			//GPIO 26
				0b11011000,			//GPIO 27
				0b11100000,			//GPIO 28
				0b11101000};			//GPIO 29
	while (1) {
		uart_send('S');					//bit de inicio de mensagem 
		uart_send((char)count_gpio(GPIOs_ativas));	//bit de numero de gpios ativas
		for (int i=0; i<30; i++){
			if (GPIOs_ativas[i]==1){
				uart_send((char)GPIOs_s[i]);	
			}
		}
		uart_send('E');					//bit de termino de mensagem
		for (int i=0; i<5000000; i++){}			//Timer rustico 
	}
}


