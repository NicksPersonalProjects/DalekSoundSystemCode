/*
 * DalekBoardInit.h
 *
 *  Created on: Jun 19, 2025
 *      Author: nicho
 */


#ifndef SRC_DALEKBOARDINIT_H_
#define SRC_DALEKBOARDINIT_H_
/*
 * Demo Board RC Reciever Specs
 * FRSky D8R-II Plus
 * Period: 18ms
 *
 * ====Left Stick====
 * 		 Theme
 * Channel 3 -> Input 1
 * 7% - 9% Up-Down
 *
 * ====Right Switches====
 * 		  Lights
 * Channel 5 -> Input 2
 * 			Up		Middle 	Down
 * Up		6.3%	7.3%	7.9%
 * Down		8.7%	9.3%	10.3%
 *
 * ====Left Knob====
 * 	  Exterminate
 * Channel 6 -> Input 3
 * 5.5% - 11.1%
 *   CW - CCW
 *
 * ====Left Switch====
 * 		 Blaster
 * Channel 7 -> Input 4
 * 6.3% - 10.7%
 *   Up - Down
 */

//Duty Cycle Thresholds
#define ThemeThreshold        8 //Input 1
#define LightsThreshold       8 //Input 2
#define ExterminateThreshold  8 //Input 3
#define BlasterThreshold      8 //Input 4

#define RGBDimmer			  100 //percentage, max 100

#define MinPeriod 21500 //28400 //any PWM period reads less than this will be ignored
#define MaxRedundancyCheck 3 //number of times a PWM needs to read the same value before it is accepted

#define PrescalarValue 4
#define ARRValue 0xffff / (0 + 1)

typedef enum Flag {HIGH,LOW} Flag;

extern Flag DWThemeFlag, BlasterFlag, LightFlag, ExterminateFlag;

void TimersInit(void);
void FlagChecker(void);
void RGBColor(uint16_t Red, uint16_t Green, uint16_t Blue);
void ColorChanger(uint16_t RedStart, uint16_t GreenStart, uint16_t BlueStart, uint16_t RedFinish, uint16_t GreenFinish, uint16_t BlueFinish, uint16_t Steps);
uint8_t SingleFlagCheck(uint32_t PosCycle, uint32_t Period, Flag PreviousFlag, uint8_t Threshold, uint8_t Checker);

#endif /* SRC_DALEKBOARDINIT_H_ */
