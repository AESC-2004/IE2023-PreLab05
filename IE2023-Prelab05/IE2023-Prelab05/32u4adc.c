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
	switch (channel) {
		case ADC_CHANNEL_ADC0:                      ADMUX = (ADMUX & 0xE0) | 0x00; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC1:                      ADMUX = (ADMUX & 0xE0) | 0x01; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC4:                      ADMUX = (ADMUX & 0xE0) | 0x04; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC5:                      ADMUX = (ADMUX & 0xE0) | 0x05; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC6:                      ADMUX = (ADMUX & 0xE0) | 0x06; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC7:                      ADMUX = (ADMUX & 0xE0) | 0x07; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC1_ADC0_10x:        ADMUX = (ADMUX & 0xE0) | 0x09; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC1_ADC0_200x:       ADMUX = (ADMUX & 0xE0) | 0x0B; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC0_ADC1_1x:         ADMUX = (ADMUX & 0xE0) | 0x10; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_1x:         ADMUX = (ADMUX & 0xE0) | 0x14; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_1x:         ADMUX = (ADMUX & 0xE0) | 0x15; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_1x:         ADMUX = (ADMUX & 0xE0) | 0x16; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_1x:         ADMUX = (ADMUX & 0xE0) | 0x17; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_1V1:                       ADMUX = (ADMUX & 0xE0) | 0x1E; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_GND:                       ADMUX = (ADMUX & 0xE0) | 0x1F; ADCSRB &= ~(1 << MUX5); break;
		case ADC_CHANNEL_ADC8:                      ADMUX = (ADMUX & 0xE0) | 0x00; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_ADC9:                      ADMUX = (ADMUX & 0xE0) | 0x01; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_ADC10:                     ADMUX = (ADMUX & 0xE0) | 0x02; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_ADC11:                     ADMUX = (ADMUX & 0xE0) | 0x03; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_ADC12:                     ADMUX = (ADMUX & 0xE0) | 0x04; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_ADC13:                     ADMUX = (ADMUX & 0xE0) | 0x05; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_TEMPERATURE:               ADMUX = (ADMUX & 0xE0) | 0x07; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_10x:        ADMUX = (ADMUX & 0xE0) | 0x18; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_10x:        ADMUX = (ADMUX & 0xE0) | 0x19; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_10x:        ADMUX = (ADMUX & 0xE0) | 0x1A; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_10x:        ADMUX = (ADMUX & 0xE0) | 0x1B; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_10x:        ADMUX = (ADMUX & 0xE0) | 0x1C; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_10x:        ADMUX = (ADMUX & 0xE0) | 0x1D; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_10x:        ADMUX = (ADMUX & 0xE0) | 0x1E; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_10x:        ADMUX = (ADMUX & 0xE0) | 0x1F; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_40x:        ADMUX = (ADMUX & 0xE0) | 0x20; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_40x:        ADMUX = (ADMUX & 0xE0) | 0x21; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_40x:        ADMUX = (ADMUX & 0xE0) | 0x22; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_40x:        ADMUX = (ADMUX & 0xE0) | 0x23; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_40x:        ADMUX = (ADMUX & 0xE0) | 0x24; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_40x:        ADMUX = (ADMUX & 0xE0) | 0x25; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_40x:        ADMUX = (ADMUX & 0xE0) | 0x26; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_40x:        ADMUX = (ADMUX & 0xE0) | 0x27; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC0_200x:       ADMUX = (ADMUX & 0xE0) | 0x28; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC0_200x:       ADMUX = (ADMUX & 0xE0) | 0x29; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC0_200x:       ADMUX = (ADMUX & 0xE0) | 0x2A; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC0_200x:       ADMUX = (ADMUX & 0xE0) | 0x2B; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC4_ADC1_200x:       ADMUX = (ADMUX & 0xE0) | 0x2C; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC5_ADC1_200x:       ADMUX = (ADMUX & 0xE0) | 0x2D; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC6_ADC1_200x:       ADMUX = (ADMUX & 0xE0) | 0x2E; ADCSRB |=  (1 << MUX5); break;
		case ADC_CHANNEL_DIFF_ADC7_ADC1_200x:       ADMUX = (ADMUX & 0xE0) | 0x2F; ADCSRB |=  (1 << MUX5); break;
		default: break;
	}
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

 
 
