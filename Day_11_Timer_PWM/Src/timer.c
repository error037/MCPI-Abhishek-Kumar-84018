/*
 * timer.c
 *
 *  Created on: Apr 5, 2024
 *      Author: abhi
 */
#include "timer.h"


void TimerInit(void) {
    // Enable GPIO clock for port C.6
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    // Configure PC6 as alternate function mode
    GPIOC->MODER |= (2 << 6*2);
    // Set alternate function as Timer8 output (AF3)
    GPIOC->AFR[0] |= (3 << GPIO_AFRL_AFSEL6_Pos);

    // Enable Timer8 clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

    // Set prescaler value
    TIM8->PSC = (TIM_PSC-1);  // Prescaler value
    // Set ARR value to 100 for 10KHz PWM output freq
    TIM8->ARR = (100-1);
    // Set CCR value i.e. Duty Cycle (must be less than ARR value)
    TIM8->CCR1 = 1-1;

    // Configure Timer8 channels as output channel
    //TIM8->CCMR1 &= ~TIM_CCMR1_CC1S;	// default
    // Configure Timer8 channel polarity as active high
    //TIM8->CCER &= ~TIM_CCER_CC1P;		// default
    // Configure Timer8 for output compare mode
    TIM8->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // PWM Mode 1 => 110

    // Set the preload bit in CCMRx register
    TIM8->CCMR1 |= TIM_CCMR1_OC1PE;
    // Set the ARPE bit in the CR1 register.
    TIM8->CR1 |= TIM_CR1_ARPE;
    // Set the PWM edge align mode in the CR1 register.
    //TIM8->CR1 &= ~TIM_CR1_CMS;	// default

    // Configure Timer8 output OCx signal to output pin
    TIM8->CCER |= TIM_CCER_CC1E;

    // Enable Timer 8 Main output and Timer8 peripheral
    TIM8->BDTR |= TIM_BDTR_MOE;
    TIM8->CR1 |= TIM_CR1_CEN;
}

