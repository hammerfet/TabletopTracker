/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_emu.h"
#include "em_gpio.h"

#include "InitDevice.h"
#include "led_driver.h"
#include "state_machine.h"

static uint32_t application_timer = 0;

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  // Set default IO configuration
  enter_DefaultMode_from_RESET();

  // Setup timer interrupts
  NVIC_EnableIRQ(TIMER0_IRQn);
  TIMER_IntEnable(TIMER0, TIMER_IF_OF);

  NVIC_EnableIRQ(TIMER1_IRQn);
  TIMER_IntEnable(TIMER1, TIMER_IF_OF);

  // Set timer period for ~1mS
  TIMER_TopSet(TIMER1, 94);

  // Put state machine into initial state
  state_machine_init();

  // Do nothing, we are fully timer event driven
  while (1){}
}

// Timer for LED modulation events
void TIMER0_IRQHandler(void)
{
	// Clear interrupt flag
	TIMER_IntClear(TIMER0, TIMER_IF_OF);

	// Get the new PWM value
	TIMER_TopSet(TIMER0, led_timer_event());

	// Zero and restart the timer
	TIMER_CounterSet(TIMER0, 0);
	TIMER_Enable(TIMER0, TIMER_CMD_START);
}

// Timer for state machine events
void TIMER1_IRQHandler(void)
{
	// Clear interrupt flag
	TIMER_IntClear(TIMER1, TIMER_IF_OF);

	// Run LED fade application
	led_fade_event();

	// Run applcation state machine
	state_machine(application_timer++);
}
