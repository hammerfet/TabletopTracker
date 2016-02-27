/*
 * state_machine.c
 *
 *  Created on: Feb 22, 2016
 *      Author: hammerfet
 */

#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"

#include "state_machine.h"
#include "state_machine_private.h"
#include "gpio_defs.h"
#include "led_driver.h"
#include "random_values.h"


// Application variables
#define AUTO_POWER_OFF_TIME 1800000 // 30min power off timer

static uint8_t led_counter = 0;
static int8_t health_fatigue_count = 0;
static uint16_t saved_red = 0;
static uint16_t saved_green = 0;
static uint16_t saved_blue = 0;
static uint16_t saved_brightness = 0;
static int8_t previous_led;
static int8_t token_colour;
static uint16_t random_time = 300;
static uint8_t swirl_start_location = 0;
static bool swirl_direction = false;


// Application state machine
void state_machine(uint32_t time)
{
	switch(current_state)
	{

	// First state, goes to power on state with reference time
	case POWER_ON:

		led_init_all();

		set_reference_time(time);
		next_state(POWER_ON_MODE_SET);

		break;


	// After a time, checks if button is still pressed, goes to
	// one of two modes, if not pressed, powers off again
	case POWER_ON_MODE_SET:

		if(time_since_last_reference(time) > 2000)
		{
			if(BUTTON_1_HIGH && BUTTON_2_HIGH)
				next_state(MODE_2_INIT);

			else if(BUTTON_1_HIGH || BUTTON_2_HIGH)
				next_state(MODE_1_INIT);

			else
				next_state(POWER_OFF);
		}

		break;


	// Power off state, clears LEDs and goes into EM4
	case POWER_OFF:

		led_init_all();
		led_power_off();

		GPIO_EM4EnablePinWakeup( GPIO_EM4WUEN_EM4WUEN_E13, _GPIO_EM4WUPOL_EM4WUPOL_E13 );
		GPIO_EM4EnablePinWakeup( GPIO_EM4WUEN_EM4WUEN_A0, _GPIO_EM4WUPOL_EM4WUPOL_A0 );
		EMU_EnterEM4();

		break;


	// If both buttons are held for a certain time, the device powers off
	case MODE_1_POWER_OFF_HOLD_BUTTON:

		if(time_since_last_reference(time) > 200)
		{
			set_reference_time(time);
			if(BUTTON_1_HIGH && BUTTON_2_HIGH)
			{
				led_set_colour_ms(led_counter++, 0, 0, 0, 10000, 100);
				{
					if (led_counter == 8)
					next_state(POWER_OFF);
				}
			}

			else
			{
				led_clear_all_ms(100);
				next_state(MODE_1_SET_LED);
			}
		}

		break;


	// If both buttons are held for a certain time, the device powers off
	case MODE_2_POWER_OFF_HOLD_BUTTON:

		if(time_since_last_reference(time) > 200)
		{
			set_reference_time(time);
			if(BUTTON_1_HIGH && BUTTON_2_HIGH)
			{
				led_set_colour_ms(led_counter++, 0, 0, 0, 10000, 100);
				{
					if (led_counter == 8)
					next_state(POWER_OFF);
				}
			}

			else
			{
				led_clear_all_ms(100);
				next_state(MODE_2_SET_LED);
			}
		}

		break;


	// Starts Mode 1 (health/fatigue counter) just a nice effect
	case MODE_1_INIT:

		if (time_since_last_reference(time) > 150)
		{
			if (led_counter < 8)
			{
				if (led_counter > 0)
				{
					led_set_colour_ms(led_counter - 1, 0, 0, 0, 10000, 100);
					led_set_colour_ms(7 - led_counter + 1, 0, 0, 0, 10000, 100);
				}

				led_set_colour_ms(led_counter, 10000, 0, 0, 0, 100);
				led_set_colour_ms(7 - led_counter, 7000, 3000, 0, 0, 100);
				set_reference_time(time);

				led_counter++;
			}

			else
			{
				led_counter = 0;
				led_clear_all_ms(100);
				next_state(MODE_1);
			}
		}

		break;


	// Starts Mode 2 (coloured tokens) just a nice effect
	case MODE_2_INIT:

		if (time_since_last_reference(time) > 150)
		{
			if (led_counter < 8)
			{
				if (led_counter > 0)
				{
					led_set_colour_ms(led_counter - 1, 0, 0, 0, 10000, 100);
					led_set_colour_ms(7 - led_counter + 1, 0, 0, 0, 10000, 100);
				}

				led_set_colour_ms(led_counter, 0, 0, 10000, 0, 100);
				led_set_colour_ms(7 - led_counter, 5000, 0, 5000, 0, 100);
				set_reference_time(time);

				led_counter++;
			}

			else
			{
				led_counter = 0;
				led_clear_all_ms(100);
				set_reference_time(time);
				next_state(MODE_2_SET_LED);
			}
		}

		break;


	// Mode 1 checks for button presses and monitors auto power off time
	// also triggers some effects after a while. Numbers go from -24 to 24
	// positive numbers count health and negative numbers count fatigue
	case MODE_1:

		// Power off/switch mode
		if(BUTTON_1_HIGH && BUTTON_2_HIGH)
		{
			led_counter = 0;
			set_reference_time(time);
			set_reference_time_auto_power_off(time);
			next_state(MODE_1_POWER_OFF_HOLD_BUTTON);
			led_set_colour_all_ms(3333, 3333, 3333, 0, 100);
		}

		// If button up then increment the health/fatigue count
		else if(BUTTON_1_HIGH)
		{
			if (health_fatigue_count < 24) // obey max limit of 24
				health_fatigue_count++;

			set_reference_time(time);
			set_reference_time_auto_power_off(time);
			next_state(MODE_1_SET_LED);
		}

		// otherwise decrement if down button pressed
		else if (BUTTON_2_HIGH)
		{
			if (health_fatigue_count > -24) // obey min limit of -24
				health_fatigue_count--;

			set_reference_time(time);
			set_reference_time_auto_power_off(time);
			next_state(MODE_1_SET_LED);
		}

		// After 10s and if health counter is 0,
		// do an effect so show device is still on
		else if (time_since_last_reference(time) > 5000)
		{
			if (health_fatigue_count == 0)
				next_state(MODE_1_INIT);
		}

		// If autopower off timer is up, then power off
		if (time_since_last_reference_auto_power_off(time) > AUTO_POWER_OFF_TIME)
			next_state(POWER_OFF);

		break;


	// Sets the LEDs for how much health/fatigue is selected. Again positive
	// numbers are health (red) and negative numbers are fatigue (yellow)
	case MODE_1_SET_LED:

		// Show health (red & white) red is units and white is 5s
		if (health_fatigue_count > 0)
		{
			int8_t hfc_fives = health_fatigue_count / 5;
			int8_t hfc_units = health_fatigue_count - (5 * hfc_fives);

			for(uint8_t i = 0; i < hfc_fives; i++)
				led_set_colour_ms(i, 3333, 3333, 3333, 0, 100);

			for(uint8_t i = hfc_fives; i < hfc_units + hfc_fives; i++)
				led_set_colour_ms(i, 10000, 0, 0, 0, 100);

			for (uint8_t i = hfc_fives + hfc_units; i < 9; i++)
				led_set_colour_ms(i, 0, 0, 0, 10000, 100);
		}

		// Show fatigue (yellow & white) yellow is units and white is 5s
		else if (health_fatigue_count < 0)
		{
			int8_t hfc_fives = -health_fatigue_count / 5;
			int8_t hfc_units = -health_fatigue_count - (5 * hfc_fives);

			for(uint8_t i = 0; i < hfc_fives; i++)
				led_set_colour_ms(i, 3333, 3333, 3333, 0, 100);

			for(uint8_t i = hfc_fives; i < hfc_units + hfc_fives; i++)
				led_set_colour_ms(i, 7000, 3000, 0, 0, 100);

			for (uint8_t i = hfc_fives + hfc_units; i < 9; i++)
				led_set_colour_ms(i, 0, 0, 0, 10000, 100);
		}

		// Clear LEDs is health/fatigue value is 0
		else
		{
			led_set_colour_ms(0, 0, 0, 0, 10000, 100);
		}

		next_state(MODE_1_BUTTON_DEBOUNCE);

		break;


	// Debounce state for when button in pressed and LEDs are set
	case MODE_1_BUTTON_DEBOUNCE:

		// Debounce value of 200
		if(time_since_last_reference(time) > 200)
			next_state(MODE_1);

		break;


	// Mode 2 button checker and auto power off timeout
	case MODE_2:

		// Power off/switch mode
		if(BUTTON_1_HIGH && BUTTON_2_HIGH)
		{
			led_counter = 0;
			set_reference_time(time);
			set_reference_time_auto_power_off(time);
			next_state(MODE_2_POWER_OFF_HOLD_BUTTON);
			led_set_colour_all_ms(3333, 3333, 3333, 0, 100);
			break;
		}

		// This counter rolls around at 20. There are three
		// banks of colour effects with 7 colours each
		// 0 to 7 are solid colours, 8 to 14 are twinkle effects
		// and 15 to 20 are swirl effects
		else if(BUTTON_1_HIGH)
		{
			token_colour++;
			if (token_colour > 20)
				token_colour = 0;
			set_reference_time_auto_power_off(time);
			next_state(MODE_2_SET_LED);
		}

		else if (BUTTON_2_HIGH)
		{
			token_colour--;
			if (token_colour < 0)
				token_colour = 20;
			set_reference_time_auto_power_off(time);
			next_state(MODE_2_SET_LED);
			break;
		}

		// if 6 < token colour < 14.. we can apply a flash effect
		else if (token_colour > 6 && token_colour < 14)
		{
			if(time_since_last_reference(time) > random_time)
			{
				random_time = rand_0_10() * 500;
				set_reference_time(time);
				next_state(MODE_2_TWINKLE_FX_INIT);
			}
		}

		// if 13 < token colour < 21.. we can apply a swirl effect
		else if (token_colour > 13 && token_colour < 21)
		{
			if(time_since_last_reference(time) > random_time)
			{
				// We need to get a random time, start location and direction
				random_time = rand_0_10() * 1000;
				swirl_start_location = rand_0_10();
				previous_led = swirl_start_location;
				swirl_direction = rand_0_10() % 2;
				set_reference_time(time);

				// Only run fx if we are within range
				if (swirl_start_location < 8)
					next_state(MODE_2_SWIRL_FX_INIT);
			}
		}

		// Autopower off timer
		if (time_since_last_reference_auto_power_off(time) > AUTO_POWER_OFF_TIME)
			next_state(POWER_OFF);

		break;


	// Sets LEDs for mode 2
	case MODE_2_SET_LED:

		// 0 to 6 are basic colours, 7 to 13 are flashing effects
		// 14 to 20 are swirling effects
		switch(token_colour)
		{
		case 0:
		case 7:
		case 14:
			led_set_colour_all_ms(5000, 0, 0, 5000, 500);
			break;

		case 1:
		case 8:
		case 15:
			led_set_colour_all_ms(0, 5000, 0, 5000, 500);
			break;

		case 2:
		case 9:
		case 16:
			led_set_colour_all_ms(0, 0, 5000, 5000, 500);
			break;

		case 3:
		case 10:
		case 17:
			led_set_colour_all_ms(2500, 0, 2500, 5000, 500);
			break;

		case 4:
		case 11:
		case 18:
			led_set_colour_all_ms(0, 2500, 2500, 5000, 500);
			break;

		case 5:
		case 12:
		case 19:
			led_set_colour_all_ms(2500, 2500, 0, 5000, 500);
			break;

		case 6:
		case 13:
		case 20:
			led_set_colour_all_ms(1667, 1667, 1667, 5000, 500);
			break;
		}

		set_reference_time(time);
		next_state(MODE_2_BUTTON_DEBOUNCE);

		break;


	// Debounce state for Mode 2 button press after LEDs are set
	case MODE_2_BUTTON_DEBOUNCE:

		if(time_since_last_reference(time) > 200)
			next_state(MODE_2);

		break;


	// Here is where the Mode 2 twinkle effect starts, we save existing led
	// values and set it white
	case MODE_2_TWINKLE_FX_INIT:

		previous_led = rand_0_10();

		if(previous_led < 8)
			led_get_colour_ms(previous_led, &saved_red, &saved_green, &saved_blue, &saved_brightness, NULL);

		if(previous_led < 8)
			led_set_colour_ms(previous_led, 3333, 3333, 3333, 0, 100);

		set_reference_time(time);
		next_state(MODE_2_TWINKLE_FX);

		break;


	// After some time we set the led back to the initial colour
	case MODE_2_TWINKLE_FX:

		if (time_since_last_reference(time) > 50)
		{
			if(previous_led < 8)
				led_set_colour_ms(previous_led, saved_red, saved_green, saved_blue, saved_brightness, 100);

			set_reference_time(time);
			next_state(MODE_2);
		}

		break;


	// Here is where the Mode 2 swirl effect starts. We go from the
	// previous_led set by swirl_start_location set in MODE_2
	// Depending on direction we increment or decrement. Again save
	// colour and set white
	case MODE_2_SWIRL_FX_INIT:

		if(swirl_direction)
			previous_led++;

		else
			previous_led--;

		if (previous_led > 7)
			previous_led -= 8;

		if (previous_led < 0)
			previous_led += 8;

		led_get_colour_ms(previous_led, &saved_red, &saved_green, &saved_blue, &saved_brightness, NULL);

		led_set_colour_ms(previous_led, 3333, 3333, 3333, 0, 400);

		set_reference_time(time);
		next_state(MODE_2_SWIRL_FX);

		break;


	// Now we set the led back to the initial colour and move on to the
	// next led in sequence. If we completed the round, we return to MODE_2
	case MODE_2_SWIRL_FX:

		if (time_since_last_reference(time) > 50)
		{
			led_set_colour_ms(previous_led, saved_red, saved_green, saved_blue, saved_brightness, 200);

			set_reference_time(time);

			if(previous_led == swirl_start_location)
				next_state(MODE_2);

			else
				next_state(MODE_2_SWIRL_FX_INIT);
		}

		break;
	}
}
