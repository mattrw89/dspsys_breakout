#include "global.h"

Display* global_current_display(Display* disp) {
	static Display* current_display_ptr;

	if( (disp != NULL) || (disp != 0) ) {
		current_display_ptr = disp;
	}
	return current_display_ptr;
}

//num only valid 0 through 2
Display* global_get_display(uint8_t num ) {
	static Display one,two,three,four,five;
	
	switch(num) {
		case 0:
			return &one;
		case 1:
			return &two;
		case 2:
			return &three;
		case 3:
			return &four;
		case 4:
			return &five;
		default: 
			return NULL;
	}
}
