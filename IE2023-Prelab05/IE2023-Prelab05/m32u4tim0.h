/*
 * m32u4tim0.h
 *
 * Created: 8/04/2025 17:33:52
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// m32u4tim0.h - Timer 0 library for ATmega32U4
/*********************************************************************************************************************************************/


#ifndef M32U4TIM0_H_
#define M32U4TIM0_H_

/*********************************************************************************************************************************************/
// External libraries
#include <avr/io.h>
#include <stdint.h>
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Enumerations

// TIM0_CHANNEL enumeration
typedef enum {
	TIM0_CHANNEL_A,
	TIM0_CHANNEL_B,
} tim0_channel_t;

// TIM0_MODE enumeration
typedef enum {
	TIM0_MODE_NORMAL,
	TIM0_MODE_PHASE_CORRECT_PWM_0xFF,
	TIM0_MODE_CTC_OCRA,
	TIM0_MODE_FAST_PWM_0xFF,
	TIM0_MODE_PHASE_CORRECT_PWM_OCRA,
	TIM0_MODE_FAST_PWM_OCRnA
} tim0_mode_t;

// TIM0_PRESCALER enumeration
typedef enum {
	TIM0_NO_CLOCK_SOURCE							= (0 << CS02) | (0 << CS01) | (0 << CS00),
	TIM0_PRESCALE_1									= (0 << CS02) | (0 << CS01) | (1 << CS00),
	TIM0_PRESCALE_8									= (0 << CS02) | (1 << CS01) | (0 << CS00),
	TIM0_PRESCALE_64								= (0 << CS02) | (1 << CS01) | (1 << CS00),
	TIM0_PRESCALE_256								= (1 << CS02) | (0 << CS01) | (0 << CS00),
	TIM0_PRESCALE_1024								= (1 << CS02) | (0 << CS01) | (1 << CS00),
	TIM0_EXT_SOURCE_FALLING_EDGE					= (1 << CS02) | (1 << CS01) | (0 << CS00),
	TIM0_EXT_SOURCE_RISING_EDGE						= (1 << CS02) | (1 << CS01) | (1 << CS00),
} tim0_prescaler_t;

// TIM0_COM enumeration
typedef enum {
	TIM0_COM_OC0x_DISCONNECTED,
	TIM0_COM_TOGGLE_OC0x,
	TIM0_COM_NON_INVERT_OC0x,
	TIM0_COM_INVERT_OC0x
} tim0_com_t;

// TIM0_OCnx_ENABLING enumeration
typedef enum {
	TIM0_OC0x_ENABLE,
	TIM0_OC0x_DISABLE
} tim0_oc0x_t;
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Function prototypes

// Initializing TIM0
void	tim0_init(tim0_channel_t	TIM0_channel,
				  tim0_prescaler_t	TIM0_prescaler,
				  tim0_mode_t		TIM0_waveform_mode,
				  uint8_t			TIM0_OCRA_value,
				  tim0_com_t		TIM0_COM_mode,
				  uint8_t			TIM0_TCNT_inital_value,
				  tim0_oc0x_t		TIM0_OC0x_DDRn_ENABLING);

// TCNT Value					(Without changing other settings)
void	tim0_tcnt_value(uint8_t TIM0_TCNT_value);

// OCR	Value					(Without changing other settings)
void	tim0_ocr_value(tim0_channel_t TIM0_channel, uint8_t TIM0_OCR_value);

// Interrupt enabling			(Without changing other settings)
void	tim0_ovf_interrupt_enable();									// Overflow								
void	tim0_oc_interrupt_enable(tim0_channel_t TIM0_channel);			// Output compare

// Interrupt disabling			(Without changing other settings)
void	tim0_ovf_interrupt_disable();									// Overflow								
void	tim0_oc_interrupt_disable(tim0_channel_t TIM0_channel);			// Output compare

// Prescaler selection			(Without changing other settings)
void	tim0_prescaler(tim0_prescaler_t TIM0_prescaler);

// Waveform mode				(Without changing other settings)
void	tim0_waveform_mode(tim0_mode_t TIM0_waveform_mode);

// COM Mode						(Without changing other settings)
void	tim0_compare_output_mode(tim0_channel_t TIM0_channel, tim0_com_t TIM0_COM_mode);

// OCnx enabling				(Without changing other settings)
void	tim0_oc0x_enable(tim0_channel_t TIM0_channel);

// OCnx disabling				(Without changing other settings)
void	tim0_oc0x_disable(tim0_channel_t TIM0_channel);

// TIM reseting					(Without changing other settings)
void tim0_reset();

/*********************************************************************************************************************************************/

#endif /* M32U4TIM0_H_ */