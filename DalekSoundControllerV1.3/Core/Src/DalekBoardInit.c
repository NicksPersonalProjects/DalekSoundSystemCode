/*
 * DalekBoardInit.c
 *
 *  Created on: Jun 19, 2025
 *      Author: nicho
 */
#include "main.h"
#include "DalekBoardInit.h"

Flag DWThemeFlag = LOW, BlasterFlag = LOW, LightFlag = LOW, ExterminateFlag = LOW;

void TimersInit(void){

	//Timer 1 Channels 1&2 for PWM Input 1, Theme Control
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->DIER |= TIM_DIER_CC1IE | TIM_DIER_CC2IE;
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;


	//Timer 2 Channels 1&2 for PWM Input 4, Blaster Control
	TIM2->DIER |= TIM_DIER_CC1IE | TIM_DIER_CC2IE;
	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
	TIM2->CR1 |= TIM_CR1_CEN;

	//Timer 3 Channels 1&2 for PWM Input 2, Main Lights Control
	TIM3->DIER |= TIM_DIER_CC1IE | TIM_DIER_CC2IE;
	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
	TIM3->CR1 |= TIM_CR1_CEN;

	//Timer 4 Channels 1&2 for PWM Input 3, Exterminate Control
	TIM4->DIER |= TIM_DIER_CC1IE | TIM_DIER_CC2IE;
	TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
	TIM4->CR1 |= TIM_CR1_CEN;

	//Green LED Config, Timer 1, Channel 4
	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->ARR = ARRValue;
	TIM1->PSC = PrescalarValue;
	TIM1->CCR4 = 0;
	TIM1->CCER |= TIM_CCER_CC4E;

	//Red LED Config, Timer 2, Channel 4
	TIM2->ARR = ARRValue;
	TIM2->PSC = PrescalarValue;
	TIM2->CCR4 = 0;
	TIM2->CCER |= TIM_CCER_CC4E;

	//Blue LED Config, Timer 3, Channel 4
	TIM3->ARR = ARRValue;
	TIM3->PSC = PrescalarValue;
	TIM3->CCR4 = 0;
	TIM3->CCER |= TIM_CCER_CC4E;

	//Making Timer 4 Be in line with the other ones, otherwise weirdness ensues
	TIM4->ARR = ARRValue;
	TIM4->PSC = PrescalarValue;

	//Light Control Config, Timer 3, Channel 3
	TIM3->CCR3 = 0;
	TIM3->CCER |= TIM_CCER_CC3E;

	//ADC Config for Volume Control
	ADC1->CR2 |= ADC_CR2_ADON;
	HAL_Delay(30);
	ADC1->CR1 |= ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_CAL;
}

void FlagChecker(void){
	uint32_t PosCycle = 0, Period = 0;
	static uint8_t ThemeRedundancyCheck = 1, BlasterRedundancyCheck = 1, LightsRedundancyCheck = 1, ExterminateRedundancyCheck = 1;
	//Grabs current duty cycle of input 1 and compares to threshold for Theme, needs to happen 3 consecutive times before the flag changes
	while(TIM1->EGR & TIM_EGR_CC1G);
	Period = TIM1->CCR1;
	PosCycle = TIM1->CCR2;
	if(Period > MinPeriod){
		ThemeRedundancyCheck = SingleFlagCheck(PosCycle, Period, DWThemeFlag, ThemeThreshold, ThemeRedundancyCheck);
		if (ThemeRedundancyCheck == 0){
			if (DWThemeFlag == HIGH){
				DWThemeFlag = LOW;
			}
			else{
				DWThemeFlag = HIGH;
			}
		}
	}

	//Grabs current duty cycle of input 4 and compares to threshold for Blaster
	while(TIM2->EGR & TIM_EGR_CC1G);
	Period = TIM2->CCR1;
	PosCycle = TIM2->CCR2;
	if(Period > MinPeriod){
		BlasterRedundancyCheck = SingleFlagCheck(PosCycle, Period, BlasterFlag, BlasterThreshold, BlasterRedundancyCheck);
		if (BlasterRedundancyCheck == 0){
			if (BlasterFlag == HIGH){
				BlasterFlag = LOW;
			}
			else{
				BlasterFlag = HIGH;
			}
		}
	}

	//Grabs current duty cycle of input 2 and compares to threshold for Lights
	while(TIM3->EGR & TIM_EGR_CC1G);
	Period = TIM3->CCR1;
	PosCycle = TIM3->CCR2;
	if(Period > MinPeriod){
		LightsRedundancyCheck = SingleFlagCheck(PosCycle, Period, LightFlag, LightsThreshold, LightsRedundancyCheck);
		if (LightsRedundancyCheck == 0){
			if (LightFlag == HIGH){
				LightFlag = LOW;
			}
			else{
				LightFlag = HIGH;
			}
		}
	}

	/*
	if(Period > MinPeriod){
		if((PosCycle * 100 / Period) <= (LightsThreshold)){
			LightFlag = LOW;
		}
		else{
			LightFlag = HIGH;
		}
	}*/

	//Grabs current duty cycle of input 3 and compares to threshold for Exterminate
	while(TIM4->EGR & TIM_EGR_CC1G);
	Period = TIM4->CCR1;
	PosCycle = TIM4->CCR2;
	if(Period > MinPeriod){
		ExterminateRedundancyCheck = SingleFlagCheck(PosCycle, Period, ExterminateFlag, ExterminateThreshold, ExterminateRedundancyCheck);
		if (ExterminateRedundancyCheck == 0){
			if (ExterminateFlag == HIGH){
				ExterminateFlag = LOW;
			}
			else{
				ExterminateFlag = HIGH;
			}
		}
	}
	return;
}

void RGBColor(uint16_t Red, uint16_t Green, uint16_t Blue){
	uint32_t MaxTime = 0x4000;
	if (TIM1->CCR1 >= MaxTime){
		MaxTime = TIM1->CCR1;
	}
	Red = MaxTime / 256 * Red;
	Red = Red * RGBDimmer/100;
	Green = MaxTime / 256 * Green;
	Green = Green * RGBDimmer/100;
	Blue = MaxTime / 256 * Blue;
	Blue = Blue * RGBDimmer/100;
	TIM2->CCR4 = Red;
	TIM1->CCR4 = Green;
	TIM3->CCR4 = Blue;
	HAL_Delay(50);
}

void ColorChanger(uint16_t RedStart, uint16_t GreenStart, uint16_t BlueStart, uint16_t RedFinish, uint16_t GreenFinish, uint16_t BlueFinish, uint16_t Steps){

	for(int i = 0; i <= Steps; i++){
		RGBColor((i * (RedFinish - RedStart)/Steps + RedStart), (i * (GreenFinish - GreenStart)/Steps + GreenStart), (i * (BlueFinish - BlueStart)/Steps + BlueStart));
	}
}

uint8_t SingleFlagCheck(uint32_t PosCycle, uint32_t Period, Flag PreviousFlag, uint8_t Threshold, uint8_t Checker){
	Flag CurrentFlag;
	if((PosCycle * 100 / Period) <= (Threshold)){
		CurrentFlag = LOW;
	}
	else{
		CurrentFlag = HIGH;
	}

	if(PreviousFlag != CurrentFlag){
		if(Checker == MaxRedundancyCheck){
			return 0;
		}
		else{
			return Checker+1;
		}
	}
	else{
		return 1;
	}
}
