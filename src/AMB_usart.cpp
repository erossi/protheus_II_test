/*
    AMB2623 - Serial port library.
    Copyright (C) 2024 Enrico Rossi

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301  USA
 */

/** @file
 *
 */

#include <avr/io.h>
#include "AMB_usart.h"

/** Overloading Start the usart port.
 *
 * Override the base resume, we may need to fix the speed.
 */
void AMB_Usart0::resume()
{
	rxbuffer.clear();
	UCSR0A |= (1 << U2X0);
	UBRR0H = 0;
	// UBRR0L = 12; // 9600bps@1Mhz
	// UBRR0L = 103; // 9600bps@8Mhz
  // UBRR0L = 25; // 38400bps@8Mhz
	UBRR0L = 8; // 115200bps@8Mhz
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // 8n1
	// Rx with interrupt and Tx normal
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
}

/** Overload the suspend.
 *
 * May be not needed.
 *
 * @todo investigate useless code.
 */
void AMB_Usart0::suspend()
{
	UCSR0B = 0;
	// UCSR0C already default
	UBRR0L = 0;
	UBRR0H = 0;
	UCSR0A &= ~(1 << U2X0);
	rxbuffer.clear();
}

/** Overloading Start the usart port.
 *
 * Override the base resume, we may need to fix the speed.
 *
 * @todo investigate useless code.
 */
void AMB_Usart1::resume()
{
	rxbuffer.clear();
	UCSR1A |= (1 << U2X1);
	UBRR1H = 0;
	// UBRR1L = 12; // 9600bps@1Mhz
	UBRR1L = 8; // 115200bps@8Mhz
	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11); // 8n1
	// Rx with interrupt and Tx normal
	UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
}

/** Overload the suspend.
 *
 * May be not needed.
 *
 * @todo investigate useless code.
 */
void AMB_Usart1::suspend()
{
	UCSR1B = 0;
	// UCSR1C already default
	UBRR1L = 0;
	UBRR1H = 0;
	UCSR1A &= ~(1 << U2X1);
	rxbuffer.clear();
}
