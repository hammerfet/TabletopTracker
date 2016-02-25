/*
 * LED_Driver.c
 *
 *  Created on: Feb 18, 2016
 *      Author: hammerfet
 */
#include "em_device.h"
#include "em_chip.h"
#include "gpio_defs.h"
#include "em_timer.h"
#include "LED_Driver.h"

// LED colour/pwm value tables
uint16_t current_led_array[8][4] = { {0} };
uint16_t target_led_array[8][4] = { {0} };
int16_t led_change_rate[8][4] = { {0} };
uint16_t led_time_to_level[8] = { 0 };

// Local variables
static uint8_t current_colour = 0;
static uint8_t current_led = 0;


// Init all the LEDs with default times This
// should be called when the application starts
void led_init_all()
{
	for (uint8_t led = 0; led < 8; led++)
	{
	current_led_array[led][0] = 0;
	current_led_array[led][1] = 0;
	current_led_array[led][2] = 0;
	current_led_array[led][3] = 10000;

	led_change_rate[led][0] = 0;
	led_change_rate[led][1] = 0;
	led_change_rate[led][2] = 0;
	led_change_rate[led][3] = 0;
	}
}


// Set a single LED to a colour with time
void led_set_colour_ms(uint8_t led, uint16_t red, uint16_t green, uint16_t blue, uint16_t brightness, uint16_t ms)
{
	if(led > 7) return;

	target_led_array[led][0] = red;
	target_led_array[led][1] = green;
	target_led_array[led][2] = blue;
	target_led_array[led][3] = brightness;
	led_time_to_level[led] = ms;

	led_change_rate[led][0] = (target_led_array[led][0] - current_led_array[led][0]) / ms;
	led_change_rate[led][1] = (target_led_array[led][1] - current_led_array[led][1]) / ms;
	led_change_rate[led][2] = (target_led_array[led][2] - current_led_array[led][2]) / ms;
	led_change_rate[led][3] = (target_led_array[led][3] - current_led_array[led][3]) / ms;
}


// Set all LEDs to a colour with time
void led_set_colour_all_ms(uint16_t red, uint16_t green, uint16_t blue, uint16_t brightness, uint16_t ms)
{
	led_set_colour_ms(0, red, green, blue, brightness, ms);
	led_set_colour_ms(1, red, green, blue, brightness, ms);
	led_set_colour_ms(2, red, green, blue, brightness, ms);
	led_set_colour_ms(3, red, green, blue, brightness, ms);
	led_set_colour_ms(4, red, green, blue, brightness, ms);
	led_set_colour_ms(5, red, green, blue, brightness, ms);
	led_set_colour_ms(6, red, green, blue, brightness, ms);
	led_set_colour_ms(7, red, green, blue, brightness, ms);
}


// Get the target colours and time of an LED
void led_get_colour_ms(uint8_t led, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *brightness, uint16_t *ms)
{
	*red = target_led_array[led][0];
	*green =target_led_array[led][1];
	*blue = target_led_array[led][2];
	*brightness = target_led_array[led][3];
	*ms = led_time_to_level[led];
}


// Clear an LED within some ms value
void led_clear_ms(uint8_t led, uint16_t ms)
{
	led_set_colour_ms(led, 0, 0, 0, 10000, ms);
}


// Clears the LEDs in the application, though
// the drive lines still togggle
void led_clear_all_ms(uint16_t ms)
{
	led_clear_ms(0, ms);
	led_clear_ms(1, ms);
	led_clear_ms(2, ms);
	led_clear_ms(3, ms);
	led_clear_ms(4, ms);
	led_clear_ms(5, ms);
	led_clear_ms(6, ms);
	led_clear_ms(7, ms);
}


// Clears LED drive lines for device powering off
void led_power_off(void)
{
	LED_RED_BUS_CLEAR;
	LED_GREEN_BUS_CLEAR;
	LED_BLUE_BUS_CLEAR;

	LED_1_CLEAR;
	LED_2_CLEAR;
	LED_3_CLEAR;
	LED_4_CLEAR;
	LED_5_CLEAR;
	LED_6_CLEAR;
	LED_7_CLEAR;
	LED_8_CLEAR;
}


// This function drives the LEDs depending on their PWM values
// It should be called from a very fast timer
uint16_t led_timer_event(void)
{
	LED_RED_BUS_CLEAR;
	LED_GREEN_BUS_CLEAR;
	LED_BLUE_BUS_CLEAR;

	uint16_t time = current_led_array[current_led][current_colour];

	switch(current_colour++)
	{
		case 0:
			if(time > 1)
				LED_RED_BUS_SINK;
			break;

		case 1:
			if(time > 1)
				LED_GREEN_BUS_SINK;
			break;

		case 2:
			if(time > 1)
				LED_BLUE_BUS_SINK;
			break;

		case 3:
			break;
	}

	if(current_colour > 3)
	{
		switch(current_led++)
		{
			case 0:
				LED_8_CLEAR;
				LED_1_SET;
				break;

			case 1:
				LED_1_CLEAR;
				LED_2_SET;
				break;

			case 2:
				LED_2_CLEAR;
				LED_3_SET;
				break;

			case 3:
				LED_3_CLEAR;
				LED_4_SET;
				break;

			case 4:
				LED_4_CLEAR;
				LED_5_SET;
				break;

			case 5:
				LED_5_CLEAR;
				LED_6_SET;
				break;

			case 6:
				LED_6_CLEAR;
				LED_7_SET;
				break;

			case 7:
				LED_7_CLEAR;
				LED_8_SET;
				break;

		}
		current_colour = 0;
	}

	if(current_led > 7)
	{
		current_led = 0;
	}

	return time;
}


// This function manages fading of LEDs from one set of values to another.
// It should be run every 1mS
void led_fade_event(void)
{
	for (uint8_t led = 0; led < 8; led++)
	{
		for (uint8_t colour = 0; colour < 4; colour++)
		{
			if (led_change_rate[led][colour] > 0)
			{
				if((current_led_array[led][colour] + led_change_rate[led][colour]) < target_led_array[led][colour])
					current_led_array[led][colour] += led_change_rate[led][colour];

				else led_change_rate[led][colour] = 1;
			}

			if(led_change_rate[led][colour] < 0)
			{
				if((current_led_array[led][colour] + led_change_rate[led][colour]) > target_led_array[led][colour])
					current_led_array[led][colour] += led_change_rate[led][colour];
				else led_change_rate[led][colour] = -1;
			}
		}
	}
}
