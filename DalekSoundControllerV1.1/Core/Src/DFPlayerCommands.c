/*
 * DFPlayerUSART.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Nick Maley
 */
#include "main.h"
#include "DFPlayerCommands.h"

void MiniPlayerInit(void){
	HAL_Delay(4500);
	//UARTCommand(Reset, 0, 0);
	//UARTCommand(0x3F, 0, 0);
	UARTCommand(Source, 0, 1);
	UARTCommand(SetEQ, 0, 0);
	//UARTCommand(PauseTrack, 0, 0);
	//UARTCommand(PlaybackType, 0, 2);
	//UARTCommand(SetVolume, 0, 15);
}

void UARTCommand(uint8_t Command, uint8_t Param1, uint8_t Param2){
	const uint8_t StartByte = 0x7e;
	const uint8_t Version = 0xff;
	const uint8_t Length = 0x06;
	const uint8_t Feedback = 0;
	uint16_t CheckSumTotal = 0;
	uint8_t CheckSum1 = 0;
	uint8_t CheckSum2 = 0;
	const uint8_t EndByte = 0xef;

	CheckSumTotal = 0 - (Version + Length + Command + Feedback + Param1 + Param2);
	CheckSum1 = CheckSumTotal >> 8;
	CheckSum2 = CheckSumTotal & 0x00ff;
	int FullCmd[10] = {StartByte, Version, Length, Command, Feedback, Param1, Param2, CheckSum1, CheckSum2, EndByte};
	for(int i = 0; i <= 9; i++){
		//dummy++;
		UARTSend(FullCmd[i]);
	}
	//HAL_Delay(5);
	HAL_Delay(300);
}

void UARTCommandF(uint8_t Command, uint8_t Param1, uint8_t Param2){
	const uint8_t StartByte = 0x7e;
	const uint8_t Version = 0xff;
	const uint8_t Length = 0x06;
	const uint8_t Feedback = 1;
	uint16_t CheckSumTotal = 0;
	uint8_t CheckSum1 = 0;
	uint8_t CheckSum2 = 0;
	const uint8_t EndByte = 0xef;

	CheckSumTotal = 0 - (Version + Length + Command + Feedback + Param1 + Param2);
	CheckSum1 = CheckSumTotal >> 8;
	CheckSum2 = CheckSumTotal & 0x00ff;
	int FullCmd[10] = {StartByte, Version, Length, Command, Feedback, Param1, Param2, CheckSum1, CheckSum2, EndByte};
	for(int i = 0; i <= 9; i++){
		//dummy++;
		UARTSend(FullCmd[i]);
	}
	//HAL_Delay(5);
	HAL_Delay(300);
}

void UARTSend (uint8_t data){
	while(!(UART4->SR & USART_SR_TXE));
	UART4->DR = data;
}

