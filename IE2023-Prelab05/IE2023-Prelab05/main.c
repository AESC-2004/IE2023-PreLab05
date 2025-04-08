/*
 * IE2023-Prelab05.c
 *
 * Created: 05/04/2025 04:19:13 p. m.
 * Author : ang50
 */ 

/*********************************************************************************************************************************************/
// Encabezado (Libraries)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "m32u4tims16b.h"

// Variables y constantes
// ADC
uint8_t ADC_MUX			= 1;

// Servo Motors
uint16_t SERVO1_READ		= 0;
uint16_t SERVO2_READ		= 0;

/*********************************************************************************************************************************************/
// Function prototypes
void SETUP();
//void PWM1init();
//void PWM3init();
void ADCinit();

/*********************************************************************************************************************************************/
// Main Function
int main(void)
{
	SETUP();
	
	while (1)
	{	
		OCR1A = 250 + ((uint32_t)SERVO1_READ * 1000) / 1023;
		OCR3A = 250 + ((uint32_t)SERVO2_READ * 1000) / 1023;
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
	//	Puertos
	DDRB			= (1 << DDB7);
	PORTB			= (1 << PORTB7);
	// Algunas funciones de inicio		 
	//PWM1init();
	//PWM3init();
	tim_16b_init(TIM_16b_NUM_1, TIM_16b_CHANNEL_A, TIM_16b_PRESCALE_1, TIM_16b_MODE_PHASE_CORRECT_PWM_ICRn, 10000, TIM_16b_COM_NON_INVERT_OCnx, 0, TIM_16b_OCnx_ENABLE);
	tim_16b_init(TIM_16b_NUM_3, TIM_16b_CHANNEL_A, TIM_16b_PRESCALE_1, TIM_16b_MODE_PHASE_CORRECT_PWM_ICRn, 10000, TIM_16b_COM_NON_INVERT_OCnx, 0, TIM_16b_OCnx_ENABLE);
	ADCinit();
	ADCSRA |= (1 << ADSC);
	sei();
}

/*
void PWM3init()
{
	
	// TIM3, CH_A, PS_1, COM_NON_INVERT, OC1A_ENABLE, MODE_PHASE_CORRECT_PWM_ICRn
	TCCR3A		= (1 << COM1A1) | (0 << COM1A0)| (0 << COM1B1) | (0 << COM1B0) | (0 << COM1C1) | (0 << COM1C0) | (1 << WGM11) | (0 << WGM10);
	TCCR3B		= (0 << ICNC1) | (0 << ICES1) | (1 << WGM13) | (0 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
	ICR3		= 10000;
	//OCR3A		= 1000;
}
*/

void ADCinit()
{
	// NO_Auto_Trigger, PS_8, ADC6 (Initial), AVCC_REF, ADC_INT_EN
	ADMUX		= (0 << REFS1) | (1 << REFS0)| (0 << ADLAR) | (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
	ADCSRB		= (0 << MUX5) | (0 << ADTS3) | (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);
	ADCSRA		= (1 << ADEN) | (0 << ADSC)| (0 << ADATE) | (0 << ADIF) | (1 << ADIE) | (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
/*********************************************************************************************************************************************/
// Interrupt routines

ISR(ADC_vect)
{
	// MUX needed
	if (ADC_MUX == 1)		// SERVO1 &	ADC6	------>		SERVO2 & ADC4
	{
		SERVO1_READ		= ADC;
		ADC_MUX			= 2;
		// ADC update to ADC4:
		ADMUX		=  (0 << REFS1) | (1 << REFS0)| (0 << ADLAR) | (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (0 << MUX1) | (0 << MUX0);
		ADCSRA |= (1 << ADSC);
	}
	else if (ADC_MUX == 2)	// SERVO2 &	ADC4	------>		SERVO1 & ADC6
	{
		SERVO2_READ		= ADC;
		ADC_MUX			= 1;
		// ADC update to ADC6:
		ADMUX		=  (0 << REFS1) | (1 << REFS0)| (0 << ADLAR) | (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
		ADCSRA |= (1 << ADSC);
	}
}


