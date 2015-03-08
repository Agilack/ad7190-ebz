/*
 * AD7190-EBZ SPI Unit test
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
#include "spi.h"

#define AD_CS  0x01
#define AD_SCK 0x02
#define AD_DIN 0x04

void spi_init(void)
{
	IOA = AD_CS | AD_SCK;
	OEA = AD_CS | AD_SCK | AD_DIN;
	
	return;
}

void spi_test(void)
{
	IOA &= ~AD_CS;
	
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	// Clock pulse
	IOA &= ~AD_SCK;
	IOA |=  AD_SCK;
	
	// Disable CS
	IOA |=  AD_CS;
}
