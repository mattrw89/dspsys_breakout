
//
//*****************************************************************************
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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
#include "lib/lib_codec_cs42448/codec.h"


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

void channels_init() {
	uint8_t i=0;

	char tempi[10] = "Input ";
	char tempo[10] = "Output ";
	char temp[10];
	//loop through all input channels.  should be MAX of input and output channels
	for(i=0; i < NUM_INPUT_CHANNELS; i++) {

		strncpy(temp,tempi,6);
		temp[6] = i + 1 + 48;
		temp[7] = '\0';
		Channel_ctor(get_channel_from_memory(INPUT,i+1),i+1, temp, ACTIVE, INPUT);

		strncpy(temp,tempo,7);
		temp[7] = i + 1 + 48;
		temp[8] = '\0';
		Channel_ctor(get_channel_from_memory(OUTPUT,i+1),i+1, temp, ACTIVE, OUTPUT);
	}
}

void menu_init(Display *one, Display *two, Display *three, Display *four, Display *five){
	
	two->menu_type = HOME;
	
	two->left = one;
	two->right = three;
	two->select = five;
	two->back = four;
	
	one->i = 0;
	two->i = 0;
	three->i = 0;
	four->i = 0;
	five->i = 0;
	
	one->func_right = &s1_right;
	two->func_right = &s1_right;
	three->func_right = &s1_right;
	four->func_right = &s1_right;
	five->func_right = &s1_right;
	
	one->func_left = &s1_left;
	two->func_left = &s1_left;
	three->func_left = &s1_left;
	four->func_left = &s1_left;
	five->func_left = &s1_left;
	
	one->func_select = &s1_select;
	two->func_select = &s1_select;
	three->func_select = &s1_select;
	four->func_select = &s1_select;
	five->func_select = &s1_select;
	
	one->func_back = &s1_back;
	two->func_back = &s1_back;
	three->func_back = &s1_back;
	four->func_back = &s1_back;
	five->func_back = &s1_back;
	
	display_set_text(five, CHANNEL_DISPLAY_TEXT, 16);
	
	display_set_text(two, HOME_TEXT, 16);
	display_set_text(three, HOME_TEXT, 16);
	display_set_text(one,HOME_TEXT,16);
	display_set_text(four,HOME_TEXT,16);
}


int
main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

	channels_init();
	I2CInit();
	screen_on();
	screen_clear();
	
	Display* one = global_get_display(0);
	Display* two = global_get_display(1);
	Display* three = global_get_display(2);
	Display* four = global_get_display(3);
	Display* five = global_get_display(4);	
	
	global_current_display(two);
	
	menu_init(one,two,three,four,five);
	
//  	Io_enum temp_io = INPUT;
//	uint8_t i;
//	for(i=1; i <= 14; i++) {
//		// 2nd argument to get_channel_from_memory is the CHANNEL NUMBER, not INDEX
//		Channel* temp_channel = get_channel_from_memory(temp_io, i);
//		screen_write_txt_line_2(channel_get_name(temp_channel),strlen(channel_get_name(temp_channel)));
//		delaymycode(30);
//		
//		screen_clear();
//		Cursor_enum temp_cursor = SEC_1;
//		screen_set_cursor(temp_cursor);
//	}
	

	screen_write_txt(&(two->characters[0][0]),strlen(two->characters[0]));
	
	delaymycode(30);
	push_encoder_button();
	
	CODEC_info codec;
	CDC_init(&codec);
	CDC_start(&codec);
	
	int testnumber = 3;
			
	while(true){
		switch(testnumber){
			case 1: {
				delaymycode(30);
				turn_encoder_right();
				
				delaymycode(30);
				turn_encoder_right();
			
				delaymycode(30);
				turn_encoder_right();
				break;
			}
			
			case 2:{
				delaymycode(30);
				turn_encoder_right();
				
				delaymycode(30);
				push_encoder_button();
				
				while(1) {
					delaymycode(30);
					turn_encoder_left();
				}
				break;
			}
			
			case 3:{ 
				delaymycode(30);
				push_encoder_button();
			
				while(1){
					delaymycode(30);
					turn_encoder_right();		
		
					delaymycode(30);
					turn_encoder_right();
					
					delaymycode(30);
					turn_encoder_right();
					
					CDC_set_mute(&codec, ENABLE,  Aout1);
					CDC_set_mute(&codec, ENABLE,  Aout2);
					
					delaymycode(30);
					
					CDC_set_mute(&codec, DISABLE,  Aout1);
					CDC_set_mute(&codec, DISABLE,  Aout2);
					
					delaymycode(30);
					
					int16_t j = 0;
					for(j=0; j < 127; j++) {
						CDC_set_output_vol(&codec, j, Aout1);
						CDC_set_output_vol(&codec, j, Aout2);
						delaymycode(1);
					}
					
					for(j=127; j > 0; j--) {
						CDC_set_output_vol(&codec, j, Aout1);
						CDC_set_output_vol(&codec, j, Aout2);
						delaymycode(1);
					}
					
					for(j=10; j > -64; j--) {
						CDC_set_input_vol(&codec, j, Ain1);
						CDC_set_input_vol(&codec, j, Ain2);
						delaymycode(1);
					}
					
					for(j=-64; j < 0; j++) {
						CDC_set_input_vol(&codec, j, Ain1);
						CDC_set_input_vol(&codec, j, Ain2);
						delaymycode(1);
					}
				break;
				}
			}	
			
			case 4:{ 
				delaymycode(30);
				turn_encoder_right();		
	
				delaymycode(30);
				turn_encoder_right();
				
				delaymycode(30);
				turn_encoder_right();
				
				delaymycode(30);
				push_encoder_button();
				
				while(1){
					delaymycode(30);
					turn_encoder_right();		
		
					delaymycode(30);
					turn_encoder_right();
					
					delaymycode(30);
					turn_encoder_right();
				}
				break;
			}	
		}
	}
}
