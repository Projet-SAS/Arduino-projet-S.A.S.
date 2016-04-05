#include "Arduino.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#include <SoftwareSerial.h>
//Xbee PIN
#define RXPIN 0
#define TXPIN 1
// Xbee Init
SoftwareSerial XBeeSerial =  SoftwareSerial(RXPIN, TXPIN);
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);// Pass our oneWire reference to Dallas Temperature. 

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;

//PIN CAPTEURS
int tmp1Pin = 10; //A10
int tmp2Pin = 11; //A11
int photoresPin = 12; //A7
int PIRPin = 40; //D30
int ds18b20Pin = 2; //PWM
  
void setup(void)
{
  Serial.begin(9600);
  Serial.println("load arduino");
  // Calibrate sensor for detect movement.
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){delay(1000);}
  Serial.print('\n');

  // Envois un message aux modules xbee
  XBeeSerial.begin(9600);
  // Start up the library
  Serial.println("[INFOS] Arduino 1 ok.");
  sensors.begin();
}

void loop(void)
{
    
  int movement = is_someone();
  float exTemp = externalTemperature();
  float inTempZ1 = internTemperatureZ1();
  float inTempZ2 = internTemperatureZ2();
  // 5/1023
  float tempMoy = (inTempZ1 + inTempZ2)/2;
  float lumZ1 = whatIsLuxZ1();
  //float lumZ2 = whatIsLux(2);


   Serial.print("Move:");Serial.print(movement);Serial.print('_');
   Serial.print("tempExt:");Serial.print(exTemp);Serial.print('_');
   Serial.print("tempM:");Serial.print(tempMoy);Serial.print('_');
   Serial.print("lumZ1:");Serial.print(lumZ1);Serial.print('\n');
  //XBeeSerial.println(lumZ1);
  /*----------------------------------------------------
   *                 XBEE COM
   ---------------------------------------------------*/

    //if (XBeeSerial.available()) {
      //Serial.println(XBeeSerial.read());
    //}
}

