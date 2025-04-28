/*
 * m32u4usart.h
 *
 * Created: 26/04/2025 06:41:44 p. m.
 *  Author: ang50
 */ 


#ifndef M32U4USART_H_
#define M32U4USART_H_

/*********************************************************************************************************************************************/
// External libraries
#include <avr/io.h>
#include <stdint.h>
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Config. characteristics
#define USART_TX_BUFFER_SIZE 64
#define USART_RX_BUFFER_SIZE 64
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Enumerations

// USART_SPEED enumeration
typedef enum {
	USART_SPEED_NORMAL									= (0 << U2X1),
	USART_SPEED_DOUBLE									= (1 << U2X1)
} usart_speed_t;

// USART_MPCM enumeration
typedef enum {
	USART_MULTIPROCESSOR_COMMUNICATION_MODE_ENABLED		= (1 << MPCM1),
	USART_MULTIPROCESSOR_COMMUNICATION_MODE_DISABLED	= (0 << MPCM1),
} usart_mpcm_t;

// USART_CHARACTER_SIZE enumeration
typedef enum {
	USART_CHARACTER_SIZE_5b,
	USART_CHARACTER_SIZE_6b,
	USART_CHARACTER_SIZE_7b,
	USART_CHARACTER_SIZE_8b,
	USART_CHARACTER_SIZE_9b
} usart_character_size_t;

// USART_MODE enumeration
typedef enum {
	USART_MODE_ASYNCHRONOUS								= (0 << UMSEL11) | (0 << UMSEL10),
	USART_MODE_SYNCHRONOUS								= (0 << UMSEL11) | (1 << UMSEL10),
	USART_MODE_MASTER_SPI								= (1 << UMSEL11) | (1 << UMSEL10)
} usart_mode_t;

// USART_PARITY_MODE enumeration
typedef enum {
	USART_PARITY_MODE_DISABLED							= (0 << UPM11) | (0 << UPM10),
	USART_PARITY_MODE_EVEN								= (1 << UPM11) | (0 << UPM10),
	USART_PARITY_MODE_ODD								= (1 << UPM11) | (1 << UPM10)
} usart_parity_mode_t;

// USART_STOP_BIT enumeration
typedef enum {
	USART_STOP_BIT_1b									= (0 << USBS1),
	USART_STOP_BIT_2b									= (1 << USBS1)
} usart_stop_bit_t;

// USART_CLOCK_POLARITY enumeration
typedef enum {
	USART_CLOCK_POLARITY_RISING_EDGE					= (0 << UCPOL1),
	USART_CLOCK_POLARITY_FALLING_EDGE					= (1 << UCPOL1)
} usart_clock_polarity_t;

// USART_HARDWARE_FLOW_CONTROL enumeration
typedef enum {
	USART_HARDWARE_FLOW_CONTROL_ENABLED					= (1 << CTSEN) | (1 << RTSEN),
	USART_HARDWARE_FLOW_CONTROL_DISABLED				= (0 << CTSEN) | (0 << RTSEN)
} usart_hardware_flow_control_t;

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Function prototypes

// Initializing a USART communication type
void	usart_init(usart_mode_t USART_mode,
usart_clock_polarity_t USART_clock_polarity,
usart_speed_t USART_speed,
usart_character_size_t USART_character_size,
usart_parity_mode_t USART_parity_mode,
usart_stop_bit_t USART_stop_bit,
usart_mpcm_t USART_multiprocessor_mode,
usart_hardware_flow_control_t USART_flow_control_mode,
uint16_t USART_baud_value
);

// Initializing a UART communication type
void	uart_init(usart_speed_t USART_speed,
usart_character_size_t USART_character_size,
usart_parity_mode_t USART_parity_mode,
usart_stop_bit_t USART_stop_bit,
usart_mpcm_t USART_multiprocessor_mode,
usart_hardware_flow_control_t USART_flow_control_mode,
uint16_t USART_baud_value
);

// Initializing a USRT communication type
void	usrt_init(usart_clock_polarity_t USART_clock_polarity,
usart_character_size_t USART_character_size,
usart_parity_mode_t USART_parity_mode,
usart_stop_bit_t USART_stop_bit,
usart_mpcm_t USART_multiprocessor_mode,
usart_hardware_flow_control_t USART_flow_control_mode,
uint16_t USART_baud_value
);

// Polling Transmit				(Without changing other settings)
// The function shall look for the number of bits being transmitted and work as needed.
void	usart_polling_transmit(unsigned char USART_data);
//void	usart_9b_polling_transmit(unsigned int USART_data);

// Interrupt transmit			(Without changing other settings)
void	usart_transmit_bytes(const uint8_t* USART_buffer, uint8_t USART_length);
void	usart_transmit_string(const char* USART_string);
uint8_t usart_load_next_byte();

// Polling Receive				(Without changing other settings)
// The function shall look for the number of bits being received and work as needed.
unsigned char	usart_polling_receive();
//unsigned int	usart_9b_polling_receive();

// Interrupt receive			(Without changing other settings)
void	usart_receive_bytes();
void	usart_receive_string(char* USART_destination_buffer);
uint8_t usart_get_received_byte(uint8_t USART_index);
uint8_t usart_get_received_length();
void	usart_rx_buffer_flush();

// Receive buffer flush			(Without changing other settings)
void	usart_flush();

// Interrupt enabling			(Without changing other settings)
void	usart_rx_interrupt_enable();									// Receive complete
void	usart_tx_interrupt_enable();									// Transmit complete
void	usart_data_register_empty_interrupt_enable();					// Data register empty

// Interrupt disabling			(Without changing other settings)
void	usart_rx_interrupt_disable();									// Receive complete
void	usart_tx_interrupt_disable();									// Transmit complete
void	usart_data_register_empty_interrupt_disable();					// Data register empty

// Frame formats				(Without changing other settings)
void	usart_frame_format(usart_character_size_t USART_character_size, usart_parity_mode_t USART_parity_mode, usart_stop_bit_t USART_stop_bit);
void	usart_character_size(usart_character_size_t USART_character_size);
void	usart_parity_mode(usart_parity_mode_t USART_parity_mode);
void	usart_stop_bit(usart_stop_bit_t USART_stop_bit);

// Pins enabling				(Without changing other settings)
void	usart_rx_enable();
void	usart_tx_enable();

// Pins disabling				(Without changing other settings)
void	usart_rx_disable();
void	usart_tx_disable();

/*********************************************************************************************************************************************/

#endif /* M32U4USART_H_ */