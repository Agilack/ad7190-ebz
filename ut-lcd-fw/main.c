/*
 * AD7190-EBZ LCD Unit test
 * 
 * Copyright (c) 
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

// Read TRM p.15-115 for an explanation on this. 
// A single nop is sufficient for default setup but like that we're on 
// the safe side. 
#define	NOP   __asm nop __endasm
#define	DELAY NOP; NOP; NOP; NOP

void lcd_init(void);
void lcd_wr4(unsigned char c);
void lcd_wr(unsigned char c, unsigned char cd);
void lcd_line(int n);
void lcd_puts(char *msg);

void main(void)
{
	long counter;
	
	CPUCS    = 0x10;  /* 48 MHz, CLKOUT output disabled. */
	IFCONFIG = 0xc0;  /* Internal IFCLK, 48MHz; A,B as normal ports. */
	DELAY;

	REVCTL   = 0x03;  /* See TRM... */
	DELAY;
	
	lcd_init();
	
	for(counter = 0; ; counter++)
	{
		if (counter == 0x00000010)
		{
			lcd_line(0);
			lcd_puts("Hello World!    ");
		}
		else if (counter == 0x00080000)
		{
			lcd_line(0);
			lcd_puts("This is the     ");
			lcd_line(1);
			lcd_puts(" LCD  Unit-Test ");
		}
		else if (counter == 0x00100000)
		{
			lcd_line(0);
			lcd_puts("={ AD7190-EBZ }=");
			lcd_line(1);
			lcd_puts("                ");
		}
		else if (counter == 0x00180000)
		{
			lcd_line(1);
			lcd_puts("Enjoy!  :-)  (-:");
		}
		else if (counter == 0x00200000)
			counter = 0;
	}
}
