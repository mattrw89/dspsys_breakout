#include "menu.h"
#include "global.h"

//------------------------------------------------------------------------------------------------------

void s1_right(Display *disp, Menu_enum menu_type, uint16_t value) {
	
	Display* oldcurrent = disp;
	Display* oldright = disp->right;
	Display* oldleft = disp->left;
	
	Display* oldselect = disp->select;
	Display* oldback = disp->back;
	
	//set up new left display (current)
	disp = oldright;
	disp->left = oldcurrent;
	disp->right = oldleft;
	
	
	//increment the menu_type
	if (menu_type < 0x13) {
		disp->menu_type = ++menu_type;
		//menu_type++;
	}
	else{ 
	disp->menu_type  = CHANNEL_DISPLAY;
	menu_type = CHANNEL_DISPLAY;
	}
	//set up new right display (advance in menu_type is)
	     //advanced menu_type
	     //set left screen to be current screen
	     //all other screens NULL
	     //TODO: Back should point to HOME
	     
	     //the menu_type for the ctor needs to be the menu type for the next right
	     if (menu_type  < 0x13) {
	     	menu_type++;
	     	}
	     else menu_type = CHANNEL_DISPLAY;
	     
	display_ctor(oldcurrent->left, menu_type, disp, NULL, NULL, NULL);
	
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
	global_current_display(disp);
	
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
	 
	//This function is using the address of left to build a new struct for left to point to
	display_ctor(oldcurrent->right, menu_type, NULL, disp, NULL, NULL);
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
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
	
	
	display_ctor(oldcurrent->select,menu_type,NULL,NULL,disp,NULL);
	
	screen_clear();
	Cursor_enum temp1 = SEC_1;
	screen_set_cursor(temp1);
	screen_write_txt(&(disp->characters[0][0]), strlen(disp->characters[0]));
	global_current_display(disp);
		
}

//------------------------------------------------------------------------------------------------------

void display_ctor(Display* disp, Menu_enum menu_type, Display* left, Display* right,
	Display* select, Display* back) {
		
	disp->menu_type = menu_type;
	disp->left = left;
	disp->right = right;
	disp->select = select;
	disp->back = back;
	
	switch(menu_type){
		case CHANNEL_DISPLAY://CHANNEL_DISPLAY:
			display_set_text(disp, CHANNEL_DISPLAY_TEXT, 16);
			break;
		
		case CHANNEL_SELECT://CHANNEL_SELECT:
			display_set_text(disp, CHANNEL_SELECT_TEXT, 16);
			break;
			
		case CHANNEL_VOLUME://CHANNEL_VOLUME:
			display_set_text(disp, VOLUME_TEXT, 16);
			break;
			
		case AMP_TYPE://AMP_TYPE:
		
			display_set_text(disp, AMP_TYPE_TEXT, 16);
			break;
		
		case CHANNEL_DISPLAY_2:
			
			break;
		
		case CHANNEL_SELECT_2:
		
			break;
			
		case CHANNEL_VOLUME_2:
		
			break;
			
		case AMP_TYPE_2:
		
			break;
			
		case CHANNEL_SELECT_3:
		
			break;
		
		case HOME:
			display_set_text(disp, HOME_TEXT, 16);
			break;
			
		default:
			printf("error disp_ctor");
			break;	
	}
}


//------------------------------------------------------------------------------------------------------

void display_set_text(Display* disp, char* chars, uint8_t length) {
	strncpy(&(disp->characters[0][0]), chars, length);
}

//------------------------------------------------------------------------------------------------------

void display_set_text_2(Display* disp, char* chars, uint8_t length){
	strncpy(&(disp->characters[2][0]), chars, length);	
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
