/*cd
8-bit counter with stm32f303vc board leds
Given a 8-bit string we will use the following notation: LD6-LD8-LD10-LD9-LD7-LD5-LD3-LD4
*/

#include "stm32f303xc.h"

int main(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
	
	GPIOA->MODER &= ~GPIO_MODER_MODER0 ;
	//GPIOE->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOE->MODER |= 0x55550000;
	while(1){
			if((GPIOA->IDR&1) == 1){
				GPIOE->ODR += (1<<8);
				while((GPIOA->IDR&1) == 1){}
			}
	}
	return 0;
}