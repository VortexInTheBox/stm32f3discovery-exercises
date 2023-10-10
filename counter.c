/*
8-bit counter with stm32f3discovery board LEDs
Given a 8-bit string we will use the following notation: LD6-LD8-LD10-LD9-LD7-LD5-LD3-LD4
*/

#include "stm32f303xc.h"

int main()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN; //Enable clock on A and E I/O Ports

	GPIOA->MODER &= ~GPIO_MODER_MODER0; //Sets the GPIOA Port 0 as Input
	GPIOE->MODER |= 0x55550000; //Sets the GPIOE Port 8,9,10,11,12,13,14,15 as Output
	while (1)
	{
		if ((GPIOA->IDR & 1) == 1) //Checks if the button is pressed
		{
			GPIOE->ODR += (1 << 8); //Adds 1 every the output registers
			while ((GPIOA->IDR & 1) == 1) {} // Doesn't count while the button is pressed
		}
	return 0;
}