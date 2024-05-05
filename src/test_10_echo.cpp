/* Copyright (C) 2024 Enrico Rossi

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

/** @file
 *
 * @page test_serial_echo Test Echo from the two serial ports
 *
 * ### Dependency.
 *
 * ### Versions
 *
 * ### How it works
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "AMB_usart.h"

#define AMB2623_PORT PORTD
#define AMB2623_DDR DDRD
#define AMB2623_RBT PD6

AMB_Usart0 uAMB2623;
AMB_Usart1 uDebug;

int main()
{
	uint8_t c;
	char b[10] {'\n', 't', 'e', 's', 't', '\n', 0}; // buffer
	char* s;

	/* Set the /RBT to 0V output
	 */
	AMB2623_PORT &= ~(1 << AMB2623_RBT);
	AMB2623_DDR |= (1 << AMB2623_RBT);

	// setup the ports
	uAMB2623.resume();
	uDebug.resume();
	sei(); // enable IRQ

	// print the "test"
	s=b;

	while (*s)
		uDebug.put(*s++);

	// Start the AMB2623, release /RSB pin
	// 1msec required
	_delay_ms(1);
	AMB2623_PORT |= (1 << AMB2623_RBT);

	while(true) {
		if (uAMB2623.get(&c)) {
			sprintf(b, "0x%02x ", c);
			s=b; // set the s to b

			// print it
			while (*s)
				uDebug.put(*s++);
		}

		if (uDebug.get(&c))
			uAMB2623.put(c);
	}

	return 0;
}
