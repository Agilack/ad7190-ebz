/*
 * AD7190-EBZ SPI Unit test
 * 
 * Copyright (c) 2015 Saint-Genest Gwenael <gwen@agilack.fr>
 * Based on "Hello World" example by Wolfgang Wieser (wwieser(a)gmx<*>de) 
 * 
 * This file may be distributed and/or modified under the terms of the 
 * GNU General Public License version 2 as published by the Free Software 
 * Foundation. (See COPYING.GPL for details.)
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 */

#define ALLOCATE_EXTERN
#include <fx2regs.h>
#include "spi.h"

// Read TRM p.15-115 for an explanation on this. 
// A single nop is sufficient for default setup but like that we're on 
// the safe side. 
#define	NOP   __asm nop __endasm
#define	DELAY NOP; NOP; NOP; NOP

void main(void)
{
	long counter;
	
	CPUCS    = 0x10;  /* 48 MHz, CLKOUT output disabled. */
	IFCONFIG = 0xc0;  /* Internal IFCLK, 48MHz; A,B as normal ports. */
	DELAY;

	REVCTL   = 0x03;  /* See TRM... */
	DELAY;
	
	spi_init();

	while(1)
		;
}
