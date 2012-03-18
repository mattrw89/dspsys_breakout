#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../lib_newhaven_screen/screen.h"

#define CHANNEL_DISPLAY_TEXT "Channel Display" 
#define CHANNEL_SELECT_TEXT "Channel Select"
#define VOLUME_TEXT "Volume"
#define AMP_TYPE_TEXT	"Amp Type"
#define HOME_TEXT	"SD Group 13"

typedef enum {
	CHANNEL_DISPLAY = 0x10,
	CHANNEL_SELECT = 0x11,
	CHANNEL_VOLUME = 0x12,
	AMP_TYPE = 0x13,
	CHANNEL_DISPLAY_2 = 0x20,
	CHANNEL_SELECT_2 = 0x21,
	CHANNEL_VOLUME_2 = 0x22,
	AMP_TYPE_2 = 0x23,
	CHANNEL_SELECT_3 = 0x31,
	HOME = 0x00
	
} Menu_enum;

typedef struct Display {
	Menu_enum menu_type;
	struct Display *left;
	struct Display *right;
	struct Display *select;
	struct Display *back;
	uint16_t i;
	char characters[2][17];
	void (*func_left)(struct Display*, Menu_enum, uint16_t);
	void (*func_right)(struct Display*,Menu_enum, uint16_t);
	void (*func_select)(struct Display*,Menu_enum, uint16_t);
	void (*func_back)(struct Display*,Menu_enum, uint16_t);
	
}Display;


//4 function that allow for movement through menu
void s1_right(Display *disp, Menu_enum menu_type, uint16_t value);

void s1_left(Display *disp, Menu_enum menu_type, uint16_t value);

void s1_select(Display *disp, Menu_enum menu_type, uint16_t value);

void s1_back(Display *disp, Menu_enum menu_type, uint16_t value);

// constructs a new menu object
void display_ctor(Display* disp, Menu_enum menu_type, Display *left, Display *right,
	Display *select, Display *back, uint16_t value);

void display_set_text(Display* disp, char* chars, uint8_t length);

void display_set_text_line_2(Display* disp, char* chars, uint8_t length);

void delaymycode(uint16_t delaytime);
#endif /*MENU_H_*/
