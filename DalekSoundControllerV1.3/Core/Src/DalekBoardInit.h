/*
 * DalekBoardInit.h
 *
 *  Created on: Jun 19, 2025
 *      Author: nicho
 */


#ifndef SRC_DALEKBOARDINIT_H_
#define SRC_DALEKBOARDINIT_H_

//Duty Cycle Thresholds
#define ThemeThreshold        7 //Input 1
#define LightsThreshold       7 //Input 2
#define ExterminateThreshold  7 //Input 3
#define BlasterThreshold      7 //Input 4

#define RGBDimmer			  100 //percentage, max 100

#define MinPeriod 31500 //28400 //any PWM period reads less than this will be ignored
#define MaxRedundancyCheck 3 //number of times a PWM needs to read the same value before it is accepted

#define PrescalarValue 4
#define ARRValue 0xffff / (0 + 1)

typedef enum Flag {HIGH,LOW} Flag;

extern Flag DWThemeFlag, BlasterFlag, LightFlag, ExterminateFlag;
//extern Flag DWThemeFlag = LOW, BlasterFlag = LOW, LightFlag = LOW, ExterminateFlag = LOW;

void TimersInit(void);
void FlagChecker(void);
void RGBColor(uint16_t Red, uint16_t Green, uint16_t Blue);
void ColorChanger(uint16_t RedStart, uint16_t GreenStart, uint16_t BlueStart, uint16_t RedFinish, uint16_t GreenFinish, uint16_t BlueFinish, uint16_t Steps);
uint8_t SingleFlagCheck(uint32_t PosCycle, uint32_t Period, Flag PreviousFlag, uint8_t Threshold, uint8_t Checker);

#endif /* SRC_DALEKBOARDINIT_H_ */
