/*
 * _32u4adc.c
 *
 * Created: 05/04/2025 04:36:05 p. m.
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// m32u4adc.c - ADC library for ATmega32U4
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Libraries
#include <avr/io.h>
#include <stdint.h>
#include "m32u4adc.h"
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC initiating function

void	adc_init(adc_ref_t				ADC_reference,
			  adc_prescaler_t			ADC_prescaler,
			  adc_adjust_t				ADC_adjust,
			  adc_channel_t				ADC_channel,
			  adc_high_speed_enable_t	ADC_high_speed,
			  adc_interrupt_enable_t	ADC_interrupt_enable,
			  adc_auto_trigger_enable_t ADC_auto_trigger_enable,
			  adc_trigger_t				ADC_trigger_source)
{
	// Set ADMUX, ADCSRA and ADCSRB initial values
	ADMUX	= 0; ADCSRA	= 0; ADCSRB	= 0;
	
	adc_ref(ADC_reference);
	adc_adjust(ADC_adjust);
	adc_channel(ADC_channel);
	adc_prescaler(ADC_prescaler);
	switch (ADC_auto_trigger_enable)
	{
		case ADC_AUTO_TRIGGER_ENABLE:	adc_auto_trigger_enable();	break;
		case ADC_AUTO_TRIGGER_DISABLE:	adc_auto_trigger_disable(); break;
		default: break;
	}
	adc_auto_trigger_source(ADC_trigger_source);
	switch (ADC_high_speed)
	{
		case ADC_HIGH_SPEED_ENABLE:		adc_high_speed_enable();	break;
		case ADC_HIGH_SPEED_DISABLE:	adc_high_speed_disable();	break;
		default: break;
	}
	switch (ADC_interrupt_enable)
	{
		case ADC_INTERRUPT_ENABLE:		adc_interrupt_enable();		break;
		case ADC_INTERRUPT_DISABLE:		adc_interrupt_disable();	break;
		default: break;
	}
	// Enable the ADC (Purposely as last step)
	ADCSRA	|=	(1 << ADEN);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC enabling functions

void	adc_enable() 
{
	ADCSRA	|=	(1 << ADEN);
}

void	adc_disable() 
{
	ADCSRA	&=	~(1 << ADEN);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC channel and reference functions

void	adc_channel(adc_channel_t ADC_channel) 
{
	uint8_t MUX5_bit	= 0;
	uint8_t MUX40_bits	= 0;
	
	switch (ADC_channel) 
	{
		case ADC_CHANNEL_ADC0:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC1:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_ADC4:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC5:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_ADC6:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC7:                      MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC1_ADC0_10x:        MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC1_ADC0_200x:       MUX5_bit = (0 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC0_ADC1_1x:         MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_1x:         MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_1x:         MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_1x:         MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_1x:         MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_1V1:                       MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_GND:                       MUX5_bit = (0 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_ADC8:                      MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC9:                      MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_ADC10:                     MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC11:                     MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_ADC12:                     MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_ADC13:                     MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_TEMPERATURE:               MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_10x:        MUX5_bit = (1 << MUX5); MUX40_bits = (0 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (0 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_40x:        MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (0 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (0 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (0 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (0 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (0 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (0 << MUX1) | (1 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (0 << MUX0); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_200x:       MUX5_bit = (1 << MUX5); MUX40_bits = (1 << MUX4)| (1 << MUX3)| (1 << MUX2) | (1 << MUX1) | (1 << MUX0); break;
		default: break;
	}
	
	ADCSRB	= (ADCSRB & ~(1 << MUX5)) | (MUX5_bit);
	ADMUX	= (ADMUX & 0xE0) | (MUX40_bits);
}

void	adc_ref(adc_ref_t ADC_reference) 
{
	ADMUX	=	(ADMUX & 0x3F) | (ADC_reference); 
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC prescaler function

void	adc_prescaler(adc_prescaler_t ADC_prescaler) 
{
	ADCSRA	=	(ADCSRA & 0xF8) | (ADC_prescaler);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC auto-trigger functions

void	adc_auto_trigger_enable() 
{
	ADCSRA	|=	(1 << ADATE);
}

void	adc_auto_trigger_disable() 
{
	ADCSRA	&=	~(1 << ADATE);
}

void	adc_auto_trigger_source(adc_trigger_t ADC_trigger_source) 
{
	ADCSRB	=	(ADCSRB & 0xF0) | (ADC_trigger_source);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Interrupt enabling functions

void	adc_interrupt_enable() 
{
	ADCSRA	|=	(1 << ADIE);
}

void	adc_interrupt_disable() 
{
	ADCSRA	&=	~(1 << ADIE);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// ADC justification function

void	adc_adjust(adc_adjust_t ADC_adjust) 
{
	ADMUX	=	(ADMUX & ~(1 << ADLAR)) | ADC_adjust;
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// High speed enabling functions

void	adc_high_speed_enable()
{
	ADCSRB	|=	(1 << ADHSM);
}
 
 void	adc_high_speed_disable()
 {
	 ADCSRB	&=	~(1 << ADHSM);
 }

/*********************************************************************************************************************************************/