/*
 * _32u4tims16b.c
 *
 * Created: 06/04/2025 06:16:23 p. m.
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// Libraries

#include <avr/io.h>
#include <stdint.h>
#include "m32u4tims16b.h"
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
//Functions

void tim_16b_init(tim_16b_num_t TIM_number,
tim_16b_channel_t TIM_channel,
tim_16b_prescaler_t TIM_prescaler,
tim_16b_mode_t TIM_waveform_mode,
uint16_t TIM_TOP_value,
tim_16b_com_t TIM_COM_mode,
uint16_t TIM_TCNT_inital_value,
tim_16b_ocnx_t TIM_OCnx_DDRn_ENABLING)
{
	tim_16b_reset(TIM_number);
	tim_16b_prescaler(TIM_prescaler);
	tim_16b_waveform_mode(TIM_number, TIM_waveform_mode);
	tim_16b_compare_output_mode(TIM_number, TIM_channel, TIM_COM_mode);
	if (TIM_OCnx_DDRn_ENABLING == TIM_16b_OCnx_ENABLE)
	{
		tim_16b_ocnx_enable(TIM_number, TIM_channel);
	}
	else if (TIM_OCnx_DDRn_ENABLING == TIM_16b_OCnx_DISABLE)
	{
		tim_16b_ocnx_disable(TIM_number, TIM_channel);
	}
	tim_16b_top_value(TIM_number, TIM_TOP_value);
	tim_16b_tcnt_value(TIM_number, TIM_TCNT_inital_value);
}

void tim_16b_tcnt_value(tim_16b_num_t TIM_number, uint16_t TIM_TCNT_value)
{
	switch (TIM_number)
	{
		case TIM_16b_NUM_1: TCNT1 = TIM_TCNT_value; break;
		case TIM_16b_NUM_3: TCNT3 = TIM_TCNT_value; break;
		default: break;
	}
}

void tim_16b_ocr_value(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel, uint16_t TIM_OCR_value)
{
	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: OCR1A = TIM_OCR_value; break;
			case TIM_16b_CHANNEL_B: OCR1B = TIM_OCR_value; break;
			case TIM_16b_CHANNEL_C: OCR1C = TIM_OCR_value; break;
			default: break;
		}
		break;
		case TIM_16b_NUM_3:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: OCR3A = TIM_OCR_value; break;
			case TIM_16b_CHANNEL_B: OCR3B = TIM_OCR_value; break;
			case TIM_16b_CHANNEL_C: OCR3C = TIM_OCR_value; break;
			default: break;
		}
		break;
	}
}

void tim_16b_ovf_interrupt_enable(tim_16b_num_t TIM_number) {
	switch (TIM_number) {
		case TIM_16b_NUM_1: TIMSK1 |= (1 << TOIE1); break;
		case TIM_16b_NUM_3: TIMSK3 |= (1 << TOIE3); break;
		default: break;
	}
}

void tim_16b_oc_interrupt_enable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel) {
	switch (TIM_number) {
		case TIM_16b_NUM_1:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: TIMSK1 |= (1 << OCIE1A); break;
			case TIM_16b_CHANNEL_B: TIMSK1 |= (1 << OCIE1B); break;
			case TIM_16b_CHANNEL_C: TIMSK1 |= (1 << OCIE1C); break;
			default: break;
		}
		break;
		case TIM_16b_NUM_3:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: TIMSK3 |= (1 << OCIE3A); break;
			case TIM_16b_CHANNEL_B: TIMSK3 |= (1 << OCIE3B); break;
			case TIM_16b_CHANNEL_C: TIMSK3 |= (1 << OCIE3C); break;
			default: break;
		}
		break;
		default: break;
	}
}

void tim_16b_ovf_interrupt_disable(tim_16b_num_t TIM_number) {
	switch (TIM_number) {
		case TIM_16b_NUM_1: TIMSK1 &= ~(1 << TOIE1); break;
		case TIM_16b_NUM_3: TIMSK3 &= ~(1 << TOIE3); break;
		default: break;
	}
}

void tim_16b_oc_interrupt_disable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel) {
	switch (TIM_number) {
		case TIM_16b_NUM_1:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: TIMSK1 &= ~(1 << OCIE1A); break;
			case TIM_16b_CHANNEL_B: TIMSK1 &= ~(1 << OCIE1B); break;
			case TIM_16b_CHANNEL_C: TIMSK1 &= ~(1 << OCIE1C); break;
			default: break;
		}
		break;
		case TIM_16b_NUM_3:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: TIMSK3 &= ~(1 << OCIE3A); break;
			case TIM_16b_CHANNEL_B: TIMSK3 &= ~(1 << OCIE3B); break;
			case TIM_16b_CHANNEL_C: TIMSK3 &= ~(1 << OCIE3C); break;
			default: break;
		}
		break;
		default: break;
	}
}

void tim_16b_prescaler(tim_16b_prescaler_t TIM_prescaler)
{
	TCCR1B = (TCCR1B & 0xF8) | (TIM_prescaler);
}

void tim_16b_waveform_mode(tim_16b_num_t TIM_number, tim_16b_mode_t TIM_waveform_mode)
{
	uint8_t WGM10_bits = 0;
	uint8_t WGM32_bits = 0;
	switch (TIM_waveform_mode)
	{
		case TIM_16b_MODE_NORMAL:								WGM32_bits = (0 << WGM13) | (0 << WGM12); WGM10_bits = (0 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_PHASE_CORRECT_PWM_8b:					WGM32_bits = (0 << WGM13) | (0 << WGM12); WGM10_bits = (0 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_PHASE_CORRECT_PWM_9b:					WGM32_bits = (0 << WGM13) | (0 << WGM12); WGM10_bits = (1 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_PHASE_CORRECT_PWM_10b:				WGM32_bits = (0 << WGM13) | (0 << WGM12); WGM10_bits = (1 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_CTC_OCRnA:							WGM32_bits = (0 << WGM13) | (1 << WGM12); WGM10_bits = (0 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_FAST_PWM_8b:							WGM32_bits = (0 << WGM13) | (1 << WGM12); WGM10_bits = (0 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_FAST_PWM_9b:							WGM32_bits = (0 << WGM13) | (1 << WGM12); WGM10_bits = (1 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_FAST_PWM_10b:							WGM32_bits = (0 << WGM13) | (1 << WGM12); WGM10_bits = (1 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_PHASE_AND_FREQ_CORRECT_PWM_ICRn:		WGM32_bits = (1 << WGM13) | (0 << WGM12); WGM10_bits = (0 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_PHASE_AND_FREQ_CORRECT_PWM_OCRnA:		WGM32_bits = (1 << WGM13) | (0 << WGM12); WGM10_bits = (0 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_PHASE_CORRECT_PWM_ICRn:				WGM32_bits = (1 << WGM13) | (0 << WGM12); WGM10_bits = (1 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_PHASE_CORRECT_PWM_OCRnA:				WGM32_bits = (1 << WGM13) | (0 << WGM12); WGM10_bits = (1 << WGM11) | (1 << WGM10); break;
		case TIM_16b_MODE_CTC_ICRn:								WGM32_bits = (1 << WGM13) | (1 << WGM12); WGM10_bits = (0 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_FAST_PWM_ICRn:						WGM32_bits = (1 << WGM13) | (1 << WGM12); WGM10_bits = (1 << WGM11) | (0 << WGM10); break;
		case TIM_16b_MODE_FAST_PWM_OCRnA:						WGM32_bits = (1 << WGM13) | (1 << WGM12); WGM10_bits = (1 << WGM11) | (1 << WGM10); break;
		default: break;
	}

	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
		TCCR1A |= (WGM10_bits);
		TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
		TCCR1B |= (WGM32_bits);
		break;
		case TIM_16b_NUM_3:
		TCCR3A &= ~((1 << WGM11) | (1 << WGM10));
		TCCR3A |= (WGM10_bits);
		TCCR3B &= ~((1 << WGM13) | (1 << WGM12));
		TCCR3B |= (WGM32_bits);
		break;
		default: break;
	}
}

void tim_16b_compare_output_mode(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel, tim_16b_com_t TIM_COM_mode)
{
	uint8_t COM_bits = 0;
	switch (TIM_channel)
	{
		case TIM_16b_CHANNEL_A:
		switch (TIM_COM_mode)
		{
			case TIM_16b_COM_OCnx_DISCONNECTED:		COM_bits = (0 << COM1A1) | (0 << COM1A0); break;
			case TIM_16b_COM_TOGGLE_OCnx:			COM_bits = (0 << COM1A1) | (1 << COM1A0); break;
			case TIM_16b_COM_NON_INVERT_OCnx:		COM_bits = (1 << COM1A1) | (0 << COM1A0); break;
			case TIM_16b_COM_INVERT_OCnx:			COM_bits = (1 << COM1A1) | (1 << COM1A0); break;
			default: break;
		}
		switch (TIM_number)
		{
			case TIM_16b_NUM_1:						TCCR1A	&= ~((1 << COM1A1) | (1 << COM1A0)); TCCR1A |= COM_bits; break;
			case TIM_16b_NUM_3:						TCCR3A	&= ~((1 << COM1A1) | (1 << COM1A0)); TCCR3A |= COM_bits; break;
		}
		break;
		case TIM_16b_CHANNEL_B:
		switch (TIM_COM_mode)
		{
			case TIM_16b_COM_OCnx_DISCONNECTED:		COM_bits = (0 << COM1B1) | (0 << COM1B0); break;
			case TIM_16b_COM_TOGGLE_OCnx:			COM_bits = (0 << COM1B1) | (1 << COM1B0); break;
			case TIM_16b_COM_NON_INVERT_OCnx:		COM_bits = (1 << COM1B1) | (0 << COM1B0); break;
			case TIM_16b_COM_INVERT_OCnx:			COM_bits = (1 << COM1B1) | (1 << COM1B0); break;
			default: break;
		}
		switch (TIM_number)
		{
			case TIM_16b_NUM_1:						TCCR1A	&= ~((1 << COM1B1) | (1 << COM1B0)); TCCR1A |= COM_bits; break;
			case TIM_16b_NUM_3:						TCCR3A	&= ~((1 << COM1B1) | (1 << COM1B0)); TCCR3A |= COM_bits; break;
		}
		break;
		case TIM_16b_CHANNEL_C:
		switch (TIM_COM_mode)
		{
			case TIM_16b_COM_OCnx_DISCONNECTED:		COM_bits = (0 << COM1C1) | (0 << COM1C0); break;
			case TIM_16b_COM_TOGGLE_OCnx:			COM_bits = (0 << COM1C1) | (1 << COM1C0); break;
			case TIM_16b_COM_NON_INVERT_OCnx:		COM_bits = (1 << COM1C1) | (0 << COM1C0); break;
			case TIM_16b_COM_INVERT_OCnx:			COM_bits = (1 << COM1C1) | (1 << COM1C0); break;
			default: break;
		}
		switch (TIM_number)
		{
			case TIM_16b_NUM_1:						TCCR1A	&= ~((1 << COM1C1) | (1 << COM1C0)); TCCR1A |= COM_bits; break;
			case TIM_16b_NUM_3:						TCCR3A	&= ~((1 << COM1C1) | (1 << COM1C0)); TCCR3A |= COM_bits; break;
		}
		break;
	}
}

void tim_16b_ocnx_enable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel)
{
	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: DDRB |= (1 << PORTB5); break;
			case TIM_16b_CHANNEL_B: DDRB |= (1 << PORTB6); break;
			case TIM_16b_CHANNEL_C: DDRB |= (1 << PORTB7); break;
			default: break;
		}
		break;
		case TIM_16b_NUM_3:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: DDRC |= (1 << PORTC6); break;
			case TIM_16b_CHANNEL_B: break;
			case TIM_16b_CHANNEL_C: break;
			default: break;
		}
		break;
		default: break;
	}
}

void tim_16b_ocnx_disable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel)
{
	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: DDRB &= ~(1 << PORTB5); break;
			case TIM_16b_CHANNEL_B: DDRB &= ~(1 << PORTB6); break;
			case TIM_16b_CHANNEL_C: DDRB &= ~(1 << PORTB7); break;
			default: break;
		}
		break;
		case TIM_16b_NUM_3:
		switch (TIM_channel)
		{
			case TIM_16b_CHANNEL_A: DDRC &= ~(1 << PORTC6); break;
			case TIM_16b_CHANNEL_B: break;
			case TIM_16b_CHANNEL_C: break;
			default: break;
		}
		break;
		default: break;
	}
}

void tim_16b_reset(tim_16b_num_t TIM_number)
{
	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1C = 0;
		TCNT1 = 0;
		OCR1A = 0;
		OCR1B = 0;
		OCR1C = 0;
		ICR1 = 0;
		TIMSK1 = 0;
		break;
		case TIM_16b_NUM_3:
		TCCR3A = 0;
		TCCR3B = 0;
		TCCR3C = 0;
		TCNT3 = 0;
		OCR3A = 0;
		OCR3B = 0;
		OCR3C = 0;
		ICR3 = 0;
		TIMSK3 = 0;
		break;
		default: break;
	}
}

void tim_16b_top_value(tim_16b_num_t TIM_number, uint16_t TIM_TOP_value)
{
	uint8_t WGM_bits = 0;
	switch (TIM_number)
	{
		case TIM_16b_NUM_1:
		WGM_bits = (TCCR1B & ((1 << WGM13) | (1 << WGM12)));
		WGM_bits |= (TCCR1A & ((1 << WGM11) | (1 << WGM10)));
		if ((WGM_bits == 0b00010000) || (WGM_bits == 0b00010010) || (WGM_bits == 0b00011000) || (WGM_bits == 0b00011010))
		{
			ICR1 = TIM_TOP_value;
		}
		else if ((WGM_bits == 0b00001000) || (WGM_bits == 0b00010001) || (WGM_bits == 0b00010011) || (WGM_bits == 0b00011011))
		{
			OCR1A = TIM_TOP_value;
		}
		break;
		case TIM_16b_NUM_3:
		WGM_bits = (TCCR3B & ((1 << WGM13) | (1 << WGM12)));
		WGM_bits |= (TCCR3A & ((1 << WGM11) | (1 << WGM10)));
		if ((WGM_bits == 0b00010000) || (WGM_bits == 0b00010010) || (WGM_bits == 0b00011000) || (WGM_bits == 0b00011010))
		{
			ICR3 = TIM_TOP_value;
		}
		else if ((WGM_bits == 0b00001000) || (WGM_bits == 0b00010001) || (WGM_bits == 0b00010011) || (WGM_bits == 0b00011011))
		{
			OCR3A = TIM_TOP_value;
		}
		break;
		default: break;
	}
}