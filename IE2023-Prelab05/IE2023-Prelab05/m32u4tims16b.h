/*
 * _32u4tims16b.h
 *
 * Created: 06/04/2025 06:16:04 p. m.
 *  Author: ang50
 */ 

/*********************************************************************************************************************************************/
// m32u4tims16b.h - 16b Timers library for ATmega32U4
/*********************************************************************************************************************************************/


#ifndef M32U4TIMS16B_H_
#define M32U4TIMS16B_H_

/*********************************************************************************************************************************************/
// External libraries
#include <avr/io.h>
#include <stdint.h>
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Enumerations

// TIM_16b_NUM enumeration
typedef enum {
	TIM_16b_NUM_1,
	TIM_16b_NUM_3
} tim_16b_num_t;

// TIM_16b_CHANNEL enumeration
typedef enum {
	TIM_16b_CHANNEL_A,
	TIM_16b_CHANNEL_B,
	TIM_16b_CHANNEL_C
} tim_16b_channel_t;

// TIM_16b_MODE enumeration
typedef enum {
	TIM_16b_MODE_NORMAL,
	TIM_16b_MODE_PHASE_CORRECT_PWM_8b,
	TIM_16b_MODE_PHASE_CORRECT_PWM_9b,
	TIM_16b_MODE_PHASE_CORRECT_PWM_10b,
	TIM_16b_MODE_CTC_OCRnA,
	TIM_16b_MODE_FAST_PWM_8b,
	TIM_16b_MODE_FAST_PWM_9b,
	TIM_16b_MODE_FAST_PWM_10b,
	TIM_16b_MODE_PHASE_AND_FREQ_CORRECT_PWM_ICRn,
	TIM_16b_MODE_PHASE_AND_FREQ_CORRECT_PWM_OCRnA,
	TIM_16b_MODE_PHASE_CORRECT_PWM_ICRn,
	TIM_16b_MODE_PHASE_CORRECT_PWM_OCRnA,
	TIM_16b_MODE_CTC_ICRn,
	TIM_16b_MODE_FAST_PWM_ICRn,
	TIM_16b_MODE_FAST_PWM_OCRnA
} tim_16b_mode_t;

// TIM_16b_PRESCALER enumeration
typedef enum {
	TIM_16b_NO_CLOCK_SOURCE								= (0 << CS12) | (0 << CS11) | (0 << CS10),
	TIM_16b_PRESCALE_1									= (0 << CS12) | (0 << CS11) | (1 << CS10),
	TIM_16b_PRESCALE_8									= (0 << CS12) | (1 << CS11) | (0 << CS10),
	TIM_16b_PRESCALE_64									= (0 << CS12) | (1 << CS11) | (1 << CS10),
	TIM_16b_PRESCALE_256								= (1 << CS12) | (0 << CS11) | (0 << CS10),
	TIM_16b_PRESCALE_1024								= (1 << CS12) | (0 << CS11) | (1 << CS10),
	TIM_16b_EXT_SOURCE_FALLING_EDGE						= (1 << CS12) | (1 << CS11) | (0 << CS10),
	TIM_16b_EXT_SOURCE_RISING_EDGE						= (1 << CS12) | (1 << CS11) | (1 << CS10),
} tim_16b_prescaler_t;

// TIM_16b_COM enumeration
typedef enum {
	TIM_16b_COM_OCnx_DISCONNECTED,
	TIM_16b_COM_TOGGLE_OCnx,
	TIM_16b_COM_NON_INVERT_OCnx,
	TIM_16b_COM_INVERT_OCnx
} tim_16b_com_t;

// TIM_16b_OCnx_ENABLING enumeration
typedef enum {
	TIM_16b_OCnx_ENABLE,
	TIM_16b_OCnx_DISABLE
} tim_16b_ocnx_t;
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Function prototypes

// Initializing a timer
// TOP_VALUE shall only be copied to the correct register when utile to the waveform selected.
void	tim_16b_init(tim_16b_num_t			TIM_number,
					 tim_16b_channel_t		TIM_channel,
					 tim_16b_prescaler_t	TIM_prescaler,
					 tim_16b_mode_t			TIM_waveform_mode,
					 uint16_t				TIM_TOP_value,
					 tim_16b_com_t			TIM_COM_mode,
					 uint16_t				TIM_TCNT_inital_value,
					 tim_16b_ocnx_t			TIM_OCnx_DDRn_ENABLING);

// TCNT Value					(Without changing other settings)
void	tim_16b_tcnt_value(tim_16b_num_t TIM_number, uint16_t TIM_TCNT_value);

// OCR	Value					(Without changing other settings)
void	tim_16b_ocr_value(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel, uint16_t TIM_OCR_value);

// TOP Value					(Without changing other settings)
// This function shall look for the WGM bits to see which register to change depending on the waveform mode established!
// If no register controls the TOP value, no action should be done!
void	tim_16b_top_value(tim_16b_num_t TIM_number, uint16_t TIM_TOP_value);

// Interrupt enabling			(Without changing other settings)
void	tim_16b_ovf_interrupt_enable(tim_16b_num_t TIM_number);									// Overflow
void	tim_16b_ic_interrupt_enable(tim_16b_num_t TIM_number);									// Input capture
void	tim_16b_oc_interrupt_enable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel);	// Output compare

// Interrupt disabling			(Without changing other settings)
void	tim_16b_ovf_interrupt_disable(tim_16b_num_t TIM_number);								// Overflow
void	tim_16b_ic_interrupt_disable(tim_16b_num_t TIM_number);									// Input capture
void	tim_16b_oc_interrupt_disable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel);	// Output compare

// Prescaler selection			(Without changing other settings)
void	tim_16b_prescaler(tim_16b_num_t TIM_number, tim_16b_prescaler_t TIM_prescaler);

// Waveform mode				(Without changing other settings)
void	tim_16b_waveform_mode(tim_16b_num_t TIM_number, tim_16b_mode_t TIM_waveform_mode);

// COM Mode						(Without changing other settings)
void	tim_16b_compare_output_mode(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel, tim_16b_com_t TIM_COM_mode);

// OCnx enabling				(Without changing other settings)
void	tim_16b_ocnx_enable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel);

// OCnx disabling				(Without changing other settings)
void	tim_16b_ocnx_disable(tim_16b_num_t TIM_number, tim_16b_channel_t TIM_channel);

// TIM reseting					(Without changing other settings)
void tim_16b_reset(tim_16b_num_t TIM_number);

/*********************************************************************************************************************************************/

#endif /* M32U4TIMS16B_H_ */