#include <stm32f303xc.h>
#include <system_stm32f3xx.h>

int main(){
	RCC->APB2ENR |= (RCC_APB2ENR_SYSCFGEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIOEEN | RCC_AHBENR_GPIOAEN);

	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOE->MODER |= GPIO_MODER_MODER8_0;
	
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0; //Enables clock to EXTI mutiplexer
	EXTI->IMR |= EXTI_IMR_MR0; //Unmasks the corresponding interrupt request line
	EXTI->RTSR |= EXTI_RTSR_TR0; //Enables rising edge detection
	EXTI->FTSR |= EXTI_FTSR_TR0; //Enables falling edge detection
	NVIC->ISER[0] |= (1<<6); //Unmasks the EXTI0 ISR
	
	while(1){}
	return 0;
}

void EXTI0_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR0; //Clears the Pending Request register
	
	if((GPIOE->ODR & GPIO_ODR_8) == GPIO_ODR_8){
		GPIOE->ODR &= ~GPIO_ODR_8; //Turns on the LED
	}
	else{
		GPIOE->ODR |= GPIO_ODR_8; //Turns off the LED
	}
}