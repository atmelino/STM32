/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f1xx.h"

void gotoSleep(void);
void delayUs(int us);
int test = 0;
int ticks;

int main(void) {
	if (((PWR->CSR) & (PWR_CSR_SBF))) {

		//clear PWR wakeup flag
		PWR->CR |= PWR_CR_CWUF;
		PWR->CR |= PWR_CR_CSBF;
		printMsg("woke up from standby");
	} else {
		printMsg("woke up from power on");

	}
	while (1) {

		printMsg("going to sleep");
		gotoSleep();
		printMsg("fail");

	}
}

void gotoSleep(void) {
// enable the PWR control clock
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

// Set SLEEPDEEP bit of Cortex System Control Register
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	// Enable Standby mode
	PWR->CR |= PWR_CR_PDDS;

	//clear wake up flag
	PWR->CR |= PWR_CR_CWUF;

	// Request Wait for Interrupt
	__WFI();

}

void delayUs(int us) {
	ticks = us;
	while (ticks)
		;
}

