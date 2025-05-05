/*
 * m32u4usart.c
 *
 * Created: 26/04/2025 06:41:59 p. m.
 *  Author: ang50
 */

/*********************************************************************************************************************************************/
// m32u4usart.c - USART library for ATmega32U4
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Libraries
#include <avr/io.h>
#include <stdint.h>
#include "m32u4usart.h"
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// Internal static variables
volatile static uint8_t USART_tx_buffer[USART_TX_BUFFER_SIZE];
volatile static uint8_t USART_tx_index	= 0;
volatile static uint8_t USART_tx_length = 0;
volatile static uint8_t USART_ready		= 1;

volatile static uint8_t USART_rx_buffer[USART_RX_BUFFER_SIZE];
volatile static uint8_t USART_rx_index = 0;
volatile static uint8_t USART_rx_ready = 0;
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART initiation functions 

void	usart_init(usart_mode_t						USART_mode,
				   usart_clock_polarity_t			USART_clock_polarity,
				   usart_speed_t					USART_speed,
				   usart_character_size_t			USART_character_size,
				   usart_parity_mode_t				USART_parity_mode,
				   usart_stop_bit_t					USART_stop_bit,
				   usart_mpcm_t						USART_multiprocessor_mode,
				   usart_hardware_flow_control_t	USART_flow_control_mode,
				   uint16_t							USART_baud_value)
{
	// Initial values
	UCSR1B	= 0; UCSR1C	= 0; UCSR1D	= 0;
	// Setting the USART BAUD RATE
	UBRR1	= USART_baud_value;
	usart_frame_format(USART_character_size, USART_parity_mode, USART_stop_bit);
	// USART multiprocessor and flow control mode
	// If multiprocessor and flow control modes are both wanted to be enabled, both are being disabled because of compatibility purposes.
	switch (USART_multiprocessor_mode)
	{
		case USART_MULTIPROCESSOR_COMMUNICATION_MODE_ENABLED:
			switch (USART_flow_control_mode)
			{
				case USART_HARDWARE_FLOW_CONTROL_ENABLED:	UCSR1A |= (0 << MPCM1);					UCSR1D |= (0 << CTSEN) | (0 << RTSEN);			break;
				case USART_HARDWARE_FLOW_CONTROL_DISABLED:	UCSR1A |= USART_multiprocessor_mode;	UCSR1D |= USART_flow_control_mode;				break;
				default: break;
			}
			break;
		case USART_MULTIPROCESSOR_COMMUNICATION_MODE_DISABLED:
			switch (USART_flow_control_mode)
			{
				case USART_HARDWARE_FLOW_CONTROL_ENABLED:	UCSR1A |= USART_multiprocessor_mode;	UCSR1D |= USART_flow_control_mode;				break;
				case USART_HARDWARE_FLOW_CONTROL_DISABLED:	UCSR1A |= USART_multiprocessor_mode;	UCSR1D |= USART_flow_control_mode;				break;
				default: break;
			}
			break;
		default: break;
	}
	// Other functions depending on synchronous or asynchronous modes
	switch (USART_mode)
	{
		case USART_MODE_ASYNCHRONOUS:						UCSR1A |= USART_speed;					UCSR1C |= (USART_mode) | (0 << UCPOL1);			break;
		case USART_MODE_SYNCHRONOUS:						UCSR1A |= (0 << U2X1);					UCSR1C |= (USART_mode) | USART_clock_polarity;	break;
		case USART_MODE_MASTER_SPI:							UCSR1C |= (USART_mode);					break;
		default: break;
	}
	
	// Enable receiver and transmitter (Purposely as the last step)
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1);
}

void	uart_init(usart_speed_t					USART_speed,
				  usart_character_size_t		USART_character_size,
				  usart_parity_mode_t			USART_parity_mode,
				  usart_stop_bit_t				USART_stop_bit,
				  usart_mpcm_t					USART_multiprocessor_mode,
				  usart_hardware_flow_control_t USART_flow_control_mode,
				  uint16_t						USART_baud_value)
{
	usart_init(USART_MODE_ASYNCHRONOUS,	
			   USART_CLOCK_POLARITY_RISING_EDGE, 
			   USART_speed, 
			   USART_character_size, 
			   USART_parity_mode, 
			   USART_stop_bit, 
			   USART_multiprocessor_mode, 
			   USART_flow_control_mode, 
			   USART_baud_value);
}

void	usrt_init(usart_clock_polarity_t		USART_clock_polarity,
				  usart_character_size_t		USART_character_size,
				  usart_parity_mode_t			USART_parity_mode,
				  usart_stop_bit_t				USART_stop_bit,
				  usart_mpcm_t					USART_multiprocessor_mode,
				  usart_hardware_flow_control_t USART_flow_control_mode,
				  uint16_t						USART_baud_value)
{
	usart_init(USART_MODE_SYNCHRONOUS, 
			   USART_clock_polarity, 
			   USART_SPEED_NORMAL, 
			   USART_character_size, 
			   USART_parity_mode, 
			   USART_stop_bit, 
			   USART_multiprocessor_mode, 
			   USART_flow_control_mode, 
			   USART_baud_value);
}
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART sub-protocoled communication functions

void	usart_multiprocessor_enable()
{
	// If flow control mode is enabled, no action will be done
	// If else, the multiprocessor mode is established as needed
	if (UCSR1D & (1 << CTSEN))
	{} else {
		UCSR1A	|= (1 << MPCM1);
	}	
}

void	usart_multiprocessor_disable()
{
	UCSR1A	&= ~(1 << MPCM1);
}

void	usart_flow_control_enable()
{
	// If multiprocessor mode is enabled, no action will be done
	// If else, the flow control mode is established as needed
		if (UCSR1A & (1 << MPCM1))
		{} else {
		UCSR1D	|= (1 << CTSEN) | (1 << RTSEN);
	}
}

void	usart_flow_control_disable()
{
	UCSR1D	&= ~((1 << CTSEN) | (1 << RTSEN));
}

/*********************************************************************************************************************************************/
// USART transmit functions

void	usart_polling_transmit(unsigned char USART_data)
{
	// Check how many bits are being sent
	uint8_t UCSZ = 0;
	UCSZ = UCSR1B & (1 << UCSZ12);
	if (UCSZ)		// If DATA = 9b
	{
		// Wait for empty transmit buffer
		while ( !( UCSR1A & (1<<UDRE1)));
		// Copy 9th bit to TXB8
		UCSR1B &= ~(1<<TXB81);
		if ( (unsigned int)USART_data & 0x0100 )
		{
			UCSR1B |= (1<<TXB81);
		}
		// Put data into buffer, sends the data
		UDR1 = (unsigned int)USART_data;
	} else          // If DATA < 9b
	{
		// Wait for empty transmit buffer
		while ( !( UCSR1A & (1<<UDRE1)));
		// Put data into buffer
		UDR1 = USART_data;
	}
}

void	usart_transmit_bytes(const uint8_t* USART_buffer, uint8_t USART_length)
{
	// Transmission will be done ONLY IF the data length is lower than the characteristic transmit buffer stated.
	if (USART_ready && USART_length <= USART_TX_BUFFER_SIZE)
	{
		for (uint8_t i=0; i<USART_length; i++)
		{
			USART_tx_buffer[i] = USART_buffer[i];
		}
		
		// Declaring values for static variables
		USART_tx_index = 0; USART_tx_length = USART_length; USART_ready = 0;
	}
}

void	usart_transmit_string(const char* USART_string)
{
	uint8_t length = 0;
	while (USART_string[length] != '\0')
	{
		length++;
	}
	usart_transmit_bytes((const uint8_t*)USART_string, length);
}

uint8_t	usart_load_next_byte()
{
	// USART_ready=0 tells if any transmission is being done. 
	// So, if USART_ready=0, the next byte (if any) should be uploaded
	if (!USART_ready) 
	{
		// If the last byte has not been sent, then we keep sending bytes.
		if (USART_tx_index < USART_tx_length)
		{
			UDR1 = USART_tx_buffer[USART_tx_index++];
			return 1;
		} else 
		{
		// If the last byte has been sent, then we stop sending bytes.
			USART_ready = 1;
			return 0;
		}
	}
	return 0;
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART receive functions

unsigned char	usart_polling_receive()
{
	// Check how many bits are being sent
	uint8_t UCSZ = 0;
	UCSZ = (UCSR1B & (1<<UCSZ12));
	if (UCSZ)		// If DATA = 9b
	{
		unsigned char status, resh, resl;
		// Wait for data to be received
		while ( !(UCSR1A & (1<<RXC1)) );
		// Get status and 9th bit, then data from buffer
		status = UCSR1A; resh = UCSR1B; resl = UDR1;
		// If error, return -1
		if ( status & (1<<FE1)|(1<<DOR1)|(1<<UPE1) )
		{
			return (unsigned char)-1;
		}
		else
		{
			// Filter the 9th bit, then return
			resh = (resh >> 1) & 0x01;
			return (unsigned char)((resh << 8) | resl);
		}	
	} else			// If DATA < 9b
	{
		// Wait for data to be received
		while ( !(UCSR1A & (1<<RXC1)) );
		// Get and return received data from buffer
		return UDR1;	
	}
}

void usart_receive_bytes()
{
	// If there are no errors while receiving
	if (!(UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1))))
	{
		// If the byte to store still has space inside the RX buffer, it is stored.
		if (USART_rx_index < USART_RX_BUFFER_SIZE)
		{
			USART_rx_buffer[USART_rx_index++] = UDR1;
		}
		// If not, nothing is done
		else{}
	// If there was an error while receiving, the data is discarded
	} else
	{
		uint8_t dummy = UDR1;
	}	
}

uint8_t usart_get_received_byte(uint8_t USART_index)
{
	// If the index (Or address) needed to be shown is shorter than the current receiving index:
	// Then, no info. is returned.
	// (I.e. if it is wanted to look for the last received byte, but a bigger index is used, 
	//  other info. may be returned; so, cautiously, "-1" is returned)
	
	if (USART_index < USART_rx_index)
	{
		return USART_rx_buffer[USART_index];
	} else {
		return 0xFF; // Return -1 in signed int nomenclature.
	}
}

uint8_t usart_get_received_length()
{
	return USART_rx_index;
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART flushing received data functions

void	usart_rx_buffer_flush()
{
	for (uint8_t i = 0; i < USART_RX_BUFFER_SIZE; i++)
	{
		USART_rx_buffer[i] = 0x00;
	}
	USART_rx_index = 0;
}

void	usart_polling_flush()
{
	unsigned char dummy;
	while ( UCSR1A & (1<<RXC1) ) 
	{
		dummy = UDR1;	
	}
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART interrupt enabling functions

void	usart_rx_interrupt_enable()
{
	UCSR1B |= (1 << RXCIE1);
}

void	usart_tx_interrupt_enable()
{
	UCSR1B |= (1 << TXCIE1);
}

void	usart_data_register_empty_interrupt_enable()
{
	UCSR1B |= (1 << UDRIE1);
}

void	usart_rx_interrupt_disable()
{
	UCSR1B &= ~(1 << RXCIE1);
}

void	usart_tx_interrupt_disable()
{
	UCSR1B &= ~(1 << TXCIE1);
}

void	usart_data_register_empty_interrupt_disable()
{
	UCSR1B &= ~(1 << UDRIE1);
}
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART frame format functions

void	usart_frame_format(usart_character_size_t USART_character_size, usart_parity_mode_t USART_parity_mode, usart_stop_bit_t USART_stop_bit)
{
	UCSR1B &= ~(1 << UCSZ12);
	UCSR1C &= ~((1 << UCSZ11) | (1 << UCSZ10) | (1 << UPM11) | (1 << UPM10) | (1 << USBS1));
	switch (USART_character_size)
	{
		case USART_CHARACTER_SIZE_5b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (0 << UCSZ11) | (0 << UCSZ10) | (USART_parity_mode) | (USART_stop_bit); break;
		case USART_CHARACTER_SIZE_6b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (0 << UCSZ11) | (1 << UCSZ10) | (USART_parity_mode) | (USART_stop_bit); break;
		case USART_CHARACTER_SIZE_7b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (0 << UCSZ10) | (USART_parity_mode) | (USART_stop_bit); break;
		case USART_CHARACTER_SIZE_8b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10) | (USART_parity_mode) | (USART_stop_bit); break;
		case USART_CHARACTER_SIZE_9b: UCSR1B |= (1 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10) | (USART_parity_mode) | (USART_stop_bit); break;
		default: break;
	}
}

void	usart_character_size(usart_character_size_t USART_character_size)
{
	UCSR1B &= ~(1 << UCSZ12);
	UCSR1C &= ~((1 << UCSZ11) | (1 << UCSZ10));
	switch (USART_character_size)
	{
		case USART_CHARACTER_SIZE_5b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (0 << UCSZ11) | (0 << UCSZ10); break;
		case USART_CHARACTER_SIZE_6b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (0 << UCSZ11) | (1 << UCSZ10); break;
		case USART_CHARACTER_SIZE_7b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (0 << UCSZ10); break;
		case USART_CHARACTER_SIZE_8b: UCSR1B |= (0 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); break;
		case USART_CHARACTER_SIZE_9b: UCSR1B |= (1 << UCSZ12); UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); break;
		default: break;
	}	
}

void	usart_parity_mode(usart_parity_mode_t USART_parity_mode)
{
	UCSR1C &= ~((1 << UPM11) | (1 << UPM10));
	UCSR1C |= (USART_parity_mode);
}

void	usart_stop_bit(usart_stop_bit_t USART_stop_bit)
{
	UCSR1C &= ~(1 << USBS1);
	UCSR1C |= (USART_stop_bit);
}

/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
// USART pin enabling functions

void	usart_rx_enable()
{
	UCSR1B |= (1 << RXEN1);
}

void	usart_tx_enable()
{
	UCSR1B |= (1 << TXEN1);
}

void	usart_rx_disable()
{
	UCSR1B &= ~(1 << RXEN1);
}

void	usart_tx_disable()
{
	UCSR1B &= ~(1 << TXEN1);
}

/*********************************************************************************************************************************************/