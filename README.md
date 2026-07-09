# Garden-Automat

![Projektübersicht](3.jpg)

This project is a self-sufficient garden automation system based on an Arduino Nano. The device monitors important environmental parameters such as soil moisture, air humidity, temperature, and atmospheric pressure to provide detailed information about the garden’s conditions.

The system is powered by solar panels and operates autonomously using a 10,000 mAh 3.4 V battery, allowing long-term outdoor operation without external power sources. The collected sensor data can be used to optimize plant care and support efficient water management.

![Projektübersicht](2.png)

The project combines embedded programming, sensor technology, and renewable energy to create an intelligent and sustainable solution for automated garden monitoring.

-------------------------------------------------------------------------------------


PinOut:

						       = D13			D12    =
						       = 3v3			D11    =
			       	  = REF			D10    =
						       = A0 			D9     =
						       = A1 			D8     =
						       = A2 			D7     =
Lightsensor  = A3 			D6     =        
			 	   SDA	 = A4 			D5     =
					   SCL	 = A5 			D4     =        								
			 		       = A6 			D3     =	Buzzer						 		
					   	    = A7 			D2     =	DHT11 Temperatur sensor
					        = 5V 			GND    =
					        = RST			RST    =
 					       = GND			D1 RX  =
					        = VIN			D0 TX  =

-------------------------------------------------------------------------------------

* Power Loading Signals:
* blue LED:  Full Battery
* rod LED:   in Charging Programm
