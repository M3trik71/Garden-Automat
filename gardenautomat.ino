/*
*__________________________________________________________________________________________
* PinOut:
*
*						       = D13			D12    =
*						       = 3v3			D11    =
*			       	     = REF			D10    =
*						       = A0 			D9     =
*						       = A1 			D8     =
*						       = A2 			D7     =
*     Lightsensor  = A3 			D6     =        
* 			 	   SDA	 = A4 			D5     =
*					   SCL	 = A5 			D4     =        								
*			 		         = A6 			D3     =	Buzzer						 		
*					   	     = A7 			D2     =	DHT11 Temperatur sensor and Homaditysensor
*					         = 5V 			GND    =
*					         = RST			RST    =
* 					       = GND			D1 RX  =
*					         = VIN			D0 TX  =
*__________________________________________________________________________________________
*
* Power Loading Signals:
* blue LED:  Full Battery
* rod LED:   in Charging Programm
*__________________________________________________________________________________________
*/


#include <Wire.h>
#include <Adafruit_INA219.h>


#include "DHT.h"
#define DHT_PIN 2                     // D3 connected to DHT11 sensor
#define DHT_TYPE DHT11

DHT dht11(DHT_PIN, DHT_TYPE);


// INA219 Voltage Sensor
Adafruit_INA219 ina219;
const float LOW_BATTERY_LIMIT = 3.3;  // Warning is under 3.3V

// Buzzer
const int buzzerPin = 3;              // D3 connected to Buzzer

// Lightsensor
const int lightSensorPin = A3;        // A3 connected to Lightsensor


// Frequenz for simple Tone (in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_C5  523

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
  delay(50); // short break after tone
}

/* Start */

void setup() {
  Serial.begin(9600);
  dht11.begin(); // initialize the sensor
  pinMode(buzzerPin, OUTPUT);
  ina219.begin();

  // Startmelodie
  playTone(NOTE_C4, 200);
  playTone(NOTE_D4, 200);
  playTone(NOTE_E4, 200);
  playTone(NOTE_C5, 300);
  playTone(NOTE_G4, 400);

  if (!ina219.begin()) {
    Serial.println("INA219 nicht gefunden. Check Verkabelung!");
    while (1); // Stop the programm
  }

}


/* Mainprogramm */

void loop() {
  // wait a few seconds between measurements.
  delay(2000);

  int sensorValue = analogRead(lightSensorPin); // 0–1023
  float lightPercent = (1.0 - (sensorValue / 1023.0)) * 100.0;

  float humi  = dht11.readHumidity();                    // read humidity
  float temperature_C = dht11.readTemperature();         // read temperature as Celsius
  float temperature_F = dht11.readTemperature(true);     // read temperature as Fahrenheit

  float busVoltage = ina219.getBusVoltage_V();           // Batteryvoltage
  float current_mA = ina219.getCurrent_mA();             // Batterycurrent
  float power_mW   = ina219.getPower_mW();               // mW Area

  // Serial Monitor
  Serial.println("-----------------------");
  Serial.print("Batteryvoltage: "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Current: "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("-----------------------");
  Serial.print("Humidity: "); Serial.print(humi); Serial.println(" %");
  Serial.print("Temperature: "); Serial.print(temperature_C); Serial.println(" °C");
  Serial.println("-----------------------");
  Serial.print("Lightintensity: "); Serial.print(lightPercent, 1); Serial.println(" %");
  Serial.println("");
  delay(2000);

  // Warning if low voltage with Buzzer
  if (busVoltage < LOW_BATTERY_LIMIT) {
    Serial.println("⚠️ WARNING: Battery barealy empty!");
    Serial.println("");
  }


}
