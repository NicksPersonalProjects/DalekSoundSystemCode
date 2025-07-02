# DalekSoundSystemCode
Versions of the code used in the DalekSoundSystemPCB, specifically programmed in the STM32CubeIDE V1.18 for a STM32F100RDT6B chip  

##Broad Function of Code  
This code is designed to serve a few major functions using a FSM format:  
- **DWTheme**: When the input from PWMInput1 goes high, this function commands the DFMiniPlayer to loop a folder that contains variations of the Doctor Who Theme until the input goes low  
- **Lights**: When the input from PWMInput2 goes high, this function makes the external lights of the Dalek fade in and fade out when the input is low
- **Exterminate**: When the input from PWMInput3 goes high, this function commands the DFMiniPlayer to play a sound clip of a Dalek saying "Exterminate!". This function will not run if the **DWTheme** function is in effect, nor will it run repeatedly if the input is held high
- **Blaster**: When the input from PWMInput4 goes high, this function commands the DFMiniPlayer to play a sound clip of the Dalek's blaster shooting and controls some RGB LEDs to mimic a real blaster firing and cooling down. This function will not run if the **DWTheme** function is in effect, nor will it run repeatedly if the input is held high
- **Volume**: Reads input of the built in potentiometer and sets the volume of the DFMiniPlayer
