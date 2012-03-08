#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>
#include "lib/menu/menu.h"

Display* global_current_display(Display* disp);

Display* global_get_display(uint8_t num );

#endif /*GLOBAL_H_*/
