/*
 * LED_Driver.h
 *
 *  Created on: Feb 18, 2016
 *      Author: hammerfet
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

void led_init_all();
void led_set_colour_ms(uint8_t led, uint16_t red, uint16_t green, uint16_t blue, uint16_t brightness, uint16_t ms);
void led_set_colour_all_ms(uint16_t red, uint16_t green, uint16_t blue, uint16_t brightness, uint16_t ms);
void led_get_colour_ms(uint8_t led, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *brightness, uint16_t *ms);
void led_clear_ms(uint8_t led, uint16_t ms);
void led_clear_all_ms(uint16_t ms);
void led_power_off(void);

uint16_t led_timer_event(void);
void led_fade_event(void);

#endif /* LED_DRIVER_H_ */
