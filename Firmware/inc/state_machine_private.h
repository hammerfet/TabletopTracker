/*
 * state_machine_private.h
 *
 *  Created on: Feb 22, 2016
 *      Author: hammerfet
 */

#ifndef STATE_MACHINE_PRIVATE_H_
#define STATE_MACHINE_PRIVATE_H_

// All the possible states
typedef enum{
	POWER_ON,
	POWER_ON_MODE_SET,
	POWER_OFF,
	MODE_1_INIT,
	MODE_2_INIT,
	MODE_1,
	MODE_1_SET_LED,
	MODE_1_BUTTON_DEBOUNCE,
	MODE_2,
	MODE_2_SET_LED,
	MODE_2_BUTTON_DEBOUNCE,
	MODE_2_TWINKLE_FX_INIT,
	MODE_2_TWINKLE_FX,
	MODE_2_SWIRL_FX_INIT,
	MODE_2_SWIRL_FX
}state_t;

state_t current_state;

// Application time variables
uint32_t reference_time;
uint32_t reference_time_auto_power_off;


// Useful functions for keeping track of states & time

// Initial state machine state
void state_machine_init(void)
{
	current_state = POWER_ON;
}

// Sets the next state
void next_state(state_t state)
{
	current_state = state;
}

// Sets a time reference
void set_reference_time(uint32_t time)
{
	reference_time = time;
}

// Resets the auto poweroff timer
void set_reference_time_auto_power_off(uint32_t time)
{
	reference_time_auto_power_off = time;
}

// Gets time since last reference
uint32_t time_since_last_reference(uint32_t time)
{
	return time - reference_time;
}

// Gets time since last power off time reference
uint32_t time_since_last_reference_auto_power_off(uint32_t time)
{
	return time - reference_time_auto_power_off;
}

#endif /* STATE_MACHINE_PRIVATE_H_ */
