//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library includes]
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
// [Library includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	HFXO_enter_DefaultMode_from_RESET();
	CMU_enter_DefaultMode_from_RESET();
	TIMER0_enter_DefaultMode_from_RESET();
	TIMER1_enter_DefaultMode_from_RESET();
	PORTIO_enter_DefaultMode_from_RESET();
	// [Config Calls]$

}

//================================================================================
// HFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void HFXO_enter_DefaultMode_from_RESET(void) {
	// $[HFXO]
	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_HFXOMODE_MASK) | CMU_CTRL_HFXOMODE_XTAL;

	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_HFXOBOOST_MASK)
			| CMU_CTRL_HFXOBOOST_50PCENT;

	SystemHFXOClockSet(24000000);
	// [HFXO]$

}

//================================================================================
// LFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void LFXO_enter_DefaultMode_from_RESET(void) {
	// $[Use oscillator source]
	// [Use oscillator source]$

	// $[LFXO Boost Percent]
	// [LFXO Boost Percent]$

	// $[REDLFXO Boost]
	// [REDLFXO Boost]$

}

//================================================================================
// CMU_enter_DefaultMode_from_RESET
//================================================================================
extern void CMU_enter_DefaultMode_from_RESET(void) {
	// $[LFXO enable]
	// [LFXO enable]$

	// $[HFXO enable]
	// [HFXO enable]$

	// $[LFACLK Setup]
	// [LFACLK Setup]$

	// $[High Frequency Clock select]
	/* Using HFXO as high frequency clock, HFCLK */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
	// [High Frequency Clock select]$

	// $[LF clock tree setup]
	/* No LF peripherals enabled */
	// [LF clock tree setup]$
	// $[Peripheral Clock enables]
	/* Enable clock for TIMER0 */
	CMU_ClockEnable(cmuClock_TIMER0, true);

	/* Enable clock for TIMER1 */
	CMU_ClockEnable(cmuClock_TIMER1, true);

	/* Enable clock for GPIO by default */
	CMU_ClockEnable(cmuClock_GPIO, true);

	// [Peripheral Clock enables]$

}

//================================================================================
// ACMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP0_enter_DefaultMode_from_RESET(void) {
	// $[ACMP Initialization]
	// [ACMP Initialization]$

	// $[ACMP Channel config]
	// [ACMP Channel config]$

}

//================================================================================
// RTC_enter_DefaultMode_from_RESET
//================================================================================
extern void RTC_enter_DefaultMode_from_RESET(void) {
	// $[RTC_Init]
	// [RTC_Init]$

}

//================================================================================
// USART1_enter_DefaultMode_from_RESET
//================================================================================
extern void USART1_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	// [USART_InitPrsTrigger]$

}

//================================================================================
// LEUART0_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART0_enter_DefaultMode_from_RESET(void) {
	// $[LEUART0 initialization]
	// [LEUART0 initialization]$

}

//================================================================================
// VCMP_enter_DefaultMode_from_RESET
//================================================================================
extern void VCMP_enter_DefaultMode_from_RESET(void) {
	// $[VCMP_Init]
	// [VCMP_Init]$

}

//================================================================================
// WDOG_enter_DefaultMode_from_RESET
//================================================================================
extern void WDOG_enter_DefaultMode_from_RESET(void) {
	// $[CMU_ClockEnable]
	// [CMU_ClockEnable]$

	// $[CMU_OscillatorEnable]
	// [CMU_OscillatorEnable]$

	// $[WDOG_Init]
	// [WDOG_Init]$

}

//================================================================================
// I2C0_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C0_enter_DefaultMode_from_RESET(void) {
	// $[I2C0 initialization]
	// [I2C0 initialization]$

}

//================================================================================
// TIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER0_enter_DefaultMode_from_RESET(void) {
	// $[TIMER0 initialization]
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 1;
	init.debugRun = 0;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale2;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 1;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER0, &init);
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModeOff;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER0, 0, &initCC0);
	// [TIMER0 CC0 init]$

	// $[TIMER0 CC1 init]
	TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

	initCC1.prsInput = false;
	initCC1.prsSel = timerPRSSELCh0;
	initCC1.edge = timerEdgeRising;
	initCC1.mode = timerCCModeOff;
	initCC1.eventCtrl = timerEventEveryEdge;
	initCC1.filter = 0;
	initCC1.cofoa = timerOutputActionNone;
	initCC1.cufoa = timerOutputActionNone;
	initCC1.cmoa = timerOutputActionNone;
	initCC1.coist = 0;
	initCC1.outInvert = 0;
	TIMER_InitCC(TIMER0, 1, &initCC1);
	// [TIMER0 CC1 init]$

	// $[TIMER0 CC2 init]
	TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

	initCC2.prsInput = false;
	initCC2.prsSel = timerPRSSELCh0;
	initCC2.edge = timerEdgeRising;
	initCC2.mode = timerCCModeOff;
	initCC2.eventCtrl = timerEventEveryEdge;
	initCC2.filter = 0;
	initCC2.cofoa = timerOutputActionNone;
	initCC2.cufoa = timerOutputActionNone;
	initCC2.cmoa = timerOutputActionNone;
	initCC2.coist = 0;
	initCC2.outInvert = 0;
	TIMER_InitCC(TIMER0, 2, &initCC2);
	// [TIMER0 CC2 init]$

}

//================================================================================
// TIMER1_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER1_enter_DefaultMode_from_RESET(void) {
	// $[TIMER1 initialization]
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = 1;
	init.debugRun = 0;
	init.dmaClrAct = 0;
	init.sync = 0;
	init.clkSel = timerClkSelHFPerClk;
	init.prescale = timerPrescale256;
	init.fallAction = timerInputActionNone;
	init.riseAction = timerInputActionNone;
	init.mode = timerModeUp;
	init.quadModeX4 = 0;
	init.oneShot = 0;
	init.count2x = 0;
	init.ati = 0;
	TIMER_Init(TIMER1, &init);
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	TIMER_InitCC_TypeDef initCC0 = TIMER_INITCC_DEFAULT;

	initCC0.prsInput = false;
	initCC0.prsSel = timerPRSSELCh0;
	initCC0.edge = timerEdgeRising;
	initCC0.mode = timerCCModeOff;
	initCC0.eventCtrl = timerEventEveryEdge;
	initCC0.filter = 0;
	initCC0.cofoa = timerOutputActionNone;
	initCC0.cufoa = timerOutputActionNone;
	initCC0.cmoa = timerOutputActionNone;
	initCC0.coist = 0;
	initCC0.outInvert = 0;
	TIMER_InitCC(TIMER1, 0, &initCC0);
	// [TIMER1 CC0 init]$

	// $[TIMER1 CC1 init]
	TIMER_InitCC_TypeDef initCC1 = TIMER_INITCC_DEFAULT;

	initCC1.prsInput = false;
	initCC1.prsSel = timerPRSSELCh0;
	initCC1.edge = timerEdgeRising;
	initCC1.mode = timerCCModeOff;
	initCC1.eventCtrl = timerEventEveryEdge;
	initCC1.filter = 0;
	initCC1.cofoa = timerOutputActionNone;
	initCC1.cufoa = timerOutputActionNone;
	initCC1.cmoa = timerOutputActionNone;
	initCC1.coist = 0;
	initCC1.outInvert = 0;
	TIMER_InitCC(TIMER1, 1, &initCC1);
	// [TIMER1 CC1 init]$

	// $[TIMER1 CC2 init]
	TIMER_InitCC_TypeDef initCC2 = TIMER_INITCC_DEFAULT;

	initCC2.prsInput = false;
	initCC2.prsSel = timerPRSSELCh0;
	initCC2.edge = timerEdgeRising;
	initCC2.mode = timerCCModeOff;
	initCC2.eventCtrl = timerEventEveryEdge;
	initCC2.filter = 0;
	initCC2.cofoa = timerOutputActionNone;
	initCC2.cufoa = timerOutputActionNone;
	initCC2.cmoa = timerOutputActionNone;
	initCC2.coist = 0;
	initCC2.outInvert = 0;
	TIMER_InitCC(TIMER1, 2, &initCC2);
	// [TIMER1 CC2 init]$

}

//================================================================================
// PCNT0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT0_enter_DefaultMode_from_RESET(void) {
	// $[PCNT0 initialization]
	// [PCNT0 initialization]$

}

//================================================================================
// PRS_enter_DefaultMode_from_RESET
//================================================================================
extern void PRS_enter_DefaultMode_from_RESET(void) {
	// $[PRS initialization]
	// [PRS initialization]$

}

//================================================================================
// PORTIO_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTIO_enter_DefaultMode_from_RESET(void) {

	// $[Port A Configuration]

	/* Pin PA0 is configured to Input enabled with pull-down */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_INPUTPULL;
	// [Port A Configuration]$

	// $[Port B Configuration]

	/* Pin PB7 is configured to Push-pull with alt. drive strength */
	GPIO->P[1].DOUT |= (1 << 7);
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULLDRIVE;

	/* Pin PB8 is configured to Push-pull with alt. drive strength */
	GPIO->P[1].DOUT |= (1 << 8);
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE8_MASK)
			| GPIO_P_MODEH_MODE8_PUSHPULLDRIVE;

	/* Pin PB11 is configured to Push-pull with alt. drive strength */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE11_MASK)
			| GPIO_P_MODEH_MODE11_PUSHPULLDRIVE;
	// [Port B Configuration]$

	// $[Port C Configuration]

	/* Pin PC0 is configured to Push-pull with alt. drive strength */
	GPIO->P[2].DOUT |= (1 << 0);
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULLDRIVE;

	/* Pin PC1 is configured to Push-pull with alt. drive strength */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULLDRIVE;

	/* Pin PC14 is configured to Push-pull with alt. drive strength */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_PUSHPULLDRIVE;

	/* Pin PC15 is configured to Push-pull with alt. drive strength */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE15_MASK)
			| GPIO_P_MODEH_MODE15_PUSHPULLDRIVE;
	// [Port C Configuration]$

	// $[Port D Configuration]

	/* Pin PD6 is configured to Push-pull with alt. drive strength */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE6_MASK)
			| GPIO_P_MODEL_MODE6_PUSHPULLDRIVE;

	/* Pin PD7 is configured to Push-pull with alt. drive strength */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULLDRIVE;
	// [Port D Configuration]$

	// $[Port E Configuration]

	/* Pin PE12 is configured to Push-pull with alt. drive strength */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE12_MASK)
			| GPIO_P_MODEH_MODE12_PUSHPULLDRIVE;

	/* Pin PE13 is configured to Input enabled with pull-down */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_INPUTPULL;
	// [Port E Configuration]$

	// $[Port F Configuration]

	/* Pin PF2 is configured to Push-pull with alt. drive strength */
	GPIO->P[5].MODEL = (GPIO->P[5].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULLDRIVE;
	// [Port F Configuration]$

	// $[Route Configuration]

	/* Module PCNT0 is configured to location 0 */
	PCNT0->ROUTE = (PCNT0->ROUTE & ~_PCNT_ROUTE_LOCATION_MASK)
			| PCNT_ROUTE_LOCATION_LOC0;
	// [Route Configuration]$

}
