#include "ints.h"

void turn_encoder_right() {
	Display* disp = global_current_display(0);
	(*(disp->func_right))(disp, disp->menu_type, NULL);
}

void turn_encoder_left() {
	Display *disp = global_current_display(0);
	(*(disp->func_left))(disp, disp->menu_type, NULL);
}

void push_encoder_button() {
	Display *disp = global_current_display(0);
	(*(disp->func_select))(disp, disp->menu_type, NULL);
}

void push_back_button() {
	Display *disp = global_current_display(0);
	(*(disp->func_back))(disp, disp->menu_type, NULL);
}
