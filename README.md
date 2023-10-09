# LM35_Temperature_Sensor
The system has the following features:
1-if the temparature on the first sensor is greater than 30 c, the first motor is working
2-if the temparature on the second sensor is greater than 40 c, the second motor is working
The system is implemented using the following components:
- PIC18F4620 Microcontroller.
- (LM044L) Alphanumeric LCD display.
- Ac motor
-temperatur sensor lm35
There is Software Architecture Layers I Used:
Application
ECU ( Dc motor ‚LCD)
MCAL (GPIO-INTERRUPT-ADC)
