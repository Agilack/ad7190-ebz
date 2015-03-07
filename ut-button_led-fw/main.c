/*
 * AD7190-EBZ Led & Buttons Unit test
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

// Read TRM p.15-115 for an explanation on this. 
// A single nop is sufficient for default setup but like that we're on 
// the safe side. 
#define	NOP   __asm nop __endasm
#define	DELAY NOP; NOP; NOP; NOP

void led_init(void);
void button_init(void);
char button_status(void);

void main(void)
{
	long counter;
	char but;
	int  mode;
	
	CPUCS    = 0x10;  /* 48 MHz, CLKOUT output disabled. */
	IFCONFIG = 0xc0;  /* Internal IFCLK, 48MHz; A,B as normal ports. */
	DELAY;

	REVCTL   = 0x03;  /* See TRM... */
	DELAY;
	
	if(USBCS & (1U<<1))
	{
		// RENUM bit is set indicating that the uC should handle USB requests.
		// This happens if the program is loaded from EEPROM.
		// Disconnect, switch off RENUM and reconnect again to force the FX2
		// logic to handle USB requests.
		USBCS |=  (1U<<3); DELAY; // Disconn
		USBCS &= ~(1U<<1); DELAY; // Renum
		USBCS &= ~(1U<<3); DELAY; // Disconn
	}

	led_init();
	button_init();
	
	mode = 0;
	
	for(counter = 0; ; counter++)
	{
	        but = button_status();
	        
	        if (but != 0)
	        {
	                if (but & 1)
	                        mode = 1;
                        else if (but & 2)
                                mode = 2;
                        else if (but & 4)
                                mode = 3;
                        else if (but & 8)
                                mode = 4;
                        else
                                mode = 0;
                        
                        counter = 0;
                }
                
                if (mode == 0)
                {
        	        if (counter == 0x00001000)
	                        IOD &= 0xFB;
        		if (counter == 0x00010000)
	        	{
		                IOD |= 0x04;
        		        counter = 0;
	        	}
                }
                
                /* Blink slowly */
                if (mode == 1)
                {
        	        if (counter == 0x00010000)
	                        IOD &= 0xFB;
        		if (counter == 0x00020000)
        		{
	        	        IOD |= 0x04;
        		        counter = 0;
	        	}
                }
                
                /* Blink at hi speed */
                if (mode == 2)
                {
        	        if (counter == 0x00002000)
	                        IOD &= 0xFB;
        		if (counter == 0x00004000)
	        	{
		                IOD |= 0x04;
        		        counter = 0;
	        	}
                }

                /*  Always Off */
                if (mode == 3)
                {
                        IOD &= 0xFB;
                }
                
                /* Always On */
                if (mode == 4)
                {
                        IOD |= 0x04;
                }
	}
}

void led_init(void)
{
        /* Reset PD2         */
	IOD = IOD & 0xFB;
	/* Set PD2 as output */
        OED = OED | 0x04;
}

void button_init(void)
{
        /* Reset PA4 (S1) PA5 (S2)PA6 (S3) PA7 (S4) */
        IOA = IOA & 0x0F;
        /* Set buttons IOs as input */
        OEA = OEA &= 0x0F;
}

char button_status(void)
{
        /* Read the current status of S1 */
        if ((IOA & 0x10) == 0)
                return(1);
        
        /* Read the current status of S2 */
        if ((IOA & 0x20) == 0)
                return(2);
        
        /* Read the current status of S3 */
        if ((IOA & 0x40) == 0)
                return(4);
        
        /* Read the current status of S4 */
        if ((IOA & 0x80) == 0)
                return(8);
        
        return(0);
}
