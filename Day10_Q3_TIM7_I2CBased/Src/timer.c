/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Abhi
 */

#include "timer.h"
void TimerInit(uint32_t ms) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    // enable timer clock
    TIM7->PSC = TIM_PR - 1;
    // set number of clocks to count
   	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
    TIM7->ARR = cnt - 1;
    TIM7->CNT = 0; // begin counting from zero
    TIM7->DIER |= TIM_DIER_UIE; // enable timer interrupt
    NVIC_EnableIRQ(TIM7_IRQn);
    TIM7->CR1 |= TIM_CR1_CEN; // Start the timer
}

extern int count = 0;
//extern int count;
// implement timer ISR
void TIM7_IRQHandler(void) {
	static int flag = 0;
		// check if interrupt occurred
		if(TIM7->SR & TIM_SR_UIF) {
			// then clear (ack) the interrupt
			TIM7->SR &= ~TIM_SR_UIF;
			// toggle LED
			if(flag == 0) {
		count++;
				flag = 1;
			} else {
				flag = 0;
			}
		}
	}

