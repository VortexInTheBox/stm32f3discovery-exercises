/*
Simple Blink program with the stm32f3discovery board LED.
It turns on the LD4 LED for 1s and turns it off for 1s repeadtly using the TIMER6
*/

#include <stm32f303xc.h>

int main(){
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	
	GPIOE->MODER |= GPIO_MODER_MODER8_0;
	
	TIM6->CR1 |= TIM_CR1_CEN; //Enables the counter
	TIM6->ARR = 8000; //The counter counts max to 8000
	TIM6->PSC = 1000; //Rescalse the 8Mhz clock in order to make the counter fit in the TIM6_CNT
	TIM6->CNT &= ~(0x00001111); //Sets the counter to 0
	
	short int flag = 0;
	
	while(1){
		if((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF && !flag){
			TIM6->SR &= ~TIM_SR_UIF; //Resets the flag raised by the counter
			GPIOE->ODR |= GPIO_ODR_8; //Turns on the led
			flag = 1;
		}
		if((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF && flag){
			TIM6->SR &= ~TIM_SR_UIF;
			GPIOE->ODR &= ~GPIO_ODR_8; //Turns off the led
			flag = 0;
		}
		
	}
	
	return 0;
}