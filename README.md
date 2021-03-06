# TabletopTracker

Silabs EFM32 Zero Gecko based RGB LED device. It's a 1" round PCB with eight RGB LEDs and a CR2032 button cell. There are two small buttons to control the LEDs.

The token can be used as a counter/tracker for board games such as Descent 2nd edition, D&D, Imperial assault, etc.

The device uses a Microchip Boost regulator to run the microcontroller at 3.6V even when the battery is as low as 0.6V. The device cannot work with 4.2V lithium cells however as the switching regulator cannot buck, only boost.

The firmware currently has two modes which are activated by either holding a single button for 2 seconds (MODE 1) or both buttons for 2 seconds (MODE 2)

## MODE 1: 

health/fatigue counter. Red and Yellow LEDs count health or fatigue respectively (depending on if you go up from 0 or down from 0). After every 4th LED lights, a while LED lights to indicate 5.

for example, White White Red Red Red would mean 13 health
for example, White Yellow Yellow Yellow Yellow would mean 9 fatigue

## MODE 2:

Solid colours with effects. There are seven colours to cycle between using the buttons. Each colour has three modes, solid, twinkle pattern and swirling pattern. These can be found by cycling through all the 21 colour options

## Hardware:

Schematic and PCB have been designed in DipTrace, get the free version here: http://diptrace.com/download-diptrace/

### Major parts used:

Silicon Labs EFM32ZG108F32 microcontroller
Microchip MCP1624 boost regulator
Avago ASMB-MTB0-0A3A2 RGB LED


### More features to come!
