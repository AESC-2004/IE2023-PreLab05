/*
 * _32u4adc.c
 *
 * Created: 05/04/2025 04:36:05 p. m.
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// 32u4adc.c - ADC library for ATmega32U4
/*********************************************************************************************************************************************/
#include "32u4adc.h"

void adc_init(adc_ref_t reference,
adc_prescaler_t prescaler,
adc_adjust_t adjust,
adc_channel_t channel,
adc_interrupt_enable_t adc_interrupt,
adc_auto_trigger_enable_t auto_trigger_enable,
adc_trigger_t trigger_source)
{
	// Set ADMUX, ADCSRA and ADCSRB as 0
	ADMUX	= 0;
	ADCSRA	= 0;
	ADCSRB	= 0;
	
	// Set voltage reference and result adjustment
	ADMUX		 = reference | adjust;

	// Set channel (MUX bits in ADMUX and MUX5 in ADCSRB)
	adc_channel(channel);

	// Set prescaler, interrupts, and auto_trigger enabling
	ADCSRA		= prescaler | adc_interrupt | auto_trigger_enable;

	// Set trigger source (Using masks)
	ADCSRB		= (ADCSRB & 0xF0) | (trigger_source & 0x0F);
	
	// Enable the ADC
	ADCSRA		|= (1 << ADEN);
}

void adc_enable() {
	ADCSRA		|= (1 << ADEN);
}

void adc_disable() {
	ADCSRA		&= ~(1 << ADEN);
}

void adc_channel(adc_channel_t channel) {
	// MUX bits (MUX[4:0] in ADMUX, MUX5 in ADCSRB)
	uint8_t mux5		 = (channel >> 5) & 0x01;
	uint8_t mux0_to_mux4 = channel & 0x1F;
	ADMUX		= (ADMUX & 0b11100000) | mux0_to_mux4;         // Preserve REFS and ADLAR, update MUX[4:0]
	ADCSRB		= (ADCSRB & ~(1 << MUX5)) | (mux5 << MUX5);
}

void adc_ref(adc_ref_t reference) {
	ADMUX		= (ADMUX & 0b00111111) | reference;        // Preserve ADLAR and MUX, set REFS
}

void adc_prescaler(adc_prescaler_t prescaler) {
	ADCSRA		= (ADCSRA & 0B11111000) | prescaler;
}

void adc_enable_auto_trigger() {
	ADCSRA		|= (1 << ADATE);
}

void adc_disable_auto_trigger() {
	ADCSRA		&= ~(1 << ADATE);
}

void adc_auto_trigger_source(adc_trigger_t trigger_source) {
	ADCSRB		= (ADCSRB & 0xF0) | (trigger_source & 0x0F);
}

void adc_interrupt_enable() {
	ADCSRA		|= (1 << ADIE);
}

void adc_interrupt_disable() {
	ADCSRA		&= ~(1 << ADIE);
}

void adc_adjust(adc_adjust_t adjust) {
	ADMUX		= (ADMUX & ~(1 << ADLAR)) | adjust;
}

 
 
