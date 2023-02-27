/*
Nov 2022
Autor : Angel Urquia 
*/

#define DHT_DDR DDRB
#define DHT_PORT PORTB
#define DHT_PIN	PINB
#define PIN 2

void DHT11_init(void)
{
	DHT_DDR |= (1<<PIN);		//SE ESTABLECE PIN COMO SALIDA
	DHT_PORT |= (1<<PIN);		// SE PONE PIN COMO NIVEL ALTO
} 

/*   _______    18ms  ___40us____   80us     80us
	   |_________|          |__________|¯¯¯¯¯¯¯¯¯¯|..............datos................
	
	---------PUC-------------|----------DHT11-------------| La transferencia de datos comienza despues de lo anterior */					

uint8_t DHT11_read(float *dht_temperatura, float *dht_humedad)
{
	uint8_t bits[5];  //[11111100,11100000, 00000000, 00011111, 00011010] EJEMPLO
	uint8_t i,j=0;
	uint8_t contador = 0;
	
	
	DHT_PORT &= ~(1<<PIN);		// Colocamos PIN en Nivel bajo
	_delay_ms(18);                  // Esperamos 18 ms
	DHT_PORT |= (1<<PIN);		// Colocamos PIN Nivel alto
	DHT_DDR &= ~(1<<PIN);		//Pin como entrada
	
	
	contador = 0;
	while(DHT_PIN & (1<<PIN)) // Mientras PIN sea 1 ejecuta a continuación
	{
		_delay_us(2); //  Delay de 2 microsegundos
		contador += 2; // Incrementamos contador 
		if (contador > 60) // Si contador mayor que 60 ejecutamos la siguiente linea si no salto
		{
			DHT_DDR |= (1<<PIN);	//Pin como salida
			DHT_PORT |= (1<<PIN);	//PIN a Nivel alto
			return 0;
		}	
	}	
	
	
	contador = 0;
	while(!(DHT_PIN & (1<<PIN)))
	{
		_delay_us(2);
		contador += 2;
		if (contador > 100)
		{
			DHT_DDR |= (1<<PIN);	//Pin como salida
			DHT_PORT |= (1<<PIN);	//Nivel alto
			return 0;
		}	
	}
	
	
	contador = 0;
	while(DHT_PIN & (1<<PIN))
	{
		_delay_us(2);
		contador += 2;
		if (contador > 100)
		{
			DHT_DDR |= (1<<PIN);	//Pin como salida
			DHT_PORT |= (1<<PIN);	//Nivel alto
			return 0;
		}
	}
	
	
	for (j=0; j<5; j++)
	{
	uint8_t result=0;
		for (i=0; i<8; i++)
		{
			while (!(DHT_PIN & (1<<PIN)));
				_delay_us(35);

			if (DHT_PIN & (1<<PIN))
				result |= (1<<(7-i));
					
			while(DHT_PIN & (1<<PIN));
		}
		bits[j] = result;
	}

	DHT_DDR |= (1<<PIN);	//Colocamos PIN como salida
	DHT_PORT |= (1<<PIN);	//Hacemos PIN Nivel alto
	
				
	if ((uint8_t) (bits[0] + bits[1] + bits[2] +bits[3]) == bits[4])		//Pregunta por el chekin
	{
		uint8_t rawhumedad = bits[0]; //modificado // aqui se toma el primer byte 
		uint8_t rawtemperatura = bits[2]; // para dht11  aqui se toma el 3er byte
	
		
		if (rawtemperatura & 0x8000) // Operación and entre rawtemperatura y 1000000000000000
		{
	
			*dht_temperatura = (float)(rawtemperatura & 0x7fff)* -1.0; //Operación and entre rawtemperatura y 0111111111111111
		}else{
			
			*dht_temperatura = (float)(rawtemperatura);
		}

		*dht_humedad = (float)(rawhumedad);

		return 1;
	}
	return 1;
}
