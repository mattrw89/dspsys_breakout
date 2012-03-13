#include "global.h"

#define NUM_INPUT_CHANNELS 14
#define NUM_OUTPUT_CHANNELS 14

// goal: statically allocate Channel objects in memory
// given Io_enum and a integral channel number within bounds
// return a pointer to the Channel object
Channel* get_channel_from_memory(Io_enum io, uint8_t channel_number) {
	static Channel input_channels[NUM_INPUT_CHANNELS];
	static Channel output_channels[NUM_OUTPUT_CHANNELS];

	//printf("size of channel %d bytes\n", sizeof(Channel));
	//printf("inputs ch1: 0x%X , ch2: 0x%X\n, ch14: 0x%X", &input_channels[0], &input_channels[1], &input_channels[13]);
	//printf("outputs ch1: 0x%X , ch2: 0x%X\n", &output_channels[0], &output_channels[1]);
	//printf("difference in ch1 and ch2: %d bytes\n", (&output_channels[1] - &output_channels[0]));

	//verify that the channel number is within bounds and that a valid IO enum value is given
	if( io == INPUT ) {
		//printf("input channel %d requested.  address: 0x%X\n",channel_number,&(input_channels[channel_number - 1]));
		return &(input_channels[channel_number - 1]);
	}
	else if( io == OUTPUT ) {
		//printf("output channel %d requested.  address: 0x%X\n",channel_number,&(output_channels[channel_number - 1]));
		return &(output_channels[channel_number - 1]);		
	} else return NULL;
}

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
