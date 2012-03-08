//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2006-2011 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 7611 of the EK-LM3S8962 Firmware Package.
//
//*****************************************************************************
#include <stdint.h>
#include <string.h>
#include "inc/lm3s8962.h"
//#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "lib/menu/menu.h"
#include "lib/i2c/lib_I2C.h"
#include "lib/lib_newhaven_screen/screen.h"
#include "global.h"
#include "ints.h"


//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``hello world''
//! on the OLED and is a starting point for more complicated applications.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif


int
main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

	I2CInit();
	screen_on();
	screen_clear();
	
//	Display begin;
//	Display channel_display;
//	Display channel_select;
//	Display Volume;
//	Display AMPtype;
//	
//	Display stage2;
//	
//	
//	begin.left = &AMPtype;
//	begin.right = &channel_select;
//	begin.select = &stage2;
//	begin.back = NULL;
//	
//	begin.menu_type = CHANNEL_DISPLAY;
//	
//	begin.func_right = &(s1_right);

	Display* one = global_get_display(0);
	Display* two = global_get_display(1);
	Display* three = global_get_display(2);
	Display* four = global_get_display(3);
	Display* five = global_get_display(4);
	
	
	global_current_display(two);
	
	two->menu_type = CHANNEL_DISPLAY;
	
	two->left = one;
	two->right = three;
	two->select = five;
	two->back = four;
	
	two->func_right = &s1_right;
	one->func_right = &s1_right;
	three->func_right = &s1_right;
	
	two->func_left = &s1_left;
	one->func_left = &s1_left;
	three->func_left = &s1_left;
	
	two->func_back = &s1_back;
	one->func_back = &s1_back;
	three->func_back = &s1_back;
	four->func_back = &s1_back;

	display_set_text(four, HOME_TEXT, 16);
	display_set_text(two, CHANNEL_DISPLAY_TEXT, 16);
	display_set_text(three, CHANNEL_SELECT_TEXT, 16);
	display_set_text(one,AMP_TYPE_TEXT,16);
	

	screen_write_txt(&(two->characters[0][0]),strlen(two->characters[0]));
	
	

	//Menu_enum temp = CHANNEL_DISPLAY;
	//(*(channel_display.func_right))(&channel_display, temp, 0);
	
	while(true){
		delaymycode(30);
		turn_encoder_right();
		delaymycode(30);
		push_back_button();
		delaymycode(30);
		push_back_button();
		delaymycode(30);
		push_back_button();
	}
}
