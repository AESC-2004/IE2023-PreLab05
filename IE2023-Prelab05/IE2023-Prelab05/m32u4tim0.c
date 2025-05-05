/*
 * m32u4tim0.c
 *
 * Created: 8/04/2025 20:46:04
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// m32u4tim0.c - Timer 0 library for ATmega32U4
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Libraries
#include <avr/io.h>
#include <stdint.h>
#include "m32u4tim0.h"
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
//Functions

void	tim0_init(tim0_channel_t	TIM0_channel,
				  tim0_prescaler_t	TIM0_prescaler,
				  tim0_mode_t		TIM0_waveform_mode,
				  uint8_t			TIM0_OCRA_value,
				  tim0_com_t		TIM0_COM_mode,
				  uint8_t			TIM0_TCNT_inital_value,
				  tim0_oc0x_t		TIM0_OC0x_DDRn_ENABLING)
{
	tim0_reset();
	tim0_prescaler(TIM0_prescaler);
	tim0_waveform_mode(TIM0_waveform_mode);
	tim0_compare_output_mode(TIM0_channel, TIM0_COM_mode);
	if (TIM0_OC0x_DDRn_ENABLING == TIM0_OC0x_ENABLE)
	{
		tim0_oc0x_enable(TIM0_channel);
	}
	else if (TIM0_OC0x_DDRn_ENABLING == TIM0_OC0x_DISABLE)
	{
		tim0_oc0x_disable(TIM0_channel);
	}
	tim0_ocr_value(TIM0_channel, TIM0_OCRA_value);
	tim0_tcnt_value(TIM0_TCNT_inital_value);
}

void tim0_tcnt_value(uint8_t TIM0_TCNT_value)
{
	TCNT0 = TIM0_TCNT_value; 
}

void tim0_ocr_value(tim0_channel_t TIM0_channel, uint8_t TIM0_OCR_value)
{
	switch (TIM0_channel)
	{
		case TIM0_CHANNEL_A: OCR0A = TIM0_OCR_value; break;
		case TIM0_CHANNEL_B: OCR0B = TIM0_OCR_value; break;
		default: break;
	}
}

void tim0_ovf_interrupt_enable() 
{
	TIMSK0 |= (1 << TOIE0);
}

void tim0_oc_interrupt_enable(tim0_channel_t TIM0_channel) 
{
	switch (TIM0_channel)
	{
		case TIM0_CHANNEL_A: TIMSK0 |= (1 << OCIE0A); break;
		case TIM0_CHANNEL_B: TIMSK0 |= (1 << OCIE0B); break;
		default: break;
	}
}

void tim0_ovf_interrupt_disable() 
{
	TIMSK0 &= ~(1 << TOIE0);
}

void tim0_oc_interrupt_disable(tim0_channel_t TIM0_channel) 
{
	switch (TIM0_channel)
	{
		case TIM0_CHANNEL_A: TIMSK0 &= ~(1 << OCIE0A); break;
		case TIM0_CHANNEL_B: TIMSK0 &= ~(1 << OCIE0B); break;
		default: break;
	}
}

void tim0_prescaler(tim0_prescaler_t TIM0_prescaler)
{
	TCCR0B = (TCCR0B & 0xF8) | (TIM0_prescaler);
	
}

void tim0_waveform_mode(tim0_mode_t TIM0_waveform_mode)
{
	uint8_t WGM10_bits	= 0;
	uint8_t WGM2_bit	= 0;
	switch (TIM0_waveform_mode)
	{
		case TIM0_MODE_NORMAL:							WGM2_bit = (0 << WGM02); WGM10_bits = (0 << WGM01) | (0 << WGM00); break;
		case TIM0_MODE_PHASE_CORRECT_PWM_0xFF:			WGM2_bit = (0 << WGM02); WGM10_bits = (0 << WGM01) | (1 << WGM00); break;
		case TIM0_MODE_CTC_OCRA:						WGM2_bit = (0 << WGM02); WGM10_bits = (1 << WGM01) | (0 << WGM00); break;
		case TIM0_MODE_FAST_PWM_0xFF:					WGM2_bit = (0 << WGM02); WGM10_bits = (1 << WGM01) | (1 << WGM00); break;
		case TIM0_MODE_PHASE_CORRECT_PWM_OCRA:			WGM2_bit = (1 << WGM02); WGM10_bits = (0 << WGM01) | (1 << WGM00); break;
		case TIM0_MODE_FAST_PWM_OCRnA:					WGM2_bit = (1 << WGM02); WGM10_bits = (1 << WGM01) | (1 << WGM00); break;
		default: break;
	}
	
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0A |= (WGM10_bits);
	TCCR0B &= ~(1 << WGM02);
	TCCR0B |= (WGM2_bit);
}

void tim0_compare_output_mode(tim0_channel_t TIM0_channel, tim0_com_t TIM0_COM_mode)
{
	uint8_t COM0_bits = 0;
	switch (TIM0_channel)
	{
		case TIM0_CHANNEL_A:
			switch (TIM0_COM_mode)
			{
				case TIM0_COM_OC0x_DISCONNECTED:	COM0_bits = (0 << COM0A1) | (0 << COM0A0); break;
				case TIM0_COM_TOGGLE_OC0x:			COM0_bits = (0 << COM0A1) | (1 << COM0A0); break;
				case TIM0_COM_NON_INVERT_OC0x:		COM0_bits = (1 << COM0A1) | (0 << COM0A0); break;
				case TIM0_COM_INVERT_OC0x:			COM0_bits = (1 << COM0A1) | (1 << COM0A0); break;
				default: break;
			}
			TCCR0A	&= ~((1 << COM0A1) | (1 << COM0A0)); 
			TCCR0A |= COM0_bits;
			break;
			
		case TIM0_CHANNEL_B:
			switch (TIM0_COM_mode)
			{
				case TIM0_COM_OC0x_DISCONNECTED:		COM0_bits = (0 << COM0B1) | (0 << COM0B0); break;
				case TIM0_COM_TOGGLE_OC0x:				COM0_bits = (0 << COM0B1) | (1 << COM0B0); break;
				case TIM0_COM_NON_INVERT_OC0x:			COM0_bits = (1 << COM0B1) | (0 << COM0B0); break;
				case TIM0_COM_INVERT_OC0x:				COM0_bits = (1 << COM0B1) | (1 << COM0B0); break;
				default: break;
			}
			TCCR0A	&= ~((1 << COM0B1) | (1 << COM0B0)); 
			TCCR0A |= COM0_bits; break;
			break;
			
		default: break;
	}
}

void tim0_oc0x_enable(tim0_channel_t TIM0_channel)
{
	switch (TIM0_channel)
		{
			case TIM0_CHANNEL_A: DDRB |= (1 << PORTB7); break;
			case TIM0_CHANNEL_B: DDRD |= (1 << PORTD0); break;
			default: break;
		}
}

void tim0_oc0x_disable(tim0_channel_t TIM0_channel)
{
	switch (TIM0_channel)
	{
		case TIM0_CHANNEL_A: DDRB &= ~(1 << PORTB7); break;
		case TIM0_CHANNEL_B: DDRD &= ~(1 << PORTD0); break;
		default: break;
	}
}

void tim0_reset()
{
	TCCR0A = 0; TCCR0B = 0; TCNT0 = 0; OCR0A = 0; OCR0B = 0; TIMSK0 = 0;
}

/*********************************************************************************************************************************************/