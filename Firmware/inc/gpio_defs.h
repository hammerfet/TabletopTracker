/*
 * PinMappings.h
 *
 *  Created on: Feb 17, 2016
 *      Author: hammerfet
 */
#ifndef PINMAPPINGS_H_
#define PINMAPPINGS_H_


#include "em_gpio.h"

#define LED_RED_BUS_SINK 		GPIO_PinOutClear(gpioPortC, 0)
#define LED_GREEN_BUS_SINK 		GPIO_PinOutClear(gpioPortB, 8)
#define LED_BLUE_BUS_SINK 		GPIO_PinOutClear(gpioPortB, 7)

#define LED_RED_BUS_CLEAR 		GPIO_PinOutSet(gpioPortC, 0)
#define LED_GREEN_BUS_CLEAR	 	GPIO_PinOutSet(gpioPortB, 8)
#define LED_BLUE_BUS_CLEAR 		GPIO_PinOutSet(gpioPortB, 7)

#define LED_1_SET				GPIO_PinOutSet(gpioPortC, 15)
#define LED_1_CLEAR				GPIO_PinOutClear(gpioPortC, 15)

#define LED_2_SET				GPIO_PinOutSet(gpioPortC, 14)
#define LED_2_CLEAR				GPIO_PinOutClear(gpioPortC, 14)

#define LED_3_SET				GPIO_PinOutSet(gpioPortD, 7)
#define LED_3_CLEAR				GPIO_PinOutClear(gpioPortD, 7)

#define LED_4_SET				GPIO_PinOutSet(gpioPortD, 6)
#define LED_4_CLEAR				GPIO_PinOutClear(gpioPortD, 6)

#define LED_5_SET				GPIO_PinOutSet(gpioPortB, 11)
#define LED_5_CLEAR				GPIO_PinOutClear(gpioPortB, 11)

#define LED_6_SET				GPIO_PinOutSet(gpioPortC, 1)
#define LED_6_CLEAR				GPIO_PinOutClear(gpioPortC, 1)

#define LED_7_SET				GPIO_PinOutSet(gpioPortE, 12)
#define LED_7_CLEAR				GPIO_PinOutClear(gpioPortE, 12)

#define LED_8_SET				GPIO_PinOutSet(gpioPortF, 2)
#define LED_8_CLEAR				GPIO_PinOutClear(gpioPortF, 2)

#define BUTTON_1_HIGH			(GPIO_PortInGet(gpioPortE) & (1 << 13))
#define BUTTON_2_HIGH			(GPIO_PortInGet(gpioPortA) & (1 << 0 ))

#endif /* PINMAPPINGS_H_ */
