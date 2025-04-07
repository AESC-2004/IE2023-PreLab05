/*
 * IE2023-Prelab05.c
 *
 * Created: 05/04/2025 04:19:13 p. m.
 * Author : ang50
 */ 

/*********************************************************************************************************************************************/
// Encabezado (Libraries)
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "32u4tims16b.h"
#include "32u4adc.h"

// Variables y constantes
// TIMERS

// ADC
uint16_t ADC_VALUE		= 0;

/*********************************************************************************************************************************************/
// Function prototypes
void SETUP();

/*********************************************************************************************************************************************/
// Main Function
int main(void)
{
	SETUP();
	
	while (1)
	{
		
	}
}

/*********************************************************************************************************************************************/
// NON-Interrupt subroutines
void SETUP()
{
	// Desactivamos interrupciones
	cli();
	// Desactivamos UART1
	UCSR1B			= 0x00;  
	// Ajustamos el Prescaler global para F_CPU = 1MHz
	CLKPR			= (1 << CLKPCE);
	CLKPR			= (0 << CLKPCE) | (0 << CLKPS3) | (1 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
	// Algunas funciones de inicio		 
	tim_16b_init(TIM_16b_NUM_1, 
				 TIM_16b_CHANNEL_A, 
				 TIM_16b_PRESCALE_1, 
				 TIM_16b_MODE_PHASE_CORRECT_PWM_ICRn, 
				 10000,
				 TIM_16b_COM_NON_INVERT_OCnx,
				 0,
				 TIM_16b_OCnx_ENABLE);			 
	tim_16b_ocr_value(TIM_16b_NUM_1, TIM_16b_CHANNEL_A, 750);	//Empezamos con 1.5ms	 
	sei();
}

/*********************************************************************************************************************************************/
// Interrupt routines
ISR(TIMER0_OVF_vect)
{
}

ISR(ADC_vect)
{
}

ISR(TIMER1_OVF_vect)
{
}


