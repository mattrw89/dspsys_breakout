#include <stdio.h>
#include "menu.h"
#include "global.h"
#include "../lib_newhaven_screen/screen.h"


//------------------------------------------------------------------------------------------------------

void s1_right(Display *disp, Menu_enum menu_type, uint16_t value) {
	
	//temp storage for realignment of pointers
	Display* oldcurrent = disp;
	Display* oldright = disp->right;
	Display* oldleft = disp->left;
	
	Display* oldselect = disp->select;
	Display* oldback = disp->back;
	
	//realign pointers to the apprioate spot
	disp = oldright;
	disp->left = oldcurrent;
	disp->right = oldleft;
	
	disp->back = oldback;
	disp->select = oldselect;

	//determines which stage menu is at
	switch(((int)menu_type >> 4)) {
		
		//turning right from home
		case(0): {
			display_ctor(oldcurrent->left, menu_type, disp, disp, oldselect, oldback,NULL);
			break;
		}
			
		//turning right from stage 1
		case(1): {
			if (menu_type < 0x13) {
				disp->menu_type = ++menu_type;
			}
			else{ 
				disp->menu_type  = CHANNEL_DISPLAY;
				menu_type = CHANNEL_DISPLAY;
			}
			
			Menu_enum temp_menu_type = (Menu_enum)(menu_type + 0x10);
			display_ctor(disp->select,temp_menu_type,NULL,NULL,NULL,disp,1);
			
			if (menu_type  < 0x13) {
				menu_type++;
			}
			else menu_type = CHANNEL_DISPLAY;
	 
			display_ctor(disp->right, menu_type, disp, NULL, oldselect, oldback,NULL);
			break;
		}
			
		//turning right from stage 2
		case(2): {
			//determines which stage 2 menu is in
			switch((int)(menu_type & 0x0F)){
				//channel display stage 2
				case 0:{
					uint16_t temp;
					
					if(disp->i < 8) //8 number of outputs on the breakout box
					temp = (disp->i)+1;
					
					else
					temp = 1;
					
					display_ctor(oldleft,menu_type,disp,NULL,oldselect,oldback,temp);
					break;}
					
				//channel select stage 2
				case 1: {
					uint16_t temp;
					
					if(disp->i < NUM_OUTPUT_CHANNELS)	//checks for end of channel list
					temp = (disp->i)+1;
					
					else 
					temp = 1;		//wraps channel list
					
					display_ctor(oldleft,menu_type,disp,NULL,oldselect,oldback,temp);  //constructs the next right
					break;
				}
				//volume stage 2
				case 2:{
					uint16_t temp;
					
					if(disp->i < 12)	//checks for end of volume
					temp = (disp->i)+1;
					
					else 
					temp = 1;		//wraps channel list
					
					display_ctor(oldleft,menu_type,disp,NULL,oldselect,oldback,temp);  //constructs the next right
					break;
				}
					break;
					
					
				//amp type stage 2
				case 3:{
					uint16_t temp;
					
					if(disp->i < 2)	//checks for end of amp type list
					temp = (disp->i)+1;
					
					else 
					temp = 1;		//wraps channel list
					
					display_ctor(oldleft,menu_type,disp,NULL,oldselect,oldback,temp);  //constructs the next right
					break;
				}
					break;
			}
		
			break;
		}
		
		//turning right from stage 3
		case(3): {
			
		
			break;
		}
	}
		
		
	
	screen_clear();		//clear screen
	Cursor_enum temp1 = SEC_1;  
	screen_set_cursor(temp1);	//set cursor on screen sec 1
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));	//writes the first line of characters to screen
	
	if((disp->menu_type >> 4)> 1)	//writes second line of characters to screen
		screen_write_txt_line_2(&(disp->characters[1][0]),strlen(disp->characters[1]));
		
	global_current_display(disp);	//updates current screen object
	
	//back stays the same
	
	//change select according to menu_type
		
}


//------------------------------------------------------------------------------------------------------

void s1_left(Display *disp, Menu_enum menu_type, uint16_t value){
	
	Display* oldcurrent = disp;
	Display* oldright = disp->right;
	Display* oldleft = disp->left;
	
	Display* oldselect = disp->select;
	Display* oldback = disp->back;
	
	
	disp = oldleft;
	disp->left = oldright;
	disp->right = oldcurrent;
	
	
	switch((menu_type >>4)) {
		
		case(0):
			display_ctor(oldcurrent->left, menu_type, disp, NULL, oldselect, oldback,NULL);
			break;
	
		case(1):
			if(menu_type > 0x10){
				disp->menu_type = --menu_type;
			} 
			else{ 
				disp->menu_type = AMP_TYPE; 
				menu_type = AMP_TYPE;
			}
	
			if (menu_type > 0x10) {
	 			menu_type--;
	 		}
	 		else menu_type = AMP_TYPE;
	 
			display_ctor(oldcurrent->right, menu_type, NULL, disp, oldselect, oldback,NULL);
			break;
		
		case(2):
			switch((int)(menu_type & 0x0F)){
				//channel display stage 2
				case 0:
					break;
				//channel select stage 2
				case 1: {
					uint16_t temp;
					
					if(disp->i >= 2) {	//checks for end of channel list
						temp = (disp->i) -1;
					}else temp = NUM_OUTPUT_CHANNELS;	//wraps channel list
					
					display_ctor(oldright,menu_type,NULL,disp,oldselect,oldback,temp);	//constructs the next left
					break;
				}
			}
			break;
		
		
		case(3):
			
			break;
	}
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
	if((disp->menu_type >> 4) > 1)  //writes second lin of charaters to screen
		screen_write_txt_line_2(&(disp->characters[1][0]),strlen(disp->characters[1]));
	
	global_current_display(disp);
	

}

//------------------------------------------------------------------------------------------------------

void s1_select(Display *disp, Menu_enum menu_type, uint16_t value){
	
	Display* oldcurrent = disp;
	Display* oldright = disp->right;
	Display* oldleft = disp->left;
	
	Display* oldselect = disp->select;
	Display* oldback = 	disp->back;
	
	disp = oldselect;
	disp->back = oldcurrent;
	disp->select = oldback;
	
	disp->left = oldleft;
	disp->right = oldright;

	//determines which stage menu is in
	switch(((int)menu_type >> 4)){
		//home stage
		case 0:{
			menu_type = (Menu_enum)(menu_type + 0x10);	
			disp->menu_type = menu_type;	//changes current menu_type of screen object 
			display_ctor(disp->left,AMP_TYPE,NULL,NULL,NULL,disp->back,NULL);	//construct future left object
			display_ctor(disp->select,CHANNEL_DISPLAY_2,NULL,NULL,NULL,disp->back,1);	//construct future select object
			display_ctor(disp->right,CHANNEL_SELECT,NULL,NULL,NULL,disp->back,NULL); //construct future right object
			break;}
			
		case 1:{
			// second stage
			menu_type = (Menu_enum)(menu_type + 0x10);
			disp->menu_type = menu_type;		//updates menu type

			//determines which stage 2 etc. channel display, channel select
			switch((disp->menu_type) & 0x0F){
				case 0:	{	//channel display
					display_ctor(disp->left,CHANNEL_DISPLAY_2,NULL,NULL,NULL,disp->back,8);
					display_ctor(disp->right,CHANNEL_DISPLAY_2,NULL,NULL,NULL,disp->back,2);
					break;}
				case 1:{	//channel select
					display_ctor(disp->left,CHANNEL_SELECT_2,NULL,NULL,NULL,disp->back,NUM_OUTPUT_CHANNELS);
					display_ctor(disp->right,CHANNEL_SELECT_2,NULL,NULL,NULL,disp->back,2);
					break;}
				case 2:{		//volume
					display_ctor(disp->left,CHANNEL_VOLUME_2,NULL,NULL,NULL,disp->back,11);
					display_ctor(disp->right,CHANNEL_VOLUME_2,NULL,NULL,NULL,disp->back,2);
					break;}
				case 3:	{	//amp type
					display_ctor(disp->left,AMP_TYPE_2,NULL,NULL,NULL,disp->back,2);
					display_ctor(disp->right,AMP_TYPE_2,NULL,NULL,NULL,disp->back,2);
					break;}
			}
			
			
			break;}
			
		case 2:{
			if(menu_type == CHANNEL_SELECT_2){
				menu_type = (Menu_enum)(menu_type + 0x10);
				disp->menu_type = menu_type;
			
				display_ctor(disp->left,CHANNEL_SELECT_3,NULL,NULL,NULL,disp->back,8);
				display_ctor(disp->right,CHANNEL_SELECT_3,NULL,NULL,NULL,disp->back,2);
				
			}
			else { 
				disp->menu_type = HOME;
				
				display_ctor(disp->left,HOME,NULL,NULL,NULL,NULL,NULL);
				display_ctor(disp->right,HOME,NULL,NULL,NULL,NULL,NULL);
				display_ctor(disp->back,HOME,NULL,NULL,NULL,NULL,NULL);
				display_ctor(disp->select,CHANNEL_DISPLAY,NULL,NULL,NULL,NULL,NULL);
			}
			break;}
		
		case 3:{
			disp->menu_type = menu_type;
			break;}
	}

	switch ( (int)(menu_type >> 4) ) {
		//IF MENU TYPE IS HOME
		case 0:
			menu_type = (Menu_enum)(menu_type + 0x10);
			break;
		//if menu type is stage 2 
		case 1:
			menu_type = (Menu_enum)(menu_type + 0x10);
			break;
		//if menu type is stage 3
		case 2: {
			if(menu_type == 0x21) {
				menu_type = (Menu_enum)(menu_type + 0x10);
				break;
			} else { 
				menu_type = HOME;
				break;
			}
		}
		//if menu type is stage 4
		case 3:
			menu_type = HOME;
			break;
	}
	
	display_ctor(oldcurrent->back,menu_type,NULL,NULL,NULL,disp,NULL);
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
	
	if((disp->menu_type >> 4) > 1)  //writes second lin of charaters to screen
		screen_write_txt_line_2(&(disp->characters[1][0]),strlen(disp->characters[1]));
	
	
	global_current_display(disp);
	
}

//------------------------------------------------------------------------------------------------------


void s1_back(Display *disp, Menu_enum menu_type, uint16_t value){
	uint8_t temp;
	
	Display* oldcurrent = disp;
	Display* oldright = disp->right;
	Display* oldleft = disp->left;
	
	Display* oldselect = disp->select;
	Display* oldback = disp->back;
	
	disp = oldback;
	disp->select = oldcurrent;
	disp->back = oldselect;
	
	if(menu_type > 0x00){
		menu_type = (Menu_enum)(menu_type - 0x10);
		disp->menu_type = menu_type;	
	}
	else {
		disp->menu_type = (Menu_enum)(0x00);
	}
	
	if(menu_type > 0x00){
		menu_type = (Menu_enum)(menu_type - 0x10);	
	}
	
	
	display_ctor(oldcurrent->select,menu_type,NULL,NULL,disp,NULL,NULL);
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
	global_current_display(disp);
		
}

//------------------------------------------------------------------------------------------------------

void display_ctor(Display* disp, Menu_enum menu_type, Display* left, Display* right,
	Display* select, Display* back, uint16_t value) {
		
	disp->menu_type = menu_type;
	disp->left = left;
	disp->right = right;
	disp->select = select;
	disp->back = back;
	disp->i = value;
	
	switch(menu_type){
		case CHANNEL_DISPLAY:{//CHANNEL_DISPLAY:
			display_set_text(disp, CHANNEL_DISPLAY_TEXT, 16);
			break;}
		
		case CHANNEL_SELECT:{//CHANNEL_SELECT:
			display_set_text(disp, CHANNEL_SELECT_TEXT, 16);
			break;}
			
		case CHANNEL_VOLUME:{//CHANNEL_VOLUME:
			display_set_text(disp, VOLUME_TEXT, 16);
			break;}
			
		case AMP_TYPE:{//AMP_TYPE:
			display_set_text(disp, AMP_TYPE_TEXT, 16);
			break;}
		
		case CHANNEL_DISPLAY_2:{
			switch(value){
				case 1:{
					display_set_text(disp,"L/Main Speaker",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 2:{
					display_set_text(disp,"R Speaker",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 3:{
					display_set_text(disp,"L SPDIF",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}				
				case 4:{
					display_set_text(disp,"R SPDIF",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 5:{
					display_set_text(disp,"L XLR",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 6:{
					display_set_text(disp,"R XLR",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 7:{
					display_set_text(disp,"L Headphone",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}
				case 8:{
					display_set_text(disp,"R Headphone",16);
					//this is just to load something onto the second line this will need to be replaced
					Io_enum temp_io = OUTPUT;
					Channel* temp_channel = get_channel_from_memory(temp_io, value);
					display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
					break;
				}												
			}
			
			break;}
		
		case CHANNEL_SELECT_2:{
			display_set_text(disp, CHANNEL_SELECT_TEXT, 16);
			Io_enum temp_io = OUTPUT;
			Channel* temp_channel = get_channel_from_memory(temp_io, value);
			display_set_text_line_2(disp, channel_get_name(temp_channel), 16);
			break;}
			
		case CHANNEL_VOLUME_2:{
			display_set_text(disp, VOLUME_TEXT, 16);	//volume TODO: volume display
			display_set_text_line_2(disp, "-123456789AB+", 16);
			break;}
			
		case AMP_TYPE_2:{
			display_set_text(disp, AMP_TYPE_TEXT, 16);
			switch(value){
				case 1: {
					 display_set_text_line_2(disp, "Stereo", 16);
					 break;
				}
				case 2: {
					display_set_text_line_2(disp, "Mono", 16);
					break;
				}
			}
			break;}
			
		case CHANNEL_SELECT_3:{
			display_set_text(disp, "channel select 3", 16);
						switch(value){
				case 1:{
					display_set_text_line_2(disp,"L/Main Speaker",16);
					break;
				}
				case 2:{
					display_set_text_line_2(disp,"R Speaker",16);
					break;
				}
				case 3:{
					display_set_text_line_2(disp,"L SPDIF",16);
					break;
				}				
				case 4:{
					display_set_text_line_2(disp,"R SPDIF",16);
					break;
				}
				case 5:{
					display_set_text_line_2(disp,"L XLR",16);
					break;
				}
				case 6:{
					display_set_text_line_2(disp,"R XLR",16);
					break;
				}
				case 7:{
					display_set_text_line_2(disp,"L Headphone",16);
					break;
				}
				case 8:{
					display_set_text_line_2(disp,"R Headphone",16);
					break;
				}												
			}
			break;}
		
		case HOME:{
			display_set_text(disp, HOME_TEXT, 16);
			break;}
			
		default:{
			printf("error disp_ctor");
			break;}	
	}
}


//------------------------------------------------------------------------------------------------------

void display_set_text(Display* disp, char* chars, uint8_t length) {
	strncpy(&(disp->characters[0][0]), chars, length);
}

//------------------------------------------------------------------------------------------------------

void display_set_text_line_2(Display* disp, char* chars, uint8_t length){
	strncpy(&(disp->characters[1][0]), chars, length);	
}

//------------------------------------------------------------------------------------------------------

void delaymycode(uint16_t delaytime) {
	uint16_t i = 0;
	
	while(i < delaytime){
		SysCtlDelay(200000);  //100ms. argument of 100 is 2uS
		i++;
	}
	return;
}
