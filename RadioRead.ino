/*	Funções disponíveis:

- RadioControl(int _numChannels, int* _pins, Callback* _callbacks)
	* Construtor da classe 'RadioControl'
		> Seta os pinos e os callbacks

- begin()
	> Seta os pinos como entrada
	> Configura as interrupções dos pinos

- getTimeChannel(int _channel)
	> Retorna último valor lido no canal informado

- readChannel(int _channel, int _value)
	> Realiza os cálculos para leitura do canal
	> '_value' é o sinal lido no momento da interrupção (HIGH ou LOW) [não aconselhável utilizar digitalRead()]
*/


// --- Exemplo de leitura de rádio controle utilizando o Arduino DUE --- //

#include "RadioControl.h"

//
//	RADIO CONTROL CONFIG
//
#define NUM_CHANNELS 5							// Quantidade de canais
#define RC_PIO_CH1	PIOC 						// PORT's dos pinos
#define RC_PIO_CH2	PIOC
#define RC_PIO_CH3	PIOC
#define RC_PIO_CH4	PIOC
#define RC_PIO_CH5	PIOC
int RC_pins[NUM_CHANNELS] = {5, 6, 7, 8, 9};	// Vetor de pinos (Pinos devem ser habilitados para modo de interrupção externa)

Callback RC_callbacks[NUM_CHANNELS] = {			// Vetor de Callbacks
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5
};


RadioControl radio(NUM_CHANNELS, RC_pins, RC_callbacks);	// Instância do 'RadioControl'

void setup() {

	Serial.begin(9600);

	radio.begin();
}

void loop() {
	Serial.print("CH1");	Serial.print(radio.getTimeChannel(CH_1));	Serial.print("\t");
	Serial.print("CH2");	Serial.print(radio.getTimeChannel(CH_2));	Serial.print("\t");
	Serial.print("CH3");	Serial.print(radio.getTimeChannel(CH_3));	Serial.print("\t");
	Serial.print("CH4");	Serial.print(radio.getTimeChannel(CH_4));	Serial.print("\t");
	Serial.print("CH5");	Serial.print(radio.getTimeChannel(CH_5));	Serial.print("\n");
}

// 
// Callbacks
// 
void CHANNEL_1(){	radio.readChannel(CH_1, bitRead(RC_PIO_CH1->PIO_PDSR, RC_pins[CH_1]));	}
void CHANNEL_2(){	radio.readChannel(CH_2, bitRead(RC_PIO_CH2->PIO_PDSR, RC_pins[CH_2]));	}
void CHANNEL_3(){	radio.readChannel(CH_3, bitRead(RC_PIO_CH3->PIO_PDSR, RC_pins[CH_3]));	}
void CHANNEL_4(){	radio.readChannel(CH_4, bitRead(RC_PIO_CH4->PIO_PDSR, RC_pins[CH_4]));	}
void CHANNEL_5(){	radio.readChannel(CH_5, bitRead(RC_PIO_CH5->PIO_PDSR, RC_pins[CH_5]));	}