/*
 * _32u4adc.h
 *
 * Created: 05/04/2025 04:30:25 p. m.
 *  Author: ang50
 */ 


#ifndef 32U4ADC_H_
#define 32U4ADC_H_

/*********************************************************************************************************************************************/
// External libraries
#include <avr/io.h>
#include <stdint.h>
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Enumerations

// ADC_REF enumeration
typedef enum {
	ADC_REF_AREF			= (0 << REFS1) | (0 << REFS0),
	ADC_REF_AVCC			= (0 << REFS1) | (1 << REFS0),
	ADC_REF_INTERNAL_2V56	= (1 << REFS1) | (1 << REFS0)
} adc_ref_t;

// ADC_PRESCALE enumeration
typedef enum {
	ADC_PRESCALE_2		= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0),
	ADC_PRESCALE_4		= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0),
	ADC_PRESCALE_8		= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0),
	ADC_PRESCALE_16		= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0),
	ADC_PRESCALE_32		= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0),
	ADC_PRESCALE_64		= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0),
	ADC_PRESCALE_128	= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)
} adc_prescaler_t;

// ADC_TRIGGER enumeration
typedef enum {
	ADC_TRIGGER_FREE_RUNNING			= (0 << ADTS3) | (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_ANALOG_COMPARATOR		= (0 << ADTS3) | (0 << ADTS2) | (0 << ADTS1) | (1 << ADTS0),
	ADC_TRIGGER_EXT_INT0				= (0 << ADTS3) | (0 << ADTS2) | (1 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_TIMER0_COMPARE_MATCH_A	= (0 << ADTS3) | (0 << ADTS2) | (1 << ADTS1) | (1 << ADTS0),
	ADC_TRIGGER_TIMER0_OVERFLOW			= (0 << ADTS3) | (1 << ADTS2) | (0 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_TIMER1_COMPARE_MATCH_B	= (0 << ADTS3) | (1 << ADTS2) | (0 << ADTS1) | (1 << ADTS0),
	ADC_TRIGGER_TIMER1_OVERFLOW			= (0 << ADTS3) | (1 << ADTS2) | (1 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_TIMER1_CAPTURE_EVENT	= (0 << ADTS3) | (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0),
	ADC_TRIGGER_TIMER4_OVERFLOW			= (1 << ADTS3) | (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_TIMER4_COMPARE_MATCH_A	= (1 << ADTS3) | (0 << ADTS2) | (0 << ADTS1) | (1 << ADTS0),
	ADC_TRIGGER_TIMER4_COMPARE_MATCH_B	= (1 << ADTS3) | (0 << ADTS2) | (1 << ADTS1) | (0 << ADTS0),
	ADC_TRIGGER_TIMER4_COMPARE_MATCH_D	= (1 << ADTS3) | (0 << ADTS2) | (1 << ADTS1) | (1 << ADTS0)
} adc_trigger_t;

// ADC_CHANNEL enumeration
typedef enum {
	ADC_CHANNEL_ADC0,
	ADC_CHANNEL_ADC1,
	ADC_CHANNEL_ADC4,
	ADC_CHANNEL_ADC5,
	ADC_CHANNEL_ADC6,
	ADC_CHANNEL_DIFF_ADC1_ADC0_10x,
	ADC_CHANNEL_DIFF_ADC1_ADC0_200x,
	ADC_CHANNEL_DIFF_ADC0_ADC1_1x,
	ADC_CHANNEL_DIFF_ADC4_ADC1_1x,
	ADC_CHANNEL_DIFF_ADC5_ADC1_1x,
	ADC_CHANNEL_DIFF_ADC6_ADC1_1x,
	ADC_CHANNEL_DIFF_ADC7_ADC1_1x,
	ADC_CHANNEL_1V1,
	ADC_CHANNEL_GND,
	ADC_CHANNEL_ADC8,
	ADC_CHANNEL_ADC9,
	ADC_CHANNEL_ADC10,
	ADC_CHANNEL_ADC11,
	ADC_CHANNEL_ADC12,
	ADC_CHANNEL_DIFF_ADC1_ADC0_40x,
	ADC_CHANNEL_TEMPERATURE,
	ADC_CHANNEL_DIFF_ADC4_ADC0_10x,
	ADC_CHANNEL_DIFF_ADC5_ADC0_10x,
	ADC_CHANNEL_DIFF_ADC6_ADC0_10x,
	ADC_CHANNEL_DIFF_ADC7_ADC0_10x,
	ADC_CHANNEL_DIFF_ADC4_ADC1_10x,
	ADC_CHANNEL_DIFF_ADC5_ADC1_10x,
	ADC_CHANNEL_DIFF_ADC6_ADC1_10x,
	ADC_CHANNEL_DIFF_ADC7_ADC1_10x,
	ADC_CHANNEL_DIFF_ADC4_ADC0_40x,
	ADC_CHANNEL_DIFF_ADC5_ADC0_40x,
	ADC_CHANNEL_DIFF_ADC6_ADC0_40x,
	ADC_CHANNEL_DIFF_ADC7_ADC0_40x,
	ADC_CHANNEL_DIFF_ADC4_ADC1_40x,
	ADC_CHANNEL_DIFF_ADC5_ADC1_40x,
	ADC_CHANNEL_DIFF_ADC6_ADC1_40x,
	ADC_CHANNEL_DIFF_ADC7_ADC1_40x,
	ADC_CHANNEL_DIFF_ADC4_ADC0_200x,
	ADC_CHANNEL_DIFF_ADC5_ADC0_200x,
	ADC_CHANNEL_DIFF_ADC6_ADC0_200x,
	ADC_CHANNEL_DIFF_ADC7_ADC0_200x,
	ADC_CHANNEL_DIFF_ADC4_ADC1_200x,
	ADC_CHANNEL_DIFF_ADC5_ADC1_200x,
	ADC_CHANNEL_DIFF_ADC6_ADC1_200x,
	ADC_CHANNEL_DIFF_ADC7_ADC1_200x
} adc_channel_t;

// ADC_AUTO_TRIGGER_ENABLE enumeration
typedef enum {
	ADC_AUTO_TRIGGER_ENABLE		= (1 << ADATE),
	ADC_AUTO_TRIGGER_DISABLE	= (0 << ADATE)
} adc_auto_trigger_enable_t;

// ADC_INTERRUPT_ENABLE enumeration
typedef enum {
	ADC_INTERRUPT_ENABLE		= (1 << ADIE),
	ADC_INTERRUPT_DISABLE		= (0 << ADIE)
} adc_interrupt_enable_t;

// ADC_ADJUST enumeration
typedef enum {
	ADC_LEFT_ADJUST				= (1 << ADLAR),
	ADC_RIGHT_ADJUST			= (0 << ADLAR)
} adc_adjust_t;

// ADC_HIGH_SPEED_enable enumeration
typedef enum {
	ADC_HIGH_SPEED_ENABLE		= (1 << ADHSM),
	ADC_HIGH_SPEED_DISABLE		= (0 << ADHSM)
} adc_high_speed_enable_t;
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Function prototypes

// Initializing the ADC 
void	adc_init(adc_ref_t reference, 
				 adc_prescaler_t prescaler,
				 adc_adjust_t adjust,
				 adc_channel_t channel, 
				 adc_interrupt_enable_t adc_interrupt, 
				 adc_auto_trigger_enable_t auto_trigger_enable, 
				 adc_trigger_t trigger_source);

// Enabling ADC				(Without changing other settings)
void	adc_enable();

// Disabling ADC			(Without changing other settings)
void	adc_disable();

// Channel selection		(Without changing other settings)
void	adc_channel(adc_channel_t channel);

// Reference source			(Without changing other settings)
void	adc_ref(adc_ref_t reference);

// Prescaler selection		(Without changing other settings)
void	adc_prescaler(adc_prescaler_t prescaler);

// Auto trigger enable		(Without changing other settings)
void	adc_enable_auto_trigger();

// Auto trigger disable		(Without changing other settings)
void	adc_disable_auto_trigger();

// Auto trigger source		(Without changing other settings)
void	adc_auto_trigger_source(adc_trigger_t trigger_source);

// Interrupt enable			(Without changing other settings)
void	adc_interrupt_enable();

// Interrupt disable		(Without changing other settings)
void	adc_interrupt_disable();

// Adjust mode (L or R)		(Without changing other settings)
void	adc_adjust(adc_adjust_t adjust);
/*********************************************************************************************************************************************/

#endif /* 32U4ADC_H_ */