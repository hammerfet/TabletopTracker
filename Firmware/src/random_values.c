/*
 * random_values.c
 *
 *  Created on: Feb 24, 2016
 *      Author: hammerfet
 */
#include "em_device.h"
#include "em_chip.h"
#include "random_values.h"

uint32_t seed_variable = 123456789;

// 32 bit LCG random number gen C99/C11 implementation
uint32_t rand_lcg_32(uint32_t seed)
{
	seed = (1103515245 * seed + 12345) % 2147483648;
	return seed;
}

// Gets a random number between 0 and 10
uint8_t rand_0_10(void)
{
	seed_variable = rand_lcg_32(seed_variable);
	return seed_variable % 10;
}
