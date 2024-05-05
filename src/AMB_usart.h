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
 * @page Serial_ports Serial Ports RS232 - IO functions.
 *
 * Serial Port 0 - DEBUG
 * Serial Port 1 - AMB2623TR
 *
 * @note: Use CBUF_SIZE to change the default size.
 */

#ifndef _AMB_USART_H_
#define _AMB_USART_H_

#include "usart_rxcbuffer.h"
#include "usart_rxcbuffer_p2.h"

class AMB_Usart0 : public Usart0_RxCBuffer {
	public:
		static void resume(); // override with custom speed
		static void suspend(); // override with custom speed
};

class AMB_Usart1 : public Usart1_RxCBuffer {
	public:
		static void resume(); // override with custom speed
		static void suspend(); // override with custom speed
};

#endif
