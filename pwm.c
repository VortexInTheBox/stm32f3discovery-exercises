/*
PWM made using two timers.
TIM6 is the period T and TIM7 is the T_on of the PWM 
*/

#include <stm32f303xc.h>
#include <system_stm32f3xx.h>

int main(){
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN);

	GPIOE->MODER |= GPIO_MODER_MODER8_0;
	
	NVIC->ISER[1] |= (1<<22 | 1<<23); //Unmasking TIM6 and TIM7 ISRs
	
	TIM6->ARR = 65535;
	TIM6->PSC = 122;
	TIM6->DIER |= TIM_DIER_UIE;
	
	
	TIM7->ARR = 65535;
	TIM7->PSC = 30;
	TIM7->DIER |= TIM_DIER_UIE;
	
	
	TIM6->CNT &= ~(0x0000FFFF);
	TIM6->CR1 |= TIM_CR1_CEN;
	
	while(1);
	
	return 0;
}

void TIM6_DAC_IRQHandler(){
	TIM6->SR &= ~TIM_SR_UIF;
	GPIOE->ODR |= GPIO_ODR_8;
	
	TIM7->CNT &= ~(0x0000FFFF);
	TIM7->CR1 |= TIM_CR1_CEN; //Starts TIM7 counter only when TIM6 restarts
}

void TIM7_IRQHandler(){
	TIM7->SR &= ~TIM_SR_UIF;
	GPIOE->ODR &= ~GPIO_ODR_8;
}
