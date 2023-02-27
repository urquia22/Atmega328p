
#define F_CPU 16000000UL

#include <avr/io.h>                 //Declaramos Librerias a utiizar
#include <util/delay.h>
#include <stdio.h>

#include "DEF_ATMEGA328P.h"        //Atmega328p
#include "LCD.h"                   //Libreria de control del LCD



int main(void)                       
{
	
	
	LCD_init();               // inicializamos el lcd

	 
 
		
			LCD_clear();                     // borramos el LCD
		        LCD_printf("   Hola Mundo   ");    							                        
			LCD_segunda_linea();             // a partir de la segunda linea.
			LCD_printf(" *RoboticaEdu*  ");     
				

}

