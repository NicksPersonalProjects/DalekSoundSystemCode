/*
 * DFPlayerCommands.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Nick Maley
 */

#ifndef SRC_DFPLAYERCOMMANDS_H_
#define SRC_DFPLAYERCOMMANDS_H_

//All commands are made with reference to both of the following websites
//https://cahamo.delphidabbler.com/resources/dfplayer-mini
//https://picaxe.com/docs/spe033.pdf


#define PlaySong 0x0F //Use parameters to declare folder number and song number
#define SetEQ 0x07 //Use parameters to declare EQ
#define Reset 0x0C //Resets track to 01 and volume to 30
//0=Default, 1=Pop, 2=Rock, 3=Jazz, 4=Classic, 5=Base
#define PlaybackType 0x08 //Use parameters to declare Playback type, potentially useless
//0=Repeat, 1=Folder Repeat, 2=Single Repeat, 3=Random
//#define FolderSelect 0x0F //Use parameters to declare what folder to play from (recommended to only go to 10)
#define AutoPlay 0x11 //Use parameters to turn on or off
//0=Stop, 1=Start
#define Source 0x09 //Use parameters to declare what storage music is to be pulled from
//0=U, 1=Mini SD Card, 2=Aux, 3=Sleep/Off, 4=USB
#define SetVolume 0x06 //Use parameters to set volume between 0-30
#define PlayTrack 0x0D //Start Playing, no Params
#define PauseTrack 0x0E //Pause Track, no Params

#define FolderLoop 0x17 //Use parameters to define folder number

#define CheckVolume 0x43 //Queries device for current volume
#define CheckSongs 0x47 //Queries device for total number of songs on sd card
/*
#define Song3   0b10000000
#define Song2   0b01000000
#define Song1   0b00100000

#define Folder2 0b00010000
#define Folder1 0b00001000

#define Pause   0b00000001

#define Volume  0b00000010
*/
void UARTCommand(uint8_t Command, uint8_t Param1, uint8_t Param2);
void UARTCommandF(uint8_t Command, uint8_t Param1, uint8_t Param2);
void UARTCommandNoDelay(uint8_t Command, uint8_t Param1, uint8_t Param2);
void UARTSend (uint8_t data);
void MiniPlayerInit(void);

#endif /* SRC_DFPLAYERCOMMANDS_H_ */
