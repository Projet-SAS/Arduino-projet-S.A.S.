#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

int calibrationTime = 10;
int RXPIN 0
int TXPIN 1
int ONE_WIRE_BUS 2
int ds18b20Pin = 2; // interrupt 0
int tmpPin[] = { 10 , 11 } // analog in
int lumPin[] = { 12, 13, 14, 15 } // analog in
int movementPin[] = { 31, 33, 35 } // digital

//Xbee
SoftwareSerial XBeeSerial =  SoftwareSerial(RXPIN, TXPIN);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 

void setup(void)
{
	Serial.begin(9600);
	Serial.println("load arduino");
	Serial.println("temperature(3)\tphotocell(4)\tmouvement(3)");
	XBeeSerial.begin(9600);

	while (! Serial);
	Serial.println("[INFOS] Arduino 1 ok.");

	//the time we give the sensor to calibrate (10-60 secs according to the datasheet) PIR Sensor
	Serial.print("calibrating sensor ");
	for(int i = 0; i < calibrationTime; i++)
		{
			Serial.print('.');
			delay(1000);
		}
	Serial.print('\n');
	sensors.begin();
}

void loop(void)
{


	int movement_zone_1 = is_someone( movementPin[0] );
	int movement_zone_2 = is_someone( movementPin[0] );
	int movement_zone_3 = is_someone( movementPin[0] );
	float ds18_sensor = externalTemperature();
	float tmp_zone_1 = internTemperature(tmpPin[0]);
	float tmp_zone_2 = internTemperature(tmpPin[1]);
	float average_tmp = (tmp_zone_1 + tmp_zone_2)/2;
	int lum_z_1_s_1 = whatIsLux(lumPin[0]);
	int lum_z_1_s_2 = whatIsLux(lumPin[1]);
	int lum_z_2_s_1 = whatIsLux(lumPin[2]);
	int lum_z_2_s_2 = whatIsLux(lumPin[3]);


	Serial.print( tmp_zone_1 ); Serial.print( '\t' );
	Serial.print( tmp_zone_2 ); Serial.print( '\t' );
	Serial.print( ds18_sensor );Serial.print( '\t' );
	
	Serial.print( lum_z_1_s_1 ); Serial.print( '\t' );
	Serial.print( lum_z_1_s_2 ); Serial.print( '\t' );
	Serial.print( lum_z_2_s_1 ); Serial.print( '\t' );
	Serial.print( lum_z_2_s_2 ); Serial.print( '\t' );
	
	Serial.print( movement_zone_1 ); Serial.print( '\t' );
	Serial.print( movement_zone_2 ); Serial.print( '\t' );
	Serial.print( movement_zone_3 ); Serial.print( '\n' );

//	if ( movement_zone_1 && movement_zone_2 || movement_zone_1 && movement_zone_3 || movement_zone_2 && movement_zone_3 )
//	{
//		Serial.print( "i'm pretty sure there is someone" );
//	}
//
//	float lum_z_1 = ( lum_z_1_s_1 + lum_z_1_s_2 )/2;
//	float lum_z_2 = ( lum_z_2_s_1 + lum_z_2_s_2 )/2;
//	
//	if ( lum_z_1 < 500 )
//	{
//		Serial.print( "lights in zone 1 should be lighter" );
//	}
//
//	if ( lum_z_2 < 500 )
//	{
//		Serial.print( "lights in zone 2 should be lighter" );
//	}

	if (XBeeSerial.available() == TRUE )
	{
		/* code for getting var */
		// analogwrite ?
	}

	delay(3000);
}

