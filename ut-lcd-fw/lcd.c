/*
 * AD7190-EBZ LCD Unit test
 * 
 * Copyright (c) 2015 Saint-Genest Gwenael <gwen@agilack.fr>
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

#define	NOP     __asm nop __endasm
#define	DELAY	NOP; NOP; NOP; NOP

void lcd_init(void);
void lcd_wr4(unsigned char c);
void lcd_wr(unsigned char c, unsigned char cd);
void lcd_line(int n);
void lcd_puts(char *msg);

void lcd_init(void)
{
	long i;
	
	IOB = 0x00;
	OEB = 0xFF;
	DELAY;
	
	// Switch back to 8bits
	lcd_wr4(0x03);
	for (i = 0; i < 0x600; i++)
		;
	// Set 4 bits interface
	lcd_wr(0x2C, 1);
	for (i = 0; i < 0x600; i++)
		;
	// Set 4 bits interface (another time)
	lcd_wr(0x2C, 1);
	for (i = 0; i < 0x600; i++)
		;
	
	// Set Display ON/OFF
	lcd_wr(0x0C, 1);
	for (i = 0; i < 0x600; i++)
		;
	
	// Send a clear display command
	lcd_wr(0x01, 1);
	// Wait at least 1,54ms (with 0x600 approx 1,54ms)
	for (i = 0; i < 0x600; i++)
		;

	// Entry Mode Set
	lcd_wr(0x06, 1);
	// Wait
	for (i = 0; i < 0x600; i++)
		;
}

void lcd_wr4(unsigned char c)
{
	// Set bits
	IOB = c;
	DELAY; DELAY;
	
	// Start pulse
	IOB = c | 0x20;
	DELAY; DELAY;
	
	// End pulse
	IOB = c;
}

void lcd_wr(unsigned char c, unsigned char cd)
{
	unsigned char d;
	
	if (cd)
		d = c >> 4;
	else
		d = (c >> 4) | 0x80;
	lcd_wr4(d);
	
	if (cd)
		d = c & 0x0F;
	else
		d = (c & 0x0F) | 0x80;
	IOB = d;        // Low 4 bits
	DELAY; DELAY;
	IOB = d | 0x20; // Pulse begin
	DELAY; DELAY;
	IOB = d;        // Pulse end
	
	return;
}

void lcd_line(int n)
{
	int i;
	
	if (n == 0)
		lcd_wr(0x80 | 0x00, 1);
	else
		lcd_wr(0x80 | 0x40, 1);
	
	// Wait at least 37us (0x28 is approx 44us)
	for (i = 0; i < 0x28; i++)
		;
}

void lcd_puts(char *msg)
{
	int i;
	while(*msg)
	{
		lcd_wr(*msg, 0);
		msg++;
		// Wait at least 37us (0x28 is approx 44us)
		for (i = 0; i < 0x28; i++)
			;
	}
}
