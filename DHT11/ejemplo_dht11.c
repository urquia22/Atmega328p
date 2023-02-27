/*
Autor: Angel Urquia
Nov 2022
*/
#define F_CPU 16000000UL


#include <avr/io.h>                 //Declaramos Librerias a utiizar
#include <util/delay.h>
#include <stdio.h>

#include "DEF_ATMEGA328P.h"        //Atmega328p
#include "LCD.h"                   //Libreria de control del LCD
#include "DHT11.h"                 //Libreria de control del sensor DHT11


int main(void)                       
{
       
	DDRD |= 0b0111000;
	PORTD &= ~(0b0111000);
		

	float temperatura;        // Declaramos variable temperatura como float
	float humedad;            // Declaramos variable humedad como float
	
	uint8_t contador=200;     // Declaramos variable contador - "uint8_t" es un entero de 8 bits incluyendo signo
	
	LCD_init();               // inicializamos el lcd
	DHT11_init();             // inicializamos e sensor
	 
    while (1)                     // Ciclo de control "while" mientas 1 
    {	
		contador++;        // incrementa el coatdor en 1
		if(contador>=100){ //Para leer el DHT11 cada 100x10ms = 1000ms y no utilizar retardos bloqueantes de 2s
			contador=0;
			
			LCD_clear();                          // borramos el LCD
		        LCD_printf(" Temp. ");
			
			uint8_t status = DHT11_read(&temperatura, &humedad); // Creamos la variable "status" y guardamos la lectura del sensor
			if (status)    // si hay lectura
			{
			   
			   if(temperatura>40.00 & temperatura<=43.00)
			   {
			     PORTD |= (1<<PD3);		       //alto
			     PORTD &= ~(1<<PD4);		//bajo
			     PORTD &= ~(1<<PD5);		//bajo		   	
	                    
			   } else if(temperatura<=40.00 & temperatura>25.00) { 
			   
			     PORTD &= ~(1<<PD3);		//bajo	
			     PORTD &= ~(1<<PD5);		//bajo		
			     PORTD |= (1<<PD4);		       //alto	      				
			}else{
			     PORTD |= (1<<PD5);		       //alto
			     PORTD &= ~(1<<PD4);		//bajo
			     PORTD &= ~(1<<PD3);		//bajo
			}
				
			}      // Fin evaluación de "status"
			
			
		}else{
			_delay_ms(10);      // Retardo de 10 ms para complementar tiempo entre lecturas del sensor
			//Otras fuciones
		}     // cierre de la función que evalua valor del "contador>=100"		
    }
}

